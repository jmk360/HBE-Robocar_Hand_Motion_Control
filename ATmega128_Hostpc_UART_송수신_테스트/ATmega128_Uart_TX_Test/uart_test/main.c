/*
atmega128에서 hostpc로 데이터 송신 테스트
*/
#define F_CPU 16000000UL // atmega128의 하드웨어 동작 주파수 반영

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void Puts_Dist(unsigned short data){
	while((UCSR0A & 0x20)==0x00); // 송신버퍼가 비워지면 while문 탈출
	UDR0=data; // 데이터 송신
	
	UCSR1A |= 0x20;         // 클리어 UDRE0
}

int main(void)
{
	/* Replace with your application code */
	DDRA = 0XFF;
	PORTE = 0XFF;
	
	UBRR0H = 103>>8; // 보레이트 : 9600bps 설정
	UBRR0L = 103;    // 보레이트 : 9600bps 설정
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	
	unsigned short n= 30;
	// 30, 31, 32 ... 39, 40, 30, 31 ... : 데이터를 1초 주기로 hostpc로 송신
	while (1)
	{
		Puts_Dist(n);
		n++;
		if(n == 41){
			n = 30;
		}
		_delay_ms(1000);
	}
	return 0;
}