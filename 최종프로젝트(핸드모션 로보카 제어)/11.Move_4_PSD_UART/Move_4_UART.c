/****************************************************************************
	UART(�������)�� �̿��� �κ�ī ���� ���α׷�
	
	����:
		�� ���� ���α׷��� Ÿ�̸�1�� ����ؼ� PWM�� �߻��ϰ� ������,
		UART1�� 115200bps�� �����Ͽ�, �Է¹޴� ��ɿ� ����
		�κ�ī�� �����ϰ� �ִ�.			

	�ҽ� ���� :
		1)	���α׷��� �ʿ��� �� ������� �����Ѵ�.
		2)	��Ʈ �ʱ�ȭ
		3)	PWM�� ���� Ÿ�̸�1 ������ ���� ��� ���� PWM ��Ƽ�� �����Ѵ�.
		4)	UART1���(��������� ����)�� 115200bps,�帧���� �������� �����Ѵ�.
		5)	���۵Ǵ� ��ɿ� ���� �κ�ī�� �� ��ɿ� �°� �̵���Ų��.	
			
			'y'	:	����
			'b'	:	����
			's'	:	����
			'j'	:	��ȸ��		
			'g'	:	��ȸ��	
			't'	:	���� ����
			'u'	:	���� ����


****************************************************************************/
//	1)
#include<avr/io.h>
#include<avr/interrupt.h>
#include"avr_lib.h"
#include"Robocar_init.h"
#include"RBC_Motor.h"

//	1)
//PSD �Ÿ� ������ ���� ����ǥ
u16 PSD_val[14]={745,512,397,331,283,255,224,200,188,171,164,151,116,110};
u08 PSD_cm[14]={10,15,20,25,30,35,40,45,50,55,60,65,70,75};

//	2)
u16 ADC_Convert(u08 ch){
	u16 _ret=0;
		
	ADMUX=0xc0 | ch; //2.56v   
	ADCSR=0xa7;     //128���� 
	ADCSR |= 0x40; //ADC start conversion

	while( (ADCSR&0x10)==0x00);		

	ADCSR |= 0x10;
	
	_ret =	ADCL & 0xff;
	_ret |=	ADCH<<8 ; 	
		
	ADMUX=0x0;   
	ADCSR=0x0;   
 		
	return _ret;
}

void Puts_Dist(u16 data){
	while((UCSR0A & 0x20)==0x00);
	UDR0=data;
	
	UCSR0A |= 0x20;         // Ŭ���� UDRE0
}

int main(){
	
	u08 Command = 0;		//���۸�� ���庯��
	s16 PWM_value = 0x200;

	u16 Dist=0;
	u08 i,j;
	u16 tmp_val;
	u08 tmp_cm;
	u08 tmp;
	
//	2)	
	PORT_init();

//	3)	
	Timer1_init(); 
	PWM_change('A', PWM_value); 

//	4)
	init_UART1(UART_115200);

//	5)	
	while(1){	

		Command = RoboCAR_getch();

		switch(Command){
			case 'y':
				PORTA &= 0xF0;
				PORTA |= FORWARD;
			break;

			case 'b':
				PORTA &= 0xF0;
				PORTA |= BACK;
			break;
			
			case 'j':
				PORTA &= 0xF0;
				PORTA |= LEFT;
			break;

			case 'g':
				PORTA &= 0xF0;
				PORTA |= RIGHT;
			break;
			
			case 't':
				PORTA &= 0xF0;
				PORTA |= LEFT_U;
			break;
			
			case 'u':
				PORTA &= 0xF0;
				PORTA |= RIGHT_U;
			break;

			case 's':
				PORTA &= 0xF0;
				PORTA |= STOP;
			break;
		}

		Dist = ADC_Convert(0x00);
		
		for(i=0,j=0;i<14;i++){
			if(Dist<PSD_val[i])
				j=i;
			else
				break;							
		}
		tmp_cm = PSD_cm[i]-PSD_cm[j];
		tmp_val = PSD_val[j]-PSD_val[i];
		
		tmp = tmp_val/tmp_cm ;
		Dist = ((PSD_val[j]-Dist)/tmp)+PSD_cm[j];
		
		Puts_Dist(Dist);

		ms_delay(100);
	}
	

	return 0;
}





