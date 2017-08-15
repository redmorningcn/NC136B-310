//#include 	"config.h"
//#include 	"string.h"
//#include 	"CpuDrive.h"
//#include 	"HardDrive.h"

#include    "includes.h"  
#include    "card.h"  


#define		SCK_IC	120//P004  
#define		MISO_IC	123//P005  
#define		MOSI_IC	124//P006 
#define     SSEL0	7//P007

#define		CS_IC	127//P228	
#define		SOFT_SPI_CS_IC	CS_IC//P228	
#define		POW_IC	211//P028

#define		IC_SWT	200//P029
#define		IC_RST	212//P230
#define		FINISH		1
#define		UNFINISH	0

uint32		l_Spi0Len 	= 0;
uint32		l_Spi0Point = 0;
//uint8_t		Spi0SendBuf[256*1];
//uint8_t		Spi0RevBuf[256*1];
uint8_t		Spi0FinishFlg = FINISH;

//------------------------------------------------------------------------
//  ��  �� ��void WriteSCK_IC( uint8_t temp )
//  ��  �� ������ SCK_IC
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSCK_IC(uint8_t temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SCK_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCK_IC,0);		
	}	
	nop();	
}

//------------------------------------------------------------------------
//  ��  �� ��uint8_t ReadSCK_IC(void)
//  ��  �� ����ȡ SCK_IC ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8_t ReadSCK_IC(void)
{
	uint8_t temp;

	temp = 	GPIO_ReadIoVal(SCK_IC);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI_IC( uint8_t temp )
//  ��  �� ������ MOSI_IC
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteMOSI_IC(uint8_t temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(MOSI_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(MOSI_IC,0);		
	}	
}

//------------------------------------------------------------------------
//  ��  �� ��uint8_t ReadMOSI_IC(void)
//  ��  �� ����ȡ MOSI_IC ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8_t ReadMOSI_IC(void)
{
	uint8_t temp;
	
	temp = 	GPIO_ReadIoVal(MOSI_IC);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI_IC( uint8_t temp )
//  ��  �� ������ MOSI_IC
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteMISO_IC(uint8_t temp)
{
	
	if(temp)		
	{
		GPIO_SetOrClearValue(MISO_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(MISO_IC,0);		
	}
		
	nop();		
}

//void  SSP0_Init(void)
//{
// //   LPC_SC->PCONP |= (1 << 21);                                         /* ��SSP0��Դ                 */
//  
////    LPC_PINCON->PINSEL3 |= (0x03ul << 8);                              /* ���ùܽŹ���                 */
////    LPC_PINCON->PINSEL3 |= (0x03ul << 14)|(0x03 << 16);
//   /* 
//    * �������ݳ���Ϊ8λ��֡��ʽSPI��SCK����Ч����һ��ʱ���ز�����λ����ΪĬ��ֵ 
//    */
//    LPC_SSP0->CR0 = (0x01 << 8)                                         /* SCR  ����SPIʱ�ӷ�Ƶ         */
//                  | (0x01 << 7)                                         /* CPHA ʱ�������λ            */
//                  | (0x01 << 6)                                         /* CPOL ʱ���������            */
//                  | (0x00 << 4)                                         /* FRF  ֡��ʽ 00=SPI           */
//                  | (0x07 << 0);                                        /* DSS  ���ݳ���,0111=8λ       */
//
//    LPC_SSP0->CR1 = (0x00 << 3)                                         /* SOD  �ӻ��������,0=����     */
//                  | (0x00 << 2)                                         /* MS   ����ѡ��,0=����,1=�ӻ�  */
//                  | (0x01 << 1)                                         /* SSE  SSPʹ��                 */
//                  | (0x00 << 0);                                        /* LBM  ��дģʽ                */
//    LPC_SSP0->CPSR = 0x52;                                              /* ����SSP��PCLK��õķ�Ƶֵ,   */
//                                                                        /* ��ģʽ����Ч, ��СֵΪ0x02   */
//}		

void SSP0_Init(void)
{
	SSP_CFG_Type SSP_ConfigStruct;

	SSP_ConfigStructInit(&SSP_ConfigStruct);
	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP0, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP0, ENABLE);
}		 
void InitCardIO( void )
{
	GPIO_PinselConfig(SCK_IC,3);
	GPIO_PinselConfig(MOSI_IC,3);
	GPIO_PinselConfig(MISO_IC,3);
	GPIO_PinselConfig(SOFT_SPI_CS_IC,0);
	GPIO_PinselConfig(IC_SWT,0);

	SSP0_Init();
}
		       
//void	InitCardIO(void)
//{
//	GPIO_PinselConfig(SCK_IC,0);
//	GPIO_PinselConfig(SCK_IC,0);
//	GPIO_PinselConfig(MOSI_IC,0);
//	GPIO_PinselConfig(MOSI_IC,0);	
//	GPIO_PinselConfig(MISO_IC,0);
//	GPIO_PinselConfig(MISO_IC,0);	
//	GPIO_PinselConfig(SOFT_SPI_CS_IC,0);			
//	GPIO_PinselConfig(POW_IC,0);
//	GPIO_PinselConfig(IC_SWT,0);
//	GPIO_PinselConfig(IC_SWT,0);
//
//	SSP0_Init();
//}




//------------------------------------------------------------------------
//  ��  �� ��uint8_t ReadMOSI_IC(void)
//  ��  �� ����ȡ MOSI_IC ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8_t ReadMISO_IC(void)
{
	uint8_t temp;

	temp = 	GPIO_ReadIoVal(MISO_IC);

	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI_IC( uint8_t temp )
//  ��  �� ������ MOSI_IC
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSoftSpiCSIC(uint8_t temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS_IC,0);		
	}	

	nop();		
}


//---------------------------------------------------------------------------------
//��������:             SentByte_SPI()
//��    ��:             SPI����һ�ֽ�����
//��ڲ���:             Data8
//���ڲ���:             ��
//˵    ��:				��ģ��SPI���߷�ʽ��������
//----------------------------------------------------------------------------------
//uint8_t SendOrRecByte_SPI_IC(uint8_t ch)
//{
//	uint8_t i,temp;   
//	
////	WriteSCK_IC ( 0 );
//	printfcom0("\r\n temp1 %x,%x",ch);
//    for (i=0;i<8;i++)
//    {
//		temp=ch&0x80;
//    	ch=ch<<1;
//      if(temp)
//      {
//      	WriteMOSI_IC( 1 );	
//
//      	WriteSCK_IC ( 0 );
//
//      	WriteSCK_IC ( 1 );	        	
//      }
//      else
//      {
//      	WriteMOSI_IC( 0 );	
//
//        WriteSCK_IC ( 0 );
//          
//      	WriteSCK_IC ( 1 );
//      }
//      
//      ch |= ReadMISO_IC();
//	  //nop();
//    }
//        
//   // WriteSCK_IC ( 0 );
//    printfcom0("\r\n temp2 %x,%x",ch);
//    return	ch;
//}


uint8_t SendOrRecByte_SPI_IC(uint8_t data)
{
	uint8_t	tmp;

    while((LPC_SSP0->SR & 0x04) == 0x04)
	{
		tmp	= LPC_SSP0->DR; 
	}
	while ((LPC_SSP0->SR & 0x02) == 0);                                 /* �ȴ�����FIFO�����ռ�         */   
    LPC_SSP0->DR = data;
    while ((LPC_SSP0->SR & 0x10) == 0x10);                              /* �ȴ�����֡�������           */ 
	
	while((LPC_SSP0->SR & 0x04) == 0x04)
	{
		tmp	= LPC_SSP0->DR; 
	}
    return tmp;
}



void	SendByte_SPI_IC(uint8_t	ch)
{
	SendOrRecByte_SPI_IC(ch);
}

uint8_t	RecByte_SPI_IC(void)
{
	uint8_t		ch =0;
	return	SendOrRecByte_SPI_IC(ch);
}



//------------------------------------------------------------------------
// ��    �ƣ�   uint8_t SentByte_SPI(uint8_t  Dat8)
// ��    �ܣ�   SPI��0���ڷ���1������
// ��ڲ�����   Dat8:���ݻ�
// ���ڲ�����	(����)
//------------------------------------------------------------------------
uint8_t SentByte_SPI(uint8_t  Dat8)
{
	SendByte_SPI_IC(Dat8);
	return 1;
}

//------------------------------------------------------------------------
// ��    �ƣ�   uint8_t RevByte_SPI(void)
// ��    �ܣ�   SPI0��ѯ��ʽ��������                  	
// ��ڲ�����  
// ���ڲ�����	���յ�������
//------------------------------------------------------------------------
uint8_t RevByte_SPI(void)
{
    uint8_t	Tmp;
    
	Tmp = RecByte_SPI_IC();
        
    return  Tmp;                  			//�巢����ɱ�ʶ
}

//------------------------------------------------------------------------
//  ��  �� ��void WritePOW_IC( uint8_t temp )
//  ��  �� ������ POW_IC
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WritePOW_IC(uint8_t temp)
{
	nop();		
	
	if(temp)		
	{
		GPIO_SetOrClearValue(POW_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(POW_IC,0);		
	}	

	nop();		
}

//------------------------------------------------------------------------------------------
//  ��  �� ��void WriteCS_IC( uint8_t temp )
//  ��  �� ������ CS_IC
// ��ڲ�������
// ���ڲ�������
//-----------------------------------------------------------------------------------------
void WriteCS_IC(uint8_t temp)
{
	GPIO_PinselConfig(CS_IC,0);
	
	nop();
	if(temp)		
	{
		GPIO_SetOrClearValue(CS_IC,1);
	}
	else
	{
		GPIO_SetOrClearValue(CS_IC,0);		
	}
	nop();	
}

//--------------------------------------------------------------------------------------------
//  ��  �� ��void WriteIC_RST( uint8_t temp )
//  ��  �� ������ IC_RST
// ��ڲ�������
// ���ڲ�������
//----------------------------------------------------------------------------------------------
void WriteIC_RST(uint8_t temp)
{
	GPIO_PinselConfig(IC_RST,0);
	
	if(temp)		
	{
		GPIO_SetOrClearValue(IC_RST,1);
	}
	else
	{
		GPIO_SetOrClearValue(IC_RST,0);		
	}		
}
//--------------------------------------------------------------------------------------------
//  ��  �� ��void WriteIC_SWT( uint8_t temp )
//  ��  �� ������ IC_SWT
// ��ڲ�������
// ���ڲ�������
//---------------------------------------------------------------------------------------------
void WriteIC_SWT(uint8_t temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(IC_SWT,1);
	}
	else
	{
		GPIO_SetOrClearValue(IC_SWT,0);		
	}	
}

//-----------------------------------------------------------------------------------------------
//  ��  �� ��uint8_t ReadIC_SWT(void)
//  ��  �� ����ȡ IC_SWT ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------------------------------
uint8_t ReadIC_SWT(void)
{
	uint8_t	Tmp;

	nop();	
	Tmp = 	GPIO_ReadIoVal(IC_SWT);

	return Tmp;	
}



//����AT45DB041D����    ���������PAGESIZE=l_CardPageSize-------------------------------------- 
#define    	READ_STU               0x57            //��״̬������
#define    	CON_ARR_READ           0xe8            //continuous array read code
#define    	BUFF1_WRITE            0x84            //write buffer1
#define    	BUFF2_WRITE            0x87            //write buffer2
#define    	BUFF1_TO_MEM           0x83            //BUFFER1 to Main Memory Page Program with Built-in Erase
#define    	BUFF2_TO_MEM           0x86            //BUFFER1 to Main Memory Page Program with Built-in Erase

//#define    BUFF1_READ             0xD4            //read Buff1
//#define    BUFF2_READ             0xD6            //read Buff2
#define    	BUFF1_READ             0x54            //read Buff1
#define   	BUFF2_READ             0x56            //read Buff2
#define    	MEM_TO_BUFF1           0x53            //
#define    	MEM_TO_BUFF2           0x55            //
//IC������
uint32		l_CardPageSize;	
uint32		l_CardStartAddr;	
uint32		l_CardPageNum;
uint8_t		l_CardTypeFlg;

//-------------------------------------------------------------------------------
//Status Register Format:
//   -----------------------------------------------------------------------
//  |  bit7  |  bit6   |  bit5  |  bit4  |  bit3  |  bit2  |  bit1  |  bit0  |
//  |--------|---------|---------|--------|---------|---------|---------|--------|
//  |RDY/BUSY|  COMP  |   0    |   1    |   1    |   1    |   X    |   X    | */
//
//bit7 - æ��ǣ�0Ϊæ1Ϊ��æ
//��Status Register��λ0�Ƴ�֮�󣬽�������ʱ���������н�ʹSPI�������������µ�״̬�ֽ��ͳ���
//bit6 - ������һ��Main Memory Page��Buffer�ıȽϽ����0��ͬ��1��ͬ��
//bit5
//bit4
//bit3
//bit2 - ��4λ������������ܶȣ�����AT45DB041B����4λӦ����0111��һ���ܱ��16�ֲ�ͬ�ܶȵ�����
//bit1
//bit0 - ��2λ��ʱ��Ч
//����ʵ�ֶ�AT45DB041DоƬ״̬�ֶ�������
//-------------------------------------------------------------------------------
uint8_t   StatusRegisterRead_Card(void)
{
    uint8_t Statues;

    WriteCS_IC(1);
    
	WriteCS_IC(0);
    WriteCS_IC(0);
    
    SentByte_SPI(READ_STU);                          	//���Ͷ�״̬�洢������
    Statues = RevByte_SPI();                       		//��ȡ״̬�Ĵ�������

    WriteCS_IC(1);

    return Statues;
}

//------------------------------------------------------------------------
// ��    �ƣ�   void   InitCardInfo(void)				
// ��    �ܣ�   ��ʼ��IC������     	
// ��ڲ�����  	��
// ���ڲ�����	��
//------------------------------------------------------------------------
void   InitCardInfo(void)								
{
	uint8_t	CardState;
	CardState = StatusRegisterRead_Card();
	
	if((CardState & 0x3c) == AT45DB041)
	{
		l_CardPageSize	= 256;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 2048;
		l_CardTypeFlg	= AT45DB041;
	}
	else if((CardState & 0x3c) == AT45DB161)
	{
		l_CardPageSize	= 512;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 4096;
		l_CardTypeFlg	= AT45DB161;		
	}	
	else if((CardState & 0x3c) == AT45DB321)
	{
		l_CardPageSize	= 512;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 8192;
		l_CardTypeFlg	= AT45DB321;		
	}	
	else if((CardState & 0x3c) == AT45DB642)
	{
		l_CardPageSize	= 1024;	
		l_CardStartAddr	= 0;	
		l_CardPageNum	= 8192;
		l_CardTypeFlg	= AT45DB642;		
	}		
	
	//printfcom0("\r\n l_CardPageSize %d l_CardStartAddr %d l_CardPageNum %d l_CardTypeFlg %d ",l_CardPageSize,l_CardStartAddr,l_CardPageNum,l_CardTypeFlg);	
}

//------------------------------------------------------------------------
// ��    �ƣ�   uint32   GetCardPageSize(void)			//ȡIC��ҳ��С
// ��    �ܣ�   ��ʼ��IC������     	
// ��ڲ�����  
// ���ڲ�����	
//------------------------------------------------------------------------
uint32   GetCardPageSize(void)							//ȡIC��ҳ��С
{
	return	l_CardPageSize;
}

//-------------------------------------------------------------------------------
//������
//    When the Flsh bit in the main memory array has been read,the device will
//    continue reading back at the beginning of the first page of memory.As w-
//    ith crossing over page boundaries,no Delays will be incurred when wrapp-
//    ing around from the end of the array to the beginning of the array.
//������
//    PA      - ҳ��ַ��0~2047
//    BFA     - ָ��BUFFER�е���ʼд���ַ
//    pHeader - ָ�����ݵ��׵�ַ
//    len     - ָ�����ݵĳ���
//��������������ȡAT45DB041D�洢�ռ书��
//------------------------------------------------------------------------------
void    ContinuousArrayRead_Card(uint16 PA,uint16 BFA,uint8_t *pHeader,uint16 Len)
{
    uint16 i = 0;
/**/
    while(i++ < 255)                                  		//ȷ��AT45DB041D׼��,ȷ��256�κ��˳��ȴ�
    {
        if(StatusRegisterRead_Card() & 0x80)              	//׼�����,���к�������
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);
    
    SentByte_SPI(CON_ARR_READ);                             //������������
    
    if(l_CardTypeFlg == AT45DB041)
    {
			SentByte_SPI((uint8_t)(PA>>7));            		//��ҳ��ַ
			SentByte_SPI((uint8_t)((PA<<1)|(BFA>>8)));   		//
			SentByte_SPI((uint8_t)BFA);                   	//��Buffer��ַ
		}
		else if(l_CardTypeFlg == AT45DB161)
		{
			SentByte_SPI((uint8_t)(PA>>6));            		//��ҳ��ַ
			SentByte_SPI((uint8_t)((PA<<2)|(BFA>>8)));     	//
			SentByte_SPI((uint8_t)BFA);   
		}
		else if(l_CardTypeFlg == AT45DB321)
		{
			SentByte_SPI((uint8_t)(PA>>6));              		//��ҳ��ַ
			SentByte_SPI((uint8_t)((PA<<2)|(BFA>>8)));     	//
			SentByte_SPI((uint8_t)BFA);   
		}	
		else if(l_CardTypeFlg == AT45DB642)
		{
			SentByte_SPI((uint8_t)(PA>>5));                	//��ҳ��ַ
			SentByte_SPI((uint8_t)((PA<<3)|(BFA>>8)));      	//
			SentByte_SPI((uint8_t)BFA);   
		}		

    SentByte_SPI(0x00);                                     //ʱ��Ҫ��
    SentByte_SPI(0x00);
    SentByte_SPI(0x00);
    SentByte_SPI(0x00);

    for(i=0;i<Len;i++)                                    	//����
    {
        pHeader[i] = RevByte_SPI();
    }
    
    WriteCS_IC(1);
}

//-----------------------------------------------------------------------------
//������
//    ��ָ������д���ĳ����ַ��0~263����ʼ��ҳ�У�����2�����������Ƚ�ָ������
//    д�뵽BUFFER 1����BUFFER 2�У����п���ָ��BUFFER�е���ʼд���ַ����д��
//    ������Ӱ��BUFFER��������ַ�е����ݣ�Ȼ���ٽ�BUFFER�е���������д�뵽ĳָ
//    ��ҳ��(��Ԥ����)��
//������
//    buffer  - ѡ��BUFFER��01Hѡ��BUFFER 1��02Hѡ��BUFFER 2
//    PA      - ҳ��ַ��0~2047
//    BFA     - ָ��BUFFER�е���ʼд���ַ
//    pHeader - ָ�����ݵ��׵�ַ
//    len     - ָ�����ݵĳ���
//--------------------------------------------------------------------------------
void    MainMemoryToBuff(uint8_t Buffer,uint16 PA)
{
    uint16 i = 0;

    while(i++<3000)                                         //ȷ��AT45DB041DΪ��æ,ȷ��1000�κ��˳��ȴ�
    {
        if(StatusRegisterRead_Card()&0x80)
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);
    
    switch(Buffer)                                          //ѡBuffer
    {
        case 1:SentByte_SPI(MEM_TO_BUFF1);break;
        case 2:SentByte_SPI(MEM_TO_BUFF2);break;
    }
    if(l_CardTypeFlg == AT45DB041)
    {
	    SentByte_SPI((uint8_t)(PA>>7));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<1));
	}
	else if(l_CardTypeFlg == AT45DB161)
	{
		SentByte_SPI((uint8_t)(PA>>6));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<2));
	}
	else if(l_CardTypeFlg == AT45DB321)
	{
		SentByte_SPI((uint8_t)(PA>>6));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<2));
	}	
	else if(l_CardTypeFlg == AT45DB642)
	{
		SentByte_SPI((uint8_t)(PA>>5));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<3));
	}		
		
    SentByte_SPI(0x00);

    WriteCS_IC(1);
}


//------------------------------------------------------------------------------
//������
//    ��ָ������д���ĳ����ַ��0~263����ʼ��BUFFER�С�
//������
//    buffer  - ѡ��BUFFER��01Hѡ��BUFFER 1��02Hѡ��BUFFER 2
//              �ڸ�ָ�������У�������84Hѡ��BUFFER 1��87Hѡ��BUFFER 2
//    BFA     - BUFFER�е���ʼ��ַ��0~263
//    pHeader - �������ݵ�ͷָ��
//    len     - �������ݵĳ���1~l_CardPageSize
//----------------------------------------------------------------------------
void    BufferRead_Card(uint8_t Buffer,uint16 PA,uint16 BFA,uint8_t *pHeader,uint16 Len)
{
    uint16 i;

	MainMemoryToBuff(Buffer,PA);							//��ȡָ����ҳ����

    while(i++<5000)                                       	//ȷ��AT45DB041DΪ��æ,ȷ��500�κ��˳��ȴ�
    {
        if(StatusRegisterRead_Card() & 0x80)
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);

    switch(Buffer)                                       	//ѡ��buffer
    {
        case 1:SentByte_SPI(BUFF1_READ);break;             	//��buffer1 д����
        case 2:SentByte_SPI(BUFF2_READ);break;             	//��buffer2 д����
    }
    
    SentByte_SPI(0x00);
    SentByte_SPI((uint8_t)(BFA>>8));                          //A8��ַ
    SentByte_SPI((uint8_t)BFA);                               //A7~A0
    SentByte_SPI(0x00);

    for(i=0;i<Len;i++)                                 		//дBuffer
    {
        pHeader[i] = RevByte_SPI();
    }

    WriteCS_IC(1);
}

//---------------------------------------------------------------------------
//������
//    ��ָ������д���ĳ����ַ��0~263����ʼ��BUFFER�С�
//������
//    buffer  - ѡ��BUFFER��01Hѡ��BUFFER 1��02Hѡ��BUFFER 2
//              �ڸ�ָ�������У�������84Hѡ��BUFFER 1��87Hѡ��BUFFER 2
//    BFA     - BUFFER�е���ʼ��ַ��0~263
//    pHeader - �������ݵ�ͷָ��
//    len     - �������ݵĳ���1~l_CardPageSize
//----------------------------------------------------------------------------
void    BufferWrite_Card(uint8_t Buffer,uint16 BFA,uint8_t *pHeader,uint16 Len)
{
    uint16 i;
/*
    while(i++<500)                                      	//ȷ��AT45DB041DΪ��æ,ȷ��500�κ��˳��ȴ�
    {
        if(StatusRegisterRead_Card() & 0x80)
        {
            break;
        }
    }
*/
    WriteCS_IC(0);

    switch(Buffer)                                        	//ѡ��buffer
    {
        case 1:SentByte_SPI(BUFF1_WRITE);break;             //��buffer1 д����
        case 2:SentByte_SPI(BUFF2_WRITE);break;             //��buffer2 д����
    }
    
    SentByte_SPI(0x00);
    SentByte_SPI((uint8_t)(BFA>>8));                          //A8��ַ
    SentByte_SPI((uint8_t)BFA);                               //A7~A0

    for(i=0;i<Len;i++)                                   	//дBuffer
    {
        SentByte_SPI(pHeader[i]);
    }

    WriteCS_IC(1);
}

//-----------------------------------------------------------------------------
//������
//    ��ָ������д���ĳ����ַ��0~263����ʼ��ҳ�У�����2�����������Ƚ�ָ������
//    д�뵽BUFFER 1����BUFFER 2�У����п���ָ��BUFFER�е���ʼд���ַ����д��
//    ������Ӱ��BUFFER��������ַ�е����ݣ�Ȼ���ٽ�BUFFER�е���������д�뵽ĳָ
//    ��ҳ��(��Ԥ����)��
//������
//    buffer  - ѡ��BUFFER��01Hѡ��BUFFER 1��02Hѡ��BUFFER 2
//    PA      - ҳ��ַ��0~2047
//    BFA     - ָ��BUFFER�е���ʼд���ַ
//    pHeader - ָ�����ݵ��׵�ַ
//    len     - ָ�����ݵĳ���
//--------------------------------------------------------------------------------
void    BufferToMainMemoryPageProgramWithBuilt_inErase_Card(uint8_t Buffer,uint16 PA,uint16 BFA,uint8_t *pHeader,uint16 Len)
{
    uint16 i = 0;

    BufferWrite_Card(Buffer,BFA,pHeader,Len);         		//дbuffer����

    while(i++<3000)                                         //ȷ��AT45DB041DΪ��æ,ȷ��1000�κ��˳��ȴ�
    {
        if(StatusRegisterRead_Card()&0x80)
        {
            break;
        }
        
        //SysHoldTast();
    }

    WriteCS_IC(0);
    
    switch(Buffer)                                          //ѡBuffer
    {
        case 1:SentByte_SPI(BUFF1_TO_MEM);break;
        case 2:SentByte_SPI(BUFF2_TO_MEM);break;
    }
    if(l_CardTypeFlg == AT45DB041)
    {
	    SentByte_SPI((uint8_t)(PA>>7));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<1));
	}
	else if(l_CardTypeFlg == AT45DB161)
	{
		SentByte_SPI((uint8_t)(PA>>6));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<2));
	}
	else if(l_CardTypeFlg == AT45DB321)
	{
		SentByte_SPI((uint8_t)(PA>>6));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<2));
	}	
	else if(l_CardTypeFlg == AT45DB642)
	{
		SentByte_SPI((uint8_t)(PA>>5));                       //ȷ��ҳ��ַ
	    SentByte_SPI((uint8_t)(PA<<3));
	}		
	
    SentByte_SPI(0x00);

    WriteCS_IC(1);
}

static	uint8_t	l_CardBufNum;
//extern	SysFastHoldTast(void);
//---------------------------------------------------------------------
//��    �ƣ�   ReadCard(uint32 Addr,uint32 *buf,uint32 Len)
//��    �ܣ�   ��ָ����IC��ֵ������
//��ڲ�����   Addr    ��ȡ���ݵĵ�ַ       ��ַ��0~Sizeof(IC)
//             buf     ��ȡ����õĻ�����
//             Len     ���������ݳ���  ��8λ������Ϊ���ȵ�λ
//���ڲ�����   ��
//----------------------------------------------------------------------
uint8_t ReadCard(uint32 Addr,uint8_t *TargetBuf,uint32 Len)
{
    uint16	PageNum;                                                    //ҳ
	uint16	PageOffset;                                                 //ҳ�ڵ�ַ
	uint16  ReadPageTimes;                                              //��ҳ����       
	uint16  LenTemp;                                                  	//����         
	uint16  i;
	uint32  BufOffset = 0;
    uint32  AddrTemp; 
	uint32	PageNoReadSize;
	uint32	BufNoReadSize;
	
	AddrTemp =  Addr; 
    AddrTemp += l_CardStartAddr;                                      	//ӳ�䵽IC���ڲ�
               
    if(AddrTemp + Len > l_CardStartAddr + l_CardPageNum*l_CardPageSize)    
    {
       //printfcom0("\r\n READ AddrTemp + Len %d > l_CardStartAddr + l_CardPageNum*l_CardPageSize %d  ", 
//       								AddrTemp + Len,l_CardStartAddr + l_CardPageNum*l_CardPageSize);
       return  FALSE;                                                   //��ַ����
    }

    PageNum         = AddrTemp / l_CardPageSize ;                     	//��ҳ
    PageOffset      = AddrTemp % l_CardPageSize ;                     	//��ҳ�ڵ�ַ
    ReadPageTimes   = (Len + PageOffset  + (l_CardPageSize - 1)) / l_CardPageSize;            
    /* 																	//��ҳ����        
    for(i = 0; i < ReadPageTimes; i++)
    {
        PageNoReadSize = 	l_CardPageSize - (PageOffset + BufOffset)
        					 % l_CardPageSize;							//����IC��һҳ��δд��ַ
        BufNoReadSize	=	Len - BufOffset;							//������δ�����ֽڳ���
        LenTemp = (PageNoReadSize < BufNoReadSize ? PageNoReadSize:BufNoReadSize);
        																//ȡ��һҳд����δ�����ֽڳ���
	    BufferRead_Card(((l_CardBufNum++%2)+1),PageNum,PageOffset
	    							,(uint8_t *)&TargetBuf[BufOffset],LenTemp);	
	    																//ȡ�� 
        BufOffset += LenTemp;
        PageNum++; 
    }
    */
    
    for(i = 0; i <= ReadPageTimes; i++)
    {
    	//SysFastHoldTast();

        PageNoReadSize = 	l_CardPageSize - (PageOffset + BufOffset)
        					 % l_CardPageSize;						//����IC��һҳ��δд��ַ
        BufNoReadSize	=	Len - BufOffset;						//������δ�����ֽڳ���
        LenTemp = (PageNoReadSize < BufNoReadSize ? PageNoReadSize:BufNoReadSize);
        																//ȡ��һҳд����δ�����ֽڳ���  
        ContinuousArrayRead_Card(PageNum,PageOffset,(uint8_t *)&TargetBuf[BufOffset],LenTemp);	//ȡ�� 
                
        BufOffset += LenTemp;
        PageOffset += LenTemp;
        PageOffset %= l_CardPageSize;
        
        PageNum++; 
    }
    
    //NOP(); 
    return  TRUE;	                                                    //��ȷ                   
}

//---------------------------------------------------------------------
//��    �ƣ�   uint8_t WriteCardPartPage(uint16 PageNum,SegmentNum,uint8_t *Buf,uint32 Len)

//��    �ܣ�   дҳ�е�һ����,Ҫ��SegmentNum+Len <= l_CardPageSize
//��ڲ�����   PageNum  ҳ��        ��ַ��0~Sizeof(IC)
//             Buf:     ���ݻ���    
//���ڲ�����   д�ɹ�
//----------------------------------------------------------------------
uint8_t WriteCardPage(uint16 PageNum,uint16 SegmentNum,uint8_t *Buf,uint32 Len)
{
    uint8_t   IC_BufTemp[256*4];  

    if(PageNum > l_CardPageNum || (SegmentNum + Len) > l_CardPageSize )
    {
        return  FALSE;
    }     
    if(Len == l_CardPageSize)                                         //д����ҳ
    {
        BufferToMainMemoryPageProgramWithBuilt_inErase_Card(((l_CardBufNum++%2)+1),PageNum,0,Buf,l_CardPageSize);
    }
    else 
    {
        ContinuousArrayRead_Card(PageNum, 0 , IC_BufTemp, l_CardPageSize); 				//IC������PageNumҳ
        memcpy((uint8_t *)&IC_BufTemp[SegmentNum], Buf ,Len);                            //���������

        BufferToMainMemoryPageProgramWithBuilt_inErase_Card(((l_CardBufNum++%2)+1),PageNum,0,IC_BufTemp,l_CardPageSize);
    }
    
    //NOP();
    return  TRUE;    
}

//---------------------------------------------------------------------
// ��    �ƣ�   WriteCard()
// ��    �ܣ�   ָ�����������ݱ�̡�
// ��ڲ�����   Addr    ��̵�ַ(�ڲ���ַ)
//						��ַ��00 ~ CARD_SIZE  
//
//              buf     ������ݻ����� ע�⣺��Ϊ16λ��

//              Len     ������ݳ���  ��8λ��д������Ϊ���ȵ�λ���൱�� Len ���ֽ���Ŀ

// ���ڲ�����   ����TRUE��ʾ�����ɹ�������FALSE��ʾ����ʧ��
//---------------------------------------------------------------------
uint8_t WriteCard(uint32 Addr,uint8_t *SourceBuf,uint16 Len)
{
    uint16	PageNum;                                                    //ҳ
	uint16	PageOffset;                                                 //ҳ�ڵ�ַ
	uint32  AddrTemp; 
	uint16  WritePageTimes;                                             //дҳ����       
	uint16  LenTemp;                                                  	//����         
	uint16  i;
	uint16  BufOffset = 0;
	uint32	PageNoWriteSize;
	uint32	BufNoWriteSize;
	
	AddrTemp =  Addr; 
    AddrTemp += l_CardStartAddr;                                      	//ӳ�䵽IC���ڲ�
              
    if(AddrTemp + Len > l_CardStartAddr + l_CardPageNum*l_CardPageSize)    
    {
       return  FALSE;                                                   //��ַ����
    }

    PageNum         = AddrTemp / l_CardPageSize ;                     	//��ҳ
    PageOffset      = AddrTemp % l_CardPageSize ;                     	//��ҳ�ڵ�ַ
    WritePageTimes  = (Len + PageOffset + (l_CardPageSize - 1)) / l_CardPageSize;            	//��ҳ����
    
    for(i = 0; i < WritePageTimes; i++)
    {
    	//SysFastHoldTast();

        PageNoWriteSize = 	l_CardPageSize - (PageOffset + BufOffset)
        					 % l_CardPageSize;							//����IC��һҳ��δд��ַ
        BufNoWriteSize	=	Len - BufOffset;							//������δд�ֽڳ���
        LenTemp = (PageNoWriteSize < BufNoWriteSize ? PageNoWriteSize:BufNoWriteSize);
        																//ȡ��һҳд���򽫻��干д���ֽڳ���
        WriteCardPage(PageNum,PageOffset,(uint8_t *)&SourceBuf[BufOffset],LenTemp);     //ȡ�� 

        BufOffset += LenTemp;
        PageOffset += LenTemp;
        PageOffset %= l_CardPageSize;
        
        PageNum++; 
    }

    return  TRUE;	                                                    //��ȷ  
}

//---------------------------------------------------------------------
// ��    �ƣ�   uint32 GetToEndLen(uint32 Addr)
// ��    �ܣ�   ָ����ָ����ַ�����Ľ����ĳ���
// ��ڲ�����   Addr    ָ����ַ
// ���ڲ�����   ���س���
//---------------------------------------------------------------------
uint32 GetToEndLen(uint32 Addr)
{
	return	(l_CardStartAddr + l_CardPageNum*l_CardPageSize - Addr);
}

static	uint8_t   mPlugInFlg = NO_PLUG_IN_CARD;                     		//��Ƭ�����ʶ

static uint32   mPlugTime  = 0;											//û�в忨����
static uint32   mNoPlugTime= 0;

uint8_t		l_CardErrorFlg = NO_ERROR;
uint8_t		l_LongTimePlugCardErrFlg = NO_ERROR;

//---------------------------------------------------------------------
// ��    �ƣ�   void   PlugCard( void )
// ��    �ܣ�   �ж��Ƿ��п�Ƭ����
// ��ڲ�����   ��
// ���ڲ�����   ��
//---------------------------------------------------------------------
void   PlugCard( void )
{
    if(ReadIC_SWT() == 1)                               //�ж��Ƿ���뿨Ƭ
    {
        mPlugTime++;                                   	//�п�����

        if( mPlugTime > 20)                          	//ȥ����,�Ƿ���뿨Ƭ
        {
            mPlugInFlg = PLUG_IN_CARD;              	//�п�
            
            mNoPlugTime = 0;
        }
    }
    else
    {            
        mNoPlugTime++;                                   //�п�����

        if( mNoPlugTime > 20)                            //ȥ����,�Ƿ���뿨Ƭ
        {
            mPlugInFlg = NO_PLUG_IN_CARD;             	//�޿�

          	l_LongTimePlugCardErrFlg = NO_ERROR;

            mPlugTime = 0;
            
      	//	ReStartPluse();							//�����ٲ���
        }
    }
    
    ////printfcom0("\r\n mPlugInFlg %d",mPlugInFlg);
}


//---------------------------------------------------------------------
// ��    �ƣ�   void   HoldCard( void )
// ��    �ܣ�   IC������ά��
// ��ڲ�����   ��
// ���ڲ�����   ��
//---------------------------------------------------------------------
void   HoldCard( void )
{
	PlugCard();
}

//---------------------------------------------------------------------
// ��    �ƣ�   uint8_t   GetPlugFlg()
// ��    �ܣ�   ���ز忨��־
// ��ڲ�����   ��
// ���ڲ�����   TRUE:�п�����,FALSE:�޿����� 
//---------------------------------------------------------------------
uint32   GetPlugTime(void)
{
    return  mPlugTime;
}

//extern	void ClosePluseInput(void);
//---------------------------------------------------------------------
// ��    �ƣ�   uint8_t   GetPlugFlg()
// ��    �ܣ�   ���ز忨��־
// ��ڲ�����   ��
// ���ڲ�����   TRUE:�п�����,FALSE:�޿����� 
//---------------------------------------------------------------------
uint8_t   GetPlugFlg(void)
{
	if(mPlugInFlg == NO_PLUG_IN_CARD)
	{
		WritePOW_IC( 1 );								//�ص�Դ
	}
	else
	{
		WritePOW_IC( 0 );								//����Դ
	}
		
    return  mPlugInFlg;
}

//---------------------------------------------------------------------
// ��    �ƣ�   uint8_t   GetPlugFlg()
// ��    �ܣ�   ���ز忨��־
// ��ڲ�����   ��
// ���ڲ�����   TRUE:�п�����,FALSE:�޿����� 
//---------------------------------------------------------------------
void   ResetPlugFlgEvt(void)
{
    //mPlugInFlg = NO_PLUG_IN_CARD;						//���α�ʾ�Զ��ж�
}

//---------------------------------------------------------------------
// ��    �ƣ�   void   LongTimePlugCard( void )
// ��    �ܣ�   ��ʱ�����IC������
// ��ڲ�����   ��
// ���ڲ�����   ��
//---------------------------------------------------------------------
uint8_t   LongTimePlugCard( void )
{
	l_LongTimePlugCardErrFlg = NO_ERROR;
	
	if(GetPlugTime() > 10*60*100)
	{
		l_LongTimePlugCardErrFlg = ERROR;
	}
	
	return	l_LongTimePlugCardErrFlg;
}

//---------------------------------------------------------------------
// ��    �ƣ�   void   GetLongTimePlugCardErrFlg( void )
// ��    �ܣ�   ��ʱ�����IC������
// ��ڲ�����   ��
// ���ڲ�����   ��
//---------------------------------------------------------------------
uint8_t   GetLongTimePlugCardErrFlg( void )
{
	return	l_LongTimePlugCardErrFlg;
}


//void	ReStartPluse(void);										//�ز��ٲ���
//---------------------------------------------------------------------
// ��    �ƣ�   uint8_t   PlugICCard(void)
// ��    �ܣ�   �ж��Ƿ����IC��
// ��ڲ�����   ��
// ���ڲ�����   TRUE:�п�����,FALSE:�޿����� 
//---------------------------------------------------------------------
uint8_t PlugICCard(void)
{
	uint8_t	CardSta;
	uint8_t	Flg;
	uint8_t	Times;

    Times 	= 3; 
    Flg 	= FALSE;
              
    while(Times-- && Flg == FALSE) 							//�ж�3��
    {        
	    NOP();
		if(GetPlugFlg() == PLUG_IN_CARD)					//�п�����
	    {
	    	WritePOW_IC( 0 );								//����Դ

			DelayX10ms(20);
							
			CardSta = StatusRegisterRead_Card();			//��IC��״̬
			
			if(	(	((CardSta & AT45DB041) == AT45DB041) 
				|| 	((CardSta & AT45DB161) == AT45DB161)
		 		|| 	((CardSta & AT45DB321) == AT45DB321)
		 		|| 	((CardSta & AT45DB642) == AT45DB642))
				&& 	( CardSta != 0xff) )
			{
				l_CardErrorFlg = NO_ERROR;					//�忨���ʹ���
				
				InitCardInfo();								//��ʼ������Ϣ

				Flg = TRUE; 								//����1	
				break;		
			}	
			else
			{		 
				l_CardErrorFlg = ERROR;						//�ÿ�����
				
				Flg = FALSE;
			}	

		}
		else
		{
			l_CardErrorFlg = NO_ERROR;							//����
			
			Flg = FALSE;

			break;	
		}
	}
	
	if(Flg == FALSE)
	{
		WritePOW_IC( 1 );										//�ǿ����ص�Դ
	}
	
	return 	Flg;
}

//---------------------------------------------------------------------
// ��    �ƣ�   uint8_t   GetCardErrorFlg()
// ��    �ܣ�   ���ز忨�����־
// ��ڲ�����   ��
// ���ڲ�����   TRUE:���뿨������ȷ,FALSE:���뿨���ʹ��� 
//---------------------------------------------------------------------
uint8_t   GetCardErrorFlg(void)
{
    return  l_CardErrorFlg;
}

#define		RIGHT_DATA					0xff
#define		CARD_TYPE_ERR				62
#define		CARD_PLUG_LONG_TIME_ERR		61
#define		USB_TYPE_ERR				66

extern	uint8_t	l_UsbErrFlg;
#define		ERR_USB_UNKNOWN 			0xFA

//extern	uint8_t	TestCH376Host( void );
//-------------------------------------------------------------------------------------------------
//��������:            	uint8_t  JudgeCardError(void) 
//��������:             ��IC���Ŀ����ͽ����ж�
//��ڲ���:            
//���ڲ���:             
//--------------------------------------------------------------------------------------------------
uint8_t  JudgeCardError(void) 
{
	uint8_t		ErrorType;
	
	#ifdef	HARD_VER_111122	
	static		uint32	Times = 0;
	#endif
	
	ErrorType = RIGHT_DATA;
	
	if(GetCardErrorFlg() == ERROR)
	{
//		ErrorType = CARD_TYPE_ERR;
	}
	
	if(GetLongTimePlugCardErrFlg() == ERROR)
	{
		ErrorType = CARD_PLUG_LONG_TIME_ERR;
	}
	
	#ifdef	HARD_VER_111122	
	if(TestCH376Host() == ERR_USB_UNKNOWN)
	{
		if(Times++ < 10)
		{
			mInitCH376Host();
		}

		ErrorType = USB_TYPE_ERR;
	}
	else
	{
		Times = 0;
	}
	#endif
	
	return	ErrorType;
}

