#include "avr_libs/leds/apa102c.h"

#include <util/delay.h>

#define APA102C_DELAY 1 // us

void rgb_led_init(apa102c_t* apa102c)
{
	// Set high
	*(apa102c->port) |= (1<<apa102c->clock_pin)|(1<<apa102c->data_pin);
	// Set as outputs
	*(apa102c->ddr)	|= (1<<apa102c->clock_pin)|(1<<apa102c->data_pin);
}

void rgb_led_send_byte(apa102c_t* apa102c, uint8_t byte)
{
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		*(apa102c->port) &= ~(1<<apa102c->clock_pin); // Pull low

		if (byte & 0x80) // msb
			*(apa102c->port) |=  (1<<apa102c->data_pin);
		else
			*(apa102c->port) &= ~(1<<apa102c->data_pin);

		_delay_us(APA102C_DELAY); // Clock low

		*(apa102c->port) |=  (1<<apa102c->clock_pin); // Pull high
		_delay_us(APA102C_DELAY); // Clock high

		byte = byte << 1;
	}
}

void rgb_led_set_leds(apa102c_t* apa102c, rgb_led_t* leds, uint8_t num_leds)
{
	uint8_t i;
	// Start frame
	for (i = 0; i < 4; ++i) {
		rgb_led_send_byte(apa102c, 0x00);
	}
	// Data
	for (i = 0; i < num_leds; ++i) {
		rgb_led_send_byte(apa102c, 0xe0 | (*leds).brightness);
		rgb_led_send_byte(apa102c, (*leds).red);
		rgb_led_send_byte(apa102c, (*leds).green);
		rgb_led_send_byte(apa102c, (*leds).blue);
	}
	// End frame
	for (i = 0; i < 4; ++i) {
		rgb_led_send_byte(apa102c, 0xff);
	}
}
