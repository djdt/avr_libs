#include "avr_libs/leds/apa102c.h"

#include <util/delay.h>

#define APA102C_DELAY 1 // us

void rgb_led_init(void)
{
	// Set high
	RGB_LED_PORT |= (1<<RGB_LED_PIN_CLK)|(1<<RGB_LED_PIN_DATA);
	// Set as outputs
	RGB_LED_DDR  |= (1<<RGB_LED_PIN_CLK)|(1<<RGB_LED_PIN_DATA);
}

void rgb_led_send_byte(apa102c_t* apa102c, uint8_t byte)
{
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		RGB_LED_PORT &= ~(1<<RGB_LED_PIN_CLK); // Pull low

		if (byte & 0x80) // msb
			RGB_LED_PORT |=  (1<<RGB_LED_PIN_DATA);
		else
			RGB_LED_PORT &= ~(1<<RGB_LED_PIN_DATA);

		_delay_us(APA102C_DELAY); // Clock low

		RGB_LED_PORT |=  (1<<RGB_LED_PIN_CLK); // Pull high
		_delay_us(APA102C_DELAY); // Clock high

		byte = byte << 1;
	}
}

void rgb_led_set_leds(rgb_led_t* leds, uint8_t num_leds)
{
	uint8_t i;
	// Start frame
	for (i = 0; i < 4; ++i) {
		rgb_led_send_byte(0x00);
	}
	// Data
	for (i = 0; i < num_leds; ++i) {
		rgb_led_send_byte(0xe0 | (*leds).brightness);
		rgb_led_send_byte((*leds).red);
		rgb_led_send_byte((*leds).green);
		rgb_led_send_byte((*leds).blue);
	}
	// End frame
	for (i = 0; i < 4; ++i) {
		rgb_led_send_byte(0xff);
	}
}
