#ifndef _RBC_MOTOR_
#define _RBC_MOTOR_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"

#define ONE_ROTATE	650 //모터 1회전에 대한 엔코더 카운터 횟수

void Motor_mode(unsigned char mode); //모터 방향전환 함수

void Timer1_init(); //phase PWM 2ms

void PWM_change(char OCR1x, unsigned int value);  // 모터 속도 제어 함수

#endif
