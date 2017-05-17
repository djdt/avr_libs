#ifndef _AVR_LCD_KS0066U_H_
#define _AVR_LCD_KS0066U_H_

#include <stdint.h>

#define LCD_SHIFT_LEFT  0x00
#define LCD_SHIFT_RIGHT 0x04
#define LCD_DISP_LEFT   0x08
#define LCD_DISP_RIGHT  0x0c

#define LCD_CMD_ENT 0x00
#define LCD_CMD_CLR 0x01
#define LCD_CMD_DSP 0x08
#define LCD_CMD_SHF 0x10
#define LCD_CMD_FNC 0x20
#define LCD_CMD_ADR 0x80

#define LCD_CMD_DSP_ON  0x08
#define LCD_CMD_DSP_OFF 0x0c

void lcd_init(void);

void lcd_cmd(uint8_t cmd);

void lcd_cursor(uint8_t x, uint8_t y);

void lcd_printf(const char* format, ...);

#endif /* ifndef _AVR_LCD_KS0066U_H_ */
