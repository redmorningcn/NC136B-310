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
void  SetRecFlsh(stcFlshRec *sFlsh)
{

    stcTime             sTime;

//��ʱû�õ���������    
    sFlsh->GpsLatitude     = 0;
    sFlsh->GpsLongitude    = 0;
    sFlsh->MaxSpeed        = 0;
    sFlsh->MstDensity      = 0;
    sFlsh->MstDipTemp      = 0;
    sFlsh->MyAddspeed      = 0;
    sFlsh->MyDip1Den       = 0;
    sFlsh->MyDip2Den       = 0;
    sFlsh->MyKileMeter     = 0;
    sFlsh->MyMstLocoPower  = 0;
    sFlsh->MyPower         = 0;
    sFlsh->Reserve1        = 0;
    sFlsh->SlvDip1Prs      = 0;
    sFlsh->SlvDip2Prs      = 0;

//  ���ݼ�¼���ݸ�����Ӧ���н��С�
//	�������ݴ洢��sCtrl.sRec �С�
         
/*
�ٶ�1���ٶ�2�����ͻ�ת�٣���������app_task_osal_speed�и���
��������app_task_osal_calc�и���
�߶�1���߶�2����app_task_oasl_comm�и���
*/    
//  �洢ʱ���µ�����
	sFlsh->StoreCnt = sCtrl.sRecNumMgr.Current;     //ȡ��ǰ���ݼ�¼��	

//  װ��ʱ��:��-��-�գ�ʱ-��-��
	ReadTime((stcTime *)&sTime);

	sCtrl.sRec.MyYear		= sTime.Year;			
	sCtrl.sRec.MyMonth	    = sTime.Month;		
	sCtrl.sRec.MyData		= sTime.Date;			
	sCtrl.sRec.MyHour		= sTime.Hour;			
	sCtrl.sRec.MyMinute	    = sTime.Min;			
	sCtrl.sRec.MySecond	    = sTime.Sec;			

//������ʾ
    sFlsh->RecTypCod = 0xff;                    //����
    if(sCtrl.sRunPara.StartFlg)
    {
        sFlsh->RecTypCod        = START_EVT;           //�_�C          
        sCtrl.sRunPara.StartFlg = 0;
    }
    else
    {
        //sCtrl.sRec.RecTypCod = 
    }
        
    
//�洢������Ϣ
    sFlsh->JcRealType   = sCtrl.sProductInfo.sLocoId.Type;
    sFlsh->JcRealNo     = sCtrl.sProductInfo.sLocoId.Num;

//����汾    
    sFlsh->SoftVes 	    = sCtrl.SoftWareID;     
//���ϴ���
//    sCtrl.sRec.ErrorCode    = 

//�������
    sFlsh->OilBoxModel  = sCtrl.SOilPara.ModelNum;
//    sCtrl.sRec.
        
// 	����TAX����Ϣ 
    GetTaxInfoToRecord(sFlsh);
     
// 	�����¼У���
	sFlsh->CrcCheck = GetCrc16Check((uint8 *)sFlsh,sizeof(stcFlshRec) - 2);
    
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
void  SetRecFlsh_NDP02B(stcFlshRecNDP02B *sFlsh)
{

    stcTime             sTime;


    sFlsh->CmdTpye		 = 0;                                   //��������       1    
 
 //������ʾ
    sFlsh->EvtType       =  0xff   ;                            //�¼�����       1    
    if(sCtrl.sRunPara.StartFlg)
    {
        sFlsh->EvtType  = START_EVT;                             //�_�C          
        sCtrl.sRunPara.StartFlg = 0;
    }   
    
    sFlsh->LocoType      =   sCtrl.sProductInfo.sLocoId.Type  ;//�����ͺ�       2                  
    sFlsh->LocoNum       =   sCtrl.sProductInfo.sLocoId.Num   ;//�� �� ��       2                     
    sFlsh->SysID         =   sCtrl.sRecNumMgr.Current;         //��¼��ˮ��     4                   
    sFlsh->Oil           =   sCtrl.sRec.MstDip      ;//����           2                    
    sFlsh->Hight1        =   sCtrl.sRec.Myhig1  ;//�߶�1          2                    
    sFlsh->Hight2        =   sCtrl.sRec.Myhig2  ;//�߶�2          2                    
    sFlsh->Pressure1     =   0  ;//ѹ��1          2                    
    sFlsh->Pressure2     =   0  ;//ѹ��2          2                    
    sFlsh->Density1      =   sCtrl.sRec.MyDip1Den  ;//�ܶ�1          2                    
    sFlsh->Density2      =   sCtrl.sRec.MyDip1Den   ;//�ܶ�2          2                    
    sFlsh->TempOil       =   0  ;//�����¶�       1                  
    sFlsh->TempEnv       =   0  ;//�����¶�       1                  
    sFlsh->Degree        =   0  ;//����           4                    
    sFlsh->Power         =   0  ;//����           2                    
    sFlsh->Voltage       =   0  ;//��ѹ           2                    
    sFlsh->Current       =   0  ;//����           2                    
    sFlsh->EngineSpeed   =   sCtrl.sRec.MyEngRotSpd  ;//����           2                    
    sFlsh->Longitude     =   0  ;//����           4                    
    sFlsh->Latitude	     =   0  ;//γ��           4                    
    sFlsh->AddSpeed      =   0  ;//���ٶ�         2                     
    sFlsh->Rssi          =   0  ;//�ź�ǿ��       1                  
    sFlsh->ErrCode       =   0  ;//���ϴ���       3                  
    sFlsh->ModelCode     =   sCtrl.sRec.OilBoxModel   ;//ģ�ͱ��       1                  
    sFlsh->DevConfig     =   0  ;//ͨѶ�豸��      1                   
    sFlsh->Recv          =   0  ;//Ԥ��           6          


//  ���ݼ�¼���ݸ�����Ӧ���н��С�
//	�������ݴ洢��sCtrl.sRec �С�
         
/*
�ٶ�1���ٶ�2�����ͻ�ת�٣���������app_task_osal_speed�и���
��������app_task_osal_calc�и���
�߶�1���߶�2����app_task_oasl_comm�и���
*/    
//  �洢ʱ���µ�����
    
//  װ��ʱ��:��-��-�գ�ʱ-��-��
	
    memset((uint8_t *)&sFlsh->Tax.buf1[0],0,sizeof(sFlsh->Tax.buf1));//clear
    
    ReadTime((stcTime *)&sTime);

	sFlsh->Tax.Tax2.LKJTime.Year    = sTime.Year;			
	sFlsh->Tax.Tax2.LKJTime.Mon	    = sTime.Month;		
	sFlsh->Tax.Tax2.LKJTime.Day     = sTime.Date;			
	sFlsh->Tax.Tax2.LKJTime.Hour    = sTime.Hour;			
	sFlsh->Tax.Tax2.LKJTime.Min     = sTime.Min;			
	sFlsh->Tax.Tax2.LKJTime.Sec     = sTime.Sec;			

    if(sCtrl.Tax.ConnectFlag == 1)              //�յ�tax����Ϣ�������ݸ��Ƶ����ݼ�¼
    {
    // 	����TAX����Ϣ 
        sFlsh->TaxType   = sCtrl.Tax.Dat.Tax2A.Record.Addr;
        sFlsh->TaxFlg    = sCtrl.Tax.Dat.Tax2A.CheZhanHaoKuoChong;
        memcpy((uint8_t *)&sFlsh->Tax.buf1[0],(uint8_t *)&sCtrl.Tax.Dat.buf1[6],64);
    }
    
// 	�����¼У���
	sFlsh->CrcCheck = GetCrc16Check((uint8 *)sFlsh,sizeof(stcFlshRecNDP02B) - 2);
    
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
    // 	�������ݼ�¼��ַ
    uint32  FlshAddr = GetRecNumAddr( sCtrl.sRecNumMgr.Current );		
    
    sCtrl.sRunPara.StoreType    = 0x02;         //����ģʽ
    sCtrl.sRunPara.StoreTypeBak = 0x02;         //����ģʽ

    if(sCtrl.sRunPara.StoreType == 0x02 && sCtrl.sRunPara.StoreTypeBak == 0x02)  //NDP02B��ʽ
    {
        SetRecFlsh_NDP02B(&sCtrl.sRecNdp02B);
    //	���ݴ洢��flash
        if(!WriteFlsh(FlshAddr, (uint16 *)&sCtrl.sRecNdp02B, sizeof(sCtrl.sRecNdp02B)))
        {}        
    }
    else
    {
        SetRecFlsh(&sCtrl.sRec);
        //	���ݴ洢��flash
        if(!WriteFlsh(FlshAddr, (uint16 *)&sCtrl.sRec, sizeof(sCtrl.sRec)))
        {}
    }
    
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
