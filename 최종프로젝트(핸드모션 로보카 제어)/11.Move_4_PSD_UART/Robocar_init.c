#include"Robocar_init.h"

/****************************************************************
	로보카 초기화 함수	
	
	PA0 ~ 3	:	모터 방향 제어 
	PA4 ~ 7	:	엔코더 입력

	PB2	:	전방 LED
	PB3	:	후방 LED
	PB5	:	좌측 모터 Enable (PWM)
	PB6	:	우측 모터 Enable (PWM)

****************************************************************/
void PORT_init()
{
	
	DDRA =	0x0F; 
    PORTA =0x00; 

	DDRB = 0xff;   
    PORTB =	0x00; 
	  
}
