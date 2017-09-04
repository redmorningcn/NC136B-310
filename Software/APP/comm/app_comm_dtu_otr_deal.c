/*******************************************************************************
*   Filename:       app_comm_dtu_otr_deal.c
*   Revised:        All copyrights reserved to redmorningcn.
*   Revision:       v1.0
*   Writer:	        redmorningcn.
*
*   Description:    ˫��ѡ�� dtu �� Ctrl + H, ��ѡ Match the case, Replace with
*                   ������Ҫ�����֣���� Replace All
*                   ˫��ѡ�� Dtu �� Ctrl + H, ��ѡ Match the case, Replace with
*                   ������Ҫ�����֣���� Replace All
*                   ˫��ѡ�� DTU �� Ctrl + H, ��ѡ Match the case, Replace with
*                   ������Ҫ�����֣���� Replace All
*                   �� app_cfg.h ��ָ��������� ���ȼ�  �� APP_TASK_COMM_PRIO     ��
*                                            �� �����ջ�� APP_TASK_COMM_STK_SIZE ����С
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
#include <app_comm_protocol.h>
#include <app_ctrl.h>
#include <app.h>
#include <os_cfg_app.h>


#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_comm_dtu_otr__c = "$Id: $";
#endif

#define APP_TASK_COMM_EN     DEF_ENABLED
#if APP_TASK_COMM_EN == DEF_ENABLED
/*******************************************************************************
* CONSTANTS
*/

/*******************************************************************************
* MACROS
*/
#define CYCLE_TIME_TICKS            (OS_TICKS_PER_SEC * 1)

/*******************************************************************************
* TYPEDEFS
*/

#define		DATA_CARD           0x0001			//���ݿ�-----��ʱδ��
#define		DENSITY_CARD		0x0020			//�ܶȿ�
#define		MODEL_CARD			0x0040			//ģ�Ϳ�-----��ʱδ��
#define		TIME_CARD           0x0100			//ʱ�俨-----
#define		COM_MODEL_CARD	    0x0100		    //����ģ�Ϳ�-��ʱδ��
#define		HIGHT_CARD			0x0200			//�߶ȿ�-----
#define		COPY_CARD           0x0400			//���ƿ�-----��ʱδ��
#define		MODEL_SELECT_CARD	0x1000			//ģ��ѡ��-
#define		FIX_CARD            0x2000			//װ����-----
#define		COPY_FRAM_CARD	    0x4000			//���縴�ƿ�-��ʱδ��
#define		SET_DATA_CARD		0x0080			//������-----��ʱδ��
#define		DEBUG_CARD			0x0800			//���Կ�-----��ʱδ��

#define		EXPAND_CARD			0x8000			//��չ��-----��ʱδ��

#define		DATA_CARD_DIS		0x10000			//���ݿ�ָʾ
#define		DATA_CARD_FIN		0x20000			//���ݿ�����
#define		SYS_RUN_PARA		0x40000			//ϵͳ������--��δʹ��
#define		CLEAR_ALL			0x80000			//���㿨�����ݼ�¼����

#define		RST_SYS				0x100000		//��λָ��
#define		CALC_PARA           0x200000		//����б��

#define    OIL_BOX_MODEL_ADDR				2000    //����ģ�ʹ洢��ַ
/*******************************************************************************
* LOCAL VARIABLES
*/

/*******************************************************************************
* GLOBAL VARIABLES
*/

/***********************************************
* ������ ��ʱ������
*/

/***********************************************
* ������ ��ʱ���ص�����
*/


/*******************************************************************************
* LOCAL FUNCTIONS
*/
uint8   comm_record_send_one(StrDevDtu * sDtu,uint8 addrnum);
void    comm_record_send(StrDevDtu * sDtu,uint8 addrnum);
void    comm_para_flow(StrDevDtu * sDtu,uint8 addrnum);
void    Restart(void);



/*******************************************************************************
* GLOBAL FUNCTIONS
*/

/*******************************************************************************
* EXTERN VARIABLES
*/

/*******************************************************************************
* EXTERN FUNCTIONS
*/
uint8   FRAM_StoreRecNumMgr(StrRecNumMgr  *SRecNumMgr);
uint8   FRAM_StoreOilPara(StrOilPara  *SOilPara);
void    BSP_DispClrAll(void);
uint8   FRAM_StoreProductInfo(StrProductInfo  *sProductInfo);
uint8   ReadFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen);            
uint8   WriteFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen);            
void    GetOilPara(void);
void    SetDispNow(void);
uint8   comm_tinyrec_send(StrDevOtr * sOtr,uint8    addrnum);

/*******************************************************************************/

extern  stcSysCtrl  sCtrl;

/*******************************************************************************
* ��    �ƣ� comm_para_flow
* ��    �ܣ� �����������ݾ���������в���
*            
* ��ڲ����� �����豸���ݽṹ
* ���ڲ����� ��
* ���� ���ߣ� redmorningcn.
* �������ڣ� 2017-05-19
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ���񴴽�������Ҫ��app.h�ļ�������
*******************************************************************************/
void    comm_para_flow(StrDevDtu * sDtu,uint8 addrnum)
{
    stcTime     sTime;
    uint8       i = 0;
    uint32      modelrecvnum =0;
    uint32      tmp32;
    static     uint32      modelstoreaddr = 0;
    
    BSP_DispClrAll();                               //��ԭ��ʾֵ��������ʾ�趨ֵ                 
    
    switch (sDtu->RxCtrl.DataCode)  
    {
        //�����ܶ�
    case    DENSITY_CARD: 
        sCtrl.SOilPara.Density = sDtu->Rd.Density;          
        
        FRAM_StoreOilPara((StrOilPara *)&sCtrl.SOilPara);   //�����ݡ��ؼ����ݴ洢ʱ����
        
        uprintf("%8d",sCtrl.SOilPara.Density);   //������ʾ�趨ֵ 
        
        break;
        
        //����ʱ��
    case    TIME_CARD:                
        
        WriteTime(sDtu->Rd.sTime);          
        ReadTime((stcTime *)&sTime);
        
        uprintf("%02d-%02d-%02d",sTime.Year
                ,sTime.Month
                    ,sTime.Date
                        );     
        uprintf("%02d-%02d-%02d",sTime.Hour
                ,sTime.Min
                    ,sTime.Sec
                        );               
        break;
        
        //�߶ȿ�
    case    HIGHT_CARD:  
        //�߶�ֵ�����ۼ�
        sCtrl.SOilPara.Hig += sDtu->Rd.Hig;
        if(sCtrl.SOilPara.Hig  > 500)
            sCtrl.SOilPara.Hig = 500;
        
        if(sCtrl.SOilPara.Hig  < -500)
            sCtrl.SOilPara.Hig = -500;
        
        FRAM_StoreOilPara((StrOilPara *)&sCtrl.SOilPara);   //�����ݡ��ؼ����ݴ洢ʱ����
        
        uprintf("%8d",sCtrl.SOilPara.Hig);     
        
        break;
        
        //ģ��ѡ��
    case    MODEL_SELECT_CARD:   
        sCtrl.SOilPara.ModelNum = sDtu->Rd.ModelNum;//ѡ���ģ�ͱ��
        
        FRAM_StoreOilPara((StrOilPara *)&sCtrl.SOilPara);   //�����ݡ��ؼ����ݴ洢ʱ����
        
        uprintf("%8d",sCtrl.SOilPara.ModelNum);      //������ʾ�趨ֵ 
        break;
        
        //���ͳ���
    case    FIX_CARD: 
        sCtrl.sProductInfo.sLocoId.Num = sDtu->Rd.sLocoId.Num;
        sCtrl.sProductInfo.sLocoId.Type = sDtu->Rd.sLocoId.Type;
        
        FRAM_StoreProductInfo((StrProductInfo *)&sCtrl.sProductInfo);
        
        uprintf("%4d%4d"   ,sCtrl.sProductInfo.sLocoId.Type
                ,sCtrl.sProductInfo.sLocoId.Num
                    );      
        break;
        
        //������ָʾ
    case    DATA_CARD_DIS: 
        i=0;
        while(i < 4)
        {
            uprintf("%8d",i); 
            i++;
        }
        break;
        
        //������ָʾ����
    case    DATA_CARD_FIN: 
        i=0;
        while(i < 4)
        {
            uprintf("    good");  
            uprintf("         ");  
            i++;
        }
        break;
        
        //��������
    case    CLEAR_ALL: 
        sCtrl.sRecNumMgr.Current = 0;
        sCtrl.sRecNumMgr.GrsRead = 0;
        sCtrl.sRecNumMgr.IcRead  = 0;
        
        FRAM_StoreRecNumMgr((StrRecNumMgr *)&sCtrl.sRecNumMgr);
        
        uprintf("    CALL");  
        
        break;
        
        //װ�ø�λ
    case    RST_SYS: 
        Restart();                      //����ϵͳ
        break;
        
        //����б��
    case    CALC_PARA: 
        //б�ʾ����ؼƵ�Ч��
        sCtrl.SOilPara.Slope = (sCtrl.SOilPara.Slope  * sDtu->Rd.Slope)/10000;
        
        //0.1~2
        if(sCtrl.SOilPara.Slope >20000 || sCtrl.SOilPara.Slope < 1000)
            sCtrl.SOilPara.Slope = 10000;
        
        FRAM_StoreOilPara((StrOilPara *)&sCtrl.SOilPara);   //�����ݡ��ؼ����ݴ洢ʱ����
        
        uprintf("%d",sCtrl.SOilPara.Slope);         //������ʾ�趨ֵ 
        break;
        
        /***********************************************
        * ������ ��������ģ�͡�
        *   IC ��ģ�����IC����IC������Ӧ��ģ�͡�  
        *   ����ÿ200ms�������ݣ���Ŵ�0��ʼ�ۼӡ�
        ���ݷ�����ɺ����Ϊ0xffffffff��
        */    
        
    case    MODEL_CARD: 
        //ģ�����ݽ������
        memcpy((uint8  *)&modelrecvnum,(uint8 *)&sDtu->Rd.Buf[0],sizeof(modelrecvnum));
        
        if( modelrecvnum == 0 )                 //��ʼ    
            modelstoreaddr = 0;
        
        if(sDtu->RxCtrl.Len < sizeof(modelrecvnum))
            break;
        //������յ�������
        WriteFM24CL64(   OIL_BOX_MODEL_ADDR+modelstoreaddr,
                      (uint8 *)&sDtu->Rd.Buf[sizeof(modelrecvnum)], 
                      sDtu->RxCtrl.Len - sizeof(modelrecvnum));
        //���ַ�ۼ�
        modelstoreaddr += (sDtu->RxCtrl.Len - sizeof(modelrecvnum));
        
        //ָʾ����
        //uprintf("   ...");
        if(modelrecvnum == 0xffffffff)  //������ָʾ
        {
            uprintf("");
            uprintf("boX");	
            uprintf("boX");		
            GetOilPara();
        }else
        {
            uprintf("o..%2d",modelrecvnum);
        }
        
        SetDispNow(); //������ʾ
        
        
        if(sDtu->pch->PortNbr == 2)
        {
            osal_start_timerRl( OS_TASK_ID_TMR, 
                               OS_EVT_TMR_OTR, 
                               OS_TICKS_PER_SEC*10 );          //ͳ��װ�ú����߷���ģ�鶨ʱ��  10s
        }
        
        if(sDtu->pch->PortNbr == 3)
        {
            osal_start_timerRl( OS_TASK_ID_TMR, 
                               OS_EVT_TMR_DTU, 
                               OS_TICKS_PER_SEC*10 );          //ͳ��װ�ú����߷���ģ�鶨ʱ��  10s
        }
        break;
        
        //����
    case    DATA_CARD: 
        
        memcpy((uint8 *)&tmp32,sDtu->Rd.Buf,sizeof(tmp32));     //������ˮ��
        if(sDtu->RxCtrl.SourceAddr == SLAVE_ADDR_DTU)           //����ͨ�������
        {
            if(sCtrl.sRecNumMgr.GrsRead  > tmp32){
                sCtrl.sRecNumMgr.GrsRead = tmp32;               //ָ��λ��ȡ����
            }
            
            comm_record_send_one(sDtu,addrnum);                 
            
            FRAM_StoreRecNumMgr((StrRecNumMgr *)&sCtrl.sRecNumMgr);         //�����¼��
            
            sCtrl.sRecNumMgr.GrsRead++;
            
        }else if(sDtu->RxCtrl.SourceAddr == SLAVE_ADDR_OTR)     //IC��
        {
            if(sCtrl.sRecNumMgr.IcRead  > tmp32){
                sCtrl.sRecNumMgr.IcRead = tmp32;                //ָ��λ��ȡ����
            }
            
            comm_record_send_one(sDtu,addrnum);                 //ָ��λ��ȡ����   
            
            FRAM_StoreRecNumMgr((StrRecNumMgr *)&sCtrl.sRecNumMgr); //�����¼��
            
            sCtrl.sRecNumMgr.IcRead++;           
            
            //����������ʱ��
            if(sCtrl.sRecNumMgr.IcRead < sCtrl.sRecNumMgr.Current ){
                osal_start_timerRl( OS_TASK_ID_TMR, 
                                   OS_EVT_TMR_OTR, 
                                   OS_TICKS_PER_SEC/2 );          //ͳ��װ�ú����߷���ģ�鶨ʱ��  10s
            }
            
        }
    }
}

/*******************************************************************************
* ��    �ƣ� comm_record_send_one
* ��    �ܣ� ����one�����ݼ�¼
* ��ڲ����� �����豸���ݽṹ
* ���ڲ����� ��
* ���� ���ߣ� redmorningcn.
* �������ڣ� 2017-05-19
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ���񴴽�������Ҫ��app.h�ļ�������
*******************************************************************************/
uint8    comm_record_send_one(StrDevDtu * sDtu,uint8    addrnum)
{
    
    //��¼��Ϊ0����δ�������ݡ�����ͨѶ״̬�ж�
    if( sCtrl.sRecNumMgr.Current == 0 )                                   
    {
        return 0;
    }
    /***********************************************
    * ������ ��¼�ź������жϡ��ѷ�����<��ǰ���� ��������
    * 
    */ 
    if(sDtu->ConnCtrl[addrnum].SlaveAddr == SLAVE_ADDR_DTU)
    {
        if(sCtrl.sRecNumMgr.Current <= sCtrl.sRecNumMgr.GrsRead )           //�ѷ��ͼ�¼�űȵ�ǰ��¼�Ŵ󣬽����쳣����
        {
            sCtrl.sRecNumMgr.GrsRead = 0;
            if(sCtrl.sRecNumMgr.Current)
                sCtrl.sRecNumMgr.GrsRead = sCtrl.sRecNumMgr.Current - 1;    //�����Ч��¼��ֵ     
            
            FRAM_StoreRecNumMgr((StrRecNumMgr *)&sCtrl.sRecNumMgr);         //�����¼��
        }
        
        sCtrl.Dtu.ConnCtrl[addrnum].SendFramNum++;
        
        /***********************************************
        * ������ ���ݼ�¼׼��,���ݼ�¼��ȡ���ݼ�¼��
        * 
        */ 
        ReadFlshRec((stcFlshRec *)&sDtu->Wr.sRec,
                    sCtrl.sRecNumMgr.GrsRead);
        
        //���¸���ʱ������ֵ��osal_start_timerRl�����Զ���ֵ��
        osal_start_timerRl( OS_TASK_ID_TMR, 
                           OS_EVT_TMR_DTU, 
                           OS_TICKS_PER_SEC*10 );  //ͳ��װ�ú����߷���ģ�鶨ʱ��  10s
    }
    
    if(sDtu->ConnCtrl[addrnum].SlaveAddr == SLAVE_ADDR_OTR)
    {
        if(sCtrl.sRecNumMgr.Current <= sCtrl.sRecNumMgr.IcRead )           //�ѷ��ͼ�¼�űȵ�ǰ��¼�Ŵ󣬽����쳣����
        {
            sCtrl.sRecNumMgr.IcRead = 0;
            if(sCtrl.sRecNumMgr.Current)
                sCtrl.sRecNumMgr.IcRead = sCtrl.sRecNumMgr.Current - 1;    //�����Ч��¼��ֵ     
            
            sCtrl.Otr.ConnCtrl[addrnum].SendFramNum++;
            FRAM_StoreRecNumMgr((StrRecNumMgr *)&sCtrl.sRecNumMgr);         //�����¼��
        }
        
        /***********************************************
        * ������ ���ݼ�¼׼��,���ݼ�¼��ȡ���ݼ�¼��
        * 
        */ 
        ReadFlshRec((stcFlshRec *)&sDtu->Wr.sRec,
                    sCtrl.sRecNumMgr.IcRead);
        
        osal_start_timerRl( OS_TASK_ID_TMR, 
                           OS_EVT_TMR_OTR, 
                           OS_TICKS_PER_SEC*10 );  //ͳ��װ�ú����߷���ģ�鶨ʱ��  10s
    }
    
    
    //��ʱֵ����SLAVE_ADDR_DTU ������
    CSNC_SendData(sDtu->pch,                                    //DTU ��PCH�����ںţ��շ����Ƶȵײ���Ϣ
                  sDtu->ConnCtrl[addrnum].MasterAddr,           //Դ��ַ��
                  sDtu->ConnCtrl[addrnum].SlaveAddr,            //Ŀ���ַ
                  sDtu->ConnCtrl[addrnum].SendFramNum,          //֡��� �����ڽ������ۼ�
                  0,                                            //������
                  (uint8 *)&sDtu->Wr.sRec,                      //������
                  sizeof(sDtu->Wr.sRec)                         //���ͳ���
                      );
    
    
    
    return 1;
}


/*******************************************************************************
* ��    �ƣ� comm_record_send
* ��    �ܣ� ͨѶ���ݴ���
*            �Ȳ�ѯ�ѷ��ͼ�¼��Ȼ���͸ü�¼����¼�ż�1��֡�ż�1����ʼ��¼��
��1��ʼ��  
*              ��ͨ��֡���ж�ͨѶ�Ƿ������ȷ��
* ��ڲ����� �����豸���ݽṹ
* ���ڲ����� ��
* ���� ���ߣ� redmorningcn.
* �������ڣ� 2017-05-19
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ���񴴽�������Ҫ��app.h�ļ�������
*******************************************************************************/
void    comm_record_send(StrDevDtu * sDtu,uint8 addrnum)
{
    /***********************************************
    * ������ ���ͺͽ��յļ�¼�������������ˮ�ż�1
    *       �ٸ������������������ݡ�
    * 
    */                         
    if(sDtu->RxCtrl.FramNum == sDtu->ConnCtrl[addrnum].SendFramNum){
        sDtu->ConnCtrl[addrnum].SendFramNum++;    //������ȷ����ż�1
        sCtrl.sRecNumMgr.GrsRead++;
        
        CPU_SR  cpu_sr;
        CPU_CRITICAL_ENTER() ;
        FRAM_StoreRecNumMgr((StrRecNumMgr *)&sCtrl.sRecNumMgr); //�����¼��
        CPU_CRITICAL_EXIT() ;
        
        if(sCtrl.sRecNumMgr.GrsRead < sCtrl.sRecNumMgr.Current) //���ݻ�δ������ɡ��յ����ݼ����͡�
        {
            comm_record_send_one(sDtu,addrnum);                 //�������ݼ�¼��
            //����������ʱ��ʱ��
            osal_start_timerRl( OS_TASK_ID_TMR, 
                               OS_EVT_TMR_DTU, 
                               OS_TICKS_PER_SEC*10 );          //ͳ��װ�ú����߷���ģ�鶨ʱ��  10s
        }
        
    }
}


/*******************************************************************************
* 				end of file
*******************************************************************************/
#endif


