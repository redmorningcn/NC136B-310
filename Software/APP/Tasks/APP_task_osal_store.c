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
void  SetRecFlsh(stcFlshRec *sFlsh)
{

    stcTime             sTime;

//暂时没用的数据清零    
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

//  数据记录内容更新在应用中进行。
//	数据内容存储在sCtrl.sRec 中。
         
/*
速度1，速度2，柴油机转速，工况，在app_task_osal_speed中更新
油量，在app_task_osal_calc中更新
高度1，高度2，在app_task_oasl_comm中更新
*/    
//  存储时更新的内容
	sFlsh->StoreCnt = sCtrl.sRecNumMgr.Current;     //取当前数据记录号	

//  装置时间:年-月-日，时-分-秒
	ReadTime((stcTime *)&sTime);

	sCtrl.sRec.MyYear		= sTime.Year;			
	sCtrl.sRec.MyMonth	    = sTime.Month;		
	sCtrl.sRec.MyData		= sTime.Date;			
	sCtrl.sRec.MyHour		= sTime.Hour;			
	sCtrl.sRec.MyMinute	    = sTime.Min;			
	sCtrl.sRec.MySecond	    = sTime.Sec;			

//开机标示
    sFlsh->RecTypCod = 0xff;                    //正常
    if(sCtrl.sRunPara.StartFlg)
    {
        sFlsh->RecTypCod        = START_EVT;           //開機          
        sCtrl.sRunPara.StartFlg = 0;
    }
    else
    {
        //sCtrl.sRec.RecTypCod = 
    }
        
    
//存储机车信息
    sFlsh->JcRealType   = sCtrl.sProductInfo.sLocoId.Type;
    sFlsh->JcRealNo     = sCtrl.sProductInfo.sLocoId.Num;

//软件版本    
    sFlsh->SoftVes 	    = sCtrl.SoftWareID;     
//故障代码
//    sCtrl.sRec.ErrorCode    = 

//运算参数
    sFlsh->OilBoxModel  = sCtrl.SOilPara.ModelNum;
//    sCtrl.sRec.
        
// 	保存TAX箱信息 
    GetTaxInfoToRecord(sFlsh);
     
// 	计算记录校验和
	sFlsh->CrcCheck = GetCrc16Check((uint8 *)sFlsh,sizeof(stcFlshRec) - 2);
    
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
void  SetRecFlsh_NDP02B(stcFlshRecNDP02B *sFlsh)
{

    stcTime             sTime;


    sFlsh->CmdTpye		 = 0;                                   //命令类型       1    
 
 //开机标示
    sFlsh->EvtType       =  0xff   ;                            //事件类型       1    
    if(sCtrl.sRunPara.StartFlg)
    {
        sFlsh->EvtType  = START_EVT;                             //開機          
        sCtrl.sRunPara.StartFlg = 0;
    }   
    
    sFlsh->LocoType      =   sCtrl.sProductInfo.sLocoId.Type  ;//机车型号       2                  
    sFlsh->LocoNum       =   sCtrl.sProductInfo.sLocoId.Num   ;//机 车 号       2                     
    sFlsh->SysID         =   sCtrl.sRecNumMgr.Current;         //记录流水号     4                   
    sFlsh->Oil           =   sCtrl.sRec.MstDip      ;//油量           2                    
    sFlsh->Hight1        =   sCtrl.sRec.Myhig1  ;//高度1          2                    
    sFlsh->Hight2        =   sCtrl.sRec.Myhig2  ;//高度2          2                    
    sFlsh->Pressure1     =   0  ;//压力1          2                    
    sFlsh->Pressure2     =   0  ;//压力2          2                    
    sFlsh->Density1      =   sCtrl.sRec.MyDip1Den  ;//密度1          2                    
    sFlsh->Density2      =   sCtrl.sRec.MyDip1Den   ;//密度2          2                    
    sFlsh->TempOil       =   0  ;//油箱温度       1                  
    sFlsh->TempEnv       =   0  ;//环境温度       1                  
    sFlsh->Degree        =   0  ;//电量           4                    
    sFlsh->Power         =   0  ;//功率           2                    
    sFlsh->Voltage       =   0  ;//电压           2                    
    sFlsh->Current       =   0  ;//电流           2                    
    sFlsh->EngineSpeed   =   sCtrl.sRec.MyEngRotSpd  ;//柴速           2                    
    sFlsh->Longitude     =   0  ;//经度           4                    
    sFlsh->Latitude	     =   0  ;//纬度           4                    
    sFlsh->AddSpeed      =   0  ;//加速度         2                     
    sFlsh->Rssi          =   0  ;//信号强度       1                  
    sFlsh->ErrCode       =   0  ;//故障代码       3                  
    sFlsh->ModelCode     =   sCtrl.sRec.OilBoxModel   ;//模型编号       1                  
    sFlsh->DevConfig     =   0  ;//通讯设备配      1                   
    sFlsh->Recv          =   0  ;//预留           6          


//  数据记录内容更新在应用中进行。
//	数据内容存储在sCtrl.sRec 中。
         
/*
速度1，速度2，柴油机转速，工况，在app_task_osal_speed中更新
油量，在app_task_osal_calc中更新
高度1，高度2，在app_task_oasl_comm中更新
*/    
//  存储时更新的内容
    
//  装置时间:年-月-日，时-分-秒
	
    memset((uint8_t *)&sFlsh->Tax.buf1[0],0,sizeof(sFlsh->Tax.buf1));//clear
    
    ReadTime((stcTime *)&sTime);

	sFlsh->Tax.Tax2.LKJTime.Year    = sTime.Year;			
	sFlsh->Tax.Tax2.LKJTime.Mon	    = sTime.Month;		
	sFlsh->Tax.Tax2.LKJTime.Day     = sTime.Date;			
	sFlsh->Tax.Tax2.LKJTime.Hour    = sTime.Hour;			
	sFlsh->Tax.Tax2.LKJTime.Min     = sTime.Min;			
	sFlsh->Tax.Tax2.LKJTime.Sec     = sTime.Sec;			

    if(sCtrl.Tax.ConnectFlag == 1)              //收到tax箱信息，将数据复制到数据记录
    {
    // 	保存TAX箱信息 
        sFlsh->TaxType   = sCtrl.Tax.Dat.Tax2A.Record.Addr;
        sFlsh->TaxFlg    = sCtrl.Tax.Dat.Tax2A.CheZhanHaoKuoChong;
        memcpy((uint8_t *)&sFlsh->Tax.buf1[0],(uint8_t *)&sCtrl.Tax.Dat.buf1[6],64);
    }
    
// 	计算记录校验和
	sFlsh->CrcCheck = GetCrc16Check((uint8 *)sFlsh,sizeof(stcFlshRecNDP02B) - 2);
    
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
    // 	计算数据记录地址
    uint32  FlshAddr = GetRecNumAddr( sCtrl.sRecNumMgr.Current );		
    
    sCtrl.sRunPara.StoreType    = 0x02;         //调试模式
    sCtrl.sRunPara.StoreTypeBak = 0x02;         //调试模式

    if(sCtrl.sRunPara.StoreType == 0x02 && sCtrl.sRunPara.StoreTypeBak == 0x02)  //NDP02B格式
    {
        SetRecFlsh_NDP02B(&sCtrl.sRecNdp02B);
    //	数据存储到flash
        if(!WriteFlsh(FlshAddr, (uint16 *)&sCtrl.sRecNdp02B, sizeof(sCtrl.sRecNdp02B)))
        {}        
    }
    else
    {
        SetRecFlsh(&sCtrl.sRec);
        //	数据存储到flash
        if(!WriteFlsh(FlshAddr, (uint16 *)&sCtrl.sRec, sizeof(sCtrl.sRec)))
        {}
    }
    
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
