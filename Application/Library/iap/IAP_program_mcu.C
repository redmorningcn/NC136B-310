#include  "includes.h"

//#define	CVI	0

#define	USER_APP_START_ADDR		0x00040000	
#define	USER_APP_PRO_SIZE		0x0002FFFF	

#define	IAP_DATA_LEN		    128
#define SEC_DIV_TIMENS          (IAP_WRITE_1024/IAP_DATA_LEN)

//���IAP������ַ
//#define	IAP_PARA_START_ADDR     0x00070000	
//#define	IAP_PARA_PRO_SIZE		0x00010000	
#define	IAP_PARA_START_ADDR     0x00070000	
#define	IAP_PARA_PRO_SIZE		0x0000FFFF	

#define zyIrqDisable()  __disable_irq()
#define zyIrqEnable()   __enable_irq()


/*******************************************************************************
 * TYPEDEFS
 */
typedef  struct   _stcIAPCtrl_
{
    char    buf[1024];      //������
    int     addr;           //���ݵ�ַ
}stcIAPCtrl;

typedef  struct   _stcIAPPara_
{
    uint16  hardver;        //Ӳ���汾
    uint16  softver;        //�����汾
    uint32  softsize;       //������С
    uint32  addr;           //��ǰ��ַ
    uint32  framenum;       //֡���
    uint16  code;           //ָ���� 01����ʾ����ȷ�Ŀ���
    uint16  crc16;
}stcIAPPara;

/*******************************************************************************
 * LOCAL VARIABLES
 */
stcIAPPara  gsIAPPara;
stcIAPCtrl  gsIAPCtrl;      //��������

/*******************************************************************************
 * ��    �ƣ� IAP_ReadDeviceInfo
 * ��    �ܣ� ��оƬ��Ϣ
 * ��ڲ����� ��
 * ���ڲ����� ��
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-08-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void    IAP_ReadDeviceInfo(void)
{
    IAP_STATUS_CODE status;    
    uint8_t ver_major, ver_minor; 
    uint32_t result[4];

    zyIrqDisable();										//���ж�
    
    status = ReadPartID(result);                        //��оƬID
    status = ReadBootCodeVer(&ver_major, &ver_minor);   //����������汾
    status = ReadDeviceSerialNum(result);               //���豸ID��    
    
    zyIrqEnable();                                      //дflash���ʱ����ȫ���ж�
}

/*******************************************************************************
 * ��    �ƣ� IAP_WriteParaFlash
 * ��    �ܣ� ��IAP��������д��Flash��
 * ��ڲ����� stcIAPCtrl
 * ���ڲ����� ��
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-08-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void    IAP_WriteParaFlash(stcIAPPara *sIAPPara)
{
    IAP_STATUS_CODE status;
    uint32_t result[4];

    uint32_t flash_prog_area_sec_start;
    uint32_t flash_prog_area_sec_end;
    
    zyIrqDisable();										                                //���ж�

    flash_prog_area_sec_start   = 	GetSecNum(IAP_PARA_START_ADDR);
    flash_prog_area_sec_end 	=  	GetSecNum(IAP_PARA_START_ADDR + IAP_PARA_PRO_SIZE); //׼������

    status = EraseSector(flash_prog_area_sec_start, flash_prog_area_sec_end);           //һ����д����
    status = BlankCheckSector(flash_prog_area_sec_start, flash_prog_area_sec_end,
                &result[0], &result[1]);
    
    //��ʼflash��д,д����������
    status 	= CopyRAM2Flash( (uint8_t *)IAP_PARA_START_ADDR,
                                  (uint8 *)sIAPPara,
                                   256
                            );                                                          //��������
    
    status =  Compare((uint8_t *)IAP_PARA_START_ADDR,
                            (uint8 *)sIAPPara,
                            sizeof(stcIAPPara)
                    );                                                                  //�Ƚ�����
            
    zyIrqEnable();                                                                      //дflash���ʱ����ȫ���ж�
}


/*******************************************************************************
 * ��    �ƣ� IAP_WriteParaFlash
 * ��    �ܣ� ��IAP��������д��Flash��
 * ��ڲ����� stcIAPCtrl
 * ���ڲ����� ��
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-08-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void    IAP_ReadParaFlash(stcIAPPara *sIAPPara)
{
    IAP_STATUS_CODE status;
    uint32_t result[4];
    
    uint32_t flash_prog_area_sec_start;
    uint32_t flash_prog_area_sec_end;
    
    zyIrqDisable();                                 //���ж�
                                                    //����copy
    memcpy((uint8 *)sIAPPara,(uint8 *)IAP_PARA_START_ADDR,sizeof(stcIAPPara));
            
    zyIrqEnable();                                  //��ȫ���ж�
}

/*******************************************************************************
 * ��    �ƣ� IAP_WriteFlash
 * ��    �ܣ� ������д��Flash��
 * ��ڲ����� stcIAPCtrl
 * ���ڲ����� ��
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-08-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
void    IAP_WriteFlash(stcIAPCtrl *sIAPCtrl)
{
    IAP_STATUS_CODE status;
    uint32_t result[4];

    uint32_t flash_prog_area_sec_start;
    uint32_t flash_prog_area_sec_end;
    
    zyIrqDisable();										//���ж�

    //����ӳ������ص�ַ��ʼ�����Ȳ������IAP��ַ���ݡ�
    if(sIAPCtrl->addr == USER_APP_START_ADDR)
    {
        flash_prog_area_sec_start   = 	GetSecNum(USER_APP_START_ADDR);
        flash_prog_area_sec_end 	=  	GetSecNum(USER_APP_START_ADDR + USER_APP_PRO_SIZE);//׼������

        status = EraseSector(flash_prog_area_sec_start, flash_prog_area_sec_end);           //һ���Բ�������

        status = BlankCheckSector(flash_prog_area_sec_start, flash_prog_area_sec_end,
                      &result[0], &result[1]);
    }
    
    //��ʼflash��д
    status 	= CopyRAM2Flash((uint8 *)sIAPCtrl->addr,
                                     sIAPCtrl->buf,
                                     IAP_WRITE_1024
                            );                      //��������
    
    status =  Compare((uint8 *) sIAPCtrl->addr,
                                sIAPCtrl->buf,
                                IAP_WRITE_1024);    //�Ƚ�����
    
    sIAPCtrl->addr += IAP_WRITE_1024;              //���ݵ�ַ�ۼ�  
        
    zyIrqEnable();                                  //дflash���ʱ����ȫ���ж�
}
                       
                       
void Boot( void );

/*******************************************************************************
 * ��    �ƣ� IAP_PragramDeal
 * ��    �ܣ� �Դ������ݴ���
 * ��ڲ����� �����������ݳ���
 * ���ڲ����� ָ��ɹ�������1�����򣬷���0��������󣬷��ظ�ֵ
                -1������֡��Ų�����
                -2��ָ�ʶ��
 * �������ߣ� redmorningcn.
 * �������ڣ� 2017-08-08
 * ��    �ģ�
 * �޸����ڣ�
 *******************************************************************************/
int8    IAP_PragramDeal(uint8 *databuf,char datalen)
{
    uint16  iapcode;                                        //����������
    uint16  iapnum;                                         //�������
    uint16  crc16;
    static  uint16  lastiapnum = 0;                         //��һ֡���
    static  uint8   times = 0;
    static  uint16  bufsize = 0;
    
    if(datalen < 2 || datalen > 256)                        //�����쳣���˳�
        return  0;
    
    memcpy((char *)&iapcode,databuf,sizeof(iapcode));       //ȡ����������
    
    switch(iapcode)
    {
        case 0x01:                                          //��ʼ����ָ����Ƕ�������
                                                            //�˵����������ĵ�ַ�������迼�ǣ�������ż����ַ��
            gsIAPCtrl.addr = USER_APP_START_ADDR;           //��ʼ����ʱ����ʼ����ַ��
            
            memcpy(&gsIAPPara,&databuf[sizeof(iapcode)],2+2+4+4+2); //cpoyӲ���汾�������汾�������С����ǰ��ַ����ǰ֡��
            
            break;
        case 0x02:                                          //�������ݰ�
            memcpy((char *)&iapnum,&databuf[sizeof(iapcode)],sizeof(iapnum));   //ȡ֡���
            
            if( iapnum )                                    //��Ŵ���0�����ж�ǰ��֡��������ԡ�(�����������ж�)
                if(iapnum != lastiapnum+1)
                    return -1; 
            
            lastiapnum = iapnum;                            //��Ÿ�ֵ
             
            memcpy(&gsIAPCtrl.buf[(iapnum % SEC_DIV_TIMENS)*IAP_DATA_LEN],
                   &databuf[2+2],
                   IAP_DATA_LEN);                                //�������ݵ�����������
            
            bufsize += IAP_DATA_LEN;
            //׼������
            if(  (iapnum % SEC_DIV_TIMENS ) == (SEC_DIV_TIMENS - 1) 
               || (datalen -4) != IAP_DATA_LEN )                 //������ݴ���1024�ֽڣ�������������������дflash������
            {
                if((datalen - 4) != IAP_DATA_LEN)                 //���������������1024�ֽ�ʣ��ռ�д0xff
                {
                    for(int i = (iapnum % SEC_DIV_TIMENS ) * IAP_DATA_LEN;i < IAP_WRITE_1024;i++ )
                    gsIAPCtrl.buf[i] = 0xff;	
                }
                
                IAP_WriteFlash(&gsIAPCtrl);                 //д����(��ַ��gsIAPCtrl.addr����д��)
                
                bufsize = 0;
            }
            
            break;
            
         //��������ָ��   //������������������жϡ������С�� //д������ɱ�ʾ
        case 0x03:                                          
                                                            
                                                            
            if( bufsize )                                   //��������δд�룬����д��
            {
                 IAP_WriteFlash(&gsIAPCtrl);                 //д����(��ַ��gsIAPCtrl.addr����д��)
            }
                
            memcpy(&gsIAPPara,&databuf[sizeof(iapcode)],2+2+4+4+2); //cpoyӲ���汾�������汾�������С����ǰ��ַ����ǰ֡��
           
            if(     gsIAPPara.softsize > (gsIAPCtrl.addr - USER_APP_START_ADDR)     //�����С�����������˳���
               ||   (gsIAPCtrl.addr - USER_APP_START_ADDR - IAP_WRITE_1024) > gsIAPPara.softsize
               )
                return -3;
            
            //��������С�������Ϊ������ȷ���޸����سɹ���ʾ
            gsIAPPara.code = 0x01;
            gsIAPPara.crc16 = GetCrc16Check((uint8 *)&gsIAPPara,sizeof(gsIAPPara)-2);
            IAP_WriteParaFlash(&gsIAPPara);
            
            //Boot();                                         //������ת
            break;
        case 0x04:                                          //��ֹ����ָ��
            gsIAPCtrl.addr = USER_APP_START_ADDR;           //��ʼ����ַ��

            break;  
        default:    //����ָ�ֱ�ӷ���
            return -2;
            ;
    }
    
    return 1;
}


typedef  void (*pFunction)(void);			    //����һ���������͵Ĳ���.

/*******************************************************************************
 * LOCAL VARIABLES
 */
/***********************************************
* ���������庯��ָ��
*/
pFunction   pApp;

void Boot( void )
{
    u32     JumpAddress = 0;
    u8      cpu_sr;
    //SCB->VTOR = USER_APP_START_ADDR & 0x1FFFFF80;	

	//JMP_Boot(USER_APP_START_ADDR);
    
//   __ASM void JMP_Boot( uint32_t address ){
//   LDR SP, [R0]		;Load new stack pointer address
//   LDR PC, [R0, #4]	;Load new program counter address
//   }

    CPU_CRITICAL_ENTER();

    JumpAddress   =*(volatile u32*) (USER_APP_START_ADDR + 4); // ��ַ+4ΪPC��ַ
    pApp          = (pFunction)JumpAddress;                     // ����ָ��ָ��APP
    __set_MSP       (*(volatile u32*) USER_APP_START_ADDR);    // ��ʼ������ջָ�루MSP��
    __set_PSP       (*(volatile u32*) USER_APP_START_ADDR);    // ��ʼ�����̶�ջָ�루PSP��
    __set_CONTROL   (0);                                        // ����CONTROL
    
    pApp();                                                     //��ת����
    
    //(*pApp)();
    
    CPU_CRITICAL_EXIT();

}