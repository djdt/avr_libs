#include "avr_libs/leds/apa102c.h"

#include <util/delay.h>

#define APA102C_DELAY 0.5 // us

void rgb_led_init(void)
{
	// Set high
	APA102C_PORT |= (1<<APA102C_PIN_CLK)|(1<<APA102C_PIN_DATA);
	// Set as outputs
	APA102C_DDR	|= (1<<APA102C_PIN_CLK)|(1<<APA102C_PIN_DATA);
}

void rgb_led_send_byte(uint8_t byte)
{
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		APA102C_PORT &= ~(1<<APA102C_PIN_CLK); // Pull low

		if (byte & 0x80) // msb
			APA102C_PORT |=  (1<<APA102C_PIN_DATA);
		else
			APA102C_PORT &= ~(1<<APA102C_PIN_DATA);

		_delay_us(APA102C_DELAY); // Clock low

		APA102C_PORT |=  (1<<APA102C_PIN_CLK); // Pull high
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
		++leds;
	}
	// End frame (unneeded?)
	for (i = 0; i < (num_leds + 1) / 2; ++i) {
		rgb_led_send_byte(0xff);
	}
}
