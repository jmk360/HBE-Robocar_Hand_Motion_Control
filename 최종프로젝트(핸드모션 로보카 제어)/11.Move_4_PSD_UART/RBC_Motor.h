#ifndef _RBC_MOTOR_
#define _RBC_MOTOR_

#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"

#define ONE_ROTATE	650 //���� 1ȸ���� ���� ���ڴ� ī���� Ƚ��

void Motor_mode(unsigned char mode); //���� ������ȯ �Լ�

void Timer1_init(); //phase PWM 2ms

void PWM_change(char OCR1x, unsigned int value);  // ���� �ӵ� ���� �Լ�

#endif
