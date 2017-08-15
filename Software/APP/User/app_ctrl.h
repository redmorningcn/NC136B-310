#ifndef	APP_CTRL_H
#define	APP_CTRL_H
/*******************************************************************************
 *   Filename:       app_ctrl.h
 *   Revised:        $Date: 2009-01-08	20:15 (Fri) $
 *   Revision:       $
 *	 Writer:		 Wuming Shen.
 *
 *   Description:
 *
 *   Notes:
 *					QQ:276193028
 *     				E-mail:shenchangwei945@163.com
 *
 *   All copyrights reserved to Wuming Shen.  �ִ����������Ǳ��о���
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#include <global.h>
#include <app.h>
//#include <bsp_key.h>
//#include <bsp_max7219.h>
//#include <protocol.h>
#include <os.h>
#include <osal.h>
#include <mb.h>
#include <RecDataTypeDef.h>
#include <CardDataTypeDef.h>


#ifdef   APP_GLOBALS
#define  APP_EXT
#else
#define  APP_EXT  extern
#endif
/*******************************************************************************
 * CONSTANTS
 */

 /*******************************************************************************
 * 				            ϵͳ������غ궨��                                  *
 *******************************************************************************/

/***************************************************
* ������ RFӦ������֡���л���
*/
#define AppMsgQ                            10
#define AppMsgQSize                        10
 
/***************************************************
* ������ ����洢�豸����
*/
#define INTNER_FLASH                        0
#define INTNER_EEPROM                       1
#define EXTERN_EEPROM                       2
#define STORAGE_TYPE                        EXTERN_EEPROM


//#define COMM_EVT_FLAG_HEART               (1 << 0)// ����������
//#define COMM_EVT_FLAG_RESET               (1 << 1)// WIFI��λ
//#define COMM_EVT_FLAG_CONNECT             (1 << 2)// WIFI����
//#define COMM_EVT_FLAG_RECV                (1 << 3)// ���ڽ���
//#define COMM_EVT_FLAG_REPORT              (1 << 4)// �ϱ���Ϣ
//#define COMM_EVT_FLAG_CLOSE               (1 << 5)// �Ͽ�
//#define COMM_EVT_FLAG_TIMEOUT             (1 << 6)// ��ʱ
//#define COMM_EVT_FLAG_CONFIG              (1 << 7)// ����
//#define COMM_EVT_FLAG_IAP_START           (1 << 8)// IAP��ʼ
//#define COMM_EVT_FLAG_IAP_END             (1 << 9)// IAP����

#define COMM_EVT_FLAG_MTR_RX                (1 << 0)	// MTR �����¼�
#define COMM_EVT_FLAG_DTU_RX                (1 << 1)	// DTU �����¼�
#define COMM_EVT_FLAG_OTR_RX                (1 << 2)	// OTR �����¼�
#define COMM_EVT_FLAG_MTR_TIMEOUT           (1 << 3)	// MTR ������ʱ����ʱ����ʹ��
#define COMM_EVT_FLAG_DTU_TIMEOUT           (1 << 4)	// DTU ������ʱ����ʱ����ʹ��
#define COMM_EVT_FLAG_OTR_TIMEOUT           (1 << 5)	// OTR ������ʱ����ʱ����ʹ��


#define OS_EVT_FLAG_00                    (1 << 0)// 
#define OS_EVT_FLAG_01                    (1 << 1)// 
#define OS_EVT_FLAG_02                    (1 << 2)// 
#define OS_EVT_FLAG_03                    (1 << 3)// 
#define OS_EVT_FLAG_04                    (1 << 4)// 
#define OS_EVT_FLAG_05                    (1 << 5)// 
#define OS_EVT_FLAG_06                    (1 << 6)// 
#define OS_EVT_FLAG_07                    (1 << 7)// 
#define OS_EVT_FLAG_08                    (1 << 8)// 
 
/*******************************************************************************
 * 				            OSAL��ض���                                       *
 *******************************************************************************/
/*******************************************************************************
* ������ OSAL�������ȼ�����
*/
#define	OS_TASK_PRO_DISP                OS_TASK_PRIO_HIGHEST - 0
#define	OS_TASK_PRO_TMR                 OS_TASK_PRIO_HIGHEST - 1
#define	OS_TASK_PRO_CALC                OS_TASK_PRIO_HIGHEST - 2
#define	OS_TASK_PRO_SPEED               OS_TASK_PRIO_HIGHEST - 3
#define	OS_TASK_PRO_STORE               OS_TASK_PRIO_HIGHEST - 4
#define	OS_TASK_PRO_TIMER               OS_TASK_PRIO_HIGHEST - 5
#define	OS_TASK_PRO_LED                 OS_TASK_PRIO_HIGHEST - 6


/***************************************************
* ������ OSAL����ID����
*/
#define OS_TASK_ID_DISP                 0x00
#define OS_TASK_ID_TMR                  0x01
#define OS_TASK_ID_CALC		            0x02
#define OS_TASK_ID_SPEED	            0x03
#define OS_TASK_ID_STORE		        0x04
#define OS_TASK_ID_TIMRE		        0x05
#define OS_TASK_ID_LED		            0x06


/*******************************************************************************
* ������ OSAL�¼�����
*/
/***************************************************
* ������ OSAL�¼����壺TMR�����¼�
*/
#define OS_EVT_TMR_TICKS                0X00000001
#define OS_EVT_TMR_MSEC                 0X00000002
#define OS_EVT_TMR_SEC                  0X00000004
#define OS_EVT_TMR_MIN                  0X00000008
#define OS_EVT_TMR_DEAL                 0X00000010
#define OS_EVT_TMR_MTR                  0X00000020
#define OS_EVT_TMR_DTU                  0X00000040
#define OS_EVT_TMR_OTR                  0X00000080
/***************************************************
* ������ OSAL�¼����壺LED�����¼�
*/
#define OS_EVT_LED_TICKS                0X00000001
#define OS_EVT_LED_1                    0X00000002
#define OS_EVT_LED_2                    0X00000004
#define OS_EVT_LED_3                    0X00000008
#define OS_EVT_LED_4                    0X00000010
#define OS_EVT_LED_5                    0X00000020
#define OS_EVT_LED_6                    0X00000040
#define OS_EVT_LED_7                    0X00000080

/***************************************************
* ������ OSAL�¼����壺DISP�����¼�
*/
#define OS_EVT_DISP_TICKS                0X00000001
#define OS_EVT_DISP_INIT                 0X00000002
#define OS_EVT_DISP_2                    0X00000004
#define OS_EVT_DISP_3                    0X00000008
#define OS_EVT_DISP_4                    0X00000010
#define OS_EVT_DISP_5                    0X00000020
#define OS_EVT_DISP_6                    0X00000040
#define OS_EVT_DISP_7                    0X00000080


/***************************************************
* ������ OSAL�¼����壺STORE �����¼�
*/
#define OS_EVT_STORE_TICKS              0X00000001
#define OS_EVT_STORE_INIT               0X00000002
#define OS_EVT_STORE_2                  0X00000004
#define OS_EVT_STORE_3                  0X00000008
#define OS_EVT_STORE_4                  0X00000010
#define OS_EVT_STORE_5                  0X00000020
#define OS_EVT_STORE_6                  0X00000040
#define OS_EVT_STORE_7                  0X00000080

/***************************************************
* ������ OSAL�¼����壺Calc �����¼�
*/
#define OS_EVT_CALC_TICKS              0X00000001
#define OS_EVT_CALC_INIT               0X00000002
#define OS_EVT_CALC_2                  0X00000004
#define OS_EVT_CALC_3                  0X00000008
#define OS_EVT_CALC_4                  0X00000010
#define OS_EVT_CALC_5                  0X00000020
#define OS_EVT_CALC_6                  0X00000040
#define OS_EVT_CALC_7                  0X00000080

/***************************************************
* ������ OSAL�¼����壺speed �����¼�
*/
#define OS_EVT_SPEED_TICKS              0X00000001
#define OS_EVT_SPEED_INIT               0X00000002
#define OS_EVT_SPEED_2                  0X00000004
#define OS_EVT_SPEED_3                  0X00000008
#define OS_EVT_SPEED_4                  0X00000010
#define OS_EVT_SPEED_5                  0X00000020
#define OS_EVT_SPEED_6                  0X00000040
#define OS_EVT_SPEED_7                  0X00000080

/*******************************************************************************
 * 				            ��������                                           *
 *******************************************************************************/
/***************************************************
* ������ ʱ�䶨��
*/
#define FILTER_LIFE_SAVE_TIME           30          // ����
#define FILTER_LIFE_TIME               (3*30*24*60/1)// ����(3����)
//#define FILTER_LIFE_SAVE_TIME           1          // ����
//#define FILTER_LIFE_TIME               (60/FILTER_LIFE_SAVE_TIME)        // ����(24Сʱ��������)

/*******************************************************************************
 * TYPEDEFS
 */
#define PARA_TYPE_INT08S                0
#define PARA_TYPE_INT08U                1
#define PARA_TYPE_INT16S                2
#define PARA_TYPE_INT16U                3

#define PARA_TYPE   PARA_TYPE_INT16S
__packed
typedef struct {
    
#if     ( PARA_TYPE == PARA_TYPE_INT08S )
    INT08S      Min;
    INT08U      Max;
#elif   ( PARA_TYPE == PARA_TYPE_INT08U )
    INT08U      Min;
    INT08U      Max;
#elif   ( PARA_TYPE == PARA_TYPE_INT16S )
    INT16S      Min;
    INT16S      Max;
#elif   ( PARA_TYPE == PARA_TYPE_INT16U )
    INT16U      Min;
    INT16U      Max;
#else
    INT08S      Min;
    INT08U      Max;
#endif
} StrParaRange;

//
//
//typedef struct _stcFlshRec   	//�����ͳ߼�¼���ݽṹ
//{
//	uint32	StoreCnt;         	//�洢��ˮ��    		4   ׷�ټ�¼��
//
//	uint8	RecTypCod;       	//��¼����          	1   �������ͣ��������ϰ࿨���°࿨�����ݼ�¼��
//	uint8	RelSpeed[3];      	//ʵ��              	3   D9~D0��ʵ�٣�D19~D10��Ԥ��
//
//	uint8	Time[4];          	//��/��/ʱ/��/��      	4   D5~D0:��,D11~D6:��,D16~D12:ʱD21~D17���գ�
//	                               	//                      	D25~D22���� ;D26~D31:��
//	uint8	LocoTyp;          	//�����ͺ�          	1   
//	uint8	E_LocoTyp;        	//�����ͺ���չ�ֽ�  	1   �����ͺ������ֽ�,������LKJ2000��ʽ��ͬ
//	uint8 	LocoNum[2];       	//������            	2	
//
//	uint8 	TrainTyp[4];     	//��������          	4   ��������,���α����·���(����[2005]72���ļ�)
//	                             	//                      	�ĳ��������ʶ��,������LKJ2000��ʽ��ͬ
//	                             	
//	uint8	TrainNum[3];     	//�������ֲ���      	3   ���α����·���(����[2005]72����)�ĳ������ݲ���
//	uint8 	Car_Truck;       	//��/������/��       	1   D0��0/1 �� ��/��   D1��0/1 �� ��/��   
//	 
//	uint8 	VoitureCnt;       	//����              	1	
//	uint8 	KmMark[3];   		//�����            	3   ��λ����
//
//	uint8 	Weight[2];       	//����              	2
//	uint8 	PlanLen[2];       	//�Ƴ�              	2   ��λ��0.1   
//
//	uint8 	MstDriverNum[2];  	//˾����            	2	
//	uint8 	E_MstDriverNum; 	//˾������չ�ֽ�    	1   
//	uint8 	E_SlvDriverNum;   	//��˾������չ�ֽ�  	1   
//
//	uint8 	SlvDriverNum[2];  	//��˾����          	2   
//	uint8	DriverUnitNum[2];  	//˾����λ���      	2   //����Ψһȷ��˾��
//
//	uint8 	RoadNum;          	//���κ�(��·��)     	1	
//	uint8  	RelRoadNum;     	//ʵ�ʽ�·��         	1   �����ʽ��LKJ2000��ͬ   
//	uint8  	StationNum;     	//��վ��            	1
//	uint8  	E_StationNum;   	//��վ����չ�ֽ�    	1   ��վ����չ�ֽ�
//
//	uint8 	SignalTyp;        	//�źŻ�����        	1   B2-B0 :2-��վ,3-��վ,4-ͨ��,5-Ԥ��,6-����
//	uint8 	LocoSign;        	//�����ź�          	1   B4 = 0/1  ����/���;   B3~B0 0-�޵�,1-��,2-��, 
//	                            	//                      	3-˫��,4-���,5-��,6-��,7-�̻�,8-��
//	uint8 	LocoWorkState;    	//��������          	1   b0-��λ,B1-���,B2-��ǰ,B3-�ƶ�,B4-ǣ��
//	uint8 	LocoState;      	//װ��״̬          	1   B0 = 1/0 - ����/���; B2 = 1/0 - ����/�ǵ���
//
////	uint8 	SignalNum[2];      	//�źŻ����        	2   
////	uint8 	LocoPipePress[2]; 	//�г���ѹ          	2   B9-B0:��ѹ(��λ:1kPa)
//
//	uint16	Myspeed1;			//�Բ��ٶ�1				2
//	uint16	Myspeed2;			//�Բ��ٶ�2				2	
//	  
//	uint32 	MstDip;           	//��������          	4   ���ͳ�����(���ӻ�����ʱΪ��������,����Ϊ����������)
//
////	uint32 	SlvDip;           	//�ӻ�����          	4   ���ͳ�����(���ӻ�����ʱΪ�ӻ�����,���������ֵΪ��)
//	uint32	MyKileMeter;		//�����				4
//		
//	int32 	MyMstLocoPower;     //������������       	4   ��������豸����
//
////	int32 	SlvLocoPower;     	//�ӻ���������       	4   �ӻ�����豸����
//	uint32	MyPower;			//�ۼƵ���				4	
//	//090901
// 	//uint16	MstDip1Prs;        	//ѹǿ            		2   �����ͳ�1ѹǿֵ
//	//uint16	MstDip2Prs;        	//ѹǿ            		2   �����ͳ�2ѹǿֵ
//	int16		Myhig1;				//Һλ�߶�1				2	
//	int16		Myhig2;				//Һλ�߶�2				2							
//
//	uint16	SlvDip1Prs;       	//ѹǿ            		2   �ӻ��ͳ�1ѹǿֵ
//	uint16 	SlvDip2Prs;       	//ѹǿ            		2   �ӻ��ͳ�2ѹǿֵ
//	
//	uint8  	MyYear;           	//��      				1   װ��ʱ�����
//	uint8 	MyMonth;         	//��      				1   װ��ʱ�����
//	uint8 	MyData;          	//��      				1   װ��ʱ�����
//	uint8 	MyHour;           	//ʱ      				1   װ��ʱ���ʱ
//	
//	uint8 	MyMinute;     		//��      				1   װ��ʱ��ķ�
//	uint8 	MySecond;       	//��       				1   װ��ʱ�����
//	uint16	MstDensity;			//�ܶ�							2	����ȼ���ܶ�
//	
////	uint16	SlvDensity;			//�ܶ�						2	�ӻ�ȼ���ܶ�
////	uint16	GpsHeight;			//�߶�						2	�����߶�
//	int16		MyAddspeed;			//�Բ���ٶ�					2
//	uint16	MyDip;				//�Բ�����							2
//		
//	int32	GpsLongitude;		//����					4	��������
//	int32	GpsLatitude;		//γ��					4	����γ��
//		
//	int16	MstEngRotSpd;		//�������ͻ�ת��		2	�������ͻ�ת��
////	int16	SlvEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��
//	int16	MyEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��
//
//	//�������� 
//	//���Լ�ʱ��оƬ���׵�������
//	uint16 	JcRealType;			//�����ͺ�				2   �ⲿ���õĻ����ͺ�
//	uint16 	JcRealNo;			//�������				2   �ⲿ���õĻ������
//	
////	uint16 	MstPotPress;		//������ѹ				2	Ԥ���Ӽ��	
////	uint16 	SlvPotPress;		//�ӻ���ѹ				2	Ԥ���Ӽ��	
//	uint16	MyDip1Tmp;	  		//�ͳ�1�¶�
//	uint16	MyDip2Tmp;			//�ͳ�2�¶�
//		
////	uint16 	MstPot1;			//��������1				2	Ԥ���Ӽ��	
////	uint16 	MstPot2;			//��������2				2	Ԥ���Ӽ��
//	uint16	MyDip1Den;
//	uint16	MyDip2Den;	
//
////	uint16 	SlvPot1;			//�ӻ�����1				2	Ԥ���Ӽ��		
////	uint16 	SlvPot2;			//�ӻ�����2				2	Ԥ���Ӽ��
//	uint16	MyDip1Err;
//	uint16	MyDip2Err;
//	
//	uint16 	MaxSpeed;			//����					2	Ԥ���Ӽ��	
////	uint16 	MstOcurrent;		//����ԭ�ߵ���   		2	Ԥ���Ӽ��
//	uint16	ErrNum;				//���й�������			2	
//	
//	
//	uint8	ErrorCode;			//���ϴ���				1   0~255
////	uint8 	DipValChgState;  	//�����仯״̬   		1   �����仯����֣����ͳ�����/��С���仯ƽ�ȡ���΢���������Ҳ���
//	uint8	MyLocoWorkState;	//�Բ����״̬			1
//	//090901
//	uint8	MstDipTemp;			//�¶�					1	�����¶�
//	uint8	OilBoxModel;		//����ģ��				1	�����������
//	
//	uint8	SoftVes;        	//�����汾          	1   
//	uint8	Reserve1;        	//Ԥ��          		1  	
////	uint16	Reserve0;        	//Ԥ��          		2   
//	uint16 	CrcCheck;         	//�洢��У���    		2   Flash��¼�洢CRCУ��
//}stcFlshRec;
//
//


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����װ��ͨѶ�ṹ
//
//�豸��֡������Ч���ݳ���
#define	MTR_COMM_RECV_BUF_LEN	160
//�豸Mtr
/***************************************************
* ������ͳ��ģ��-- ����װ�ã���ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
*/
// �������ݽṹ������-->�ͳ�
__packed
typedef struct {
    INT32U                  Oil;                                // ����	        4	��ֵ��Χ0-9999L  
    INT16S                  Accelerations;                      // ���ٶ�	    2	-9.000-9.000��m/s2��(1000��)
    INT16U                  Speed;                              // �ٶ�	        2	��ֵ0-600��Km/H��
    struct __recv_work__ {                                     	// ��������	    1
    INT08U                  Null     	: 1;   	//              0x01:��λ
    INT08U                  Tow   	: 1;       	 //              0x02:ǣ��
    INT08U                  Brake   	: 1;       	 //              0x04:�ƶ�
    INT08U                  Rsv        	: 5;  	// ������δ����
    } Work;
    INT16U                  Density;                            	// �߶ȼ����ܶ�	2	0.xxxx��/�������ף�10000����
    INT08U                  Rsv[1+10];                         	 // ����	        3
} StrMtrCommSendData;


//���������壬�ɶ�������ͽṹ����
typedef union {
	StrMtrCommSendData	StrSend;
	uint8				Buf[MTR_COMM_RECV_BUF_LEN];
}UniMtrCommSendData;


/***************************************************
* ������ ͳ��ģ��-- ����װ�ã���ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
*/
// Ӧ�����ݽṹ���ͳ�-->����
__packed
typedef struct {
    INT16U                  Hight;                              	// Һλ�߶�	    2	xxx.x���ף�10����
    INT16U                  Density;                            	// �߶ȼ����ܶ�	2	0.xxxx��/�������ף�10000����
//    union __usend_status {
//    StrSenErr               Udat;
//    INT08U                  Dat;
//    } Sts;
    INT08U                  RefLiqTemp;            		// Һ��ο��¶�	1	0.25~63.50�ȣ��ֱ���1-254��ʾ������-49.5~77.0�ȣ��ֱ���1-254��ʾ��100��ʾ0�ȣ�0�����ͣ�255������
    INT16U                  AdcValue[2];                        // Adcֵ
    INT16U                  HightDiff;                          	// �߶Ȳ�	    2	0~1000x0.1mm(���������߶Ȳ�)
    INT16U                  Volume;                             	// ���  	    2	0~10000L(����)
    INT16U                  Weight;                             	// ����	        2	0~10000kg(����)
    INT16S                  Pressure[2];                        // ѹǿ	        2	0~10000pa
    INT16S                  CalcDensity;                        // �����ܶ�     x10000
    INT16S                  Gravity;                            	// ������ٶ�   x10000
    INT16S                  CalcGravity;                        // �������ٶ�   x10000
    //INT08U                  Rsv[2+10];                        // ����	        2	
} StrMtrCommRecvData;

//Ӧ�������壬�ɶ�������ͽṹ����
typedef union {
	StrMtrCommRecvData		sRecv;
	uint8				Buf[MTR_COMM_RECV_BUF_LEN];
}UniMtrCommRecvData;

//������������
//8 Bytes
//#define     COMM_REC_END_FLG        0x01
//#define     COMM_REC_STRAT_FLG      0x02
//

typedef struct {     
    INT08U          DestAddr;       //���յ�ַ      slave  =0xA1\A2	   
    INT08U          SourceAddr;     //Դ��ַ       master   =0x80	   
    INT08U          FramNum;        //֡���
    INT08U			Len;			//������Ч���ݳ���
    INT32U			Code;			//���տ�����
} StrDevMtrRecvCtrl;

//���ӿ�����
// 4 Bytes
typedef struct {     
    uint8          ConnFlg;        //���ӿ���,1���������ӣ�0������������
    uint8			RecvEndFlg;		//���ձ�ʾ��1�����ݽ�����ɣ�0�������ݽ��ա�
    uint8			TimeOut;		//��ʱʱ�䣬��λ1s
    uint8			ErrFlg;		    //�����ʾ������������0�����Ӵ���1
    uint8          SlaveAddr;       //���յ�ַ         slave  =0xCA	   
    uint8          MasterAddr;     //Դ��ַ           master   =0x80	   
    uint8          SendFramNum;    //֡���   
    uint8          SendFlg;        //���ͱ�ʾ�� �����ݷ��ͣ�1�������ݷ��ͣ�0
} StrDevMtrConnCtrl;		

//ͳ��ĳ��ͨѶ���ƽṹ
//128 +128 + 8 + 8 + 4  = 276
#define	COMM_DEV_MTR_CONN_NUM	2	// �豸������A1\A2	
__packed
typedef struct {  
	UniMtrCommRecvData      Rd;				// 160 ����������
	UniMtrCommSendData      Wr;				// 160 ����������

    /***************************************************
    * ������ ���ڿ�����
    */
	StrDevMtrRecvCtrl    	RxCtrl;     // 8		���տ��ƣ�������ǰ���յ��Ŀ�����Ϣ
	StrDevMtrConnCtrl		ConnCtrl[COMM_DEV_MTR_CONN_NUM];
                                        // 4*2	���ӿ��ƣ���ÿ����ַ��Ϊ�������������ӡ�
	
    MODBUS_CH            	*pch;       // 4 	MODBUS���
    
    INT08U                  ConnectTimeOut  : 7;             // ���ӳ�ʱ����������Ϊ��λ
    INT08U                  ConnectFlag     : 1;                // ���ӱ�־
} StrDevMtr;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����߷���װ��ͨѶ�ṹ
//�豸DTU
//
/***************************************************
* ������ ͳ��ģ��--���߷���ģ�飬��ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
*/
// �������ݽṹ  		ͳ��-->����
__packed
typedef union {
	stcFlshRec	sRec;						//���ݼ�¼     128 	
	uint8		Buf[160];					//
} UniDtuCommSendData;

typedef struct {     
 	uint16	Type;				//��������	2	�μ��������ʹ����
 	uint16	Num;				//������		2	
} stcLocoId;
/***************************************************
* ������ ͳ��ģ��--���߷���ģ�飬��ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
*/
// �������ݽṹ		����-->ͳ��		
__packed
typedef union {
	int16		Density;			//DENSITY_CARD   �����ܶ�ֵ   		2     0.xxxx��/�������ף�10000����
	stcTime		sTime;			    //TIME_CARD     ����ʱ��            8     second,minute,hour,data,month,year,crccheck
	int16		Hig;				//HIGHT_CARD    ���ø߶�ֵ          2     0.1mm  (10��)
	stcLocoId   sLocoId;		    //FIX_CARD      ���û�����Ϣ	    4     type,num;
	uint32      Slope;			    //CALC_PARA	    ���ü����б��	    4	(slope/10000);     ������������
    uint8       ModelNum;           //              ģ�ͱ��            1       
	uint8		Buf[160];		    //	
} UniDtuCommRecvData;

//���տ�����
typedef struct {     
    INT08U          DestAddr;       //���յ�ַ      slave  =
    INT08U          SourceAddr;     //Դ��ַ       master   =0x80	   
    INT08U          FramNum;        //֡���
    INT08U			Len;			//������Ч���ݳ���
    INT32U			Code;			//���տ�����
} StrDevDtuRecvCtrl;

//���ӿ����֣�
typedef struct {     
    INT08U          ConnFlg;        //���ӿ���,1���������ӣ�0������������
    INT08U			RecvEndFlg;		//���ձ�ʾ��1�����ݽ�����ɣ�0�������ݽ��ա�
    INT08U			TimeOut;		//��ʱʱ�䣬��λ1s
    INT08U			ErrFlg;		    //�����ʾ������������0�����Ӵ���1

    INT08U          SlaveAddr;       //���յ�ַ      slave  =0xCA	   
    INT08U          MasterAddr;     //Դ��ַ           master   =0x80	   
    INT08U          SendFramNum;    //֡���   
    INT08U          SendFlg;        //���ͱ�ʾ�� �����ݷ��ͣ�1�������ݷ��ͣ�0
} StrDevDtuConnCtrl;		


#define	COMM_DEV_DTU_CONN_NUM	2	// �豸������CA/C1	
__packed
typedef struct {  
	UniDtuCommRecvData	Rd;			//����������
	UniDtuCommSendData	Wr;			//����������

    /***************************************************
    * ������ ���ڿ�����
    */
	StrDevDtuRecvCtrl    	RxCtrl;				//���տ��ƣ�������ǰ���յ��Ŀ�����Ϣ
	StrDevDtuConnCtrl		ConnCtrl[COMM_DEV_DTU_CONN_NUM];//���ӿ��ƣ���ÿ����ַ��Ϊ�������������ӡ�
	
    MODBUS_CH            	*pch;                   		// MODBUS���
    
    INT08U                  ConnectTimeOut  : 7;     	// ���ӳ�ʱ����������Ϊ��λ
    INT08U                  ConnectFlag     : 1;         	// ���ӱ�־
} StrDevDtu;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����IC��ģ��ͨѶ�ṹ
//�豸OTR
//
/***************************************************
* ������ ͳ��ģ��--������ģ�飬��ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
*/
typedef struct _stcTinyRec{  
    uint8   Addr;
    uint8   ModelNum;
    uint16  Oil;
    uint32  CurRecNum;
    uint16  Speed1;
    uint16  Speed2;
    uint16  Speedcs;
    int16   Hig1;
    int16   Hig2;
    uint8   LocoWorkSta;
}stcTinyRec;


// �������ݽṹ  		ͳ��--> ��
__packed
typedef union {
	stcFlshRec	sRec;						//���ݼ�¼     128 	
    stcTinyRec  sTinyRec;                   //�����ݼ�¼
	uint8		Buf[160];					//
} UniOtrCommSendData;


/***************************************************
* ������ ͳ��ģ��--������ģ�飬��ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
*/
// �������ݽṹ	��-->ͳ��		
__packed
typedef union {
	int16		Density;			//DENSITY_CARD   �����ܶ�ֵ   		2     0.xxxx��/�������ף�10000����
	stcTime		sTime;			//TIME_CARD        ����ʱ��        		8     second,minute,hour,data,month,year,crccheck
	int16		Hig;				//HIGHT_CARD	     ���ø߶�ֵ   		2     0.1mm  (10��)
	stcLocoId		sLocoId;		//FIX_CARD          ���û�����Ϣ	4     type,num;
	uint32          	Slope;			//CALC_PARA	     ���ü����б��	4	(slope/10000);     ������������
	uint8       ModelNum;    
    uint8		Buf[160];		//	
} UniOtrCommRecvData;

//���տ�����
typedef struct {     
    INT08U          DestAddr;       //���յ�ַ      slave  = 
    INT08U          SourceAddr;     //Դ��ַ       master   =0x80	   
    INT08U          FramNum;        //֡���
    INT08U			Len;			//������Ч���ݳ���
    INT32U			Code;			//���տ�����
} StrDevOtrRecvCtrl;

//���ӿ����֣�
typedef struct {     
    INT08U          ConnFlg;        //���ӿ���,1���������ӣ�0������������
    INT08U			RecvEndFlg;		//���ձ�ʾ��1�����ݽ�����ɣ�0�������ݽ��ա�
    INT08U			TimeOut;		//��ʱʱ�䣬��λ1s
    INT08U			ErrFlg;		    //�����ʾ������������0�����Ӵ���1

    INT08U          SlaveAddr;       //���յ�ַ      slave  =0xCA	   
    INT08U          MasterAddr;     //Դ��ַ           master   =0x80	   
    INT08U          SendFramNum;    //֡���   
    INT08U          SendFlg;        //���ͱ�ʾ�� �����ݷ��ͣ�1�������ݷ��ͣ�0
} StrDevOtrConnCtrl;		


#define	COMM_DEV_OTR_CONN_NUM	2	// �豸������CA/C1	
__packed
typedef struct {  
	UniOtrCommRecvData	Rd;			//����������
	UniOtrCommSendData	Wr;			//����������

    /***************************************************
    * ������ ���ڿ�����
    */
	StrDevOtrRecvCtrl    	RxCtrl;				//���տ��ƣ�������ǰ���յ��Ŀ�����Ϣ
	StrDevOtrConnCtrl		ConnCtrl[COMM_DEV_OTR_CONN_NUM];//���ӿ��ƣ���ÿ����ַ��Ϊ�������������ӡ�
	
    MODBUS_CH            	*pch;                   		// MODBUS���
    
    INT08U                  ConnectTimeOut  : 7;     	// ���ӳ�ʱ����������Ϊ��λ
    INT08U                  ConnectFlag     : 1;         	// ���ӱ�־
} StrDevOtr;





//    Ctrl.Os.CommEvtFlag = M_EVT_FLAG_HEART       	// ?????
//                        + COMM_EVT_FLAG_RESET       	// COMM??
//                        + COMM_EVT_FLAG_CONNECT    	 // COMM??
//                        + COMM_EVT_FLAG_RECV        	 // ????
//                        + COMM_EVT_FLAG_REPORT     	 // ????
//                        + COMM_EVT_FLAG_CLOSE      	 // ??
//                        + COMM_EVT_FLAG_TIMEOUT    	 // ??
//                        + COMM_EVT_FLAG_CONFIG     	 // ??
//                        + COMM_EVT_FLAG_IAP_START  	 // IAP??
//                        + COMM_EVT_FLAG_IAP_END;    	// IAP??



//��¼�Ź���:��ǰ��¼�ţ����Ѷ���¼�ţ����߷���ģ���¼��
//16 bytes
typedef struct _StrRecNumMgr {
    uint32		Current;				//��ǰ��¼��	0~0xffffffff
    uint32		IcRead;				//IC���Ѷ�ȡ��¼��
    uint32		GrsRead;			//�����Ѷ�ȡ��¼��
    uint32		Back;				//����
}StrRecNumMgr;

//��Ʒ��Ϣ:  �ͺ�+ ���
//12 bytes
typedef struct _StrProductInfo {
	uint32		Type;			//��Ʒ���0 :NDP02  ,1:NDP02-B
	uint32		ID;				//��Ʒ���	16110002
	stcLocoId		sLocoId;		//������Ϣ	104(DF4B) - 1000
}StrProductInfo;

//�����������: ģ�ͱ�ţ��߶ȣ��ܶȣ�б��
//12 bytes
typedef struct _StrOilPara {
    uint8			ModelNum;			//ģ�ͱ��	0~64
    uint8			Rec8;				//����
    int16			Hig;					//�߶�  -500~500
    int16			Density;				//�ܶ�  800~900,     0.xxxx��/�������ף�10000����
    int16			Rec16;				//����
    uint32			Slope;				//����ϵ�� :����ֵ�ٳ�(slope/10000)  
}StrOilPara;

//���в�����װ��������أ����ݴ洢���ڣ���ʾ�������ָ���������
//8 bytes
typedef struct _stcRunPara_					
{
	uint8		StoreTime;					// 1 		���ݼ�¼�洢����
	uint8		RecClear;					// 1		���ݼ�¼���㣬��StrRecNumMgr����
	uint8		SysReset;					// 1    	ϵͳ�������ã���StrRecNumMgr + StrOilPara 	�е����ݡ�
	uint8		StartFlg;					// 1    	�״�����
	uint8		SysSta;						// 1   	    ϵͳ����״̬
	uint8		Buf[3];						// 1        ����
}stcRunPara;

//����ģ�͵㣬�߶ȣ�����
// 4 bytes
//typedef struct _stcModPot_					//
//{
//	uint16	Hig;								// 2 		�߶�
//	uint16	Oil;								// 2 		����
//}stcModPot;
//����������ģ��
//408 bytes
typedef struct _stcCalcModel_					
{
	stcModPot	sModPot[100];					// 4*100 	����
	uint16		PotNum;							// 2 		ģ����Ч���� 
	uint16		StartOil;                       // 2    	ģ�ͳ�ʼ����   	
	uint8		ModelNum;						// 1		ģ�ͱ��
	uint8		Res0;							// 1        ����
	uint16		CrcCheck;						// 2 		CrcCheck;
}stcCalcModel;

//OS ϵͳ���в�����
//�¼���ʾ�顣
__packed
typedef struct {
    OS_FLAG_GRP             WifiEvtFlagGrp;
    OS_FLAGS                WifiEvtFlag;
    OS_FLAG_GRP             CommEvtFlagGrp;		// ����ͨѶ��ʾ��
    OS_FLAGS                CommEvtFlag;        // ����ͨѶ��ʾ
    OS_FLAG_GRP             MaterEvtFlagGrp;
    OS_FLAGS                MaterEvtFlag;
    OS_FLAG_GRP             DtuEvtFlagGrp;
    OS_FLAGS                DtuEvtFlag;
} StrCtrlOS;

//ϵͳ����
__packed
typedef struct _StrSysCtrlPara {
    /***************************************************
    * ������ ϵͳ��������ʼ��ַ = 000   ͨѶ���룬�����汾����¼�ţ���Ʒ��Ϣ
    */    
    INT16U      Password;               // 	2  	����MODEBUSͨѶȷ����Կ��Ĭ��Ϊ6237����ֹ�Ƿ�������
    INT16U		SoftWareID;				//	2  	�����汾
    //
    /***************************************************
    * ��������¼�Ź�����ַ����ʼ��ַ = 004
    */
    StrRecNumMgr   sRecNumMgr;			//	16	��¼�Ź���: ��ǰ��¼�ţ����Ѷ���¼�ţ������Ѷ���¼��
       //
    /***************************************************
    * ��������Ʒ��Ϣ����ʼ��ַ = 020
    */
    StrProductInfo	sProductInfo;			//	12	��Ʒ��Ϣ: ��Ʒ�źż���Ʒ��ţ�
	   
    //
    /***************************************************
    * ���������ݼ�¼����ʼ��ַ = 032
    */
	stcFlshRec	sRec;					//  128  ���ݼ�¼      �������вɼ����ݼ���������

    //
    /***************************************************
    * ���������������������ʼ��ַ = 160
    */
	StrOilPara	SOilPara	;				// 12  �߶ȡ��ܶȣ�б�ʣ�ģ�ͱ�ţ�

    //
    /***************************************************
    * ������ϵͳ���в�������ʼ��ַ = 172
    */
	stcRunPara	sRunPara;				// 8		//���ݴ洢���ڣ��������㣬��������

    //
    /***************************************************
    * ����������������ģ�ͣ���ʼ��ַ = 180
    */
	stcCalcModel	sCalcModel;				// 408    100������ģ�ͣ�ģ�͵�����ģ�ͱ�ţ���ʼ������crccheck

    //
    /***************************************************
    * ������ͨѶ�豸�������Ͳ���װ��ͨѶ����ʼ��ַ = 588
    */
    //128 +128 + 8 + 8 + 4  = 276          
	StrDevMtr	Mtr;						//  �Ͳ���ģ��ͨѶ�����֣������ա������壬���տ��ƣ����Ϳ���

    //
    /***************************************************
    * ������ͨѶ�豸�����������߷���ͨѶ����ʼ��ַ = 892
    */
    //128 +128 + 8 + 8 + 4  = 276          
	StrDevDtu	Dtu;						//  �����߷���ģ��ͨѶ�����֣������ա������壬	���տ��ƣ����Ϳ���

    //
    /***************************************************
    * ������ͨѶ�豸��������IC ��ģ��ͨѶ����ʼ��ַ = 1168
    */
    //128 +128 + 8 + 8 + 4  = 276          
	StrDevOtr	Otr;						//  ����IC��ģ�����ͨѶ�����֣������ա������壬	���տ��ƣ����Ϳ���

    //����ȫ�ֵ�Os��������?   
    	StrCtrlOS    	Os;                                	 // OSϵͳ�ṹ�����    
    	
//    //��ʾ�ṹ��	
//    	StrDisp           Disp;                            	//��ʾ�ṹ����� 	
	
} stcSysCtrl;

extern  stcSysCtrl       sCtrl;

//
//__packed
//typedef struct  {    
//    CPU_FP32            I1;                         // ����1  uAΪ��λ
//    CPU_FP32            I2;                         // ����2
//    CPU_FP32            Adc1;                       // ADC1
//    CPU_FP32            Adc2;                       // ADC2
//    CPU_FP32            K;                          // б��   �Ŵ�10000��
//    CPU_FP32            B;                          // ƫ��
//} StrAdcToIBoardChk;    //li??
//
//__packed
//typedef struct  {
//    CPU_FP32              P1;                       // ѹ��1  PaΪ��λ
//    CPU_FP32              P2;                       // ѹ��2
//    CPU_FP32              I1;                       // ����1  uAΪ��λ
//    CPU_FP32              I2;                       // ����2
//    CPU_FP32              K;                        // б��
//    CPU_FP32              B;                        // ƫ��
//} StrIToPSenChk;        //??
//
///***************************************************
//* ������ ����������
//*/
//__packed
//typedef struct {                                   // ״̬	        1	
//    INT08U                  HSenBrokenErr           : 1;        //              Bit0����λ��������·
//    INT08U                  HSenExitDetection       : 1;        //              Bit1����λ�������˳����
//    INT08U                  HSenShortErr            : 1;        //              Bit2����λ��������·
//    INT08U                  PwrDownEvt              : 1;        //              Bit3���е����¼�����ȷ���պ󣬸�0��
//    INT08U                  LSenBrokenErr           : 1;        //              Bit4����λ��������·
//    INT08U                  LSenExitDetection       : 1;        //              Bit5����λ�������˳����
//    INT08U                  LSenShortErr            : 1;        //              Bit6����λ��������·
//    INT08U                  WorkStsReq              : 1;        //              Bit7������״̬
//} StrSenErr;
//
///*************************************************
//* ������ ����ģ�ͱ�
//*/
//__packed
// typedef struct {
//    INT16U  Hight;                                  // �߶�
//    INT16U  Volume;                                 // ����
// } _StrOilPoint;
//
//__packed
// typedef struct {
//    INT16S                  Offset;                 // �߶�ƫ��
//    INT16U                  Cnts;                   // ģ�͵���,14
//    _StrOilPoint            Point[10];              // �߶�,����
// } StrOilVolumeTab;
// 
//__packed
// typedef union {
//    StrOilVolumeTab         Tab;                    // ����ģ��    
//    INT08U                  buf1[44];
//    INT16U                  buf2[22];
//    INT32U                  buf3[11];
// } StrOilTab;
////////// 
/////////***************************************************
////////* ������ ��������������256 + 4 = 260�ֽ�
////////*/
////////__packed
////////typedef struct _StrCtrlPara {
////////    /***************************************************
////////    * ������ ϵͳ��������ʼ��ַ = 000
////////    */    
////////    INT16U              Password;                       // ����MODEBUSͨѶȷ����Կ��Ĭ��Ϊ6237����ֹ�Ƿ�������
////////    /***************************************************
////////    * ������ �ܶȣ���ʼ��ַ = 002
////////    */
////////    CPU_FP32            LastDensity;                    // �ϴβ����ܶ�
////////    
////////    /***************************************************
////////    * ������ ƫ�ã���ʼ��ַ = 006
////////    */
////////    INT16S              DispLevel;                      // ��ʾ����
////////    /***************************************************
////////    * ������ Ԥ������ʼ��ַ = 008
////////    */     
////////    CPU_FP32            LastGravity;                    // �ϴβ����������ٶ�
////////    
////////    CPU_FP32            SetDensity;                     // �����ܶ�
////////    CPU_FP32            SetGravity;                     // �����������ٶ�   
////////    
////////    //INT16U              Rsv1[3];
////////    /***************************************************
////////    * ������ У׼��������ʼ��ַ = 020
////////    */
////////    StrAdcToIBoardChk   Check[2]; 
////////    /***************************************************
////////    * ������ У׼��������ʼ��ַ = 068
////////    */
////////    StrIToPSenChk       SenChk[2];    
////////    /***************************************************
////////    * ������ У׼��������ʼ��ַ = 116
////////    */
////////    union __uSENSOR_CHECK_TYPE {
////////        struct __sSENSOR_CHECK_TYPE {
////////            INT08U      RstFlag             : 1;        // ��λ��־,��־λλ�úͼĴ���λ�ò������������MB_DATA.C�еĸ�λҲҪ���ŵ���
////////            INT08U      Test                : 1;        // ���Ա�־
////////            INT08U      Rsv                 : 6;        //
////////            StrSenErr   Err;                            // �����־
////////        }Udat;
////////        INT08U Dat[2];
////////    } SenSts;
////////    /***************************************************
////////    * ������ У׼��������ʼ��ַ = 116
////////    */
////////    union __uSEL_TYPE {
////////        struct __sSEL_TYPE {
////////            INT16U      FilterSel           : 4;        // �������˲�����ѡ��0~4
////////            INT16U      SensorSel           : 2;        // ������ѡ��:0�͡�1�ߡ�2ƽ����3����
////////            INT16U      DensitySel          : 2;        // �ܶ�ѡ��0�趨��1������2�趨����ƽ��ֵ��3����
////////            INT16U      GravitySel          : 2;        // �������ٶ�ѡ��0�趨��1������2�趨����ƽ����3����
////////            INT16U      CalcSel             : 2;        // ���㷽��ѡ��0A-I-P��1A-P
////////            INT16U      DispSel             : 2;        // ��ʾģʽ��0������ʾ�������Ͽ���ʾ�߶ȣ�1��ʾ�߶ȣ�2��������ʾ 3���ر���ʾ
////////            INT16U      DevSel              : 2;        // �豸���ͣ�0˫ͨ������ģ�飻1��ͨ������ģ�飻2��չ��ʾģ��
////////        }udat;
////////        INT16U dat;
////////    } Sel;
////////    
////////    /***************************************************
////////    * ������ �û���������ʼ��ַ = 118
////////    */
////////    StrOilTab   Vtab;
////////    /***************************************************
////////    * ������ �û���������ʼ��ַ = 118
////////    */
////////    INT16S              RSV[44];                        // ����13������
////////    /***********************************************
////////    * ������״̬�� ����ʼ��ַ = 252
////////    */
////////    union __sSYSTEM_STATUS {
////////        struct __uSYSTEM_STATUS {
////////            uint16_t  AbnormalPowerReset    : 1;        // �쳣�����־
////////            uint16_t  App_Fault_ISR         : 1;        // �쳣�ж�
////////            uint16_t  ResetFlag             : 1;        // ������־λ
////////            uint16_t  rsv1                  : 1;        // 
////////            
////////            uint16_t  ModuleType            : 2;        // ģ������
////////            uint16_t  Channels              : 2;        // ͨ����
////////            
////////            INT16U    FirstPwrFlag          : 1;        // �״��ϵ��־λ
////////            INT16U    SenChkFlag            : 1;        // PM2D5У׼��־λ
////////            uint16_t  RSV2                  : 6;        //
////////        }udat;
////////        INT16S dat;
////////    } SysSts;
////////
////////    /***************************************************
////////    * ������ �ָ��������ã���ʼ��ַ = 254
////////    */
////////    INT16S          RestoreSetting;                     // �ָ���������
////////
////////    const struct _StrCtrlPara *idx;                    // ���ָ�룬ռ4�ֽ�
////////
////////} StrCtrlPara;
//////
///////***************************************************
//////* ������
//////*/
//////__packed
//////typedef struct {
//////    INT08U                 *pEdit;                      // �༭����ָ��
//////    INT08U                 *pMax;                       // �༭���������ֵָ��
//////    INT08U                 *pMin;                       // �༭��������Сֵָ��
//////    INT08U                 *pStart;                     // �༭����ʼ����
//////    INT08U                 *pEnd;                       // �༭�Ľ�������
//////    INT08U                  EditIdx;                    // �༭��Ŀ���
//////    INT08U                  Edit;                       // �༭����
//////} StrEdit;
////
////__packed
////typedef struct {
////    INT08U                  Mode;                       // �����޸ı�־
////    //StrLedDisp             *Led;
////} StrDisp;
////
////__packed
////typedef struct {
////    INT08U                 *p08;
////    INT16U                 *p16;
////    INT32U                 *p32;
////    INT16U                  len;
////} NOTIFY_EEP_SAVE_TYPE;
////
////__packed
////typedef struct {
////    OS_FLAG_GRP             WifiEvtFlagGrp;
////    OS_FLAGS                WifiEvtFlag;
////    OS_FLAG_GRP             CommEvtFlagGrp;
////    OS_FLAGS                CommEvtFlag;
////    OS_FLAG_GRP             MaterEvtFlagGrp;
////    OS_FLAGS                MaterEvtFlag;
////    OS_FLAG_GRP             DtuEvtFlagGrp;
////    OS_FLAGS                DtuEvtFlag;
////} StrCtrlOS;
////
//
//__packed
//typedef struct {    
//    INT08U                  SysSts                  : 4;        // ϵͳ״̬
//    INT08U                  WifiSts                 : 4;        // WIFI״̬
//        
//    INT16U                  FirstPwrFlag            : 1;        // �״��ϵ��־λ
//    INT16U                  PM2D5ChkFlag            : 1;        // PM2D5У׼��־λ
//    INT16U                  RsvFlag                 :14;        // ����    
//} StrSystem;
//
///***************************************************
//* ������ ֡ͷ����ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
//*/
//__packed
//typedef struct {    
//    INT16U                  Head;                               // ��ͷ
//    INT08U                  SrcAddr;                            // Դ��ַ
//    INT08U                  DstAddr;                            // Ŀ�ĵ�ַ   
//    INT08U                  PacketSn;                           // �������
//    INT08U                  PacketCtrl;                         // ���Ŀ����֣� b0000
//    INT08U                  DataLen;                            // ���������ȣ� 12
//    INT08U                  PacketIdx;                          // ��������
//    INT08U                  PacketIdxChk;                       // ��������У��
//} StrCommHead;
//
///***************************************************
//* ������ �������ݣ���ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
//*/
//// �������ݽṹ������-->�ͳ�
//__packed
//typedef struct {
//    INT32U                  Oil;                                // ����	        4	��ֵ��Χ0-9999L 
//    INT16S                  Accelerations;                      // ���ٶ�	    2	-9.000-9.000��m/s2��(1000��)
//    INT16U                  Speed;                              // �ٶ�	        2	��ֵ0-600��Km/H��
//    struct __recv_work__ {                                     // ��������	    1
//    INT08U                  Null                    : 1;        //              0x01:��λ
//    INT08U                  Tow                     : 1;        //              0x02:ǣ��
//    INT08U                  Brake                   : 1;        //              0x04:�ƶ�
//    INT08U                  Rsv                     : 5;        // ������δ����
//    } Work;
//    INT16U                  Density;                            // �߶ȼ����ܶ�	2	0.xxxx��/�������ף�10000����
//    INT08U                  Rsv[1+10];                          // ����	        3
//} StrCommRecvData;
//
///***************************************************
//* ������ �������ݣ���ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
//*/
//// Ӧ�����ݽṹ���ͳ�-->����
//__packed
//typedef struct {
//    INT16U                  Hight;                              // Һλ�߶�	    2	xxx.x���ף�10����
//    INT16U                  Density;                            // �߶ȼ����ܶ�	2	0.xxxx��/�������ף�10000����
//    union __usend_status {
//    StrSenErr               Udat;
//    INT08U                  Dat;
//    } Sts;
//    INT08U                  RefLiqTemp;                         // Һ��ο��¶�	1	0.25~63.50�ȣ��ֱ���1-254��ʾ������-49.5~77.0�ȣ��ֱ���1-254��ʾ��100��ʾ0�ȣ�0�����ͣ�255������
//    INT16U                  AdcValue[2];                        // Adcֵ
//    INT16U                  HightDiff;                          // �߶Ȳ�	    2	0~1000x0.1mm(���������߶Ȳ�)
//    INT16U                  Volume;                             // ���  	    2	0~10000L(����)
//    INT16U                  Weight;                             // ����	        2	0~10000kg(����)
//    INT16S                  Pressure[2];                        // ѹǿ	        2	0~10000pa
//    INT16S                  CalcDensity;                        // �����ܶ�     x10000
//    INT16S                  Gravity;                            // ������ٶ�   x10000
//    INT16S                  CalcGravity;                        // �������ٶ�   x10000
//    //INT08U                  Rsv[2+10];                        // ����	        2	
//} StrCommSendData;
//
//
///***************************************************
//* ������ ���ݣ���ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
//*/
//__packed
//typedef struct { 
//    INT16U                  Check;                              // У���룬����ǰ�����ں�
//    INT16U                  Tail;                               // ��β
//} StrCommTail;
//
//__packed
//typedef struct { 
//    /***************************************************
//    * ������ ��ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
//    */
//    StrCommHead             Head;                               // ͷ
//    StrCommRecvData         Data;                               // ����������
//    StrCommTail             Tail;                               // β
//} StrCommRecvPack;
//
//__packed
//typedef struct { 
//    /***************************************************
//    * ������ ��ɳ������ͨ����װ���첽����ͨ��ͨ��ͨ��Э��
//    */
//    StrCommHead             Head;                               // ͷ
//    StrCommSendData	        Data;                               // ����������
//    StrCommTail             Tail;                               // β
//} StrCommSendPack;
//
//__packed
//typedef struct {     
//    StrCommRecvPack         Rd;                                 // ����������
//    StrCommSendPack	        Wr;                                 // ����������
//    /***************************************************
//    * ������ ���ڿ�����
//    */
//    INT08U                  SlaveAddr;                          // �ӻ���ַ    
//    MODBUS_CH               *pch;                               // MODBUS���
//    
//    INT08U                  ConnectTimeOut  : 7;                // ���ӳ�ʱ����������Ϊ��λ
//    INT08U                  ConnectFlag     : 1;                // ���ӱ�־
//} StrDevComm;
//
//__packed
//typedef struct {     
//    StrCommRecvPack         Rd;                                 // ����������
//    StrCommSendPack	        Wr;                                 // ����������
//    /***************************************************
//    * ������ ���ڿ�����
//    */
//    INT08U                  SlaveAddr;                          // �ӻ���ַ    
//    MODBUS_CH               *pch;                               // MODBUS���
//    
//    INT08U                  ConnectTimeOut  : 7;                // ���ӳ�ʱ����������Ϊ��λ
//    INT08U                  ConnectFlag     : 1;                // ���ӱ�־
//} StrDevDtu;
//
//__packed
//typedef struct {     
//    StrCommRecvPack         Rd;                                 // ����������
//    StrCommSendPack	        Wr;                                 // ����������
//    /***************************************************
//    * ������ ���ڿ�����
//    */
//    INT08U                  SlaveAddr;                          // �ӻ���ַ    
//    MODBUS_CH               *pch;                               // MODBUS���
//    
//    INT08U                  ConnectTimeOut  : 7;                // ���ӳ�ʱ����������Ϊ��λ
//    INT08U                  ConnectFlag     : 1;                // ���ӱ�־
//} StrDevMater;
//
//__packed
//typedef struct {
//    StrCommRecvPack         Rd;                                 // ����������
//    StrCommSendPack	        Wr;                                 // ����������
//    /***************************************************
//    * ������ ���ڿ�����
//    */
//    INT08U                  SlaveAddr;                          // �ӻ���ַ    
//    MODBUS_CH               *pch;                               // MODBUS���
//    
//    INT08U                  ConnectTimeOut;                     // ���ӳ�ʱ����������Ϊ��λ
//    INT08U                  ConnectFlag;                        // ���ӱ�־
//} StrDevServer;
//
//#define ADC_SAMPLE_CNTS_PER_SEC     10                          // ÿ��ͨ��һ���Ӳ�������
//#define ADC_SAMPLE_SECS             5                           // �뼶�˲�����
//#define ADC_SAMPLE_CNTS_MAX         18                          // 
//#define ADC_SAMPLE_TIME             (OS_CFG_TICK_RATE_HZ / ADC_SAMPLE_CNTS_PER_SEC / 2)                          // 
//
//#define ADC_SIGNAL_CYCLE            1500                        // ��ͨ�˲�����С�ź�����
//#define ADC_SIGNAL_CYCLE_CNT        10                          // �ɼ����ڸ���
//#define ADC_SAMPLE_CYCLE            100                         // ������ݴ�����������
//#define ADC_SAMPLE_CNT              (1)                         // ������ݴ�����������
//#define ADC_SAMPLE_CNTS_DEEPTH      (ADC_SIGNAL_CYCLE * ADC_SIGNAL_CYCLE_CNT / ADC_SAMPLE_CYCLE) // ���ݴ������
//
//__packed
//typedef struct { 
//    INT16U                  AdcValue;                           // ����ADCֵ
//    INT16U                  AdcValueSec;                        // ÿ����ADCֵ
//    INT16U                  AdcValueMin;                        // ÿ����ADCֵ
//    INT16U                  AdcValueAll;                        // ������ADCֵ
//    INT16U                  AdcValueSample;                     // ���е�ѹ
//    CPU_FP32                Pressure;                           // ѹ��
//    CPU_FP32                PressureSec;                        // ÿ����ѹ��
//    CPU_FP32                PressureMin;                        // ÿ����ѹ��
//    CPU_FP32                PressureAll;                        // ����ѹ��
//    CPU_FP32                PressureSample;                         // ���е�ѹ
//    INT16S                  Hight;                              // �߶�
//    INT16S                  HightSec;                           // ÿ���Ӹ߶�
//    INT16S                  HightMin;                           // ÿ���Ӹ߶�
//    INT16S                  HightAll;                           // ���и߶�
//    INT16S                  HightSample;                         // ���е�ѹ
//    INT16S                  Voltage;                            // ��ѹ0.1MV
//    INT16S                  VoltageSec;                         // ÿ���ӵ�ѹ
//    INT16S                  VoltageMin;                         // ÿ���ӵ�ѹ
//    INT16S                  VoltageAll;                         // ���е�ѹ
//    INT16S                  VoltageSample;                      // ���е�ѹ
//    
//    CPU_FP32                Current;                            // ����
//    CPU_FP32                CurrentSec;                         // ÿ���ӵ���
//    CPU_FP32                CurrentMin;                         // ÿ���ӵ���
//    CPU_FP32                CurrentAll;                         // ���е���
//    CPU_FP32                CurrentSample;                      // ���е���
//    
//    INT08U                  Head;                               // �˲�����ͷָ��
//    INT08U                  Tail;                               // �˲�����βָ��
//    INT08U                  HeadSec;                            // �˲�����ͷָ��
//    INT08U                  TailSec;                            // �˲�����βָ��
//    INT08U                  HeadMin;                            // �˲�����ͷָ��
//    INT08U                  TailMin;                            // �˲�����βָ��
//    
//    INT16U                  AdcFilter   [ADC_SAMPLE_CNTS_PER_SEC];// 100������ADCֵ
//    INT16U                  AdcFilterSec[ADC_SAMPLE_SECS];      // 1����ADCֵ
//    INT16U                  AdcFilterMin[ADC_SAMPLE_CNTS_MAX];  // 1����ADCֵ
//    INT16U                  Rsv[100-38-ADC_SAMPLE_CNTS_PER_SEC-ADC_SAMPLE_SECS-ADC_SAMPLE_CNTS_MAX]; 
//}__StrSen;
//
//__packed
//typedef struct {     
//    INT16S                  AverHight;                          // ƽ���߶�
//    INT16S                  AverHightSec;                       // ƽ���߶�
//    INT16S                  AverHightMin;                       // ƽ���߶�
//    INT16S                  AverHightAll;                       // ƽ���߶�
//    INT16S                  AverHightSample;                    // ���е�ѹ
//    INT16S                  AverPressure;                       // ƽ��ѹ��
//    INT16S                  AverPressureSec;                    // ƽ��ѹ��
//    INT16S                  AverPressureMin;                    // ƽ��ѹ��
//    INT16S                  AverPressureAll;                    // ƽ��ѹ��
//    INT16S                  AverPressureSample;                 // ���е�ѹ
//    CPU_FP32                DiffPressure;                       // ѹ����
//    CPU_FP32                DiffPressureSec;                    // ѹ����
//    CPU_FP32                DiffPressureMin;                    // ѹ����
//    CPU_FP32                DiffPressureAll;                    // ѹ����
//    CPU_FP32                DiffPressureSample;                 // ���е�ѹ
//    INT16S                  CalcHight;                          // ����߶Ȳ�
//    INT16S                  CalcHightSec;                       // ����߶Ȳ�
//    INT16S                  CalcHightMin;                       // ����߶Ȳ�
//    INT16S                  CalcHightAll;                       // ����߶Ȳ�
//    INT16S                  CalcHightSample;                    // ���е�ѹ
//    INT16S                  OffsetHight;                        // �߶�ƫ��
//    INT16S                  CalcDiffHight;                      // ����߶Ȳ�
//    INT16S                  CalcDiffHightSec;                   // ����߶Ȳ�
//    INT16S                  CalcDiffHightMin;                   // ����߶Ȳ�
//    INT16S                  CalcDiffHightAll;                   // ����߶Ȳ�
//    INT16S                  CalcDiffHightSample;                // У׼�߶Ȳ�
//    INT16S                  ChkedDiffHight;                     // У׼�߶Ȳ�
//    CPU_FP32                ChkedDensity;                       // �ܶ�
//    CPU_FP32                CalcDensity;                        // �ܶ�
//    CPU_FP32                CalcDensitySec;                     // �ܶ�
//    CPU_FP32                CalcDensityMin;                     // �ܶ�
//    CPU_FP32                CalcDensityAll;                     // �ܶ�
//    CPU_FP32                CalcDensitySample;                  // ���е�ѹ
//    CPU_FP32                Kp;                                 // 
//    CPU_FP32                KpSample;                           // 
//    CPU_FP32                Volume;                             // ���
//    CPU_FP32                Weight;                             // ����
//    INT16S                  Hight;                              // �ϴ��߶�   
//    CPU_FP32                Density;                            // �����ܶ�
//    CPU_FP32                Gravity;                            // ������ٶ�
//    CPU_FP32                CalcGravity;                        // �������ٶ�
//    INT08U                  Rsv[200-118];//100-57];                         // 
//
//} __StrSenCom;
//
///***************************************************
//* ������ ��������������256 + 4 = 260�ֽ�
//*/
//__packed
//typedef struct _StrSenPara {
//    /***************************************************
//    * ������ ��2����ϵͳ��������ʼ��ַ = 000
//    */    
//    CPU_FP32                ChkedDiffHight;             // У׼�߶Ȳ�
//    CPU_FP32                DiffPNbr;                   // ѹǿ�����������
//    CPU_FP32                PINbr;                      // ѹǿ�������������    
//    CPU_FP32                TestDensity;                // �����ܶ�
//    CPU_FP32                TestGravity;                // ���Լ��ٶ�
//    
//    INT32U                  SenId;                      // ��������ţ�����ǰ�����ں�
//    CPU_FP32                Offset;                     // ����5������
//    /***************************************************
//    * ������ У׼��������ʼ��ַ = 28
//    */
//    union __uSENSOR_CHECK_TYPE2 {
//        struct __sSENSOR_CHECK_TYPE2 {
//            INT16U      ChkType             : 4;        // ��λ������У׼���ͣ�0��У׼��1ѹǿ��ֶΣ�2��ѹǿ�����ԣ�3��ѹ�������ֶΣ�4��ѹ����������
//            INT16U      Test                : 4;        // ��λ������У׼���ͣ�0��У׼��1ѹǿ��ֶΣ�2��ѹǿ�����ԣ�3��ѹ�������ֶΣ�4��ѹ����������
//            INT16U      Rst                 : 4;        // ��λ��־
//            INT16U      Rsv                 : 4;
//        }udat;
//        INT32U dat;
//    } SenSts;
//    //CPU_FP32                RSV1[2];                    // ����5������
//    
//    CPU_FP32                Density_K;                  // �ܶȲ���б��
//    CPU_FP32                Density_B;                  // �ܶȲ���ƫ��
//    /***************************************************
//    * ������ ��2����ϵͳ��������ʼ��ַ = 040 
//    */
//    CPU_FP32                DiffP[10];
//    /***************************************************
//    * ������ ��3����ϵͳ��������ʼ��ַ = 080
//    */ 
//    CPU_FP32                PI[2][6][2];
//    /***************************************************
//    * ������ ��4����ϵͳ��������ʼ��ַ = 176
//    */ 
//    
//    StrIToPSenChk           Check[2];
//    /***************************************************
//    * ������ ��1�����û���������ʼ��ַ = 200
//    */
//    CPU_FP32                RSV2[7];                    // ����5������
//
//    /***************************************************
//    * ������ У���룺��ʼ��ַ = 252
//    */
//    INT16U                  CheckSum;                   // У����
//    /***************************************************
//    * ������ У���룺��ʼ��ַ = 254
//    */
//    INT16U                  ReadFlag;                   // �Ѷ�ȡ��־��0X5AΪ�����ݣ�0XA5Ϊ�Ѷ�������Ϊ��Ч
//} StrSenPara;
//
//__packed
//typedef union {
//    StrSenPara             dat;
//    INT08U                  buf1[256];
//    INT16U                  buf2[128];
//    INT32U                  buf3[64];
//} UnionSenPara;
//
//__packed
//typedef struct { 
//    __StrSen                H;                                  // �ߵ㴫����
//    __StrSen                L;                                  // �͵㴫����
//    __StrSenCom             C;                                  // ��������������
//    UnionSenPara            Para;
//    INT16U                  Filter[2][ADC_SAMPLE_CNTS_DEEPTH];  //������ݴ���
//    INT08U                  DensityStep;                        //�ܶȻ�ȡ״̬��
//    INT08U                  DensitySts;                         //�ܶȻ�ȡ״̬��
//    INT16U                  DensityCtr;                         //�ܶȻ�ȡ״̬��
//} StrSen; 
//
//
//__packed
//typedef union {
//    StrCtrlPara             dat;
//    INT08U                  buf1[256];
//    INT16U                  buf2[128];
//    INT32U                  buf3[64];
//} UnionCtrlPara;
//
////APP_EXT StrOilTab       OilTab;
//
//__packed
//typedef struct {
//    /***************************************************
//    * ������ ���ݽṹ��˳�����������
//    */
//    UnionCtrlPara           Para;                               // ���Ʋ���
//    StrSen                  Sen;                                // ���������� 
//    StrOilTab               Tab;                                // ����ģ��
//    StrDevComm              Com;                                // COMM���� 
//    StrDevMater             Mtr;                                // Mater���� 
//    StrDevDtu               Dtu;                                // DTU���� 
//    StrDevComm              Otr;                                // Sen����
//    
//    StrOilTab              *VTab;                               // �����ݻ���
//    StrParaRange           *Prge;                               // ���Ʋ�����Χ
//    
//    StrDevServer            Sevr;                               // ������ͨ������
//    StrCtrlOS               Os;                                 // OS����        
//    StrDisp                 Disp;                               // ��ʾ����        
//    StrSystem               Sys;                                // ϵͳ״̬
//    
//    INT32U                  ImpKwh;
//    INT32U                  PPpulseLast;
//    float                  PFreq;                               // ����Ƶ��
//    INT32U                  ID;
//    
//} StrCtrlDCB;
//
//extern StrCtrlDCB           Ctrl;
//
///*******************************************************************************
// * 				                  ����                                         *
// *******************************************************************************/
///***************************************************
//* ������ ������Ϣ���ݽṹ�����ڷ���
//*/
//__packed
//typedef struct {
//  INT08U                tail;                                   // β
//  INT08U                head;                                   // ͷ
//  INT08U                cnt;                                    // ������
//  INT08U                qbuf[AppMsgQ][AppMsgQSize];             // ��Ϣ����
//} StrMsgInfo;
//
///*******************************************************************************
// * GLOBAL VARIABLES
// */
///***************************************************
//* ������ �ṹ������
//*/
//APP_EXT NOTIFY_EEP_SAVE_TYPE    NotifyEepSave;

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */
void        Beep                        (INT32U flag);
//void        BeepExt                     (u8 cnt, u16 freq, u16 dly);
void        Power                       (INT08U onoff);
/***************************************************
* ������ Ӧ�ò㺯��������
*/
BOOL        App_PraInit                 (void);
BOOL        App_GetParaFromEeprom       (void);
BOOL        App_SetParaToEeprom         (void);
void        App_Error                   (void);
void        App_FanHandCtrl             (INT08U step);
void        App_FanAutoCtrl             (INT08U step);
void        App_ParaFilter              (void);

/***************************************************
* ������ OSAL�����ʼ������������
*/
void        TaskInitBeep                ( void );
void        TaskInitKey                 ( void );
void        TaskInitCtrl                ( void );
void        TaskInitTmr                 ( void );
void        TaskInitDisp                ( void );
/***************************************************
* ������ OSAL�����¼���������������
*/
osalEvt     TaskBeepEvtProcess          (INT8U task_id, osalEvt task_event);
osalEvt     TaskKeyEvtProcess           (INT8U task_id, osalEvt task_event);
osalEvt     TaskCtrlEvtProcess          (INT8U task_id, osalEvt task_event);
osalEvt     TaskTmrEvtProcess           (INT8U task_id, osalEvt task_event);
osalEvt     TaskDispEvtProcess          (INT8U task_id, osalEvt task_event);

/***************************************************
* ������ AES�Ӽ��ܺ���������
*/
/***************************************************
* ������ ���Ź�����������
*/
void        App_MsgWriteCmd             ( INT16U cmd );
/*******************************************************************************
 * 				end of file                                                    *
 *******************************************************************************/
#endif	/* GLOBLES_H */