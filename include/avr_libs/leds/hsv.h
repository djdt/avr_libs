#ifndef _AVR_LIBS_LED_HSV_H_
#define _AVR_LIBS_LED_HSV_H_

#include <stdint.h>
#include "avr_libs/leds/rgb.h"

typedef struct hsv {
	uint8_t h;
	uint8_t s;
	uint8_t v;
} hsv_t;

rgb_t hsv_to_rgb(hsv_t hsv);
// hsv_t rgb_to_hsv(rgb_t rgb);

#endif /* ifndef _AVR_LIBS_LED_HSV_H_ */

