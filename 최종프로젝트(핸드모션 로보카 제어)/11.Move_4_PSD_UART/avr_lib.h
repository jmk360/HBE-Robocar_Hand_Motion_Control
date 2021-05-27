#ifndef _AVR_LIB_
#define _AVR_LIB_

#include<avr/io.h>
#include<avr/interrupt.h>

typedef unsigned char u08;
typedef unsigned short u16;


typedef signed char s08;
typedef signed short s16;

//uart 속도 7372800hz
#define UART_9600	47
#define UART_57600	7
#define UART_115200	3

void init_UART1(u08 bps);   // 시리얼 함수 초기화


u08 RoboCAR_getch(void);

void RoboCAR_putch(unsigned char data);

void us_delay(unsigned short time_us);

void ms_delay(u16 time_ms);

#endif
