#ifndef OW_LIB_H
#define OW_LIB_H

//----------
#define OW_DELAY_A_US		6
#define OW_DELAY_B_US		64
#define OW_DELAY_C_US		60
#define OW_DELAY_D_US		10
#define OW_DELAY_E_US		9
#define OW_DELAY_F_US		55
#define OW_DELAY_G_US		0
#define OW_DELAY_H_US		480
#define OW_DELAY_I_US		70
#define OW_DELAY_J_US		410
//----------
#define OW_SEARCH_ROM		0xF0
#define OW_READ_ROM		0x33
#define OW_MATCH_ROM		0x55
#define OW_SKIP_ROM		0xCC
#define OW_ALARM_SEARCH		0xEC
//----------

#define OW_PORT		PORTB
#define OW_DDR			DDRB
#define OW_PIN			PINB
#define OW_P			PB2

#include <avr/io.h>

void ow_init();

void ow_reset();

uint8_t ow_detect_presence();

void ow_write(uint8_t data);

void ow_write0();

void ow_write1();

uint8_t ow_read();

#endif /* OW_LIB_H */
