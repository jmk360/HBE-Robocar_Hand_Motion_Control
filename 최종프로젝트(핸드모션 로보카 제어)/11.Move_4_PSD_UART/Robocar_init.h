#ifndef _ROBOCAR_INIT_
#define _ROBOCAR_INIT_

#include<avr/io.h>

// 모터 방향에 대한 매크로 상수 (PORTA의 0~3핀에 FRONT가 들어가면, 모터는 전진하게 된다.)
#define FORWARD	0x06	//전진
#define BACK	0x09	//후진
#define LEFT	0x02	//좌회전
#define RIGHT	0x04	//우회전
#define STOP    0x00	//정지
#define LEFT_U	0x0A	//좌측 유턴
#define RIGHT_U	0x05	//우측 유턴
#define B_RIGHT	0x08	//우측으로 후진 
#define B_LEFT	0x01	//좌측으로 후진 

void PORT_init();

#endif
