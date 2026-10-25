#include "main.h"
#include "lcd.h"
#include "lcd_port.h"

/************ Hardware Port ************/
void lcd_delay(uint32_t delay)
{
    HAL_Delay(delay);
}

static void lcd_io_ctrl(gpio_io* io, bool flag)
{
    if(io && io->port)
        HAL_GPIO_WritePin(io->port, io->pin, flag ^ io->invert);
}

static void lcd_spi_transmit(lcd_io* lcdio, uint8_t* data, uint32_t len)
{
    SPI_HandleTypeDef* spi = (SPI_HandleTypeDef*)lcdio->spi;

    if (!spi) {
        return;
    }

    lcd_io_cs(lcdio, 0);
    while(spi && len) {
        uint16_t tx_len = (len > 0xFFFFu) ? 0xFFFFu : (uint16_t)len;
        HAL_SPI_Transmit(spi, data, tx_len, 0xFFFF);
        data += tx_len;
        len -= tx_len;
    }

    lcd_io_cs(lcdio, 1);
}

// 下面移动到core里面？
/************ GPIO ************/
void lcd_io_rst(lcd_io* lcdio, bool flag)
{
    lcd_io_ctrl(&lcdio->rst, flag);
}

void lcd_io_bl(lcd_io* lcdio, bool flag)
{
    lcd_io_ctrl(&lcdio->bl, flag);
}

void lcd_io_cs(lcd_io* lcdio, bool flag)
{
    lcd_io_ctrl(&lcdio->cs, flag);
}

void lcd_io_dc(lcd_io* lcdio, bool flag)
{
    lcd_io_ctrl(&lcdio->dc, flag);
}

/************ SPI ************/
void lcd_write_byte(lcd_io* lcdio, uint8_t data)
{
    lcd_io_dc(lcdio, 1);
    lcd_spi_transmit(lcdio, &data, 0x01);
}

void lcd_write_halfword(lcd_io* lcdio, uint16_t data)
{
    lcd_io_dc(lcdio, 1);
    /* note: 使用HAL库一次发送两个字节顺序与屏幕定义顺序相反 */
    data = (data << 8) | (data >> 8);
    lcd_spi_transmit(lcdio, (uint8_t *)&data, 0x02);
}

void lcd_write_bulk(lcd_io* lcdio, uint8_t* data, uint32_t len)
{
    lcd_io_dc(lcdio, 1);
    lcd_spi_transmit(lcdio, (uint8_t *)data, len);
}

void lcd_write_reg(lcd_io* lcdio, uint8_t data)	 
{	
    lcd_io_dc(lcdio, 0);
    lcd_spi_transmit(lcdio, &data, 0x01);
}