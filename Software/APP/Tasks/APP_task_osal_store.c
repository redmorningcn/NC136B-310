/*******************************************************************************
 *   Filename:       app_task_store.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    双击选中 store 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 Store 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   双击选中 STORE 按 Ctrl + H, 钩选 Match the case, Replace with
 *                   输入您要的名字，点击 Replace All
 *                   在 app_cfg.h 中指定本任务的 优先级  （ APP_TASK_STORE_PRIO ）
 *                                            和 任务堆栈（ APP_TASK_STORE_STK_SIZE ）大小
 *                   在 app.h 中声明本任务的     创建函数（ void  App_TaskStoreCreate(void) ）
 *                                            和 看门狗标志位 （ WDTFLAG_Store ）
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
* 描述： 任务控制块（TCB）
*/
static  OS_TCB   AppTaskStoreTCB;

/***********************************************
* 描述： 任务堆栈（STACKS）
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
extern	stcSysCtrl       sCtrl;       	//	全局结构控制体
/*******************************************************************************/

/*******************************************************************************
 * 名    称： 		GetRecNumAddr
 * 功    能：      取数据记录地址。
                flash地址;更新记录号等信息。
 * 入口参数： 	无
 * 出口参数： 	无
 * 作　 　者： 	redmornigcn
 * 创建日期： 	2017-05-15
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint32  GetRecNumAddr(uint32 FlshRecNum)
{				
    return  (uint32)(((FlshRecNum * sizeof(stcFlshRec)) % FLSH_MAX_SIZE)); 			
}


/*******************************************************************************
 * 名    称： 	GetTaxInfoToRecord
 * 功    能：   取TAX箱信息
 * 入口参数： 	无
 * 出口参数： 	无
 * 作　 　者： 	redmornigcn
 * 创建日期： 	2017-09-15
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint32  GetTaxInfoToRecord(stcFlshRec *sFlshRec)
{
    if(sCtrl.Tax.ConnectFlag == 1)              //收到tax箱信息，将数据复制到数据记录
    {
        if(sCtrl.Tax.TaxType == TAX2_SET)       //TAX2
        {
            sCtrl.Tax.ConnectFlag = 0;          //清已取信息
            
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
        
        if(sCtrl.Tax.TaxType == TAX3_SET)   //TAX3设备
        {
            
        }
    }
}

      
      
/*******************************************************************************
 * 名    称：RoadNum;        		StoreData
 * 功    能：RelRoadNum;     		数据存储。根据数据记录号将数据存储到指定
 			StationNum;    		flash地址;更新记录号等信息。大部分数据记录的
 			E_StationNum;  		内容在其他任务直接对sCtrl.sRec 中更新。少部分
 					数据内容在该函数中跟新。
 * 入口参数：SignalTyp;      	无
 * 出口参数：LocoSign;       	无
 * 作　 　者                 ： 	redmornigcn
 * 创建日期：LocoWorkState;  	2017-05-15
 * 修    改：LocoState;     
 * 修改日期：
 *******************************************************************************/
void  StoreData(void)
{	
	uint32				FlshAddr;							//数据存储地址
    stcTime             sTime;
//  数据记录内容更新在应用中进行。
//	数据内容存储在sCtrl.sRec 中。
/*
速度1，速度2，柴油机转速，工况，在app_task_osal_speed中更新
油量，在app_task_osal_calc中更新
高度1，高度2，在app_task_oasl_comm中更新
*/    
//  存储时更新的内容
	sCtrl.sRec.StoreCnt = sCtrl.sRecNumMgr.Current;     //取当前数据记录号	

//  装置时间:年-月-日，时-分-秒
	ReadTime((stcTime *)&sTime);

	sCtrl.sRec.MyYear		= sTime.Year;			
	sCtrl.sRec.MyMonth	    = sTime.Month;		
	sCtrl.sRec.MyData		= sTime.Date;			
	sCtrl.sRec.MyHour		= sTime.Hour;			
	sCtrl.sRec.MyMinute	    = sTime.Min;			
	sCtrl.sRec.MySecond	    = sTime.Sec;			

//开机标示
    if(sCtrl.sRunPara.StartFlg)
    {
        sCtrl.sRec.RecTypCod = START_EVT;               
        sCtrl.sRunPara.StartFlg = 0;
    }
    
//存储机车信息
    sCtrl.sRec.JcRealType   = sCtrl.sProductInfo.sLocoId.Type;
    sCtrl.sRec.JcRealNo     = sCtrl.sProductInfo.sLocoId.Num;

//软件版本    
    sCtrl.sRec.SoftVes 	    = sCtrl.SoftWareID;     
//故障代码
//    sCtrl.sRec.ErrorCode    = 

//运算参数
    sCtrl.sRec.OilBoxModel  = sCtrl.SOilPara.ModelNum;
//    sCtrl.sRec.
        
    
//暂时没用的数据清零    
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

     
// 	保存TAX箱信息 
    GetTaxInfoToRecord(&sCtrl.sRec);
     
// 	计算记录校验和
	sCtrl.sRec.CrcCheck = GetCrc16Check((uint8 *)&sCtrl.sRec,sizeof(sCtrl.sRec) - 2);

// 	计算数据记录地址
    FlshAddr = GetRecNumAddr( sCtrl.sRec.StoreCnt);		//

//	数据存储到flash
	if(!WriteFlsh(FlshAddr, (uint16 *)&sCtrl.sRec, sizeof(sCtrl.sRec)))
	{}

// 	保存数据记录号
    sCtrl.sRecNumMgr.Current++;
	FRAM_StoreRecNumMgr((StrRecNumMgr  *)&sCtrl.sRecNumMgr);    //数据记录号加1，并保存
}

/*******************************************************************************
 * 名    称： 		ReadFlshRec
 * 功    能： 		根据记录号，取数据记录
 * 入口参数： 	    无
 * 出口参数： 	    无
 * 作　 　者： 	    redmornigcn
 * 创建日期： 	    2017-05-15
 * 修    改：
 * 修改日期：
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
 * 名    称：  TaskInitStore
 * 功    能：  任务初始化
 * 入口参数： 	无
 * 出口参数： 	无
 * 作　 　者： 	redmornigcn
 * 创建日期： 	2017-05-15
 * 修    改：
 * 修改日期：
 *******************************************************************************/
void    BSP_StoreInit(void)
{
	InitFlashIO();      //初始化flash

    GPIO_Fram_Init();   //初始化fram
    
    InitDS3231();       //初始化时钟
        
   //读sCtrl 
    FRAM_ReadRecNumMgr((StrRecNumMgr  *)&sCtrl.sRecNumMgr);         //读记录号
    FRAM_ReadProductInfo((StrProductInfo  *)&sCtrl.sProductInfo);   //读产品编号
    FRAM_ReadCurRecord((stcFlshRec  *)&sCtrl.sRec);                 //读当前记录
    FRAM_ReadOilPara((StrOilPara  *)&sCtrl.SOilPara);               //读计算参数
    FRAM_ReadRunPara((stcRunPara  *)&sCtrl.sRunPara);               //读运行参数
    FRAM_ReadCalcModel((stcCalcModel  *)&sCtrl.sCalcModel);         //读计算模型

}

/*******************************************************************************
 * 名    称：  TaskInitStore
 * 功    能：  任务初始化
 * 入口参数： 	无
 * 出口参数： 	无
 * 作　 　者： 	redmornigcn
 * 创建日期： 	2017-05-15
 * 修    改：
 * 修改日期：
 *******************************************************************************/
void TaskInitStore(void)
{    
//    /***********************************************
//    * 描述： 初始化本任务用到的相关硬件
//    */
    BSP_StoreInit();			//初始化Flash底层相关函数

//初始化定时器
    osal_start_timerEx( OS_TASK_ID_STORE,
                      OS_EVT_STORE_TICKS,
                      1000);
}

extern  MODBUS_CH   *g_pch; 
/*******************************************************************************
 * 名    称： 		AppTaskStore
 * 功    能： 		控制任务
 * 入口参数： 	p_arg - 由任务创建函数传入
 * 出口参数： 	无
 * 作　 　者： 	redmorningcn.
 * 创建日期： 	2017-05-15
 * 修    改：
 * 修改日期：
 *******************************************************************************/
osalEvt  TaskStoreEvtProcess(INT8U task_id, osalEvt task_event)
{
    OS_ERR      err;
    INT32U      ticks;
    INT32S      dly;
    CPU_SR_ALLOC();

    if( task_event & OS_EVT_STORE_TICKS ) {

            StoreData();            //保存数据记录
            
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
