#ifndef _AVR_LIBS_LED_RGB_LED_H_
#define _AVR_LIBS_LED_RGB_LED_H_

#include <stdint.h>

typedef struct hsv {
	uint16_t h;
	uint16_t s;
	uint16_t v;
} hsv_t;

typedef struct rgb {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_t;

rgb_t hsv_to_rgb(hsv_t hsv);

// APA102C LED

typedef struct rgb_led {
	uint8_t brightness;
	rgb_t color;
} rgb_led_t;

#endif /* ifndef _AVR_LIBS_LED_RGB_LED_H_ */
