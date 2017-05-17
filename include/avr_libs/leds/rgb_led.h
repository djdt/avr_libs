#ifndef _AVR_LIBS_LED_RGB_LED_H_
#define _AVR_LIBS_LED_RGB_LED_H_

#include <stdint.h>

#define RGB_LED_SET(port, ddr, clk, data) \
	RGB_LED_PORT     = port;                \
	RGB_LED_DDR      = ddr;                 \
	RGB_LED_PIN_CLK  = pin_clk;             \
	RGB_LED_PIN_DATA = pin_data;

typedef struct rgb_led {
	uint8_t brightness;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} rgb_led_t;

#endif /* ifndef _AVR_LIBS_LED_RGB_LED_H_ */
