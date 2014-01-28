#include "lcd_lib.h"

static inline
void lcd_enable()
{
	LCD_CONTROL_PORT |= (1<<LCD_E);
	_delay_us(LCD_ENABLE_US);
	LCD_CONTROL_PORT &= ~(1<<LCD_E);
	return;
}

#ifdef LCD_4BIT

//4BIT mode specific code
//----------

//Sends the upper nibble of data
static
void lcd_nibble_out(uint8_t data)
{
	data = data & 0xF0;
	LCD_DB_PORT &= ~(0xF0>>(4-LCD_4BIT_OFFSET));
	LCD_DB_PORT |= (data>>(4-LCD_4BIT_OFFSET));
	lcd_enable();
}
static
void lcd_out(uint8_t data)
{
	//High nibble first
	lcd_nibble_out(data);
	lcd_nibble_out(data<<4);
	return;
}

void lcd_init()
{
	_delay_ms(LCD_BOOT_MS);

	LCD_DB_DDR |= (0x0F<<LCD_4BIT_OFFSET);
	LCD_DB_PORT &= ~(0x0F<<LCD_4BIT_OFFSET);

	LCD_CONTROL_DDR |= (1<<LCD_E) | (1<<LCD_RS);
	LCD_CONTROL_PORT &= ~(1<<LCD_E) & ~(1<<LCD_RS);

	LCD_DB_PORT |= LCD_FUNCTION_4BIT;

	lcd_command(LCD_FUNCTION_4BIT |
			LCD_FUNCTION_2LINE |
			LCD_FUNCTION_5X8);
	lcd_command(LCD_DISPLAY_ON);
	lcd_clear();
	return;
}

#endif

#ifdef LCD_8BIT

//8BIT mode specific code
//----------

static inline
void lcd_out(uint8_t data)
{
	LCD_DB_PORT = data;
	lcd_enable();
	return;
}

void lcd_init()
{
	_delay_ms(LCD_BOOT_MS);

	LCD_DB_DDR = 0xFF;
	LCD_DB_PORT = 0x00;

	LCD_CONTROL_DDR |= (1<<LCD_E) | (1<<LCD_RS);
	LCD_CONTROL_PORT &= ~(1<<LCD_E) & ~(1<<LCD_RS);

	lcd_command(LCD_FUNCTION_8BIT |
			LCD_FUNCTION_2LINE |
			LCD_FUNCTION_5X8);
	lcd_command(LCD_DISPLAY_ON);
	lcd_clear();
	return;
}

#endif

void lcd_command(uint8_t command)
{
	LCD_CONTROL_PORT &= ~(1<<LCD_RS);
	lcd_out(command);
	_delay_us(LCD_COMMAND_US);
	return;
}
void lcd_data(uint8_t data)
{
	LCD_CONTROL_PORT |= (1<<LCD_RS);
	lcd_out(data);
	_delay_us(LCD_DATA_US);
	return;
}

void lcd_string(char *data)
{
	while(*data != 0)
	{
		lcd_data(*data++);
	}
	return;
}

void lcd_move_cursor(uint8_t x, uint8_t y)
{
	uint8_t addr;

	#ifdef ONE_LINE_DISPLAY
		addr = LCD_DDRAM_LINE1 + x;
	#endif
	#ifdef TWO_LINE_DISPLAY
		if (y == 0)
			addr = LCD_DDRAM_LINE1 + x;
		else
			addr = LCD_DDRAM_LINE2 + x;
	#endif
	#ifdef FOUR_LINE_DISPLAY
		if (y == 1) addr = LCD_DDRAM_LINE1 + x;
		else if (y == 2) addr = LCD_DDRAM_LINE2 + x;
		else if (y == 3) addr = LCD_DDRAM_LINE3 + x;
		else if (y == 4) addr = LCD_DDRAM_LINE4 + x;
	#endif

	#ifndef ONE_LINE_DISPLAY
		#ifndef TWO_LINE_DISPLAY
			#ifndef FOUR_LINE_DISPLAY
				#error "Number of display lines undefined."
			#endif
		#endif
	#endif

	lcd_command(addr);
	return;
}

void lcd_clear()
{
	lcd_command(LCD_CLEAR_DISPLAY);
	_delay_ms(LCD_CLEAR_DISPLAY_MS);
	return;
}

#ifdef USES_CHAR_GENERATOR

void lcd_generate_char(uint8_t code, uint8_t *data)
{
	lcd_command(LCD_SET_CGRAM_ADDR | code<<3);

	for (uint8_t c = 0; c < 8; c++)
	{
		lcd_data(data[c]);
	}
	return;
}

#endif
