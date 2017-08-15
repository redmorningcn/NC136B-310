/*******************************************************************************
 *   Filename:       app_lib.c
 *   Revised:        All copyrights reserved to Wuming Shen.
 *   Date:           2014-07-05
 *   Revision:       v1.0
 *   Writer:	     Wuming Shen.
 *
 *   Description:    ˫��ѡ�� wdt �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� Wdt �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   ˫��ѡ�� WDT �� Ctrl + H, ��ѡ Match the case, Replace with
 *                   ������Ҫ�����֣���� Replace All
 *                   �� app_cfg.h ��ָ����������ȼ� �� �����ջ��С
 *
 *   Notes:
 *					QQ:276193028
 *     				E-mail:shenchangwei945@163.com
 *
 *******************************************************************************/

/*******************************************************************************
 * INCLUDES
 */
#define  SNL_APP_SOURCE
#include <app.h>
#include <CrcCheck.h>
//#include <bsp_usart.h>

#define BSP_COMM_PROTOCOL_MODULE_EN 1
#if BSP_COMM_PROTOCOL_MODULE_EN > 0

#ifdef VSC_INCLUDE_SOURCE_FILE_NAMES
const  CPU_CHAR  *app_comm_protocol__c = "$Id: $";
#endif

/*******************************************************************************
 * CONSTANTS
 */
#define         FRAM_HERD0     		0x10         	//����ͷ
#define         FRAM_HERD1     		0x28       		//����ͷ				
#define     	HOST_ID      		10				//��λ����ַ	  		   
#define   		DEVICE_ID0      	15				//������ַ0	
#define   		DEVICE_ID1      	15				//������ַ1	
	   
#define			RS485_CHK_SUM		0x02			//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 
#define			RS485_CHK_CRC		0x01			//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 
#define			RS485_CHK_RESUM		0x03			//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 

#define         FRAM_END0     		0x10         	//����β
#define         FRAM_END1     		0x2C       		//����β	

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

/*******************************************************************************
 * LOCAL FUNCTIONS
 */

/*******************************************************************************
 * GLOBAL FUNCTIONS
 */

/*******************************************************************************
 * EXTERN VARIABLES
 */

/*******************************************************************************
 * EXTERN FUNCTIONS
 */
 
static unsigned char   l_recslaveaddr = 0;
static unsigned char   l_RecvFrameNbr = 0;
/***********************************************
* ������ 
*/
unsigned char GetRecSlaveAddr(void)
{
	return	l_recslaveaddr;
}
/***********************************************
* ������������� 
*/
unsigned char GetRecvFrameNbr(void)
{
	return	l_RecvFrameNbr;
}

//static uint8	RecvFrameNbr = 0;
///***********************************************
//* ������ 
//*/
//uint8	GetRecvFrameNbr(void)
//{
//	return 	RecvFrameNbr;
//}


/***********************************************
* ������ 
*/
void	SetRecvFrameNbr(void)
{
	l_RecvFrameNbr++;		
}

/*******************************************************************************
* ��    �ƣ� GetCheckSumNR
* ��    �ܣ� 
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-07
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
static uint8 GetCheckSumNR(uint8  Buf[], uint32 Len)
{
    int32  i;
    int8   CheckSum = 0;
    
    for(i = 0;i < Len; i++) {
        CheckSum += Buf[i];                         //���
    }
    
    if((unsigned char)CheckSum >= 0x80) {
    	CheckSum = ~CheckSum + 1 +0x80;             //ȡ��+1
    } else {
    	CheckSum = CheckSum;                       	//ȡ��+1
    }
    return  CheckSum;
}

/*******************************************************************************
* ��    �ƣ� CSNC_GetData
* ��    �ܣ� 
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-07
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
unsigned char  CSNC_GetData(	INT08U *RecBuf,
								INT16U	RecLen,
								INT08U *Datapos,
								INT16U *InfoLen)
{
    unsigned short		i,j,k;
    unsigned char		    SumCheck8;
    unsigned char		    Tmp;
    unsigned short		RecCRC16,Check16;
		
	//unsigned char 		DstAddr;	
    unsigned char 		SourceAddr;
	unsigned short		DataLen;  
    unsigned char         *pDat         = RecBuf;
    
    unsigned short        MaxDataLen    = RecLen - 10;
    
    if(RecLen < 10)         //����С����С���ȣ�ֱ���˳���
        return 0;   
    
    *InfoLen            = 0;
    //StrCommRecvPack *Rd = (StrCommRecvPack *)DataBuf;
    //DataBuf = DataBuf;
    /***********************************************
    * ������ ʶ��֡ͷ
    */
    for(i = 0; i < MaxDataLen -1; i++)	{		        //ѭ������ (2017 redmorningcnѭ�����м�1�ģ�����ֵ���1)
		if(	( (RecBuf[i + 0] ) == FRAM_HERD0 ) && 
            ( (RecBuf[i + 1] ) == FRAM_HERD1 ) ) {
            pDat    = &RecBuf[i];
            goto next;
        }
    }
    return 0;
next:
    /***********************************************
    * ������ ��������ȥ��֡ͷʶ����0X10���ظ�����
    */
	for(j = 0;j < RecLen - 1 ;j++ )	{				    //ȥ�ظ�ͨѶ���ֽ�   (2017 redmorningcnѭ�����м�1�ģ�����ֵ���1)
        if( ( pDat[j]   == FRAM_HERD0 ) &&
            ( pDat[j+1] == FRAM_HERD0 ) ) {
            for(k = j; k < RecLen -1; k++) {
               pDat[k] =  pDat[k+1];
//               Tmp      = pDat[k+1];
//               pDat[k]  = Tmp;
            }
        }
	}
    pDat    += 6;
    DataLen  = *pDat;
    // ���ȳ���Χ
    if ( DataLen > MaxDataLen )
        return 0;
    
    pDat    += DataLen + 4;
    /***********************************************
    * ������ ���֡β
    */
    if( ( pDat[0] 	!= FRAM_END0)	||
        ( pDat[1] 	!= FRAM_END1) ) {
        return 0;
    }
    
    pDat            = &RecBuf[i];
    l_recslaveaddr 	= pDat[3];
    
    //DstAddr         = l_recslaveaddr;
    SourceAddr      = pDat[2];
    
    l_RecvFrameNbr  = pDat[4];
    *InfoLen 		= DataLen; 

    SumCheck8 		= GetCheckSumNR((unsigned char *)&pDat[2],5);	//������У��

    RecCRC16 		= ((unsigned short)pDat[8+DataLen])
                    * 256 + pDat[9+DataLen];	        //У��	
               
    switch(pDat[5]>>4) {							    //У����㷨�ж�
    case	RS485_CHK_SUM:
        break;
    case	RS485_CHK_CRC:
       Check16 = GetCrc16Check(&pDat[2],6+DataLen);;
        break;
    case	RS485_CHK_RESUM:
        break;
    }
    
    if(	(SumCheck8 == 	pDat[7] ) && 
        (RecCRC16  ==	Check16 ) ) {
        /***********************************************
        * ������ ��ȡ֡ͷ
        */
        //memcpy( (INT08U *)&Rd.Head, (INT08U *)&pDat[0], 8 );

        /***********************************************
        * ������ ��ȡ����
        */       
        //memcpy( (INT08U *)DataBuf,  (INT08U *)&pDat[8], DataLen);					//���ݿ���
        
            
        //DataBuf     = (INT08U *)&pDat[8];
         *Datapos   = 8;
        //return		DstAddr;//SourceAddr;
        return  SourceAddr;
    }
               
    return	0;
}

static uint8	SendFrameNbr = 0;

/***********************************************
* ������ 
*/
uint8	GetSendFrameNbr(void)
{
	return SendFrameNbr;		
}

/***********************************************
* ������ 
*/
void	SetSendFrameNbr(void)
{
	SendFrameNbr++;		
}

static  unsigned char	SndBuf[250] = {0};
static  unsigned char	SndBufTmp[250] = {0};
/*******************************************************************************
* ��    �ƣ� CSNC_SendData
* ��    �ܣ� 
* ��ڲ����� ��
* ���ڲ����� ��
* ��  ���ߣ� wumingshen.
* �������ڣ� 2015-12-07
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void	CSNC_SendData(	MODBUS_CH *pch,
                        INT08U  SourceAddr,
						INT08U  DistAddr,
                        INT08U  SendFrameNum,
						INT08U  SendCode,                       
						INT08U *DataBuf,
						INT16U  DataLen)
{
	unsigned char	    SumCheck8;
	unsigned short	Crc16;
	unsigned short	AddHeadNum;
	unsigned short	i;
	unsigned char	    ByteStation;	
    
	ByteStation = 0;
	SndBuf[ByteStation++] = FRAM_HERD0;
	SndBuf[ByteStation++] = FRAM_HERD1;
	SndBuf[ByteStation++] = SourceAddr;	 
	SndBuf[ByteStation++] = DistAddr;				    // ��ַ
	SndBuf[ByteStation++] = SendFrameNum;               // ����֡���

	SndBuf[ByteStation++] =  ( RS485_CHK_CRC<<4 )+ SendCode;// ���Ϳ�����	
	SndBuf[ByteStation++] = DataLen;
	
	SumCheck8 = GetCheckSumNR(&SndBuf[2],5);		   	// ������У��

	SndBuf[ByteStation++] = SumCheck8;

	memcpy(&SndBuf[8],DataBuf,DataLen);

	Crc16 = GetCrc16Check(&SndBuf[2],6+DataLen);

	SndBuf[2+6+DataLen+1] = Crc16;
	SndBuf[2+6+DataLen]   = Crc16>>8;

	SndBufTmp[0] = SndBuf[0];						    // ׼�����ݷ���
	SndBufTmp[1] = SndBuf[1];
	
	AddHeadNum = 0;
	for(i = 2; i< 2+6+DataLen + 2 + AddHeadNum;i++ )	{				// ���ݣ�����λ FRAM_HERD0
	
		SndBufTmp[i+AddHeadNum] = SndBuf[i];
		
		if(SndBuf[i] == FRAM_HERD0) {
			SndBufTmp[i+AddHeadNum+1] = FRAM_HERD0;
			AddHeadNum++;
		}
	}

	SndBufTmp[2+6+DataLen + 2 +AddHeadNum] = FRAM_END0;
	SndBufTmp[2+6+DataLen + 2 +AddHeadNum+1] = FRAM_END1;      
    
    CPU_INT16U nbr_bytes= (2+6+DataLen + 2 +AddHeadNum +2);
    if ( nbr_bytes < MB_DATA_NBR_REGS * 2 ) {  
        //�����ڷǽ���״̬���������ݡ�
        if (pch->RxBufByteCtr == 0) 
        {                
            NMB_Tx(pch,
                   (CPU_INT08U  *)SndBufTmp,
                   (CPU_INT16U   )nbr_bytes);
        }
        else
        {
            return;
        }
    }
}

/*******************************************************************************
 * 				                    end of file                                *
 *******************************************************************************/
#endif