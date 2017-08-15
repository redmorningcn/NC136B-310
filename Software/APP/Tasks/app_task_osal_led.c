/*******************************************************************************
 *   Filename:       app_task_led.c
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmoringcn.
 *
 *   Description:    ˫��ѡ�� led �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Led �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� LED �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_LED_PRIO ��
 *                                            �� �����ջ�� APP_TASK_LED_STK_SIZE ����С
 *                   �� app.h �������������     ���������� void  App_TaskLedCreate(void) ��
 *                                            �� ���Ź���־λ �� WDTFLAG_Led ��
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
//#include <iap.h>

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_task_led__c = "$Id: $";
#endif

#define APP_TASK_LED_EN     DEF_ENABLED
#if APP_TASK_LED_EN == DEF_ENABLED
/*******************************************************************************
 * CONSTANTS
 */
#define CYCLE_TIME_TICKS     (OS_CFG_TICK_RATE_HZ * 2u)

/*******************************************************************************
 * MACROS
 */
//#define     BSP_LED_NUM         8
////LED�������� 
//#define     LED_TOGGLE_CNT      15


/*******************************************************************************
 * TYPEDEFS
 */

/*******************************************************************************
 * LOCAL VARIABLES
 */
//
//uint8   LedWorkTimes[BSP_LED_NUM + 1] = 0;

#if ( OSAL_EN == DEF_ENABLED )
#else
/***********************************************
* ������ ������ƿ飨TCB��
*/
static  OS_TCB   AppTaskLedTCB;

/***********************************************
* ������ �����ջ��STACKS��
*/
//static  CPU_STK  AppTaskLedStk[ APP_TASK_LED_STK_SIZE ];

#endif
/*******************************************************************************
 * GLOBAL VARIABLES
 */

/*******************************************************************************
 * LOCAL FUNCTIONS
 */
#if ( OSAL_EN == DEF_ENABLED )
#else
static  void    AppTaskLed           (void *p_arg);
#endif

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */
extern  stcSysCtrl  sCtrl;

/*******************************************************************************/


/*******************************************************************************
 * ��    �ƣ� AppTaskLed
 * ��    �ܣ� ��������
 * ��ڲ����� p_arg - �����񴴽���������
 * ���ڲ����� ��
 * ���� ���ߣ� wumingshen.
 * �������ڣ� 2015-02-05
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/

//#if ( OSAL_EN == DEF_ENABLED )
osalEvt  TaskLedEvtProcess(INT8U task_id, osalEvt task_event)
//#else
//static  void  AppTaskLed (void *p_arg)
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
//    TaskInitLed();
//    
//    while (DEF_TRUE) {
//#endif
//        /***********************************************
//        * ������ �������Ź���־��λ
//        */
//        OS_FlagPost ((OS_FLAG_GRP *)&WdtFlagGRP,
//                     (OS_FLAGS     ) WDT_FLAG_LED,
//                     (OS_OPT       ) OS_OPT_POST_FLAG_SET,
//                     (CPU_TS       ) 0,
//                     (OS_ERR      *) &err);
//        /***********************************************
//        * ������ �õ�ϵͳ��ǰʱ��
//        */
//        ticks = OSTimeGet(&err);
//        
//#if ( OSAL_EN == DEF_ENABLED )
        if( task_event & OS_EVT_LED_TICKS ) {
//#else
//#endif
            static  uint8   mode = 0;
            /***********************************************
            * ������ ������ʾ
            */
            while(mode < 9)
            {
                mode++;
                BSP_LED_On(mode);
                osal_start_timerEx( OS_TASK_ID_LED,
                                    OS_EVT_LED_TICKS,
                                    600);
                return ( task_event ^ OS_EVT_LED_TICKS );
            }

            
            /***********************************************
            * ������ MTR�ӿ�ͨѶָʾ,��ͨѶ���ݣ�ָʾ����˸
            */
            //if(sCtrl.Mtr.pch->RxBufByteCtr){
            if(sCtrl.Mtr.ConnectFlag){
                BSP_LED_Toggle(1);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(1);     //��Ӧָʾ�Ƶ�ر�
            }
            
            
            /***********************************************
            * ������ OTR�ӿ�ͨѶָʾ,��ͨѶ���ݣ�ָʾ����˸
            */
            if(sCtrl.Otr.ConnectFlag){
                BSP_LED_Toggle(2);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(2);     //��Ӧָʾ�Ƶ�ر�
            }
            
            /***********************************************
            * ������ DTU���ͨѶָʾ,��ͨѶ���ݣ�ָʾ����˸
            */
            if(sCtrl.Dtu.ConnectFlag){
                BSP_LED_Toggle(3);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(3);     //��Ӧָʾ�Ƶ�ر�
            }
            
            /***********************************************
            * ������ ���ٶ��źţ�ָʾ����˸��������ٶ��źţ�
            * ��ȡ����ֵ��ʱ���㡣
            */
            if(sCtrl.sRec.Myspeed1){
                BSP_LED_Toggle(4);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(4);     //��Ӧָʾ�Ƶ�ر�
            }
            
            /***********************************************
            * ������ ���ٶ��źţ�ָʾ����˸
            * ���ź�ʱ����ȡ����ֵ��ʱ���㡣
            */
            if(sCtrl.sRec.Myspeed2){
                BSP_LED_Toggle(5);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(5);     //��Ӧָʾ�Ƶ�ر�
            }
            
            /***********************************************
            * ������ ���ٶ��źţ�ָʾ����˸
            * ���ź�ʱ����ȡ����ֵ��ʱʱ���㡣
            */
            if(sCtrl.sRec.MyEngRotSpd){
                BSP_LED_Toggle(6);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(6);     //��Ӧָʾ�Ƶ�ر�
            }
            
            /***********************************************
            * ������ �������ź�
            * 
            */
            if(sCtrl.sRec.MyLocoWorkState){
                BSP_LED_Toggle(7);  //��Ӧָʾ�Ƶ���
            }else{
                BSP_LED_Off(7);     //��Ӧָʾ�Ƶ�ر�
            }
            
            /***********************************************
            * ������ ����ָʾ��
            */
            BSP_LED_Toggle(8);
//            LedWorkTimes[8] = LED_TOGGLE_CNT;

            /***********************************************
            * ������ ���ݹ���������������Ӧ��ָʾ��
            */
//            for(uint8 i=1;i<BSP_LED_NUM+1;i++){
//                if(LedWorkTimes[i]){
//                    LedWorkTimes[i]--;
//                    BSP_LED_Toggle(i);  //��Ӧָʾ�Ƶ���
//                }else{
//                    BSP_LED_Off(i);     //��Ӧָʾ�Ƶ�ر�
//                }
//            }

            /***********************************************
            * ������ ��ʱ������
            */
            osal_start_timerEx( OS_TASK_ID_LED,
                                OS_EVT_LED_TICKS,
                                100);
            return ( task_event ^ OS_EVT_LED_TICKS );
        }
        
        return  task_event;
}


/*******************************************************************************
 * ��    �ƣ�APP_LedInit
 * ��    �ܣ������ʼ��
 * ��ڲ�������
 * ���ڲ�������
 * ���� ���ߣ�redmorningcn.
 * �������ڣ�2017-05-15
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void TaskInitLed(void)
{    
//    /***********************************************
//    * ������ ��ʼ���������õ������Ӳ��
//    */
//    BSP_LedInit();

    /***********************************************
    * ������ �ڿ��Ź���־��ע�᱾����Ŀ��Ź���־
    */
    //WdtFlags |= WDT_FLAG_LED;
    /*************************************************
    * �����������¼���ѯ
    */
//    for(uint8 i = 0; i< 8;i++)
//    {
//        LedWorkTimes[i] = 0;
//    }
//    
    osal_start_timerEx( OS_TASK_ID_LED,
                        OS_EVT_LED_TICKS,
                        1000);
}

/*******************************************************************************
 * 				                    end of file                                *
 *******************************************************************************/
#endif