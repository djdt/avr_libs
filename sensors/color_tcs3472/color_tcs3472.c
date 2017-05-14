#include "avr_libs/sensors/color_tcs3472.h"
#include "avr_libs/utils/usi_twi.h"

#include <util/delay.h>

#define TCS3472_ADR 0x29

void set_read_address(uint8_t adr)
{
	adr = adr + 0x80 + 0x20;
	usi_twi_send_bytes(TCS3472_ADR, &adr, 1);
}

// Init into a wait state
uint8_t color_sensor_init()
{
	// Enable device
	uint8_t data[] = {0x00, 0x09};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);

	// Set the RGBC intergration time to 10 cycles (24ms)
	data[0] = 0x01;
	data[1] = 0xf6;
	usi_twi_send_bytes(TCS3472_ADR, data, 2);

	// Set wait time (24ms)
	data[0] = 0x03;
	usi_twi_send_bytes(TCS3472_ADR, data, 2);

	// Read the ID to confirm
	set_read_address(0x12);
	usi_twi_read_bytes(TCS3472_ADR, data, 1);

	return !(data[0] == 0x44 || data[0] == 0x4d);
}

void color_sensor_sleep()
{
	uint8_t data[] = {0x00, 0x08};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

void color_sensor_wake()
{
	uint8_t data[] = {0x00, 0x09};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

void color_sensor_read(
		uint16_t* clear, uint16_t* red, uint16_t* green, uint16_t* blue)
{
	// Enable the RGBC ADC
	uint8_t data_rgbc_enable[] = {0x00, 0x0b};
	uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	usi_twi_send_bytes(TCS3472_ADR, data_rgbc_enable, 2);
	_delay_ms(50);

	// Set address and read data
	set_read_address(0x14);
	usi_twi_read_bytes(TCS3472_ADR, data, 8);

	*clear = (data[1] << 8) | data[0];
	*red   = (data[3] << 8) | data[2];
	*green = (data[5] << 8) | data[4];
	*blue  = (data[7] << 8) | data[6];

	// Disable the RGBC ADC
	data_rgbc_enable[1] = 0x09;
	usi_twi_send_bytes(TCS3472_ADR, data_rgbc_enable, 2);
}

// Gain are 00:1x, 01:4x, 10:16x, 11:60x
void color_sensor_gain(uint8_t gain)
{
	uint8_t data[] = {0x0f, gain & 0x03};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

//TODO check that writing also auto increments address
void color_sensor_int_threshold(uint16_t low, uint16_t high)
{
	uint8_t data[] = {0x04,
		low  & 0x00ff, (low  >> 8) & 0x00ff,
		high & 0x00ff, (high >> 8) & 0x00ff};
	usi_twi_send_bytes(TCS3472_ADR, data, 5);
}
