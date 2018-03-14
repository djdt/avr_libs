#include "avr_libs/leds/hsv.h"

rgb_t hsv_to_rgb(hsv_t hsv)
{
	rgb_t rgb;
	if (hsv.s == 0) {
		rgb.r = hsv.v; rgb.g = hsv.v; rgb.b = hsv.v;
		return rgb;
	}

	uint8_t i = hsv.h / 43;
	uint8_t f = (hsv.h - (i * 43)) * 6;

	uint8_t p = (hsv.v * (255 - hsv.s)) >> 8;
	uint8_t q = (hsv.v * (255 - ((hsv.s * f) >> 8))) >> 8;
	uint8_t t = (hsv.v * (255 - ((hsv.s * (255 - f)) >> 8))) >> 8;

	switch (i) {
		case 0:
			rgb.r = hsv.v; rgb.g = t;     rgb.b = p;
			break;
		case 1:
			rgb.r = q;     rgb.g = hsv.v; rgb.b = p;
			break;
		case 2:
			rgb.r = p;     rgb.g = hsv.v; rgb.b = t;
			break;
		case 3:
			rgb.r = p;     rgb.g = q;     rgb.b = hsv.v;
			break;
		case 4:
			rgb.r = t;     rgb.g = p;     rgb.b = hsv.v;
			break;
		default:
			rgb.r = hsv.v; rgb.g = p;     rgb.b = q;
			break;
	}
	return rgb;
}
