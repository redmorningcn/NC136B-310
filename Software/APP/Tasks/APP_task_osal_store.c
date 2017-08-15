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
 * ��    �ƣ� 		StoreData
 * ��    �ܣ� 		���ݴ洢���������ݼ�¼�Ž����ݴ洢��ָ��
 					flash��ַ;���¼�¼�ŵ���Ϣ���󲿷����ݼ�¼��
 					��������������ֱ�Ӷ�sCtrl.sRec �и��¡��ٲ���
 					���������ڸú����и��¡�
 * ��ڲ����� 	��
 * ���ڲ����� 	��
 * ���� ���ߣ� 	redmornigcn
 * �������ڣ� 	2017-05-15
 * ��    �ģ�
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
     sCtrl.sRec.Car_Truck       = 0;
     *sCtrl.sRec.DriverUnitNum   = 0;
     sCtrl.sRec.E_LocoTyp       = 0;
     sCtrl.sRec.E_MstDriverNum  = 0;
     sCtrl.sRec.E_SlvDriverNum  = 0;
     sCtrl.sRec.E_StationNum    = 0;
     sCtrl.sRec.GpsLatitude     = 0;
     sCtrl.sRec.GpsLongitude    = 0;
     *sCtrl.sRec.KmMark          = 0;
     *sCtrl.sRec.LocoNum         = 0;
     sCtrl.sRec.LocoSign        = 0;
     sCtrl.sRec.LocoState       = 0;
     sCtrl.sRec.LocoTyp         = 0;
     sCtrl.sRec.LocoWorkState   = 0;
     sCtrl.sRec.MaxSpeed        = 0;
     sCtrl.sRec.MstDensity      = 0;
     sCtrl.sRec.MstDipTemp      = 0;
     sCtrl.sRec.MyAddspeed      = 0;
     sCtrl.sRec.MyDip1Den       = 0;
     sCtrl.sRec.MyDip2Den       = 0;
     sCtrl.sRec.MyKileMeter     = 0;
     sCtrl.sRec.MyMstLocoPower  = 0;
     sCtrl.sRec.MyPower         = 0;
     *sCtrl.sRec.PlanLen         = 0;
     sCtrl.sRec.RelRoadNum      = 0;
     sCtrl.sRec.Reserve1        = 0;
     sCtrl.sRec.RoadNum         = 0;
     sCtrl.sRec.SignalTyp       = 0;
     sCtrl.sRec.SlvDip1Prs      = 0;
     sCtrl.sRec.SlvDip2Prs      = 0;
     sCtrl.sRec.StationNum      = 0;
     *sCtrl.sRec.SlvDriverNum    = 0;
     *sCtrl.sRec.Time            = 0;
     *sCtrl.sRec.TrainNum        = 0;
     *sCtrl.sRec.TrainTyp        = 0;
     sCtrl.sRec.VoitureCnt      = 0;
     *sCtrl.sRec.Weight          = 0;
     
    

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
