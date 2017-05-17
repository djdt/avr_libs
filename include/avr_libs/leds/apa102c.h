#ifndef _AVR_LIBS_LED_APA102C_H_
#define _AVR_LIBS_LED_APA102C_H_

#include <avr/io.h>

#include "avr_libs/leds/rgb_led.h"

typedef struct {
	uint8_t* ddr;
	uint8_t* port;
	uint8_t  clock_pin;
	uint8_t  data_pin;
} apa102c_t;

// Setup for pins.
void rgb_led_init(apa102c_t* apa102c);

// Only considers the 5 lsb of brightness.
void rgb_led_set_leds(apa102c_t* apa102c, rgb_led_t* leds, uint8_t num_leds);

#endif /* ifndef _AVR_LIBS_LED_APA102C_H_ */
