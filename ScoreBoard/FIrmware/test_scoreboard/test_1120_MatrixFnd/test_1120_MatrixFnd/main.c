//main.c
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "matrix.h"
#include "fnd.h"

const uint64_t symbol[] PROGMEM = {
	0x1800183860663c00, /* ? */
	0x10387cfefeee4400, /* heart */
	0x060e0c0808281800, /* note */
	0x10307efe7e301000, /* right */
	0x1018fcfefc181000  /* left */
};

const uint64_t string[] PROGMEM = {
	//home
	0x007f7f08087f7f00,	//0
	0x7f7f3018307f7f00,	//1
	//guest
	0x00266745417f3e00,	//2
	0x00266f49497b3200	//3
};

uint64_t pgm_read_64( void *ptr )
{
	uint64_t result;
	memcpy_P( &result, ptr, sizeof(uint64_t) );
	return result;
}

int main(void)
{
	MAX7219_MatrixInit();
	FND_Init();
	MAX7219_MatrixUpdate();
	
	uint8_t number = 0;
	
	while (1)
	{
		//=== 매트릭스 제어 ===
		/*
		MAX7219_MatrixSetRow64(0, pgm_read_64(&string[0]));
		MAX7219_MatrixSetRow64(1, pgm_read_64(&string[1]));
		MAX7219_MatrixSetRow64(2, pgm_read_64(&string[2]));
		MAX7219_MatrixSetRow64(3, pgm_read_64(&string[3]));
		MAX7219_MatrixUpdate();
		_delay_ms(2000);
		*/
		//=== FND 제어 ===
		for (uint8_t digit = 0; digit < 8; digit++)
		{
			FND_DisplayNumber(0, digit, number); // 첫 번째 FND에서 숫자 표시
			number = (number + 1) % 10;          // 숫자 증가 (0~9 순환)
			_delay_ms(500);
		}
		FND_Clear(0);  // 첫 번째 FND 클리어
		
		
	}
}
