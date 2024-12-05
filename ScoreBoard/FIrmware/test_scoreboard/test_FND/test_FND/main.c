//main.c
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

//#include "matrix.h"
#include "MAX7219.h"

// 7세그먼트 숫자 패턴 (0-9, 10: ':' 표시)
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
};

// 시간 변수 (분, 초)
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;

// 시간 표시 함수
void MAX7219_DisplayTime(uint8_t index, uint8_t minutes, uint8_t seconds)
{
	if(index >= MAX7219_IC_NUM) return;

	// 분, 초의 각 자리를 표시 (분:초 형식)
	uint8_t time_digits[4] = { 0 };

	// 분의 10의 자리와 1의 자리를 나누어 저장
	time_digits[0] = minutes / 10;   // 분의 10의 자리
	time_digits[1] = minutes % 10;   // 분의 1의 자리
	time_digits[2] = seconds / 10;   // 초의 10의 자리
	time_digits[3] = seconds % 10;   // 초의 1의 자리

	// 첫 번째 자리: 분의 10의 자리
	//MAX7219_Digit(index, 0, SEGMENT_PATTERNS[time_digits[0]]);

	// 두 번째 자리: 분의 1의 자리
	//MAX7219_Digit(index, 1, SEGMENT_PATTERNS[time_digits[1]]);

	// 세 번째 자리: 초의 10의 자리
	//MAX7219_Digit(index, 2, SEGMENT_PATTERNS[time_digits[2]]);

	// 네 번째 자리: 초의 1의 자리
	MAX7219_Digit(index, 0, SEGMENT_PATTERNS[time_digits[3]]);
}

// 타이머 초기화 함수
void Timer_Init()
{
	// 타이머 1을 CTC (Clear Timer on Compare Match) 모드로 설정
	TCCR1B |= (1 << WGM12);  // CTC 모드
	// 프리스케일러 1024로 설정 (F_CPU = 16MHz -> 주파수 16MHz / 1024 = 15625Hz)
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	// 1초마다 인터럽트 발생
	OCR1A = 15624;  // (16MHz / 1024) - 1 = 15624
	
	// 타이머 인터럽트 허용
	TIMSK |= (1 << OCIE1A);
	
	// 전역 인터럽트 활성화
	sei();
}

// 타이머 인터럽트 서비스 루틴 (1초마다 호출)
ISR(TIMER1_COMPA_vect)
{
	// 초 증가
	seconds++;
	
	if (seconds >= 60) {
		seconds = 0;  // 초가 60초가 되면 0으로 리셋
		minutes++;    // 분 증가
		
		if (minutes >= 60) {
			minutes = 0;  // 분이 60분이 되면 다시 0으로 리셋
		}
	}
	
	// 시간을 7세그먼트 디스플레이에 출력
	MAX7219_DisplayTime(0, minutes, seconds);  // 0번 디스플레이에 시간을 표시
}

int main()
{
	// 타이머 초기화
	Timer_Init();
	
	// 7세그먼트 디스플레이 초기화 (필요시)
	MAX7219_Init();
	
	// 무한 루프
	while (1)
	{
		// 타이머 인터럽트가 1초마다 시간을 자동으로 업데이트
	}
	
	return 0;
}


