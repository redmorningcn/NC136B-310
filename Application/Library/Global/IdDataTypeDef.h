#ifndef  _IdDataTypeDef_h_
#define  _IdDataTypeDef_h_

//2009-02-19 15:50
//�豸�����Ϣ
//���������Ϣ���ݽṹ //40

//������Ʒ���
typedef struct _stcDeviceInfo    //�豸�����Ϣ 	//����ʱ���� 40
{
    uint8_t   DeviceTyp[8];      	//�豸�ͺ�          8  	"NDP02-X"
//	uint16_t  DeviceNum;          //�豸���          2   "0-65535"
//	uint8_t   ProduceDate[6];     //��������			6	"090303"
	uint32_t  DeviceNum;          //�豸���          2   "0-65535"
	uint8_t   ProduceDate[4];     //��������			6	"090303"
	uint8_t   HardwareVer[10];    //Ӳ���汾	        10  "HV2009201"   
    uint8_t   SoftwareVer[10];    //����汾          10  "SV2009201"
    uint16_t  Reserve0;        	//Ԥ��			    2
	uint16_t  CrcCheck;           //У���            2   
}stcDeviceInfo;

//2009-02-19 16:40
//��װ�豸��Ϣ		 
//��װ�ú�,�ṹ����
typedef struct _stcFixInfo    //�豸�����Ϣ 	        //����ʱ���� 28
{
    uint8_t   LocoTyp;            //�����ͺ�          1   
    uint8_t   E_LocoTyp;          //�����ͺ���չ�ֽ�  1   �����ͺ������ֽ�,������LKJ2000��ʽ��ͬ
    uint8_t   LocoNum[2];         //������            2
	uint8_t   FixDate[6];         //��װ����			6	"20090303"
	uint8_t   FixUint[4];         //��װ��λ			4	"GTZJ"	
	uint8_t   ReFixDate[6];       //��װ����			6	"20190303"   
	uint8_t   ReFixUint[4];      	//��װ��λ			4	"GTGJ"	
    uint16_t 	Reserve0;   		//Ԥ��				2
	uint16_t  CrcCheck;           //У���            2   
}stcFixInfo;

#endif
