#ifndef USART_H
#define USART_H

//----------
#define BAUD 9600
//----------

void usart_init(void);

void usart_enable_tx(void);

void usart_enable_rx(void);

void usart_tx_byte(uint8_t data);

void usart_tx_string(char *data);

uint8_t usart_rx_byte(void);

#endif /* USART_H */

