#ifndef DS1820_H
#define DS1820_H

#define COUNT_PER_C 0x10

#include <stdlib.h>

char* temp_to_string(uint8_t data[9], char *buf)
{
	//truncate bit0
	uint8_t temp_read = data[0] >> 1;

	uint8_t COUNT_REMAIN = data[6];

	//sixteenth parts of temp reading, see datasheet
	uint16_t parts = COUNT_PER_C - COUNT_REMAIN - 4;
	parts = 100 / COUNT_PER_C * parts;

	if (0x00 == data[1])
		buf[0] = '+';
	else
		buf[0] = '-';

	itoa(temp_read, buf+1, 10);

	buf[3] = '.';

	if (parts < 10)
	{
		buf[4] = '0';
		itoa(parts, buf+5, 10);
	}
	else
	{
		itoa(parts, buf+4, 10);
	}

	buf[6] = '\0';

	return buf;
}


#endif /* DS1820_H */
