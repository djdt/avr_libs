#ifndef _AVR_SENSOR_TCS3472_H_
#define _AVR_SENSOR_TCS3472_H_

#include <stdint.h>

// Inits device into wait state
uint8_t color_sensor_init(void);

void color_sensor_sleep(void);
void color_sensor_wake(void);

// Simultaneous read for all channels
void color_sensor_read(uint16_t* clear,
		uint16_t* red, uint16_t* green, uint16_t* blue);

// Gain are 00:1x, 01:4x, 10:16x, 11:60x
void color_sensor_gain(uint8_t gain);
// If clear channel crosses out of this range an interrupt is generated
void color_sensor_int_threshold(uint16_t low, uint16_t high);

#endif /* ifndef _AVR_SENSOR_TCS3472_H_ */
