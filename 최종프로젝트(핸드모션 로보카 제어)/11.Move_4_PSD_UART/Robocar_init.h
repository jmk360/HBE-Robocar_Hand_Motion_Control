#ifndef _ROBOCAR_INIT_
#define _ROBOCAR_INIT_

#include<avr/io.h>

// ���� ���⿡ ���� ��ũ�� ��� (PORTA�� 0~3�ɿ� FRONT�� ����, ���ʹ� �����ϰ� �ȴ�.)
#define FORWARD	0x06	//����
#define BACK	0x09	//����
#define LEFT	0x02	//��ȸ��
#define RIGHT	0x04	//��ȸ��
#define STOP    0x00	//����
#define LEFT_U	0x0A	//���� ����
#define RIGHT_U	0x05	//���� ����
#define B_RIGHT	0x08	//�������� ���� 
#define B_LEFT	0x01	//�������� ���� 

void PORT_init();

#endif
