/*******************************************************************************
 *   Filename:       app_task_store.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    ˫��ѡ�� store �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Store �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� STORE �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_STORE_PRIO ��
 *                                            �� �����ջ�� APP_TASK_STORE_STK_SIZE ����С
 *                   �� app.h �������������     ���������� void  App_TaskStoreCreate(void) ��
 *                                            �� ���Ź���־λ �� WDTFLAG_Store ��
 *
 *   Notes:
 *     				E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#define  SNL_APP_SOURCE
#include <includes.h>
#include <global.h>
#include <app_ctrl.h>
#include <CardDataTypeDef.h>
#include <cpu.h>
#include "app_tax.h"
     

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_store__c = "$Id: $";
#endif

#define APP_TASK_STORE_EN     DEF_ENABLED
#if APP_TASK_STORE_EN == DEF_ENABLED				//
/*******************************************************************************
 * CONSTANTS
 */

/*******************************************************************************
 * MACROS
 */
#define		START_EVT		31		

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */

#if ( OSAL_EN == DEF_ENABLED )
#else
/***********************************************
* ������ ������ƿ飨TCB��
*/
static  OS_TCB   AppTaskStoreTCB;

/***********************************************
* ������ �����ջ��STACKS��
*/
//static  CPU_STK  AppTaskStoreStk[ APP_TASK_STORE_STK_SIZE ];

#endif
/*******************************************************************************
 * GLOBAL VARIABLES
 */

/*******************************************************************************
 * LOCAL FUNCTIONS
 */
#if ( OSAL_EN == DEF_ENABLED )
#else
extern	void    BSP_StoreInit(void);
#endif

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */
extern	stcSysCtrl       sCtrl;       	//	ȫ�ֽṹ������
/*******************************************************************************/

/*******************************************************************************
 * ��    �ƣ� 		GetRecNumAddr
 * ��    �ܣ�      ȡ���ݼ�¼��ַ��
                flash��ַ;���¼�¼�ŵ���Ϣ��
 * ��ڲ����� 	��
 * ���ڲ����� 	��
 * ���� ���ߣ� 	redmornigcn
 * �������ڣ� 	2017-05-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint32  GetRecNumAddr(uint32 FlshRecNum)
{				
    return  (uint32)(((FlshRecNum * sizeof(stcFlshRec)) % FLSH_MAX_SIZE)); 			
}


/*******************************************************************************
 * ��    �ƣ� 	GetTaxInfoToRecord
 * ��    �ܣ�   ȡTAX����Ϣ
 * ��ڲ����� 	��
 * ���ڲ����� 	��
 * ���� ���ߣ� 	redmornigcn
 * �������ڣ� 	2017-09-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint32  GetTaxInfoToRecord(stcFlshRec *sFlshRec)
{
    if(sCtrl.Tax.ConnectFlag == 1)              //�յ�tax����Ϣ�������ݸ��Ƶ����ݼ�¼
    {
        if(sCtrl.Tax.TaxType == TAX2_SET)       //TAX2
        {
            sCtrl.Tax.ConnectFlag = 0;          //����ȡ��Ϣ
            
            memcpy(&sFlshRec->RelSpeed,&sCtrl.Tax.Dat.Tax2.sTAX2Bak.RelSpeed,sizeof(sFlshRec->RelSpeed));
            memcpy(&sFlshRec->TrainNum,&sCtrl.Tax.Dat.Tax2.sTAX2Bak.TrainNum,sizeof(sFlshRec->TrainNum));
            memcpy(&sFlshRec->KmMark,&sCtrl.Tax.Dat.Tax2.sTAX2Bak.KmMark,sizeof(sFlshRec->KmMark));

            sFlshRec->Time          = sCtrl.Tax.Dat.Tax2.sTAX2Bak.Time;
            sFlshRec->LocoTyp       = sCtrl.Tax.Dat.Tax2.sTAX2Bak.LocoTyp;
            sFlshRec->E_LocoTyp     = sCtrl.Tax.Dat.Tax2.sTAX2Bef.E_LocoTyp;
            sFlshRec->LocoNum       = sCtrl.Tax.Dat.Tax2.sTAX2Bak.LocoNum;
            sFlshRec->TrainTyp      = sCtrl.Tax.Dat.Tax2.sTAX2Bef.TrainTyp;
            sFlshRec->Car_Truck     = sCtrl.Tax.Dat.Tax2.sTAX2Bak.Car_Truck;
            sFlshRec->VoitureCnt    = sCtrl.Tax.Dat.Tax2.sTAX2Bak.VoitureCnt;
            sFlshRec->Weight        = sCtrl.Tax.Dat.Tax2.sTAX2Bak.Weight;
            sFlshRec->PlanLen       = sCtrl.Tax.Dat.Tax2.sTAX2Bak.PlanLen;
            sFlshRec->MstDriverNum  = sCtrl.Tax.Dat.Tax2.sTAX2Bak.MstDriverNum;  
            sFlshRec->E_MstDriverNum= sCtrl.Tax.Dat.Tax2.sTAX2Bef.E_MstDriverNum;
            sFlshRec->E_SlvDriverNum= sCtrl.Tax.Dat.Tax2.sTAX2Bef.E_SlvDriverNum;
            sFlshRec->SlvDriverNum  = sCtrl.Tax.Dat.Tax2.sTAX2Bak.SlvDriverNum;  
            
            sFlshRec->RoadNum       = sCtrl.Tax.Dat.Tax2.sTAX2Bak.RoadNum;      
            sFlshRec->RelRoadNum    = sCtrl.Tax.Dat.Tax2.sTAX2Bef.RelRoadNum;   
            sFlshRec->StationNum    = sCtrl.Tax.Dat.Tax2.sTAX2Bak.StationNum;   
            sFlshRec->E_StationNum  = sCtrl.Tax.Dat.Tax2.sTAX2Bef.E_StationNum; 
            sFlshRec->SignalTyp     = sCtrl.Tax.Dat.Tax2.sTAX2Bak.SignalTyp;    
            sFlshRec->LocoSign      = sCtrl.Tax.Dat.Tax2.sTAX2Bak.LocoSign;     
            sFlshRec->LocoWorkState = sCtrl.Tax.Dat.Tax2.sTAX2Bak.LocoWorkState;
            sFlshRec->LocoState     = sCtrl.Tax.Dat.Tax2.sTAX2Bak.LocoState;  
        }
        
        if(sCtrl.Tax.TaxType == TAX3_SET)   //TAX3�豸
        {
            
        }
    }
}

      
      
/*******************************************************************************
 * ��    �ƣ�RoadNum;        		StoreData
 * ��    �ܣ�RelRoadNum;     		���ݴ洢���������ݼ�¼�Ž����ݴ洢��ָ��
 			StationNum;    		flash��ַ;���¼�¼�ŵ���Ϣ���󲿷����ݼ�¼��
 			E_StationNum;  		��������������ֱ�Ӷ�sCtrl.sRec �и��¡��ٲ���
 					���������ڸú����и��¡�
 * ��ڲ�����SignalTyp;      	��
 * ���ڲ�����LocoSign;       	��
 * ���� ����                 �� 	redmornigcn
 * �������ڣ�LocoWorkState;  	2017-05-15
 * ��    �ģ�LocoState;     
 * �޸����ڣ�
 *******************************************************************************/
void  StoreData(void)
{	
	uint32				FlshAddr;							//���ݴ洢��ַ
    stcTime             sTime;
//  ���ݼ�¼���ݸ�����Ӧ���н��С�
//	�������ݴ洢��sCtrl.sRec �С�
/*
�ٶ�1���ٶ�2�����ͻ�ת�٣���������app_task_osal_speed�и���
��������app_task_osal_calc�и���
�߶�1���߶�2����app_task_oasl_comm�и���
*/    
//  �洢ʱ���µ�����
	sCtrl.sRec.StoreCnt = sCtrl.sRecNumMgr.Current;     //ȡ��ǰ���ݼ�¼��	

//  װ��ʱ��:��-��-�գ�ʱ-��-��
	ReadTime((stcTime *)&sTime);

	sCtrl.sRec.MyYear		= sTime.Year;			
	sCtrl.sRec.MyMonth	    = sTime.Month;		
	sCtrl.sRec.MyData		= sTime.Date;			
	sCtrl.sRec.MyHour		= sTime.Hour;			
	sCtrl.sRec.MyMinute	    = sTime.Min;			
	sCtrl.sRec.MySecond	    = sTime.Sec;			

//������ʾ
    if(sCtrl.sRunPara.StartFlg)
    {
        sCtrl.sRec.RecTypCod = START_EVT;               
        sCtrl.sRunPara.StartFlg = 0;
    }
    
//�洢������Ϣ
    sCtrl.sRec.JcRealType   = sCtrl.sProductInfo.sLocoId.Type;
    sCtrl.sRec.JcRealNo     = sCtrl.sProductInfo.sLocoId.Num;

//����汾    
    sCtrl.sRec.SoftVes 	    = sCtrl.SoftWareID;     
//���ϴ���
//    sCtrl.sRec.ErrorCode    = 

//�������
    sCtrl.sRec.OilBoxModel  = sCtrl.SOilPara.ModelNum;
//    sCtrl.sRec.
        
    
//��ʱû�õ���������    
    sCtrl.sRec.GpsLatitude     = 0;
    sCtrl.sRec.GpsLongitude    = 0;

    sCtrl.sRec.MaxSpeed        = 0;
    sCtrl.sRec.MstDensity      = 0;
    sCtrl.sRec.MstDipTemp      = 0;
    sCtrl.sRec.MyAddspeed      = 0;
    sCtrl.sRec.MyDip1Den       = 0;
    sCtrl.sRec.MyDip2Den       = 0;
    sCtrl.sRec.MyKileMeter     = 0;
    sCtrl.sRec.MyMstLocoPower  = 0;
    sCtrl.sRec.MyPower         = 0;

    sCtrl.sRec.Reserve1        = 0;

    sCtrl.sRec.SlvDip1Prs      = 0;
    sCtrl.sRec.SlvDip2Prs      = 0;

     
// 	����TAX����Ϣ 
    GetTaxInfoToRecord(&sCtrl.sRec);
     
// 	�����¼У���
	sCtrl.sRec.CrcCheck = GetCrc16Check((uint8 *)&sCtrl.sRec,sizeof(sCtrl.sRec) - 2);

// 	�������ݼ�¼��ַ
    FlshAddr = GetRecNumAddr( sCtrl.sRec.StoreCnt);		//

//	���ݴ洢��flash
	if(!WriteFlsh(FlshAddr, (uint16 *)&sCtrl.sRec, sizeof(sCtrl.sRec)))
	{}

// 	�������ݼ�¼��
    sCtrl.sRecNumMgr.Current++;
	FRAM_StoreRecNumMgr((StrRecNumMgr  *)&sCtrl.sRecNumMgr);    //���ݼ�¼�ż�1��������
}

/*******************************************************************************
 * ��    �ƣ� 		ReadFlshRec
 * ��    �ܣ� 		���ݼ�¼�ţ�ȡ���ݼ�¼
 * ��ڲ����� 	    ��
 * ���ڲ����� 	    ��
 * ���� ���ߣ� 	    redmornigcn
 * �������ڣ� 	    2017-05-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
uint8	ReadFlshRec(stcFlshRec * sFlshRec,uint32	FlshRecNum)
{
	uint32		FlshAddr;
	
	FlshAddr = GetRecNumAddr( FlshRecNum );						
	
	if(ReadFlsh(FlshAddr,(uint16 *)sFlshRec,sizeof(stcFlshRec)))
	{
		return 1;
	}
	
	return	0;
}

/*******************************************************************************
 * ��    �ƣ�  TaskInitStore
 * ��    �ܣ�  �����ʼ��
 * ��ڲ����� 	��
 * ���ڲ����� 	��
 * ���� ���ߣ� 	redmornigcn
 * �������ڣ� 	2017-05-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void    BSP_StoreInit(void)
{
	InitFlashIO();      //��ʼ��flash

    GPIO_Fram_Init();   //��ʼ��fram
    
    InitDS3231();       //��ʼ��ʱ��
        
   //��sCtrl 
    FRAM_ReadRecNumMgr((StrRecNumMgr  *)&sCtrl.sRecNumMgr);         //����¼��
    FRAM_ReadProductInfo((StrProductInfo  *)&sCtrl.sProductInfo);   //����Ʒ���
    FRAM_ReadCurRecord((stcFlshRec  *)&sCtrl.sRec);                 //����ǰ��¼
    FRAM_ReadOilPara((StrOilPara  *)&sCtrl.SOilPara);               //���������
    FRAM_ReadRunPara((stcRunPara  *)&sCtrl.sRunPara);               //�����в���
    FRAM_ReadCalcModel((stcCalcModel  *)&sCtrl.sCalcModel);         //������ģ��

}

/*******************************************************************************
 * ��    �ƣ�  TaskInitStore
 * ��    �ܣ�  �����ʼ��
 * ��ڲ����� 	��
 * ���ڲ����� 	��
 * ���� ���ߣ� 	redmornigcn
 * �������ڣ� 	2017-05-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void TaskInitStore(void)
{    
//    /***********************************************
//    * ������ ��ʼ���������õ������Ӳ��
//    */
    BSP_StoreInit();			//��ʼ��Flash�ײ���غ���

//��ʼ����ʱ��
    osal_start_timerEx( OS_TASK_ID_STORE,
                      OS_EVT_STORE_TICKS,
                      1000);
}

extern  MODBUS_CH   *g_pch; 
/*******************************************************************************
 * ��    �ƣ� 		AppTaskStore
 * ��    �ܣ� 		��������
 * ��ڲ����� 	p_arg - �����񴴽���������
 * ���ڲ����� 	��
 * ���� ���ߣ� 	redmorningcn.
 * �������ڣ� 	2017-05-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
osalEvt  TaskStoreEvtProcess(INT8U task_id, osalEvt task_event)
{
    OS_ERR      err;
    INT32U      ticks;
    INT32S      dly;
    CPU_SR_ALLOC();

    if( task_event & OS_EVT_STORE_TICKS ) {

            StoreData();            //�������ݼ�¼
            
            osal_start_timerEx( OS_TASK_ID_STORE,
                                OS_EVT_STORE_TICKS,
                                1000*60);
                                //1000);
            return ( task_event ^ OS_EVT_STORE_TICKS );
    }
}



/*******************************************************************************
 * 				                    end of file                                *
 *******************************************************************************/
#endif
