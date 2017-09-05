/*******************************************************************************
 *   Filename:       app_task_disp.c
 *   Revised:        All copyrights reserved to wumingshen.
 *   Revision:       v1.0
 *   Writer:	     wumingshen.
 *
 *   Description:    ˫��ѡ�� disp �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Disp �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� DISP �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_DISP_PRIO ��
 *                                            �� �����ջ�� APP_TASK_DISP_STK_SIZE ����С
 *                   �� app.h �������������     ���������� void  App_TaskDispCreate(void) ��
 *                                            �� ���Ź���־λ �� WDTFLAG_Disp ��
 *
 *   Notes:
 *     				E-mail: shenchangwei945@163.com
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#define  SNL_APP_SOURCE
#include <includes.h>
#include <global.h>
#include <app_ctrl.h>
#include <bsp_max7219.h>
//#include <iap.h>

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_disp__c = "$Id: $";
#endif

#define APP_TASK_DISP_EN     DEF_ENABLED
#if APP_TASK_DISP_EN == DEF_ENABLED
/*******************************************************************************
 * CONSTANTS
 */
#define CYCLE_TIME_TICKS     (OS_CFG_TICK_RATE_HZ * 2u)

/*******************************************************************************
 * MACROS
 */

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
static  OS_TCB   AppTaskDispTCB;

/***********************************************
* ������ �����ջ��STACKS��
*/
//static  CPU_STK  AppTaskDispStk[ APP_TASK_DISP_STK_SIZE ];

#endif
/*******************************************************************************
 * GLOBAL VARIABLES
 */
/*******************************************************************************
 * LOCAL FUNCTIONS
 */
void    comm_mtr_err_judye(void);

     
#if ( OSAL_EN == DEF_ENABLED )
#else
static  void    AppTaskDisp           (void *p_arg);
#endif

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */
uint8 JudgeFlashIDErrFlg(void) ;  

/*******************************************************************************
 * EXTERN VARIABLES
 */
extern  stcSysCtrl  sCtrl;


/*******************************************************************************/
static  uint8   dis_mode    = 0;

void    SetDispNow(void)
{
    BSP_DispEvtProcess();
    dis_mode = 13*2;
}

/*******************************************************************************
 * ��    �ƣ� AppTaskDisp
 * ��    �ܣ� ��������
 * ��ڲ����� p_arg - �����񴴽���������
 * ���ڲ����� ��
 * ���� ���ߣ� wumingshen.
 * �������ڣ� 2015-02-05
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
extern  MODBUS_CH   *g_pch; 

//#if ( OSAL_EN == DEF_ENABLED )
osalEvt  TaskDispEvtProcess(INT8U task_id, osalEvt task_event)
//#else
//static  void  AppTaskDisp (void *p_arg)
//#endif
{
//    OS_ERR      err;
//    INT32U      ticks;
//    INT32S      dly;
//    CPU_SR_ALLOC();
//    
//    /***********************************************
//    * ������Task body, always written as an infinite loop.
//    */
//#if ( OSAL_EN == DEF_ENABLED )
//#else
//    TaskInitDisp();
//    
//    while (DEF_TRUE) {
//#endif
//        /***********************************************
//        * ������ �������Ź���־��λ
//        */
//        OS_FlagPost ((OS_FLAG_GRP *)&WdtFlagGRP,
//                     (OS_FLAGS     ) WDT_FLAG_DISP,
//                     (OS_OPT       ) OS_OPT_POST_FLAG_SET,
//                     (CPU_TS       ) 0,
//                     (OS_ERR      *) &err);
//        /***********************************************
//        * ������ �õ�ϵͳ��ǰʱ��
//        */
//        ticks = OSTimeGet(&err);
//        
//#if ( OSAL_EN == DEF_ENABLED )

        if( task_event & OS_EVT_DISP_TICKS ) {
//#else
//#endif
            static  uint8   times   = 0;
            static  uint8   disflg  = 0;
            uint8            delay  = 4;      //������ʾ���ʱ����

            stcTime         sTime;

            /***********************************************
            * ������ ������ʾģʽ��ʾ
            */
            switch(dis_mode/2) {
            /*******************************************************************
            * ������ ��ʾװ��ʱ��
            */
            case 0: 
                    dis_mode++;
                    ReadTime((stcTime * )& sTime);
                    uprintf("%02d-%02d-%02d",sTime.Year
                                            ,sTime.Month
                                            ,sTime.Date
                            );     
                    break;
            case 1: 
                    dis_mode++;
                    ReadTime((stcTime * )& sTime);     
                    uprintf("%02d-%02d-%02d",sTime.Hour
                                            ,sTime.Min
                                            ,sTime.Sec
                            );    
                    break;

            /*******************************************************************
            * ������ ��ʾ����汾
            *        ʱ�䣺������ʾһ�Σ���ʾ2s��
            */
            case 2: 
                dis_mode++;
                sCtrl.SoftWareID = 0x0104;
                uprintf("SV_%02X.%02X",(uint8)(sCtrl.SoftWareID>>8),(uint8)sCtrl.SoftWareID);
                
                break;
            /*******************************************************************
            * ������ ��ʾӲ���汾
            *        ������Ӳ��    
            */
            case 3: 
                dis_mode++;
                uprintf("SV31");
                
                break;
            /*******************************************************************
            * ������ ��ʾ����ģ�ͱ��
            */
            case 4: 
                dis_mode++;
                
                uprintf("C_%d",sCtrl.SOilPara.ModelNum);                
                break;
            /*******************************************************************
            * ������ �߶�
            */
            case 5:  
                dis_mode++;
                uprintf("H_%d",sCtrl.SOilPara.Hig);                
                break;  
            /*******************************************************************
            * ������ ����
            */
            case 6:  
                dis_mode++;
                uprintf("L_%d",sCtrl.SOilPara.Hig);                
                break; 
            /*******************************************************************
            * ������ ���ͳ���
            */
            case 7:  
                dis_mode++;
                uprintf("%4d.%4d",   sCtrl.sProductInfo.sLocoId.Type,
                                    sCtrl.sProductInfo.sLocoId.Num);                
                break; 
            /*******************************************************************
            * ������ ȫ��
            */
            case 8:  
                dis_mode++;
//                dis_mode++;
                uprintf("      ");                
                break;   
            /*******************************************************************
            * ������ �߶�ֵ
            */
            case 9:  
                dis_mode++;
                uprintf("%4d.%4d",sCtrl.sRec.Myhig1,sCtrl.sRec.Myhig2);                
                break;  
            /*******************************************************************
            * ������ �ٶ�1
            */
            case 10:  
                dis_mode++;
                uprintf("S1_%d",sCtrl.sRec.Myspeed1);                
                break;   
                
            /*******************************************************************
            * ������ �ٶ�1
            */
            case 11:  
                dis_mode++;
                uprintf("CS_%d",sCtrl.sRec.Myspeed1);                
                break;   
            /*******************************************************************
            * ������ �����жϡ�---���磬flash������쳣����ʾ�쳣���롣
            */
            case 12:  
                dis_mode++;
                //uprintf("CS_%d",sCtrl.sRec.Myspeed1);   
                uint8   ErrFlg;
                //FLASH�����жϡ�
                ErrFlg  = JudgeFlashIDErrFlg();  
                if(ErrFlg != 0xff)
                    uprintf("E-%d",ErrFlg); 
                else
                    uprintf("88888888"); 

                //��������жϡ�������ȡ����װ���쳣��
                break;   
            case 13:  
                dis_mode++;
                //����ֵ��ֻ��ʾ
                //disflg = BSP_DispEvtProcess();  //ִ����ʾ��������������ʾ������ֵ������������ֵ

                break;   
//            case 14:  
//               dis_mode++;
//                //����ֵ��ֻ��ʾ
//                //disflg = BSP_DispEvtProcess();  //ִ����ʾ��������������ʾ������ֵ������������ֵ
//                break;   
//            case 15:  
//                dis_mode++;
//                //disflg = BSP_DispEvtProcess();  //ִ����ʾ��������������ʾ������ֵ������������ֵ
//                //����ֵ��ֻ��ʾ
//                times = 0;
//                break;   
            /*******************************************************************
            * ������ ��������ʾ������ͨѶ�����жϼ����ϴ���
            */
            default:
                times++;
                if(disflg == 0 || (times % delay == 0))  //�����������ʾ����ʾ����ֵ
                {
                    uprintf("%8d",sCtrl.sRec.MstDip);   //��ʾ����
                    
                    if( sCtrl.sRunPara.SysSta && times % delay == 0)
                        uprintf("E-%d",sCtrl.sRunPara.SysSta);   //��ʾ���ϴ���
                }
                
                comm_mtr_err_judye();           //�ͳ�ͨѶ�����ж�
                break;
            }
            
            disflg = BSP_DispEvtProcess();  //ִ����ʾ��������������ʾ������ֵ������������ֵ
            
            osal_start_timerEx( OS_TASK_ID_DISP,
                                OS_EVT_DISP_TICKS,
                                500);
            return ( task_event ^ OS_EVT_DISP_TICKS );
        }
    return  task_event;
}


/*******************************************************************************
 * ��    �ƣ� APP_DispInit
 * ��    �ܣ� �����ʼ��
 * ��ڲ����� ��
 * ���ڲ����� ��
 * ���� ���ߣ� wumingshen.
 * �������ڣ� 2015-12-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void TaskInitDisp(void)
{    
//    /***********************************************
//    * ������ ��ʼ���������õ������Ӳ��
//    */
    BSP_DispInit();

    BSP_DispOff();
    
    BSP_DispSetBrightness(10);
    BSP_DispClrAll();
    uprintf("88888888");
    BSP_DispEvtProcess();
    

    /***********************************************
    * ������ �ڿ��Ź���־��ע�᱾����Ŀ��Ź���־
    */
    WdtFlags |= WDT_FLAG_DISP;
    /*************************************************
    * �����������¼���ѯ
    */
    osal_start_timerEx( OS_TASK_ID_DISP,
                        OS_EVT_DISP_TICKS,
                        100);
}

void    comm_mtr_err_judye(void)
{
    /*******************************************************************
    * �������ͳߴ���ͨѶ�����ж�
    */
    static  uint32  comm_mtr_err_times = 0;
    
    if(         sCtrl.Mtr.ConnCtrl[0].ErrFlg == 1 
       &&       sCtrl.Mtr.ConnCtrl[1].ErrFlg == 1){

        comm_mtr_err_times++;                   //�������
        
        if(comm_mtr_err_times > 4 && sCtrl.sRunPara.SysSta == 0 ){
            sCtrl.sRunPara.SysSta   = 83;       //����װ��1������װ��2���й���
            
            sCtrl.sRec.ErrorCode    = sCtrl.sRunPara.SysSta;    //������븳ֵ
        }
    }else if(   sCtrl.Mtr.ConnCtrl[0].ErrFlg == 1){
        comm_mtr_err_times++;                   //�������
        
        if(comm_mtr_err_times > 8 && sCtrl.sRunPara.SysSta == 0 ){
            sCtrl.sRunPara.SysSta   = 71;       //����װ��1����
            
            sCtrl.sRec.ErrorCode    = sCtrl.sRunPara.SysSta;    //������븳ֵ
        }
        
    }else if(   sCtrl.Mtr.ConnCtrl[1].ErrFlg == 1){
        comm_mtr_err_times++;                   //�������
        
        if(comm_mtr_err_times > 8 && sCtrl.sRunPara.SysSta == 0 )
            sCtrl.sRunPara.SysSta   = 81;       //����װ��2����
        
            sCtrl.sRec.ErrorCode    = sCtrl.sRunPara.SysSta;    //������븳ֵ
    }else {
        comm_mtr_err_times = 0;                 //�������

        if(     sCtrl.sRunPara.SysSta == 81
            ||  sCtrl.sRunPara.SysSta == 71
            ||  sCtrl.sRunPara.SysSta == 83){
            uprintf("E-%d",sCtrl.sRunPara.SysSta+100);  //��ʾ���ϴ���+100
            
            sCtrl.sRec.ErrorCode    = sCtrl.sRunPara.SysSta+100;//������븳ֵ
            sCtrl.sRunPara.SysSta   = 0;        //������ϴ���
        }
    }
}
/*******************************************************************************
 * 				                    end of file                                *
 *******************************************************************************/
#endif