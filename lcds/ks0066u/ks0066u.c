#include "avr_libs/lcds/ks0066u.h"

#include "avr_libs/utils/usi_twi.h"

#include <util/delay.h>
#include <stdio.h>

#define LCD_ADR 0x7e

#define RS      0x01
#define RW      0x02
#define EN      0x04
#define BL      0x08

void send_4_bits(uint8_t bits)
{
	usi_twi_send_bytes(LCD_ADR, &bits, 1);
	uint8_t enable = bits | EN;
	usi_twi_send_bytes(LCD_ADR, &enable, 1);
	_delay_us(1);
	usi_twi_send_bytes(LCD_ADR, &bits, 1);
	_delay_us(50);
}

void send_byte(uint8_t byte, uint8_t mask)
{
	uint8_t nib_high = byte & 0xf0;
	uint8_t nib_low  = (byte<<4) & 0xf0;

	send_4_bits(nib_high | mask);
	send_4_bits(nib_low  | mask);
}

void lcd_ram(uint8_t ram)
{
	send_byte(ram, RS | BL); //RS = 1
	_delay_us(50);
}

/* END INTERNAL */

void lcd_init()
{
	send_4_bits(LCD_CMD_FNC);
	_delay_us(100);
	lcd_cmd(LCD_CMD_FNC | 0x08);
	lcd_cmd(LCD_CMD_DSP | 0x04);
	lcd_cmd(LCD_CMD_CLR);
	_delay_ms(2);
}

void lcd_cmd(uint8_t cmd)
{
	send_byte(cmd, BL);
	_delay_us(50);
}

void lcd_cursor(uint8_t x, uint8_t y)
{
	if (y > 0) x += 0x40;
	lcd_cmd(LCD_CMD_ADR | x);
}

void lcd_printf(const char* format, ...)
{
	/* Generate string */
	char buffer[19]; // Standard write address
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args); // Skips overwrite of address
	va_end(args);

	/* Write string to LCD */
	char* b = buffer;
	while (*b != '\0') {
		lcd_ram(*b);
		b++;
	}
}
