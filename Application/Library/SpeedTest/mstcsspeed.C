#include <includes.h>
#include <FRAM.h>
#include <osal.h>
#include <bsp_os.h>

//ÿȦ���峣��
#define		PPR		200
//pi = 3.14 * 100
#define		PI		314
//�ֶ�ֱ�� 1.1m * 10
//#define		DIM		11
#define		DIM		10.5
//��̳��� PPR *10*100*1000  
#define		PI_DIM_MUL		(10*100)

#if (UCOS_EN == DEF_ENABLED ) && ( OS_VERSION > 30000U )
extern  OS_SEM           time2_over_Sem;               // �ź���
#endif

uint32	mPluseSumCntcs = 0;
//-------------------------------------------------------------------------------
//��������:         GetFrqCnt()
//��������:         ȡƵ��ֵ
//��ڲ���:         ��		 
//���ڲ���:         
//-------------------------------------------------------------------------------
uint32  GetFrq3SumCnt(void)
{
	return	mPluseSumCntcs;
}

uint32	m_TimecsSum = 0;
uint32	m_AddPlusecs = 0;
uint32	m_PlusecsChgFlg = 0;
static	stcSpeedPluse	m_sSpeedcsPluse;


#define	MATH_PLUSE_TIME	 (2*1000*1000)
#define	MATH_PLUSE_NUM 	 100

#define		CAP00	126
#define		CAP10	118
#define		CAP20	4

void TIMER2_IRQHandler(void)
{        
    uint8  tmp = 0;

	if (TIM_GetIntCaptureStatus(LPC_TIM2,TIM_MR0_INT))
	{
		TIM_ClearIntCapturePending(LPC_TIM2,TIM_MR0_INT);

        nop();
   
        tmp = GPIO_ReadIoVal(CAP20);  
        
        if(tmp == 1)
            return;
        
		m_TimecsSum += TIM_GetCaptureValue(LPC_TIM2,TIM_COUNTER_INCAP0);
		TIM_ResetCounter(LPC_TIM2);

		m_AddPlusecs++;
		mPluseSumCntcs++;

		if(m_AddPlusecs == MATH_PLUSE_NUM || m_TimecsSum > MATH_PLUSE_TIME) 		//500�������1��ʱ�䵽
		{
			m_sSpeedcsPluse.TimeCnt 	= 	m_TimecsSum;
			m_sSpeedcsPluse.PluseCnt	=   m_AddPlusecs;
				
			m_AddPlusecs = 0;
			m_TimecsSum = 0;
			m_PlusecsChgFlg = 1;
            
            #if (OS_VERSION > 30000U)
                BSP_OS_SemPost(&time2_over_Sem);                        	// �����ź���
            #endif
		}
	}
}


uint16  l_speedcs = 0;
uint16	GetMyEngRotSpd(void)
{
	return	l_speedcs;
}

void GetSpeedPlusecs(stcSpeedPluse * sSpeedPluse)
{
	static	uint32	Time;
	
	sSpeedPluse->PluseCnt = m_sSpeedcsPluse.PluseCnt;
	sSpeedPluse->TimeCnt  = m_sSpeedcsPluse.TimeCnt;

	if(m_PlusecsChgFlg == 1)							//�����ۼӴ���,
	{
		m_PlusecsChgFlg = 0;
//		Time = GetSysTime();
	}
		
//	if(GetSysTime() - Time > 250)					//����2��û���£�����    ---  ����ˢ��ʱ��2��
	{	
//		printfcom0("\r\n outtime");
		sSpeedPluse->PluseCnt = 0;
		sSpeedPluse->TimeCnt = 0;
	}	
}

//���㹫ʽ��V = ��PI * DIM * n * 3600��/ (( DPR *1000*10*100 )*(t/12000000);
//------------------------------------------------------------------------------
//��    �ܣ�    ��������̣��ֶ���̣��Զ������
//��ڲ�����    
//���ڲ�����    
//------------------------------------------------------------------------------
void  CalcSpeedcs( void )
{
	uint32	PluseCnt = 0;
	uint32	TimeCnt;
	uint32	DistInSec;
	uint16	speed;
	uint32	cstime     = 0;
	uint32	avg;

    
    PluseCnt = m_sSpeedcsPluse.PluseCnt;
	cstime	 = m_sSpeedcsPluse.TimeCnt;
    	

    
    
//	if(sSpeedPluse.TimeCnt)
//	{
//		if(times < 3)
//		{		
//			PluseCnt 		= sSpeedPluse.PluseCnt;
//			cstime	 		= sSpeedPluse.TimeCnt;
//		}
//		else
//		{
//			avg =  PluseCnt/3;
//			PluseCnt = PluseCnt - avg + sSpeedPluse.PluseCnt;
//			avg =  cstime/3;
//			cstime   = cstime - sSpeedPluse.PluseCnt;
//		}
//
#if (OS_VERSION > 30000U)
    CPU_BOOLEAN err;   
    static  uint8 times = 0;

    err = BSP_OS_SemWait(&time2_over_Sem,10);                        	// �����ź���
    if(!err)
    {
            // �����ź���,�ٶ�������Ҫ3�����һ�Σ�������׼ȷ
        if(times++ > 5)
            l_speedcs = 0;  
    }
    
    if(err){
        times = 0;
#endif    
        if( cstime >1000    && 
        m_PlusecsChgFlg      )                   //����������
    //	if(cstime >1000)
        {
            m_PlusecsChgFlg = 0;            
            l_speedcs = ((PluseCnt * 60 * 1000) / (cstime/1000));
        }
    }
}

