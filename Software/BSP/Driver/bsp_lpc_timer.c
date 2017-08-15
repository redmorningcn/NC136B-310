#include <includes.h>
#include <osal.h>
#include <bsp_os.h>


#define		CAP00	126
#define		CAP10	118
#define		CAP20	4

/***********************************************
* ������ OS�ӿ�
*/
#if (UCOS_EN == DEF_ENABLED ) && ( OS_VERSION > 30000U )
OS_SEM           time0_over_Sem;               // �ź���
#endif

/***********************************************
* ������ OS�ӿ�
*/
#if (UCOS_EN == DEF_ENABLED ) && ( OS_VERSION > 30000U )
OS_SEM           time1_over_Sem;               // �ź���
#endif

/***********************************************
* ������ OS�ӿ�
*/
#if (UCOS_EN == DEF_ENABLED ) && ( OS_VERSION > 30000U )
OS_SEM           time2_over_Sem;               // �ź���
#endif


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ115200
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void Time0Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);


	GPIO_PinselConfig(CAP00,3);

	// Initialize timer 0, prescale count time of 1000000uS = 1S
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000000;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, CAPn.0
	TIM_CaptureConfigStruct.CaptureChannel = 0;
	// DISABLE capture on CAPn.0 rising edge
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;
	// Enable capture on CAPn.0 falling edge
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
	// Generate capture interrupt
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;


	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigCapture(LPC_TIM0, &TIM_CaptureConfigStruct);
	TIM_ResetCounter(LPC_TIM0);


	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER0_IRQn, TIMER0_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER0_IRQn);
	// To start timer 0
	TIM_Cmd(LPC_TIM0,ENABLE);		
    
    #if ( OS_VERSION > 30000U )
        BSP_OS_SemCreate(&time0_over_Sem, 0, "time0 over Sem");
    #endif
}


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ115200
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void Time1Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);

	GPIO_PinselConfig(CAP10,3);

	// Initialize timer 0, prescale count time of 1000000uS = 1S
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000000;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, CAPn.0
	TIM_CaptureConfigStruct.CaptureChannel = 0;
	// DISABLE capture on CAPn.0 rising edge
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;
	// Enable capture on CAPn.0 falling edge
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
	// Generate capture interrupt
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;


	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM1, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigCapture(LPC_TIM1, &TIM_CaptureConfigStruct);
	TIM_ResetCounter(LPC_TIM1);


	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER1_IRQn, TIMER1_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER1_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM1,ENABLE);		
    
    #if (OS_VERSION > 30000U )
        BSP_OS_SemCreate(&time1_over_Sem, 0, "time1 over Sem");
    #endif
}


/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ115200
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void Time2Init (void)
{
//	UART_CFG_Type		UART_ConfigStruct_Test;
//	UART_FIFO_CFG_Type 	FIFOCfg_Test;
//	UART_INT_Type 		UARTIntCfg_Test;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_CAPTURECFG_Type TIM_CaptureConfigStruct;

//	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCTIM0,ENABLE);


	GPIO_PinselConfig(CAP20,3);

	// Initialize timer 0, prescale count time of 1000000uS = 1S
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
//	TIM_ConfigStruct.PrescaleValue	= 1000000;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// use channel 0, CAPn.0
	TIM_CaptureConfigStruct.CaptureChannel = 0;
	// DISABLE capture on CAPn.0 rising edge
	TIM_CaptureConfigStruct.RisingEdge = DISABLE;
	//TIM_CaptureConfigStruct.RisingEdge = ENABLE;
	// Enable capture on CAPn.0 falling edge
	TIM_CaptureConfigStruct.FallingEdge = ENABLE;
	//TIM_CaptureConfigStruct.FallingEdge = DISABLE;
	// Generate capture interrupt
	TIM_CaptureConfigStruct.IntOnCaption = ENABLE;


	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM2, TIM_TIMER_MODE,&TIM_ConfigStruct);
	TIM_ConfigCapture(LPC_TIM2, &TIM_CaptureConfigStruct);
	TIM_ResetCounter(LPC_TIM2);


	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER2_IRQn, TIMER2_IRQn);
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER2_IRQn);
	// To start timer 1
	TIM_Cmd(LPC_TIM2,ENABLE);	
    
    #if ( OS_VERSION > 30000U )
        BSP_OS_SemCreate(&time2_over_Sem, 0, "time2 over Sem");
    #endif
}
