#include "avr_libs/sensors/color_tcs3472.h"
#include "avr_libs/utils/usi_twi.h"

#include <util/delay.h>

#define TCS3472_ADR 0x29

#define ADR(adr) (adr | 0x80 | 0x20)

#define TIME_MS(step) ((256 - step) * 2.4)

// Init into a wait state
uint8_t color_sensor_init(void)
{
	// Set the RGBC intergration time
	uint8_t data[] = {ADR(0x01), TCS3472_ATIME};
	if (usi_twi_send_bytes(TCS3472_ADR, data, 2))
		return 1;

	// Set wait time
	data[0] = ADR(0x03);
	data[1] = TCS3472_WTIME;
	usi_twi_send_bytes(TCS3472_ADR, data, 2);

	// Enable device
	data[0] = ADR(0x00);
	data[1] = 0x09;
	usi_twi_send_bytes(TCS3472_ADR, data, 2);

	// Read the ID to confirm
	data[0] = ADR(0x12);
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
	if (usi_twi_read_bytes(TCS3472_ADR, data, 1))
		return 2;

	if (data[0] == 0x44)
		return 0;
	else
		return data[0];
}

void color_sensor_sleep(void)
{
	uint8_t data[] = {ADR(0x00), 0x08};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

void color_sensor_wake(void)
{
	uint8_t data[] = {ADR(0x00), 0x09};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

void color_sensor_read(
		uint16_t* clear, uint16_t* red, uint16_t* green, uint16_t* blue)
{
	uint8_t rgbc_data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	// Enable the RGBC ADC
	uint8_t data[] = {ADR(0x00), 0x0b};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);

	// Wait an appropriate time
	_delay_ms(TIME_MS(TCS3472_WTIME) + TIME_MS(TCS3472_ATIME) + 2.4);

	// Set address and read data
	data[0] = ADR(0x14);
	usi_twi_send_bytes(TCS3472_ADR, data, 1);
	usi_twi_read_bytes(TCS3472_ADR, rgbc_data, 8);

	*clear = (rgbc_data[1] << 8) | rgbc_data[0];
	*red   = (rgbc_data[3] << 8) | rgbc_data[2];
	*green = (rgbc_data[5] << 8) | rgbc_data[4];
	*blue  = (rgbc_data[7] << 8) | rgbc_data[6];

	// Disable the RGBC ADC
	data[0] = ADR(0x00);
	data[1] = 0x09;
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

// Gain are 00:1x, 01:4x, 10:16x, 11:60x
void color_sensor_gain(uint8_t gain)
{
	uint8_t data[] = {ADR(0x0f), gain & 0x03};
	usi_twi_send_bytes(TCS3472_ADR, data, 2);
}

//TODO check that writing also auto increments address
void color_sensor_int_threshold(uint16_t low, uint16_t high)
{
	uint8_t data[] = {ADR(0x04),
		low  & 0x00ff, (low  >> 8) & 0x00ff,
		high & 0x00ff, (high >> 8) & 0x00ff};
	usi_twi_send_bytes(TCS3472_ADR, data, 5);
}
