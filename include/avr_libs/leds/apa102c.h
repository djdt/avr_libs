#ifndef _AVR_LIBS_LED_APA102C_H_
#define _AVR_LIBS_LED_APA102C_H_

#include <avr/io.h>

/* User must define their own config file.
 * Minimum example:

 * #define APA102C_PORT     PORTB
 * #define APA102C_DDR      DDRB
 * #define APA102C_PIN_CLK  0
 * #define APA102C_PIN_DATA 1
*/

#include "apa102c.config.h"
#include "avr_libs/leds/rgb_led.h"

// Setup for pins.
void rgb_led_init(void);

// Only considers the 5 lsb of brightness.
void rgb_led_set_leds(rgb_led_t* leds, uint8_t num_leds);

#endif /* ifndef _AVR_LIBS_LED_APA102C_H_ */
