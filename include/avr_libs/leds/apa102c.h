#ifndef _AVR_LIBS_LED_APA102C_H_
#define _AVR_LIBS_LED_APA102C_H_

#include <avr/io.h>

#include "avr_libs/leds/rgb_led.h"

// Setup for pins.
void rgb_led_init(void);

// Only considers the 5 lsb of brightness.
void rgb_led_set_leds(rgb_led_t* leds, uint8_t num_leds);

#endif /* ifndef _AVR_LIBS_LED_APA102C_H_ */
