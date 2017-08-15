#ifndef  _CardDataTypeDef_h_
#define  _CardDataTypeDef_h_
#include <stdint.h>
#include <idDataTypeDef.h>

//ʱ��----------------------------------------
typedef		struct	_stcTime_
{
	uint8_t	Sec;
	uint8_t	Min;
	uint8_t	Hour;
	uint8_t	Date;
	uint8_t	Month;
	uint8_t	Year;
	uint16_t	CrcCheck;
}stcTime;

typedef struct _stcCardID_						//IC ��ID��	  32
{
	uint8_t	ProductNum[12];						//IC�����
	uint8_t	DriverNum[4];						//˾������
	uint8_t	DriverUnit[8];						//˾�����ڵ�λ���
	uint8_t	Reserve0[4];						//Ԥ��0
	uint16_t	Reserve1;	 						//Ԥ��1
	uint16_t	CrcCheck;							//CRC����
}stcCardID;

typedef struct _stcCardType_					//IC ������ 8
{
	uint16_t	CardType[3];						//IC������
	uint16_t	CrcCheck;							//CRC����
}stcCardType;

typedef struct _stcDensity_						//IC ���ܶ� 24
{
	uint8_t		LocoType[2];					//�����ͺ�
	uint8_t		LocoNum[2];						//�������
	//uint8_t		DriverNum[4];					//˾�����
	uint32_t		DenChageTimes;					//�ܶȱ仯��
	uint32_t		Density;						//�����ܶ�
	uint32_t		AddOilStationNum;				//���ͻ����
	uint32_t		AddOilerNum;					//������Ա���	
	uint16_t		AddVol;							//��������
	uint16_t		CrcCheck;						//CRC����
}stcDensity;

typedef struct _stcModPot_						//IC ��cd����
{
	uint16_t	HigVal;								//ѹ��ֵ
	uint16_t	DipVal;								//����ֵ
}stcModPot;

typedef struct _stcModel_						//����ģ�͸������ݽṹ
{
	stcModPot	sModPot[50];					//����ģ��
	uint16_t		PotNum;							//����ģ�͵�ĸ���	
	uint16_t		StartHight;						//��ʼ�߶�
	uint8_t		ModelNum;						//ģ�ͱ��
	uint8_t		Reserve0;						//Ԥ��    //100919   0x01��ʾʹ�ã�0x00��ʾδ��
	uint16_t		CrcCheck;						//CRCУ��
}stcModel;

typedef struct _stcModelSemple_					//����ģ�ͼ����ݽṹ
{
	stcModPot	sModPot[10];					//����ģ��
	uint16_t		PotNum;							//����ģ�͵�ĸ���	
	uint16_t		StartHight;						//��ʼ�߶�
	uint8_t		ModelNum;						//ģ�ͱ��
	uint8_t		Reserve0;						//Ԥ��	//100919	0x01��ʾʹ�ã�0x00��ʾδ��	
	uint16_t		CrcCheck;						//CRCУ��
}stcModelSemple;

typedef struct _stcModelComplex_				//����ģ�ͼ����ݽṹ
{
	stcModPot	    sModPot[100];					//����ģ��
	uint16_t		PotNum;							//����ģ�͵�ĸ���	
	uint16_t		StartHight;						//��ʼ�߶�
	uint8_t		    ModelNum;						//ģ�ͱ��
	uint8_t		    Reserve0;						//Ԥ��
	uint16_t		CrcCheck;						//CRCУ��
}stcModelComplex;


typedef struct _stcModelCard_					//����ģ�͸������ݽṹ
{
	stcModel		sModel[18];					//��������ģ��
	stcModelSemple	sModelSemple[46];			//������ģ��

//	stcModel		sModel[18];					//��������ģ��
//	stcModelSemple	sModelSemple[18];			//������ģ��
//	stcModelComplex	sModelComplex;	   			
	uint16_t			Reserve0;					//Ԥ��
	uint16_t			CrcCheck;					//CRCУ��	
}stcModelCard;


typedef struct _stcReviseHight_					//IC �����߶�
{
	int16_t		ReviseHight;					//�����߶���ʼ�߶�
	uint16_t		CrcCheck;						//CRCУ��
}stcReviseHight;

typedef struct _stcAddDipVal_					//IC ��������
{
	int16_t		AddDipVal;						//��������
	uint16_t		CrcCheck;						//CRCУ��
}stcAddDipVal;

typedef struct _stcDebugCard_					//
{
	uint16_t		DebugCode;						//���Դ���
	uint16_t		BufLen;							//��Ч���ݳ���
	uint8_t		Buf[100];						//������
	uint16_t		Reserve0;						//Ԥ��
	uint16_t		CrcCheck;						//CRCУ��
}stcDebugCard;

//����ģ�Ϳ�����
typedef struct _stcCardPara_ 					//IC ��cd���� 352
{
	stcDensity		sDensity;					//�ܶ�
	uint32_t			SetVal;						//����ֵ
	stcTime			sTime;						//ʱ��
 	stcReviseHight	sReviseHight;				//������ʼ�߶�
	stcFixInfo      sFixInfo;              	 	//װ����
	stcDebugCard	sDebugCard;					//���Կ�
	uint16_t			Reserve0;					//Ԥ��
	uint16_t			CrcCheck;					//CRC����
}stcCardPara;

typedef struct _stcCardIndex_					//IC ���ļ����� 36
{
	uint8_t			LocoType[2];				//�����ͺ�
	uint8_t			LocoNum[2];					//�������
	uint8_t			ProNum[16];					//��Ʒ���
	uint32_t			StartAddr;					//��ʼ��ַ
	uint32_t			EndAddr;					//������ַ
	uint16_t			RecLen;						//��¼����
	uint16_t			RecNum;						//��¼����	
}stcCardIndex;

typedef struct _stcCardFlg_						//IC ����ʶ
{
	stcCardID		sCardID;					//IC�� ID�ṹ
	stcCardType		sCardType;					//IC�� IC�����ͣ����ݿ����ܶȿ�����
	stcCardPara		sCardPara;					//IC�� ������
	stcCardIndex	sCardIndex[100];			//IC�� �ļ�����
	uint16_t			WriteCardTimes;				//��д������
	uint16_t			CrcCheck;					//CRC����
}stcCardFlg;


#endif
