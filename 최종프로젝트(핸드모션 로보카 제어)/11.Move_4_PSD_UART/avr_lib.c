#include"avr_lib.h"

void init_UART1(u08 bps)   // 시리얼 함수 초기화
{
    DDRD &= 0xFB;
	DDRD |= 0x08;     // PE1(TXD) 출력(4), PE0(RXD) 입력(3)

     UCSR0A=0x00;
     UCSR0B=0x18;   // Receive enable, Transmitte enable
     UCSR0C=0x06;   // 비동기 방식, No parity bit, 1 stop bit   

     UBRR0H=0x00;
     UBRR0L=bps;   // 115200
}

u08 RoboCAR_getch(void){
	unsigned char data;	
	
	while((UCSR0A & 0x80)==0x00);		
		data=UDR0;
	
	UCSR0A	|=  0x80;
	return data;
}

void RoboCAR_putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0x00);
	UDR0=data;
  
	UCSR0A |= 0x20;         // 클리어 UDRE0
}

void us_delay(unsigned short time_us){
	
	register u08 i;

	for(i=0; i < time_us ; i++){		//4 
		asm volatile("PUSH R0");		//2
		asm volatile("POP R0");			//2	 = 8cycle = 1.08us
									
	}

}
void ms_delay(u16 time_ms){
	register u16 i;

	for(i=0; i < time_ms ; i++){	
		us_delay(250);	
		us_delay(250);	
		us_delay(250);	
		us_delay(250);	// 1us * 1000 = 1ms
		
	}
}
