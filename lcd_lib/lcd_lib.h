#ifndef LCD_LIB_H
#define LCD_LIB_H

//-- DELAY TIMES --
//---------
#define LCD_BOOT_MS				15
#define LCD_ENABLE_US			1
#define LCD_CLEAR_DISPLAY_MS	2
#define LCD_RETURN_HOME_MS		2
#define LCD_COMMAND_US			41
#define LCD_DATA_US				46
//---------

//-- COMMAND CODES --
//---------
#define LCD_CLEAR_DISPLAY		0x01
//---------
#define LCD_RETURN_HOME			0x02
//---------
#define LCD_ENTRY_MODE			0x04
#define LCD_ENTRY_LEFT			(0x02 | LCD_ENTRY_MODE)
#define LCD_ENTRY_RIGHT			(0x00 | LCD_ENTRY_MODE)
#define LCD_ENTRY_SHIFT			(0x01 | LCD_ENTRY_MODE)
#define LCD_ENTRY_NOSHIFT		(0x00 | LCD_ENTRY_MODE)
//---------
#define LCD_DISPLAY_CONTROL		0x08
#define LCD_DISPLAY_ON			(0x04 | LCD_DISPLAY_CONTROL)
#define LCD_DISPLAY_OFF			(0x00 | LCD_DISPLAY_CONTROL)
#define	LCD_CURSOR_ON			(0x02 | LCD_DISPLAY_CONTROL)
#define	LCD_CURSOR_OFF			(0x00 | LCD_DISPLAY_CONTROL)
#define LCD_BLINKING_ON			(0x01 | LCD_DISPLAY_CONTROL)
#define LCD_BLINKING_OFF		(0x00 | LCD_DISPLAY_CONTROL)
//---------
#define LCD_SHIFT				0x10
#define LCD_SHIFT_CURSOR		(0x00 | LCD_SHIFT)
#define LCD_SHIFT_DISPLAY		(0x08 | LCD_SHIFT)
#define LCD_SHIFT_LEFT			(0x00 | LCD_SHIFT)
#define LCD_SHIFT_RIGHT			(0x04 | LCD_SHIFT)
//---------
#define LCD_FUNCTION_SET		0x20
#define LCD_FUNCTION_8BIT		(0x10 | LCD_FUNCTION_SET)
#define LCD_FUNCTION_4BIT		(0x00 | LCD_FUNCTION_SET)
#define LCD_FUNCTION_1LINE		(0x00 | LCD_FUNCTION_SET)
#define LCD_FUNCTION_2LINE		(0x08 | LCD_FUNCTION_SET)
#define LCD_FUNCTION_5X8		(0x00 | LCD_FUNCTION_SET)
#define LCD_FUNCTION_5X10		(0x04 | LCD_FUNCTION_SET)
//---------
#define LCD_SET_CGRAM_ADDR		0x40
//---------
#define LCD_SET_DDRAM_ADDR		0x80
#define LCD_DDRAM_LINE1			(0x00 | LCD_SET_DDRAM_ADDR)
#define LCD_DDRAM_LINE2			(0x40 | LCD_SET_DDRAM_ADDR)
#define LCD_DDRAM_LINE3			(0x10 | LCD_SET_DDRAM_ADDR)
#define LCD_DDRAM_LINE4			(0x50 | LCD_SET_DDRAM_ADDR)
//---------


//-- CONFIG --
//---------
//#define ONE_LINE_DISPLAY
#define TWO_LINE_DISPLAY
//#define FOUR_LINE_DISPLAY
//---------
//#define LCD_4BIT
#define LCD_8BIT
//---------
#define USES_CHAR_GENERATOR
//---------

//-- PORT DEFINITIONS --
//---------
#define LCD_DB_PORT				PORTD
#define LCD_DB_DDR				DDRD

#define LCD_4BIT_OFFSET			4
//EXAMPLE: 2 means DB4 to DB7 are mapped to PIN2 - PIN5. So, 4 is the maximum.
//Unused in 8BIT mode. In 4BIT mode DB PORT May be same as CONTROL PORT 
//---------

#define LCD_CONTROL_PORT		PORTC
#define LCD_CONTROL_DDR			DDRC
#define LCD_E				PC4
#define LCD_RS				PC5
//---------

#include <avr/io.h>
#include <util/delay.h>

void lcd_init();

void lcd_command(uint8_t command);

void lcd_data(uint8_t data);

void lcd_string(char *data);

void lcd_move_cursor(uint8_t x, uint8_t y);

void lcd_clear();

void lcd_generate_char(uint8_t code, uint8_t *data);

#endif /* LCD_LIB_H */

