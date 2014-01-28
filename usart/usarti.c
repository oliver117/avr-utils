#include <avr/io.h>
#include <avr/interrupt.h>

#include "usarti.h"

ISR(USART_UDRE_vect)
{
	if (*tx_data != 0)
		UDR = *tx_data++;
	else
	{
		UCSRB &= ~(1<<UDRIE);
		tx_running = 0;
	}
}

void uarti_tx_string(char *data)
{
    tx_data = data;
	tx_running = 1;
	UCSRB |= (1<<UDRIE);
	sei();

    return;
}