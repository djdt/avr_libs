#include "avr_libs/utils/usi_twi.h"

uint8_t USISR_8BIT = // Clear flags and set to count 16 clocks
(1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(USIDC)|(0x0<<USICNT0);
uint8_t USISR_1BIT = // Clear flags and set to count 2 clocks
(1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(USIDC)|(0xe<<USICNT0);

void usi_twi_init(void)
{
	// Enable pullup on SDA/SCL, to set high as released state.
	PORT_USI |= (1<<PIN_USI_SDA);
	PORT_USI |= (1<<PIN_USI_SCL);
	// Set as outputs
	DDR_USI  |= (1<<PIN_USI_SCL);
	DDR_USI  |= (1<<PIN_USI_SDA);
	USIDR = 0xff;                                // Preload data.
	USICR = (0<<USISIE)|(0<<USIOIE)|             // Disable Interrupts.
		(1<<USIWM1)|(0<<USIWM0)|             // Set USI in Two-wire mode.
		(1<<USICS1)|(0<<USICS0)|(1<<USICLK)| // Software stobe clock
		(0<<USITC);
	// Clear flags and reset counter
	USISR = (1<<USISIF)|(1<<USIOIF)|(1<<USIPF)|(1<<USIDC)|
		(0x0<<USICNT0);
}

uint8_t usi_twi_transfer_byte(uint8_t byte)
{
	USISR = byte; // Set to byte
	byte = (0<<USISIE)|(0<<USIOIE)|             // Interrupts disabled.
		(1<<USIWM1)|(0<<USIWM0)|             // Set usi two wire.
		(1<<USICS1)|(0<<USICS0)|(1<<USICLK)| // Software strobe clock.
		(1<<USITC);                          // Toggle Clock Port.
	do {
		_delay_us(T2_DELAY);
		USICR = byte;                             // Tick
		while (!(PIN_USI & (1<<PIN_USI_SCL)));    // Wait for SCL to go high.
		_delay_us(T4_DELAY);
		USICR = byte;                             // Tick
	} while (!(USISR & (1<<USIOIF)));           // Check for transfer.

	_delay_us(T2_DELAY);
	byte  = USIDR;                              // Read out data.
	USIDR = 0xff;                               // Release SDA.
	DDR_USI |= (1<<PIN_USI_SDA);                // Enable SDA as output.

	return byte;
}

uint8_t usi_twi_transfer_start(uint8_t adr)
{
	// Release SCL and wait until high for start cond.
	PORT_USI |= (1<<PIN_USI_SCL);
	while (!(PIN_USI & (1<<PIN_USI_SCL)));
	_delay_us(T2_DELAY);

	// Generate start cond.
	PORT_USI &= ~(1<<PIN_USI_SDA);
	_delay_us(T4_DELAY);
	PORT_USI &= ~(1<<PIN_USI_SCL);
	PORT_USI |= (1<<PIN_USI_SDA);

	// Send address
	PORT_USI &= ~(1<<PIN_USI_SCL);
	USIDR = adr;
	usi_twi_transfer_byte(USISR_8BIT);
	// Check for acknowledge
	DDR_USI  &= ~(1<<PIN_USI_SDA); // Set as input
	if (usi_twi_transfer_byte(USISR_1BIT) & 0x01)
		return 1;

	return 0;
}

void usi_twi_transfer_stop(void)
{
	// Stop condition
	PORT_USI &= ~(1<<PIN_USI_SDA);         // Pull SDA low.
	PORT_USI |= (1<<PIN_USI_SCL);          // Release SCL.
	while (!(PIN_USI & (1<<PIN_USI_SCL))); // Wait for SCL to go high.
	_delay_us(T4_DELAY);
	PORT_USI |= (1<<PIN_USI_SDA);          // Release SDA.
	_delay_us(T2_DELAY);
}

uint8_t usi_twi_send_bytes(uint8_t adr, uint8_t* data, uint8_t data_len)
{
	// Start cond.
	if (usi_twi_transfer_start(adr))
		return 1;

	// Send the data.
	do {
		PORT_USI &= ~(1<<PIN_USI_SCL);
		USIDR = *(data++);
		usi_twi_transfer_byte(USISR_8BIT);
		// Check for acknowledge
		DDR_USI  &= ~(1<<PIN_USI_SDA); // Set as input
		if (usi_twi_transfer_byte(USISR_1BIT) & 0x01)
			return 1;
	} while (--data_len);

	// Stop cond.
	usi_twi_transfer_stop();
	return 0;
}

uint8_t usi_twi_read_bytes(uint8_t adr, uint8_t* data, uint8_t data_len)
{
	// Start cond.
	if (usi_twi_transfer_start(adr & 0x01))
		return 1;

	// Read data.
	do {
		DDR_USI &= ~(1<<PIN_USI_SDA); // Set as input
		*(data)++ = usi_twi_transfer_byte(USISR_8BIT);

		if (data_len == 1)
			USIDR = 0xff; // Load NACK
		else
			USIDR = 0x00; // Load ACK
		usi_twi_transfer_byte(USISR_1BIT); // Generate (N)ACK
	} while (--data_len);

	// Stop cond.
	usi_twi_transfer_stop();
	return 0;
}
