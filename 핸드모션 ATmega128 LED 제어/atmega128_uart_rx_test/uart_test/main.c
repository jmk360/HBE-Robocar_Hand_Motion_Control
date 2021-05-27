/*
atmega128���� hostpc�� ������ �۽� �׽�Ʈ
*/
#define F_CPU 16000000UL // atmega128�� �ϵ���� ���� ���ļ� �ݿ�

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
/* Replace with your application code */
unsigned char rx_data;
DDRA = 0XFF;
PORTE = 0XFF;

UBRR0H = 103>>8;
UBRR0L = 103;
UCSR0A = 0X00;
UCSR0B = 0X18;
UCSR0C = 0X06;
rx_data = UDR0;

while (1)
{
while(!(UCSR0A & 0X80));
	rx_data = UDR0;
	if(rx_data == 'y'){
		PORTA |= (1<<7);
		_delay_ms(10);
		PORTA &= ~(1<<7);
	}
	else if(rx_data == 'b'){
		PORTA |= (1<<5);
		_delay_ms(10);
		PORTA &= ~(1<<5);
	}
	else if(rx_data == 'j'){
		PORTA |= (1<<3);
		_delay_ms(10);
		PORTA &= ~(1<<3);
	}
	else if(rx_data == 'g'){
		PORTA |= (1<<1);
		_delay_ms(10);
		PORTA &= ~(1<<1);
	}
}
return 0;
}