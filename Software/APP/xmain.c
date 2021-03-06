/*******************************************************************************
 *   Filename:      app.c
 *   Revised:       $Date: 2013-06-30$
 *   Revision:      $
 *	 Writer:		Wuming Shen.
 *
 *   Description:
 *   Notes:
 *					QQ:276193028
 *     				E-mail:shenchangwei945@163.com
 *
 *   All copyrights reserved to Wuming Shen.
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#define  SNL_APP_SOURCE
#include <app.h>
#include <app_ctrl.h>

//#include <iap.h>

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *main__c = "$Id: $";
#endif


void    TaskInitStore(void);
osalEvt  TaskStoreEvtProcess(INT8U task_id, osalEvt task_event);

void    TaskInitCalc(void);
osalEvt  TaskCalcEvtProcess(INT8U task_id, osalEvt task_event);

void    TaskInitSpeed(void);
osalEvt  TaskSpeedEvtProcess(INT8U task_id, osalEvt task_event);

void     TaskInitLed(void);
osalEvt  TaskLedEvtProcess(INT8U task_id, osalEvt task_event);

uint8 	FRAM_StoreRunPara(stcRunPara  *sRunPara);


//void    TaskInitStore(void);
//osalEvt  TaskStoreEvtProcess(INT8U task_id, osalEvt task_event);
/*******************************************************************************
 * CONSTANTS
 */
#define CYCLE_TIME_TICKS            (OS_TICKS_PER_SEC * 2)

/*******************************************************************************
 * MACROS
 */

/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */

/*******************************************************************************
 * GLOBAL VARIABLES
 */
/***********************************************
* 描述： 创建标志组
*/
OS_FLAG_GRP         WdtFlagGRP;                     //看门狗标志组
OS_FLAGS            WdtFlags;

/*******************************************************************************
 * LOCAL FUNCTIONS
 *
 * 返回类型         函数名称                入口参数
 */

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

stcSysCtrl       sCtrl;


void    app_init_sctrl(void)
{
    sCtrl.Password      =   6237;
    sCtrl.SoftWareID    =   1705;   //年月，版本
    

//   	FRAM_StoreRunPara((stcRunPara *) &sCtrl.sRunPara);
    FRAM_ReadRunPara((stcRunPara *) &sCtrl.sRunPara);   //读取运行参数
 
//开始标示    //存储时间间隔
    sCtrl.sRunPara.StartFlg = 1;  
    sCtrl.sRunPara.SysSta   = 0;        
        
    sCtrl.sRunPara.RecClear = 0;
    sCtrl.sRunPara.StoreTime= 60;       
    sCtrl.sRunPara.SysReset = 0;
    
    FRAM_StoreRunPara((stcRunPara *) &sCtrl.sRunPara);   //读取运行参数
    
   
    
//    sCtrl.sRunPara.StoreType    = 0x02;            //shu ju NDP02B
//    sCtrl.sRunPara.StoreTypeBak = 0x02;


    
//测量装置1 初始化    
    sCtrl.Mtr.ConnCtrl[0].ConnFlg   = 1;
    sCtrl.Mtr.ConnCtrl[0].ErrFlg    = 0;
    sCtrl.Mtr.ConnCtrl[0].MasterAddr= 0x80;
    sCtrl.Mtr.ConnCtrl[0].SlaveAddr = 0x80+0x10;
    sCtrl.Mtr.ConnCtrl[0].SlaveAddr = SLAVE_ADDR_DIP1;
    sCtrl.Mtr.ConnCtrl[0].SendFlg   = 0;
    sCtrl.Mtr.ConnCtrl[0].SendFramNum=1;
    sCtrl.Mtr.ConnCtrl[0].TimeOut   = 10;
    
//测量装置2 初始化    
    sCtrl.Mtr.ConnCtrl[1].ConnFlg   = 1;
    sCtrl.Mtr.ConnCtrl[1].ErrFlg    = 0;
    sCtrl.Mtr.ConnCtrl[1].MasterAddr= 0x80;
    sCtrl.Mtr.ConnCtrl[1].SlaveAddr = SLAVE_ADDR_DIP2;
    sCtrl.Mtr.ConnCtrl[1].RecvEndFlg= 0;
    sCtrl.Mtr.ConnCtrl[1].SendFlg   = 0;
    sCtrl.Mtr.ConnCtrl[1].SendFramNum=1;
    sCtrl.Mtr.ConnCtrl[1].TimeOut   = 10;    
    
//无线模块 数据 初始化    
    sCtrl.Dtu.ConnCtrl[0].ConnFlg   = 1;
    sCtrl.Dtu.ConnCtrl[0].ErrFlg    = 0;
    sCtrl.Dtu.ConnCtrl[0].MasterAddr= 0x80;
    sCtrl.Dtu.ConnCtrl[0].SlaveAddr = SLAVE_ADDR_DTU;
    sCtrl.Dtu.ConnCtrl[0].RecvEndFlg= 0;
    sCtrl.Dtu.ConnCtrl[0].SendFlg   = 0;
    sCtrl.Dtu.ConnCtrl[0].SendFramNum=1;
    sCtrl.Dtu.ConnCtrl[0].TimeOut   = 10;    
    
//无线模块 参数 初始化    
    sCtrl.Dtu.ConnCtrl[1].ConnFlg   = 1;
    sCtrl.Dtu.ConnCtrl[1].ErrFlg    = 0;
    sCtrl.Dtu.ConnCtrl[1].MasterAddr= 0x80;
    sCtrl.Dtu.ConnCtrl[1].SlaveAddr = SLAVE_ADDR_SET;
    sCtrl.Dtu.ConnCtrl[1].RecvEndFlg= 0;
    sCtrl.Dtu.ConnCtrl[1].SendFlg   = 0;
    sCtrl.Dtu.ConnCtrl[1].SendFramNum=1;
    sCtrl.Dtu.ConnCtrl[1].TimeOut   = 10;   
    
//IC模块 数据 初始化    
    sCtrl.Otr.ConnCtrl[0].ConnFlg   = 1;
    sCtrl.Otr.ConnCtrl[0].ErrFlg    = 0;
    sCtrl.Otr.ConnCtrl[0].MasterAddr= 0x80;
    sCtrl.Otr.ConnCtrl[0].SlaveAddr = SLAVE_ADDR_OTR;
    sCtrl.Otr.ConnCtrl[0].RecvEndFlg= 0;
    sCtrl.Otr.ConnCtrl[0].SendFlg   = 0;
    sCtrl.Otr.ConnCtrl[0].SendFramNum=1;
    sCtrl.Otr.ConnCtrl[0].TimeOut   = 10;       
    
//IC模块 参数 初始化    
    sCtrl.Otr.ConnCtrl[1].ConnFlg   = 1;
    sCtrl.Otr.ConnCtrl[1].ErrFlg    = 0;
    sCtrl.Otr.ConnCtrl[1].MasterAddr= 0x80;
    sCtrl.Otr.ConnCtrl[1].SlaveAddr = SLAVE_ADDR_SET;
    sCtrl.Otr.ConnCtrl[1].RecvEndFlg= 0;
    sCtrl.Otr.ConnCtrl[1].SendFlg   = 0;
    sCtrl.Otr.ConnCtrl[1].SendFramNum=1;
    sCtrl.Otr.ConnCtrl[1].TimeOut   = 10;       
}



/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */

/*******************************************************************************
 * 名    称： App_Main
 * 功    能： 系统初开始前调用此函数
 * 入口参数： 无
 * 出口参数： 无
 * 作　 　者： 无名沈
 * 创建日期： 2014-08-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
 void App_Main(void)
 {
     
     //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x10000);
     
     //NVIC_SetVTOR(0x10000);
 
    #if DEBUG_MODEL_DISENABLE > 0 
        WDT_Feed();                    /* 喂狗                             */
    #endif   
        
     app_init_sctrl();                  //初始化全局变量
 

    #if DEBUG_MODEL_DISENABLE > 0 
        WDT_Feed();                    /* 喂狗                             */
    #endif   
        
        
     //FeedDog();
     
    //NVIC_SetVTOR(0x10000);
    /***********************************************
    * 描述： Disable all interrupts.
    */
    //BSP_IntDisAll();
    /***********************************************
    * 描述： 重新设置应用程序中断向量表，如果没有BOOTLOADER
    *        NVIC_VectTab_FLASH_OFFSET = 0
    */
//#if defined     (IMAGE_A)
//    /***********************************************
//    * 描述： 程序A
//    */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, FLASH_APP_ADDR_A-FLASH_BOOT_ADDR);
//    IAP_SetStatus(IAP_STS_SUCCEED); 
//#elif defined   (IMAGE_B)
//    /***********************************************
//    * 描述： 程序B
//    */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, FLASH_APP_ADDR_B-FLASH_BOOT_ADDR);
//    IAP_SetStatus(IAP_STS_SUCCEED); 
//#else
//    /***********************************************
//    * 描述： 程序
//    */
//    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0X0000);
//#endif
 
 }

/*******************************************************************************
 * 名    称： App_InitStartHook
 * 功    能： 系统初始化开始前调用此函数
 * 入口参数： 无
 * 出口参数： 无
 * 作　 　者： 无名沈
 * 创建日期： 2014-08-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
 void App_InitStartHook(void)
 {
 
 }
 
/*******************************************************************************
 * 名    称： App_InitEndHook
 * 功    能： 系统初始化结速后调用此函数
 * 入口参数： 无
 * 出口参数： 无
 * 作　 　者： 无名沈
 * 创建日期： 2014-08-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
 void App_InitEndHook(void)
 {
 
 }
 
 /*******************************************************************************
 * 名    称： OS_TaskCreateHook
 * 功    能： OS创建任务回调函数
 * 入口参数： 无
 * 出口参数： 无
 * 作  　者： 无名沈
 * 创建日期： 2014-08-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
 void OS_TaskCreateHook(void)
 {     
   App_TaskCommCreate();
    //App_TaskMaterCreate();
    //App_TaskDtuCreate();
    //App_TaskKeyCreate();
    //App_TaskBeepCreate();
 }
 
 /*******************************************************************************
 * 名    称： OSAL_TaskCreateHook
 * 功    能： OSAL创建任务回调函数
 * 入口参数： 无
 * 出口参数： 无
 * 作　 　者： 无名沈
 * 创建日期： 2014-08-08
 * 修    改：
 * 修改日期：
 *******************************************************************************/
 void OSAL_TaskCreateHook(void)
 {
 
    //osal_add_Task(TaskInitKey,                      // 任务初始化函数指针
    //              TaskKeyEvtProcess,                // 任务事件处理函数指针
    //              OS_TASK_PRO_KEY,                  // 任务优先级
    //              OS_TASK_ID_KEY);                  // 任务ID
    
    //osal_add_Task(TaskInitCtrl,                     // 任务初始化函数指针
    //              TaskCtrlEvtProcess,               // 任务事件处理函数指针
    //              OS_TASK_PRO_CTRL,                 // 任务优先级
    //              OS_TASK_ID_CTRL);                 // 任务ID
    
    osal_add_Task(TaskInitTmr,                      // 任务初始化函数指针
                  TaskTmrEvtProcess,                // 任务事件处理函数指针
                  OS_TASK_PRO_TMR,                  // 任务优先级
                  OS_TASK_ID_TMR);                  // 任务ID
        
   
    osal_add_Task(TaskInitDisp,                     // 任务初始化函数指针
                  TaskDispEvtProcess,               // 任务事件处理函数指针
                  OS_TASK_PRO_DISP,                 // 任务优先级
                  OS_TASK_ID_DISP);                 // 任务ID 
    
    osal_add_Task(TaskInitStore,                    // 任务初始化函数指针
                  TaskStoreEvtProcess,              // 任务事件处理函数指针
                  OS_TASK_PRO_STORE,                // 任务优先级
                  OS_TASK_ID_STORE);                // 任务ID
    
    osal_add_Task(TaskInitCalc,                    // 任务初始化函数指针
                  TaskCalcEvtProcess,              // 任务事件处理函数指针
                  OS_TASK_PRO_CALC,                // 任务优先级
                  OS_TASK_ID_CALC);                // 任务ID   
    
    osal_add_Task(TaskInitSpeed,                    // 任务初始化函数指针
                  TaskSpeedEvtProcess,              // 任务事件处理函数指针
                  OS_TASK_PRO_SPEED,                // 任务优先级
                  OS_TASK_ID_SPEED);                // 任务ID       
    
    osal_add_Task(TaskInitLed,                  // 任务初始化函数指针
                  TaskLedEvtProcess,                // 任务事件处理函数指针
                  OS_TASK_PRO_LED,                  // 任务优先级
                  OS_TASK_ID_LED);                  // 任务ID    
 }
/*******************************************************************************
 *              end of file                                                    *
 *******************************************************************************/
