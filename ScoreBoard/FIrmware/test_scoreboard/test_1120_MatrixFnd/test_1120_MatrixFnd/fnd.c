// fnd.c
#include "fnd.h"
#include "MAX7219.h"

void FND_Init(void)
{
	MAX7219_Init();
	for (uint8_t i = 0; i < MAX7219_IC_NUM; i++)
	{
		MAX7219_ShutDown(i, 1);      // Turn on the MAX7219
		MAX7219_Test(i, 0);          // Disable test mode
		MAX7219_Decode(i, 0xFF);     // Enable BCD decoding for all digits
		MAX7219_ScanLimit(i, 7);     // Use all 8 digits
		MAX7219_Intensity(i, 1);     // Set default brightness
		FND_Clear(i);                // Clear display
	}
}

void FND_DisplayNumber(uint8_t index, uint8_t digit, uint8_t number)
{
	if (digit > 7 || number > 9) return; // Validate digit and number range
	MAX7219_Digit(index, digit, number);
}

void FND_Clear(uint8_t index)
{
	for (uint8_t digit = 0; digit < 8; digit++)
	{
		MAX7219_Digit(index, digit, 0xF); // Turn off all digits
	}
}

void FND_SetBrightness(uint8_t index, uint8_t level)
{
	if (level > 15) level = 15; // Brightness range: 0 (dim) to 15 (brightest)
	MAX7219_Intensity(index, level);
}
