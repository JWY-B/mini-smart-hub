#include "stm32f10x.h"                  // Device header

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOA��ʱ��
															//ʹ�ø�������ǰ���뿪��ʱ�ӣ����������Ĳ�����Ч
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;					//����ṹ�����
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIOģʽ����ֵΪ�������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				//GPIO���ţ���ֵΪ��0������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO�ٶȣ���ֵΪ50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//����ֵ��Ĺ���������ݸ�GPIO_Init����
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	while(1)
	{
		
	}
}
