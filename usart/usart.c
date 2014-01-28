#include <avr/io.h>

#include "usart.h"

void usart_init(void)
{
	#include <util/setbaud.h>
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
	UCSRA |= (1<<U2X);
	#else
	UCSRA &= ~(1<<U2X);
	#endif
	return;
}

void usart_enable_tx(void)
{
	UCSRB |= (1<<TXEN);
	return;
}

void usart_enable_rx(void)
{
	UCSRB |= (1<<RXEN);
	return;
}

void usart_tx_byte(uint8_t data)
{
	while ( !(UCSRA & (1<<UDRE)) )
	{}
	UDR = data;

	return;
}

void usart_tx_string(char *data)
{
	while (*data != 0)
		uart_tx_byte(*data++);
	return;
}

uint8_t usart_rx_byte(void)
{
	uint8_t data;
	while ( !(UCSRA & (1<<RXC)) )
	{}
	data = UDR;
	return data;
}
