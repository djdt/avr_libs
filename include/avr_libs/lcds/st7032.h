#ifndef _AVR_LIBS_LCD_ST7032_H_
#define _AVR_LIBS_LCD_ST7032_H_

#include <stdio.h>

#define LCD_CMD_CLR 0x01
#define LCD_CMD_ENT 0x04
#define LCD_CMD_DSP 0x08
#define LCD_CMD_SHF 0x10
#define LCD_CMD_FNC 0x20
#define LCD_CMD_ADR 0x80

#define LCD_CMD_DSP_ON  0x08
#define LCD_CMD_DSP_OFF 0x0c

uint8_t lcd_init(void);

void lcd_cmd(uint8_t cmd);

void lcd_cursor(uint8_t x, uint8_t y);

void lcd_printf(const char* format, ...);

#endif /* ifndef _AVR_LIBS_LCD_ST7032_H_ */
