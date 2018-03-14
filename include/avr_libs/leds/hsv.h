#ifndef _AVR_LIBS_LED_HSV_H_
#define _AVR_LIBS_LED_HSV_H_

#include <stdint.h>
#include "avr_libs/leds/rgb.h"

typedef struct hsv {
	uint16_t h;
	uint16_t s;
	uint16_t v;
} hsv_t;

rgb_t hsv_to_rgb(hsv_t hsv);
// hsv_t rgb_to_hsv(rgb_t rgb);

#endif /* ifndef _AVR_LIBS_LED_HSV_H_ */

