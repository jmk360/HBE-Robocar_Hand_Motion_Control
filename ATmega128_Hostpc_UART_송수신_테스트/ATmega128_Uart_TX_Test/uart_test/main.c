/*
atmega128���� hostpc�� ������ �۽� �׽�Ʈ
*/
#define F_CPU 16000000UL // atmega128�� �ϵ���� ���� ���ļ� �ݿ�

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void Puts_Dist(unsigned short data){
	while((UCSR0A & 0x20)==0x00); // �۽Ź��۰� ������� while�� Ż��
	UDR0=data; // ������ �۽�
	
	UCSR1A |= 0x20;         // Ŭ���� UDRE0
}

int main(void)
{
	/* Replace with your application code */
	DDRA = 0XFF;
	PORTE = 0XFF;
	
	UBRR0H = 103>>8; // ������Ʈ : 9600bps ����
	UBRR0L = 103;    // ������Ʈ : 9600bps ����
	UCSR0A = 0X00;
	UCSR0B = 0X18;
	UCSR0C = 0X06;
	
	unsigned short n= 30;
	// 30, 31, 32 ... 39, 40, 30, 31 ... : �����͸� 1�� �ֱ�� hostpc�� �۽�
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