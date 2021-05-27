#include"RBC_Motor.h"

/*********************************************
	Timer1 Phase correct PWM 10bit 설정

	Phase correct PWM 10bit, 8 분주 모드로 사용하여,
	PWM 주파수 = 7.3728MHz/(2*8*0x3FF)
	PWM 주파수 = 450Hz, PWM 주기 = 2.222msec
	PWM의 주기는 2msec가 된다.
***********************************************/
void Timer1_init()
{

	TCCR1A |= 0xA3;  
    TCCR1B |= 0x02;  
    TCCR1C=0x00;  
    
    TCNT1=0x0000;  

    OCR1A=0x0000;
	OCR1B=0x0000;
}

/******************************************************************************************************
	속도 변경 함수
	첫번째 매개변수는 속도를 제어할 모터를 선택하는 값을 대입하고,
	두번쨰 매개변수는 속도값을 대입한다.
	
	속도값이란, PWM 의 듀티비를 결정하는 값인데,
	0x3FF 를 대입하면 듀티비는 (0x3FF / 0x3FF) x 100 = 100 % 이므로 최고 속도가 나오며, 
	0x100 을 대입하면, 듀티비는 (0x100 / 0x3FF) x 100 = 25 % 이므로 최고 속도의 1/4 속도가 나온다.
*****************************************************************************************************/

void PWM_change(char OCR1x, unsigned int value)
{
	switch(OCR1x)
	{
		case 'R':
			OCR1A=value;			
			break;
		
		case 'L':
			OCR1B=value;
			break;
		
		case 'A':			
			OCR1A=value;			
			OCR1B=value;
			break;
		default:
			break;

	}
	
}
