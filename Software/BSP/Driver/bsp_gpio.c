/*******************************************************************************
 *   Filename:      bsp_gpio.c
 *   Revised:       $Date: 2017-05-15$
 *   Revision:      $
 *   Writer:	    redmorningcn.
 *
 *   Description:
 *   Notes:
 *     			E-mail:redmorningcn@qq.com
 *
 *   All copyrights reserved to redmorningcn.
 *
 *******************************************************************************/
#include 		<includes.h>  
#include 		"string.h"
#include    	"stdio.h" 
#include   	    "stdarg.h"

//-------------------------------------------------------------------------------------------------------
//��������:         GPIO_SetOrClearValue()
//��    ��:         	��ָ���Ķ˿�д1��0
//��ڲ���:         GpioNum:   ���ű�ţ��ɶ˿�*100+ ���ű�� ��ɡ�
//                  		Val:   �趨ֵ��0 ��
//��		��:		redmorningcn
//��		��:		2017-05-15
//���ڲ���:         ��
//˵����            
//--------------------------------------------------------------------------------------------------------
void	GPIO_SetOrClearValue(uint32_t GpioNum,uint8_t Val)
{
	uint32 		PortBuf[] = {PINSEL_PORT_0,PINSEL_PORT_1,PINSEL_PORT_2,PINSEL_PORT_3,PINSEL_PORT_4};
	uint8		PortNum;
	uint8		IoNum;

	PortNum 	= GpioNum/100;
	IoNum	= GpioNum%100;

	GPIO_SetDir(PortBuf[PortNum], 0x01ul<<IoNum,1);
	Val>0?GPIO_SetValue(PortBuf[PortNum], 0x01ul<<IoNum):
			  GPIO_ClearValue(PortBuf[PortNum], 0x01ul<<IoNum);
}

//-------------------------------------------------------------------------------------------------------
//��������:         GPIO_PinselConfig()
//��    ��:         	�������Ź���
//��ڲ���:         GpioNum:   ���ű�ţ��ɶ˿�*100+ ���ű�� ��ɡ�
//                  		FuncNum:    ���Ź��ܺţ�һ�㹦��0~4
//��		��:		redmorningcn
//��		��:		2017-05-15
//���ڲ���:         ��
//˵����            
//--------------------------------------------------------------------------------------------------------
void	GPIO_PinselConfig(uint8_t GpioNum,uint8_t FuncNum)
{
	PINSEL_CFG_Type	PinCfg_Test;

	uint32 		PortBuf[] = {PINSEL_PORT_0,PINSEL_PORT_1,PINSEL_PORT_2,PINSEL_PORT_3,PINSEL_PORT_4};
	uint8		PortNum;
	uint8		IoNum;

	PortNum 	= GpioNum/100;
	IoNum	= GpioNum%100;

	PinCfg_Test.Portnum = PortBuf[PortNum];
	PinCfg_Test.Pinnum  = IoNum;
	PinCfg_Test.Funcnum = FuncNum;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
}

//-------------------------------------------------------------------------------------------------------
//��������:        GPIO_ReadIoVal()
//��    ��:         	��ȡ������ֵ
//��ڲ���:         GpioNum:   ���ű�ţ��ɶ˿�*100+ ���ű�� ��ɡ�
//���ڲ���:		0 ��1                 		
//��		��:		redmorningcn
//��		��:		2017-05-15
//���ڲ���:         ��
//˵����            
//--------------------------------------------------------------------------------------------------------
uint8	GPIO_ReadIoVal(uint32_t GpioNum)
{
	uint32 		PortBuf[] = {PINSEL_PORT_0,PINSEL_PORT_1,PINSEL_PORT_2,PINSEL_PORT_3,PINSEL_PORT_4};
	uint8		PortNum;
	uint8		IoNum;
	uint32 		PortVal;	

	PortNum = GpioNum/100;
	IoNum	= GpioNum%100;

	GPIO_SetDir(PortBuf[PortNum], 0x01ul<<IoNum,0);
	PortVal = GPIO_ReadValue(PortBuf[PortNum]);	
	
	if(PortVal & 1ul<<IoNum)
	{
		return	1;
	}
	return	0;
}
