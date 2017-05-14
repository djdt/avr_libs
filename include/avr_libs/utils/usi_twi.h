#ifndef _AVR_LIBS_USI_TWI_H_
#define _AVR_LIBS_USI_TWI_H_

#include <avr/io.h>
#include <util/delay.h>

#ifdef USI_TWI_FAST_MODE
	// TWI FAST mode timing limits. SCL = 100-400kHz
  #define T2_DELAY (((F_CPU / 1000) *1300) /250000) +1 // >1,3us
  #define T4_DELAY (((F_CPU / 1000) * 600) /250000) +1 // >0,6us
#else
	// TWI STANDARD mode timing limits. SCL <= 100kHz
  #define T2_DELAY (((F_CPU / 1000) *4700) /250000) +1 // >4,7us
  #define T4_DELAY (((F_CPU / 1000) *4000) /250000) +1 // >4,0us
#endif

// Device dependant defines
#if defined(__AVR_AT90Mega169__) || defined(__AVR_ATmega169PA__) || \
    defined(__AVR_AT90Mega165__) || defined(__AVR_ATmega165__) || \
    defined(__AVR_ATmega325__) || defined(__AVR_ATmega3250__) || \
    defined(__AVR_ATmega645__) || defined(__AVR_ATmega6450__) || \
    defined(__AVR_ATmega329__) || defined(__AVR_ATmega3290__) || \
    defined(__AVR_ATmega649__) || defined(__AVR_ATmega6490__)
    #define DDR_USI             DDRE
    #define PORT_USI            PORTE
    #define PIN_USI             PINE
    #define PORT_USI_SDA        PORTE5
    #define PORT_USI_SCL        PORTE4
    #define PIN_USI_SDA         PINE5
    #define PIN_USI_SCL         PINE4
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || \
    defined(__AVR_AT90Tiny26__) || defined(__AVR_ATtiny26__)
    #define DDR_USI             DDRB
    #define PORT_USI            PORTB
    #define PIN_USI             PINB
    #define PORT_USI_SDA        PORTB0
    #define PORT_USI_SCL        PORTB2
    #define PIN_USI_SDA         PINB0
    #define PIN_USI_SCL         PINB2
#elif defined(__AVR_AT90Tiny2313__) || defined(__AVR_ATtiny2313__)
	#define DDR_USI             DDRB
	#define PORT_USI            PORTB
	#define PIN_USI             PINB
	#define PORT_USI_SDA        PORTB5
	#define PORT_USI_SCL        PORTB7
	#define PIN_USI_SDA         PINB5
	#define PIN_USI_SCL         PINB7
#elif defined(__AVR_ATtiny24A__) || defined(__AVR_ATtiny44A__) \
	|| defined(__AVR_ATtiny84A__)
	#define DDR_USI             DDRA
	#define PORT_USI            PORTA
	#define PIN_USI             PINA
	#define PORT_USI_SDA        PORTA6
	#define PORT_USI_SCL        PORTA4
	#define PIN_USI_SDA         PINA6
	#define PIN_USI_SCL         PINA4
#endif

void usi_twi_init();

uint8_t usi_twi_send_bytes(uint8_t adr, uint8_t* data, uint8_t data_len);

uint8_t usi_twi_read_bytes(uint8_t adr, uint8_t* data, uint8_t data_len);

#endif /* ifndef _AVR_LIBS_USI_TWI_H_ */
