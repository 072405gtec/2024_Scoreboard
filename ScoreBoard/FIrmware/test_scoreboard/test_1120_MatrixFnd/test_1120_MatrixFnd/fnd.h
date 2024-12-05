//fnd.h
#ifndef FND_H_
#define FND_H_

#include <stdint.h>

void FND_Init(void);
void FND_DisplayNumber(uint8_t index, uint8_t digit, uint8_t number);
void FND_Clear(uint8_t index);
void FND_SetBrightness(uint8_t index, uint8_t level);

#endif
