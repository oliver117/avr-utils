#include "ow_lib.h"

#include <util/delay.h>
#include <avr/interrupt.h>

void ow_init()
{
	ONEWIRE_DDR &= ~(1<<ONEWIRE_P);
	ONEWIRE_PORT &= ~(1<<ONEWIRE_P);
}

void ow_reset()
{
	cli();

	ONEWIRE_DDR |= (1<<ONEWIRE_P);
	_delay_us(OW_DELAY_H_US);
	ONEWIRE_DDR &= ~(1<<ONEWIRE_P);
	_delay_us(OW_DELAY_I_US);
	_delay_us(OW_DELAY_J_US);

	sei();
}

uint8_t ow_detect_presence()
{
	uint8_t data = 0xFF;
	cli();

	ONEWIRE_DDR |= (1<<ONEWIRE_P);
	_delay_us(OW_DELAY_H_US);
	ONEWIRE_DDR &= ~(1<<ONEWIRE_P);
	_delay_us(OW_DELAY_I_US);
	if (ONEWIRE_PIN & (1<<ONEWIRE_P))
	{
		data = 0x00;
	}
	_delay_us(OW_DELAY_J_US);

	sei();
	return data;
}

void ow_write(uint8_t data)
{
	for (uint8_t c = 0; c < 8; c++)
	{
		if (data & 0x01)
			onewire_write1();
		else
			onewire_write0();

		data >>= 1;
	}
	return;
}

inline
void ow_write0()
{
	cli();

	ONEWIRE_DDR |= (1<<ONEWIRE_P);
	_delay_us(OW_DELAY_C_US);
	ONEWIRE_DDR &= ~(1<<ONEWIRE_P);
	_delay_us(OW_DELAY_D_US);

	sei();
}

inline
void ow_write1()
{
	cli();

	ONEWIRE_DDR |= (1<<ONEWIRE_P);
	_delay_us(OW_DELAY_A_US);
	ONEWIRE_DDR &= ~(1<<ONEWIRE_P);
	_delay_us(OW_DELAY_B_US);

	sei();
}

uint8_t ow_read()
{
	uint8_t data = 0x00;
	for (uint8_t c = 0; c < 8; c++)
	{
		data >>= 1;
		cli();

		ONEWIRE_DDR |= (1<<ONEWIRE_P);
		_delay_us(OW_DELAY_A_US);
		ONEWIRE_DDR &= ~(1<<ONEWIRE_P);
		_delay_us(OW_DELAY_E_US);
		if (ONEWIRE_PIN & (1<<ONEWIRE_P))
		{
			data |= 0x80;
		}
		_delay_us(OW_DELAY_F_US);

		sei();
	}
	return data;
}
