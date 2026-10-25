# STM32 开发环境快速上手：STM32CubeMX + Keil MDK

> **适用对象**：初次接触 STM32 的开发者
> **示例平台**：STM32G491VET6（G4V_MINI 开发板，LQFP100 封装，512KB Flash / 112KB SRAM）
> **配套文档**：[STM32G491VET6 目录说明](./README.md)

本文介绍如何使用 **STM32CubeMX** 生成工程、再用 **Keil MDK-ARM** 编译下载，并用 **STM32CubeProgrammer** 完成 SWD / DFU 烧录，带你跑通从“新建工程”到“点灯”的完整流程。文末附开源教程与官方文档链接。

---

## 目录

- [一、开发环境准备](#一开发环境准备)
- [二、STM32CubeMX 快速上手](#二stm32cubemx-快速上手)
- [三、Keil MDK 快速入门](#三keil-mdk-快速入门)
- [四、STM32CubeProgrammer 下载（SWD / DFU）](#四stm32cubeprogrammer-下载swd--dfu)
- [五、常见问题排查](#五常见问题排查)
- [六、参考资料（开源教程）](#六参考资料开源教程)

---

## 一、开发环境准备

### 1.1 需要安装的软件

| 软件 | 作用 | 下载地址 |
|------|------|----------|
| **STM32CubeMX** | 图形化配置引脚/时钟，一键生成初始化代码 | [ST 官网](https://www.st.com/en/development-tools/stm32cubemx.html) |
| **STM32CubeG4 固件包** | STM32G4 系列 HAL 库（CubeMX 可在线自动下载） | [ST 官网](https://www.st.com/en/embedded-software/stm32cubeg4.html) |
| **Keil MDK-ARM v5** | 编译、下载、在线调试 | [Keil 官网](https://www.keil.com/download/product/) |
| **Keil.STM32G4xx_DFP 器件包** | MDK 中 STM32G4 芯片支持包 | [Pack 列表](https://www.keil.com/dd2/pack/) |
| **ST-Link 驱动** | 让电脑识别 ST-Link 调试器 | [ST 官网](https://www.st.com/en/development-tools/stsw-link009.html) |
| **STM32CubeProgrammer** | 官方烧录工具，支持 SWD / DFU / UART 等下载方式 | [ST 官网](https://www.st.com/en/development-tools/stm32cubeprog.html) |
| 串口调试助手（可选） | 查看串口打印输出 | XCOM / SSCOM / MobaXterm 等 |

> 提示：Keil MDK 个人/教育用途可申请免费的 **Community 版本**；STM32CubeG4 固件包既可以在 CubeMX 内自动下载，也可以从 ST 官网手动下载后导入。

### 1.2 硬件连接

- 调试器：ST-Link/V2 或 ST-Link/V3
- 接线：`3V3`、`SWDIO`、`SWCLK`、`GND` 四根线，与开发板 SWD 排针一一对应

![SWD 接线](../assets/cubemx_keil/swd_wiring.png)

---

## 二、STM32CubeMX 快速上手

CubeMX 的完整流程共 6 步，如下图：

![CubeMX 流程](../assets/cubemx_keil/cubemx_workflow.png)

### 2.1 新建工程与选择芯片

1. 打开 STM32CubeMX，点击 **File → New Project**（或首页 **ACCESS TO MCU SELECTOR**）。
2. 在 **Part Number Search** 输入 `STM32G491VET6`，双击选中该型号，进入配置界面。

### 2.2 配置时钟

1. 在左侧 **System Core → RCC** 中，将 **HSE** 设置为 `Crystal/Ceramic Resonator`（G4V_MINI 板载 24MHz 晶振）。
2. 打开顶部 **Clock Configuration** 页，按以下参数配置（最高 170MHz）：

| 参数 | 取值 | 说明 |
|------|------|------|
| Input Frequency | 24 MHz | 板载 HSE 晶振 |
| PLL Source | HSE | PLL 时钟源 |
| PLLM | /6 | 24 ÷ 6 = 4 MHz |
| PLLN | ×85 | 4 × 85 = 340 MHz（VCO） |
| PLLR | /2 | 340 ÷ 2 = **170 MHz（SYSCLK）** |
| AHB Prescaler | /1 | HCLK = 170 MHz |
| APB1 Prescaler | /1 | PCLK1 = 170 MHz |
| APB2 Prescaler | /1 | PCLK2 = 170 MHz |

![时钟树](../assets/cubemx_keil/clock_tree.png)

### 2.3 配置外设（以 G4V_MINI 为例）

在左侧 **Pinout & Configuration** 页完成以下配置：

**① 调试口（务必配置，否则芯片可能无法再次下载）**

- **System Core → SYS → Debug** 选择 `Serial Wire`。

**② RGB LED（GPIO 输出）**

| 引脚 | 功能 | 配置 |
|------|------|------|
| PC0 | 红色 LED | GPIO_Output |
| PC1 | 绿色 LED | GPIO_Output |
| PC2 | 蓝色 LED | GPIO_Output |

- 依次右键每个引脚 → **Enter User Label**，分别命名 `LED_RED`、`LED_GREEN`、`LED_BLUE`（方便在代码中直接使用）。

**③ 串口 USART1（打印/调试）**

| 引脚 | 功能 | 配置 |
|------|------|------|
| PA9 | USART1_TX | USART1 → Mode: Asynchronous |
| PA10 | USART1_RX | 同上，115200-8-N-1 |

> 完整引脚定义见 [PinMap.md](./PinMap.md) 或 [README 引脚映射表](./README.md)。

### 2.4 工程设置

进入 **Project Manager** 页：

1. **Project** 选项卡：
   - Project Name：例如 `LED_Blink`
   - Project Location：选择存放路径（避免中文和空格）
   - Toolchain / IDE：选择 **MDK-ARM**，Min Version 选 `V5`
2. **Code Generator** 选项卡（推荐勾选）：
   - ✅ Generate peripheral initialization as a pair of `.c/.h` files per peripheral
   - ✅ Copy only the necessary library files

### 2.5 生成代码

点击右上角 **GENERATE CODE**，等待生成完成。生成的 Keil 工程位于：

```
<工程目录>\MDK-ARM\<工程名>.uvprojx
```

---

## 三、Keil MDK 快速入门

Keil 侧流程共 5 步，如下图：

![Keil 流程](../assets/cubemx_keil/keil_workflow.png)

### 3.1 安装器件包

1. 打开 Keil，点击工具栏 **Pack Installer**（或菜单 **Project → Manage → Pack Installer**）。
2. 搜索 `STM32G4`，安装 **Keil.STM32G4xx_DFP** 最新版本。

> 器件包缺失会直接导致编译报错或下载失败（见第四节常见问题）。

### 3.2 打开并编译工程

1. 双击 CubeMX 生成的 `<工程名>.uvprojx`。
2. 点击 **Build（F7）** 编译，确认输出：

```
0 Error(s), 0 Warning(s)
```

### 3.3 配置 ST-Link 下载

1. 点击 **Options for Target**（魔术棒图标）：
   - **Device** 选项卡：确认芯片为 `STM32G491VETx`。
   - **Target** 选项卡：勾选 **Use MicroLIB**（使用 `printf` 重定向时需要）。
   - **Output** 选项卡：勾选 **Create HEX File**（需要 .hex 时）。
   - **Debug** 选项卡：右侧选择 **ST-Link Debugger**。
2. 点击 **Settings**：
   - **Flash Download** 页勾选 **Reset and Run**（下载后自动复位运行）。
   - 确认 Programming Algorithm 中有 `STM32G4xx 512KB Flash` 对应的算法。
3. 按 [SWD 接线图](#12-硬件连接) 连接 ST-Link 与开发板。

### 3.4 下载与调试

| 操作 | 快捷键 | 说明 |
|------|--------|------|
| 编译 | F7 | Build，检查错误 |
| 下载 | F8 | Download，烧录到 Flash |
| 调试 | Ctrl+F5 | 进入在线调试 |
| 单步 | F11 / F10 | Step Into / Step Over |
| 复位运行 | — | Debug 工具栏 RST 按钮 |

> 提示：首次下载前，确认 ST-Link 驱动已安装、调试口已在 CubeMX 中配置为 `Serial Wire`。

### 3.5 常用工程设置（推荐）

| 设置项 | 位置 | 推荐值 |
|--------|------|--------|
| Use MicroLIB | Target 选项卡 | ✅（printf 重定向） |
| Create HEX File | Output 选项卡 | ✅ |
| Optimization | C/C++ 选项卡 | -O0 调试 / -O1 发布 |
| Compiler | C/C++ 选项卡 | AC6（新工程默认） |
| Reset and Run | Debug → Settings | ✅ |

---

## 四、STM32CubeProgrammer 下载（SWD / DFU）

**STM32CubeProgrammer** 是 ST 官方推出的全能烧录工具，支持 **SWD（ST-Link）**、**USB DFU**、UART Bootloader 等多种下载方式。它既可以用于常规烧录，也可以在生产量产和“芯片被锁死”的恢复场景中使用。

### 4.1 下载与安装

1. 从 [ST 官网](https://www.st.com/en/development-tools/stm32cubeprog.html) 下载 STM32CubeProgrammer 并安装。
2. 安装完成后打开，主界面顶部可选连接方式（ST-LINK / USB / UART）。

### 4.2 SWD 下载（ST-Link）

1. 按 [SWD 接线图](#12-硬件连接) 连接 ST-Link 与开发板（`3V3`、`SWDIO`、`SWCLK`、`GND`）。
2. 打开 STM32CubeProgrammer，右上角选择 **ST-LINK**，Port 选择 **SWD**，点击 **Connect**。
3. 连接成功后点击 **Open file**，选择编译生成的 `.hex` / `.bin` / `.elf` 文件。
4. 点击 **Download** 开始烧录；烧录完成后可点 **Verify** 校验。
5. 点击 **Disconnect**，按 RST 复位即可运行新程序。

> 提示：SWD 是日常开发最常用的方式，支持在线调试；Keil 里其实也是通过 ST-Link SWD 下载，两者二选一即可。

### 4.3 DFU 下载（USB，无需 ST-Link）

DFU 通过芯片内置的 **USB 系统 Bootloader** 下载，不需要 ST-Link，只需要一根 USB 线连接板载 TYPE-C（PA11/PA12）。适用于量产烧录、以及 SWD 被禁用时的“救砖”。

**进入 DFU（系统 Bootloader）**

本板 **BOOT0 按键按下为低电平**。进入方式二选一：

1. **上电进入**：按住 BOOT0 按键 → 给开发板上电；
2. **复位进入**：按住 BOOT0 按键 → 按一下 RST 复位键复位芯片（保持 BOOT0 按住）→ 芯片复位后即进入 Bootloader。

进入 Bootloader 后，电脑会枚举出 `STM32 BOOTLOADER` USB 设备（设备管理器中可见）。

![DFU 下载流程](../assets/cubemx_keil/cubeprogrammer_dfu.png)

**DFU 下载步骤**

1. 按上述方式进入系统 Bootloader。
2. 用 USB 线连接开发板 TYPE-C 接口与电脑。
3. 打开 STM32CubeProgrammer，连接方式选择 **USB**，点击 **Connect**，确认识别到 `STM32 BOOTLOADER`（DFU）。
4. 点击 **Open file** 选择要烧录的 `.hex` / `.bin` 文件。
5. 点击 **Download** 开始烧录。
6. 烧录完成后，**断开 USB 或按 RST 复位**（不再按住 BOOT0），芯片即从用户 Flash 正常运行。

> 对比：SWD 需调试器、可在线调试；DFU 仅需 USB 线、适合量产与恢复，但无法在线调试。

---

## 五、常见问题排查

| 现象 | 原因 | 解决办法 |
|------|------|----------|
| 下载报 `No target connected` | 未接好线 / 驱动未装 / 调试口被禁 | 检查 SWD 接线与驱动；确认 CubeMX 中 SYS Debug 选 `Serial Wire` |
| 下载报 `No Algorithm found` | 未安装器件包 / 缺少 Flash 算法 | 安装 `Keil.STM32G4xx_DFP`；在 Flash Download 页添加 Programming Algorithm |
| 下载报 `Flash Download failed - Cortex-M4` | 调试口被复用导致芯片“锁死” | 按住复位键点下载，松开复位；或用 STM32CubeProgrammer 经 [DFU 恢复](#43-dfu-下载usb无需-st-link) |
| 编译报 `Error: L6218E` / 未定义 | HAL 库文件缺失或路径错误 | 确认固件包已下载；检查 Include 路径 |
| `printf` 不输出 | 未重定向 / 未勾 MicroLIB | 勾选 Use MicroLIB，并重写 `fputc` 到 USART |
| 程序跑飞 / 时钟不对 | HSE/PLL 配置错误 | 对照 2.2 节重新检查时钟配置 |

---

## 六、参考资料（开源教程）

**官方文档（推荐优先阅读）**

- STM32CubeMX 官方用户手册 UM1718：[Configuration and initialization C code generation](https://www.st.com/resource/en/user_manual/dm00104712-stm32cubemx-for-stm32-configuration-and-initialization-c-code-generation-stmicroelectronics.pdf)
- Keil MDK 官方文档：[µVision User's Guide](https://www.keil.com/support/man/docs/uv4/)
- STM32CubeG4 固件包与例程：[STM32CubeG4](https://www.st.com/en/embedded-software/stm32cubeg4.html)

**开源 / 社区教程**

- 正点原子（ALIENTEK）STM32 教程：[openedv 官方论坛](http://www.openedv.com/)
- 野火（EmbedFire）STM32 教程：[野火教程文档](https://doc.embedfire.com/)
- 立创开源硬件平台（硬件工程参考）：[oshwhub](https://oshwhub.com/)
- CSDN / 知乎 / B 站：搜索关键词 `STM32CubeMX 入门`、`Keil MDK 新建工程` 可获取大量图文与视频教程。

> 说明：以上社区链接用于资料索引与学习参考，请以各站点最新发布内容为准。
