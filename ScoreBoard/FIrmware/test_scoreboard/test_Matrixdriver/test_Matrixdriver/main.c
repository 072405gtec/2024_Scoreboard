#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "matrix.h"

const uint64_t symbol[] PROGMEM = {
	0x1800183860663c00, /* ? */
	0x10387cfefeee4400, /* heart */
	0x060e0c0808281800, /* note */
	0x10307efe7e301000, /* right */
	0x1018fcfefc181000  /* left */
};

const uint8_t SEGMENT_PATTERNS[] = {
	0x7E, // 0
	0x0C, // 1
	0x5E, // 2
	0x5C, // 3
	0x3C, // 4
	0x6C, // 5
	0x6E, // 6
	0x0C, // 7
	0x7E, // 8
	0x6E, // 9
	//0x02  // ':' (콜론, 시각 구분용)
};

const uint64_t string[] PROGMEM = {
	//home
	0x007f7f08087f7f00,	//0
	0x7f7f3018307f7f00,	//1
	//guest
	0x00266745417f3e00,	//2
	0x00266f49497b3200	//3
};

volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;


uint64_t pgm_read_64( void *ptr )
{
	uint64_t result;
	memcpy_P( &result, ptr, sizeof(uint64_t) );
	return result;
}

int main(void)
{
	MAX7219_MatrixInit();
	MAX7219_MatrixUpdate();
	
	while (1)
	{
		
		MAX7219_MatrixSetRow64(0, pgm_read_64(&string[0]));
		MAX7219_MatrixSetRow64(1, pgm_read_64(&string[1]));
		MAX7219_MatrixSetRow64(2, pgm_read_64(&string[2]));
		MAX7219_MatrixSetRow64(3, pgm_read_64(&string[3]));
		MAX7219_MatrixUpdate();
		_delay_ms(4000);
		
		/*
		for(int i = 0; i < 16; i++)
		{
			MAX7219_MatrixRShift(1);
			MAX7219_MatrixUpdate();
			_delay_ms(100);
		}
		for(int i = 0; i < 16; i++)
		{
			MAX7219_MatrixLShift(1);
			MAX7219_MatrixUpdate();
			_delay_ms(100);
		}
		*/
	}
}
