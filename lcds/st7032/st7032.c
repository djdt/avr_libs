#include "avr_libs/lcds/st7032.h"

#include "avr_libs/utils/usi_twi.h"

#define LCD_ADR 0x3e

#define CTRL_CMD 0x00
#define CTRL_RAM 0x40

uint8_t lcd_init(void)
{
	uint8_t data[] = {
		0x00, 0x38, // cmd, function
		0x14, 0x70, // osc, contrast
		0x52, 0x6c, // power, follower
		0x0c, 0x01  // on, clear
	};
	usi_twi_send_bytes(LCD_ADR, data, 2);
	data[1] = 0x39;

	uint8_t success;
	success = usi_twi_send_bytes(LCD_ADR, data, 8);
	_delay_ms(1);

	return success;
}

void lcd_cmd(uint8_t cmd)
{
	uint8_t data[] = {CTRL_CMD, cmd};
	usi_twi_send_bytes(LCD_ADR, data, 2);
	_delay_ms(1);
}

void lcd_cursor(uint8_t x, uint8_t y)
{
	if (y > 0) x += 0x40;
	lcd_cmd(LCD_CMD_ADR + x);
}

void lcd_printf(const char* format, ...)
{
	// Generate string
	uint8_t buffer[18] = {CTRL_RAM}; // Standard write address
	va_list args;
	va_start(args, format);
	uint8_t len = vsprintf((char*)buffer + 1, format, args);
	va_end(args);

	// Send data
	usi_twi_send_bytes(LCD_ADR, buffer, len + 1);
	_delay_us(50);
}
