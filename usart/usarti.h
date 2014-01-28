#ifndef UARTI_H
#define UARTI_H

volatile uint8_t tx_running;
char *tx_data;

void uarti_tx_string(char *data);

#endif /* UARTI_H */

