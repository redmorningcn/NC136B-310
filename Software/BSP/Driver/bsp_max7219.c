/*******************************************************************************
 *   Filename:      bsp_max7219.c
 *   Revised:       $Date: 2015-12-07$
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
#include <includes.h>
#include <global.h>
#include <app_lib.h>
#include <string.h>
#include <stdlib.h> 
#include <bsp_max7219.h>

#define BSP_MAX7219_MODULE_EN 1
#if BSP_MAX7219_MODULE_EN > 0
/*******************************************************************************
 * CONSTANTS
 */
/***********************************************
* ������ max7219�Ĵ�����ַ����
*/
#define MAX7279_NON_OPT         0x00            // �ղ����Ĵ���
#define Digit0                  0x01            // �����1�Ĵ���
#define Digit1                  0x02            // �����2�Ĵ���
#define Digit2                  0x03            // �����3�Ĵ���
#define Digit3                  0x04            // �����4�Ĵ���
#define Digit4                  0x05            // �����5�Ĵ���
#define Digit5                  0x06            // �����6�Ĵ���
#define Digit6                  0x07            // �����7�Ĵ���
#define Digit7                  0x08            // �����8�Ĵ���
/**/
#define MAX7279_DECODE_MODE     0x09            // ����ģʽ�Ĵ���
#define MAX7279_BRIGHTNESS      0x0a            // ���ȼĴ���
#define MAX7279_SCAN            0x0b            // ɨ��λ���Ĵ���
#define MAX7279_LOW_PWR         0x0c            // �͹���ģʽ�Ĵ���
#define MAX7279_DISP_TEST       0x0f            // ��ʾ���ԼĴ���

/***********************************************
* ������ max7219���ƼĴ�������
*/
#define MAX7279_LOW_PWR_MODE    0x00            // �͹��ķ�ʽ
#define MAX7279_NORMAL_MODE     0x01            // ����������ʽ
#define MAX7279_DECODE_SET      0x00            // �������ã�8λ��ΪBCD��;��8����������
#define MAX7279_8_DIGIT_SCAN    0x07            // ɨ��λ�����ã���ʾ8λ�����
#define MAX7279_4_DIGIT_SCAN    0x03            // ɨ��λ�����ã���ʾ4λ�����
//#define MAX7279_BRIGHTNESS_LEVEL    0x00      // ���ȼ�������
#define MAX7279_BRIGHTNESS_LEVEL 0X0A           // ���ȼ�������
//#define MAX7279_BRIGHTNESS_LEVEL    0xf       // ���ȼ�������
#define MAX7279_TEST_ENTER      0x01            // ��ʾ����ģʽ
#define MAX7279_TEST_EXIT       0x00            // ��ʾ���Խ������ָ���������ģʽ


/***********************************************
* ������ 
*/

/***********************************************
* ������ 
*/
uint8           dis_num_pos = 0;                //��ʾλ��

StrLedDisp    LedDispCtrl[DISPLAY_FRAME_NUM]  = {0};
uint8_t       LedDispBuf[DISPLAY_LED_NUM]     = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
/***********************************************
* ������ redmorningcn 2017-05-22
*/
const uint8_t LED_SEG_CODE[]    = {
    //
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

//    //�ո� !    "    #    $    %    &    '    (     )    *    +    ,    -    .   /
//    0x00,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0x01,0xE5,0xE5,
//    // 0    1    2      3        4    5    6    7    8    9
//    0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,
//    // :    ;    <    =     >   ?    @
//    0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,
//    //  A    B   C    D     E    F    G    H   I    J    K    L    M
//    0x77,0x1F,0x4E,0x3d,0x4F,0x47,0x5F,0x37,0x30,0x3c,0x87,0x0e,0xE5,
//    //  N    O    P   Q    R     S    T    U    V   W    X    Y    Z
//    0x76,0x7E,0x67,0xFE,0x66,0x5B,0x0F,0x3E,0x3E,0xE5,0x37,0x33,0x6D,
//    // [    \    ]    ^    _    `
//    0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,
//    // a    b   c    d     e    f    g    h    i    j     k    l    m
//    0x77,0x1F,0x0D,0x3D,0x4F,0x47,0x5F,0x17,0x30,0x3c,0x87,0x0e,0xE5,
//    // n    o   p    q     r    s    t    u    v   w    x    y    z
//    0x15,0x1D,0x67,0x73,0x05,0x5B,0x0F,0x1C,0x1C,0xD3,0x37,0x33,0x6D,
//    // {    |    }    ~       ��
//    0xE5,0xE5,0xE5,0xE5,0xE5,0x00
    
    
    0x00,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0x80,0x01,0x80,0xE5,
    //       !    "    #    $    %    &    '    (     )    *    +    ,    -    .   /
      0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B, 
    // 0    1    2		3   4    5    6    7    8    9	
      0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,
    // :    ;    <    =     >   ?    @
      0x77,0x1F,0x4E,0x3d,0x4F,0x47,0x5F,0x37,0x30,0x3c,0x87,0x0e,0xE5,
    //  A    B   C    D     E    F    G    H   I    J    K    L    M    
      0x76,0x7E,0x67,0xFE,0x66,0x5B,0x0F,0x3E,0x3E,0xE5,0x37,0x33,0x6D,
    //  N    O    P   Q    R     S    T    U    V   W    X    Y    Z     
      0xE5,0xE5,0xE5,0xE5,0x08,0xE5,
     // [    \    ]    ^    _    `
      0x77,0x1F,0x0D,0x3D,0x4F,0x47,0x7B,0x17,0x30,0x3c,0x87,0x0e,0xE5,
     // a    b   c    d     e    f    g    h    i    j     k    l    m
      0x15,0x1D,0x67,0x73,0x05,0x5B,0x0F,0x1C,0x1C,0xD3,0x37,0x33,0x6D,
     // n    o   p    q     r    s    t    u    v   w    x    y    z     
      0xE5,0xE5,0xE5,0xE5,0xE5,0x00//
      // {    |    }    ~       ?e
    
};


/*******************************************************************************
 * MACROS
 */
/***********************************************
* ������ IO,ʱ�ӵȶ���
*/
#define SPI_CS_PIN            DEF_BIT_13             /* PB.12 */
#define SPI_CS_PIN_NUM        13 
#define SPI_CS_GPIO_PORT      CSP_GPIO_PORT_NBR_02
#define SPI_CS_GPIO_CLK       CSP_GPIO_FNCT_00

#define SPI_SCK_PIN           DEF_BIT_07             /* PB.13 */
#define SPI_SCK_PIN_NUM       7          
#define SPI_SCK_GPIO_PORT     CSP_GPIO_PORT_NBR_00 
#define SPI_SCK_GPIO_CLK      CSP_GPIO_FNCT_00

#define SPI_MOSI_PIN          DEF_BIT_09             /* PB.15 */
#define SPI_MOSI_PIN_NUM      9 
#define SPI_MOSI_GPIO_PORT    CSP_GPIO_PORT_NBR_00
#define SPI_MOSI_GPIO_CLK     CSP_GPIO_FNCT_00

/***********************************************
* ������ IO��������
*/
#define SPI_CS_LOW()     	  CSP_GPIO_BitClr(SPI_CS_GPIO_PORT, SPI_CS_PIN)
#define SPI_CS_HIGH()    	  CSP_GPIO_BitSet(SPI_CS_GPIO_PORT, SPI_CS_PIN)

#define SPI_SCK_LOW()    	  CSP_GPIO_BitClr(SPI_SCK_GPIO_PORT,SPI_SCK_PIN)
#define SPI_SCK_HIGH()   	  CSP_GPIO_BitSet(SPI_SCK_GPIO_PORT,SPI_SCK_PIN)

#define SPI_MOSI_LOW()        CSP_GPIO_BitClr(SPI_MOSI_GPIO_PORT,SPI_MOSI_PIN)
#define SPI_MOSI_HIGH()       CSP_GPIO_BitSet(SPI_MOSI_GPIO_PORT,SPI_MOSI_PIN)

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

/*******************************************************************************
* ��    �ƣ� SPI_GpioInit
* ��    �ܣ� ADC GPIO��ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-07
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
static void SPI_GpioInit(void)
{
    CSP_GPIO_Cfg(SPI_CS_GPIO_PORT,
                 SPI_CS_PIN,
                 CSP_GPIO_DIR_OUT,
                 CSP_GPIO_FLAG_MODE_NONE,
                 DEF_NO,
                 0u,
                 SPI_CS_GPIO_CLK);
    
    CSP_GPIO_Cfg(SPI_SCK_GPIO_PORT,
                 SPI_SCK_PIN,
                 CSP_GPIO_DIR_OUT,
                 CSP_GPIO_FLAG_MODE_NONE,
                 DEF_NO,
                 0u,
                 SPI_SCK_GPIO_CLK);
    
    CSP_GPIO_Cfg(SPI_MOSI_GPIO_PORT,
                 SPI_MOSI_PIN ,
                 CSP_GPIO_DIR_OUT,
                 CSP_GPIO_FLAG_MODE_NONE,
                 DEF_NO,
                 0u,
                 SPI_MOSI_GPIO_CLK);

    SPI_CS_HIGH();
}

/*******************************************************************************
* ��    �ƣ� SPI_SendByte
* ��    �ܣ� ͨ��SPI���߷���һ���ֽ�����(ͬʱ����һ���ֽ�����)
* ��ڲ����� Ҫд���һ���ֽ�����
* ���ڲ����� �ڷ�����ʱ��MISO�ź����Ͻ��յ�һ���ֽ�
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-07
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
static void SPI_SendByte(uint8_t byte)
{
    uint8_t i;
    
    /***********************************************
    * ������ 
    */
    for(i=0;i<8;i++) {		
		SPI_SCK_LOW();
		Delay_Nus(10);
		if(byte & 0x80)
			SPI_MOSI_HIGH();
		else
			SPI_MOSI_LOW();
		byte = byte << 1;
		Delay_Nus(5);
		SPI_SCK_HIGH();
		Delay_Nus(10);
	}
}	

/*******************************************************************************
* ��    �ƣ� BSP_MAX7219Init
* ��    �ܣ� MAX7219��ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-07
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_MAX7219Init( void )
{
	SPI_GpioInit(); 
    
	SPI_CS_HIGH();
	SPI_SCK_HIGH();
    
	Delay_Nus(30);
}

/*******************************************************************************
* ��    �ƣ� LED_SPI_SendData
* ��    �ܣ� ��7219����1Byte���ݻ�����
* ��ڲ�����-addr:   ���ݽ��յ�ַ
*           -num:   Ҫ�������
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void LED_SPI_SendData(uint8_t Addr,uint8_t Num)
{    
    SPI_CS_LOW();                                  //7219�����ӽ���
    SPI_SendByte( Addr );                          //�͵�ַ
    SPI_SendByte( Num );                           //������
    SPI_CS_HIGH();                                 //��7219����
}

/*******************************************************************************
* ��    �ƣ� BSP_DispWrite
* ��    �ܣ� ����ʾ����д����ʾ����
* ��ڲ����� - Num         ��ʾ����
*           - Fmt         ��ʾ���ݸ�ʽ���磺"e%",��ʾ��ĸ��e��������Num
*           - Align       ���뷽ʽ ��1��Ϊ����룬��0��Ϊ�Ҷ���
*           - FmtType     ��ʽ��ģʽ����1��ǰ����ʾ����0��������ʾ
*           - DotPosition ��ʾ���λ��
*           - Cycle       ��˸����
*           - Duty    ����ʱ��
*           - OffX100ms   ���ʱ��
*           - Index       ��ʾ���
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_DispWrite( int     Num,
                    char    *Fmt,
                    char    Align,
                    uint8_t   FmtType,
                    uint8_t   DotPosition,
                    uint8_t   Cycle,
                    uint8_t   Duty,
                    // uint8_t   OffX100ms,
                    uint8_t   Index)
{

    char    i               = 0,    Nflag   = 0,    b       = 0;
    char    NbrCnt          = 0,    Chcnt   = 0;
    char    NumPosition     = 0;
    int     temp            = 0;
    char    flag            = 0;
    uint8_t   BSP_DispBuff[8] = {0};
    uint8_t   CharBuffer[8]   = {0};
    uint8_t   NumbBuffer[8]   = {0};
    uint8_t   buf[DISPLAY_LED_NUM]          = {128,128,128,128,128,128,128,128};
            temp            = Num;

    /***********************************************
    * ������ 
    */
    if(Index > sizeof(LedDispCtrl)/sizeof(StrLedDisp)-1) {
        return;
    }
    
    LedDispCtrl[Index].Flag         = 1;
    LedDispCtrl[Index].Cycle        = Cycle;
    LedDispCtrl[Index].Duty         = Duty;
    // LedDispCtrl[Index].OffX100ms     = OffX100ms;

    /***********************************************
    * ������ 
    */
    for(i = 0;i < strlen(Fmt);i++) {
        if(Fmt[i] == '%') {
            if ( FmtType == 0 ) {
                if(temp < 0) {
                    Nflag = 1;
                    temp = abs(temp);
                    NumbBuffer[0] = '-';
                    NbrCnt++;
                }
                
                do {
                    NumbBuffer[NbrCnt] = temp%10 + '0';
                    temp /= 10;
                    NbrCnt++;
                } while((NbrCnt <= 8)&&temp);
            } else {
                do {
                    NumbBuffer[NbrCnt] = temp%10 + '0';
                    temp /= 10;
                    NbrCnt++;
                } while((NbrCnt <= 8)&&temp);
                
                if(temp < 0) {
                    Nflag = 1;
                    temp = abs(temp);
                    NumbBuffer[NbrCnt] = '-';
                    NbrCnt++;
                }
            
            }
            
            switch(i) {
            case 0: NumPosition = 0;break;
            case 1: NumPosition = 1;break;
            case 2: NumPosition = 2;break;
            case 3: NumPosition = 3;break;
            }
            
            if(Nflag == 0) {
                flag = 1;
            } else {
                flag = 0;
            }
            
            for(b = 0;b < (NbrCnt - Nflag)/2;b++) {
                temp = NumbBuffer[b + Nflag];
                NumbBuffer[b + Nflag] = NumbBuffer[NbrCnt -flag- Nflag - b];
                NumbBuffer[NbrCnt - flag - Nflag - b] = temp;
            }
        } else {
            CharBuffer[Chcnt] = Fmt[i];
            Chcnt++;
        }
    }
    /***********************************************
    * ������ 
    */
    switch(NumPosition) {
    case 0: 
        for(i = 0;i < 8;i++) {
            BSP_DispBuff[i] = NumbBuffer[i];
        }
        for(i = NbrCnt;i < 8;i++) {
            BSP_DispBuff[i] = CharBuffer[i - NbrCnt];
        }
        break;
    case 1: 
        BSP_DispBuff[0] = CharBuffer[0];
        for(i = 1;i < 8;i++) {
            BSP_DispBuff[i] = NumbBuffer[i - 1];
        }
        for(i = (NbrCnt + 1);i < 8;i++) {
            BSP_DispBuff[i] = CharBuffer[i - NbrCnt];
        }
    break;
    case 2: 
        BSP_DispBuff[0] = CharBuffer[0];
        BSP_DispBuff[1] = CharBuffer[1];
        for(i = 2;i < 8;i++) {
            BSP_DispBuff[i] = NumbBuffer[i - 2];
        }
        for(i = (NbrCnt + 2);i < 8;i++) {
            BSP_DispBuff[i] = CharBuffer[i - NbrCnt];
        }
    break;
    case 3: 
        for(i = 0;i < 3;i++) {
            BSP_DispBuff[i] = CharBuffer[i];
        }
        for(i = 3;i < 8;i++) {
            BSP_DispBuff[i] = NumbBuffer[i - 3];
        }
    }
    
    for(i = 0;i < DISPLAY_LED_NUM;i++) {
        buf[i] = 128;
    }
    
    /***********************************************
    * ������ 
    */
	if(Align == 1) {
        for(i = 0;(i < (NbrCnt + Chcnt))&&(i < DISPLAY_LED_NUM);i++) {
            buf[i]      = BSP_DispBuff[i];
        }
    } else {
        for(i = 0;(i < (NbrCnt + Chcnt))&&(i < DISPLAY_LED_NUM);i++) {
            buf[3 - i]  = BSP_DispBuff[NbrCnt + Chcnt -1 -i];
        }
    }
    
    /***********************************************
    * ������ 
    */
    for(i = 0;i < DISPLAY_LED_NUM;i++) {
        if(DotPosition & (0x01 << (3 - i))) {
            LedDispCtrl[Index].Code[i] = LED_SEG_CODE[buf[i]]|0x80;
        } else {
            LedDispCtrl[Index].Code[i] = LED_SEG_CODE[buf[i]];
        }
    }
}

/*******************************************************************************
* ��    �ƣ� BSP_Disp
* ��    �ܣ� ������ţ���7219����Ӧ������
* ��ڲ����� 
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void WIN_DispMsg(const char *msg)
{

    static  uint8   k = 0;
    
    
    while(k < DISPLAY_FRAME_NUM){
        if(LedDispCtrl[k].Flag == 0){
            break;
        }
        k++;
    }
    
    if(k == DISPLAY_FRAME_NUM)          //û�п����ݣ�ֱ���˳�
    {   
        k = 0;
        return; 
    }
    
    char i,j;
    LedDispCtrl[k].Flag         = 1;
    LedDispCtrl[k].Cycle        = 1;
    LedDispCtrl[k].Duty         = 20;
    
    /***********************************************
    * ����������8λ����,����ֽ�8����ǰ�油�ո� 
    * redmorningcn 
    * 2017-05-24
    */
    
    //��С���㴦����2017-05-24
    uint8   datalen = strlen(msg);
    for(i = 0;i < strlen(msg);i++) {
        if(msg[i+1] == '.' && msg[i] != '.'){
            datalen--;
            i++;
        }
    }
    
    for(i = 0,j = 0;j < DISPLAY_LED_NUM;j++) {
        if(datalen < DISPLAY_LED_NUM)
        {
            LedDispCtrl[k].Code[j] = LED_SEG_CODE[0];
            datalen++;
        } else{
            if(msg[i+1] == '.' && msg[i] != '.') {
                LedDispCtrl[k].Code[j] = LED_SEG_CODE[msg[i]] | 0x80;
                i++;
            } else {
                LedDispCtrl[k].Code[j] = LED_SEG_CODE[msg[i]];
            }
            i++;
        }
    }
    
//    /***********************************************
//    * ������ 
//    */
//    for(i = 0,j = 0;j < DISPLAY_LED_NUM;j++,i++) {
//        if(msg[i] == '.') {
//            i++;
//            LedDispCtrl[k].Code[j] = LED_SEG_CODE[msg[i]] | 0x80;
//        } else {
//            LedDispCtrl[k].Code[j] = LED_SEG_CODE[msg[i]];
//        }
//    }    
    
    //BSP_DispSetBrightness(Ctrl.Para.dat.DispLevel);
    //BSP_DispEvtProcess();    
}

/*******************************************************************************
* ��    �ƣ� BSP_Disp
* ��    �ܣ� ������ţ���7219����Ӧ������
* ��ڲ����� 
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_Disp(uint8_t Index)
{
    uint8_t i;
    if(Index > sizeof(LedDispCtrl)/sizeof(StrLedDisp)-1) {
        return;
    }
    //BSP_DispInit();
    for(i = 0; i<DISPLAY_LED_NUM ; i++) {
        LED_SPI_SendData(LedDispBuf[i],LedDispCtrl[Index].Code[i]);
    }
}

/*******************************************************************************
* ��    �ƣ� BSP_DispOff
* ��    �ܣ� ͨ��������������������������ʾ
* ��ڲ����� 
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_DispOff(void)
{
    uint8_t i;
    BSP_DispInit();
    for(i = 0; i<DISPLAY_LED_NUM ; i++) {
        LED_SPI_SendData(LedDispBuf[i],0);
    }
}


/*******************************************************************************
* ��    �ƣ� BSP_DispEvtProcess
* ��    �ܣ� ������ܽ�����������ʾ����
* ��ڲ����� 
* ���ڲ����� ��������ʾ������1����������ʾ������0
* ���� ���ߣ� redmorningcn.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
uint8 BSP_DispEvtProcess(void)
{    
    uint8   i = 0;
    
    while(i < DISPLAY_FRAME_NUM)                          //FIFO��ʾ
    {
        //��ʾ�����Ը�ֵ����������ʾ
        if(LedDispCtrl[ dis_num_pos % DISPLAY_FRAME_NUM ].Flag != 0 ) {
            LedDispCtrl[dis_num_pos % DISPLAY_FRAME_NUM ].Flag = 0;    //�������¸�ֵ
            BSP_Disp(   dis_num_pos % DISPLAY_FRAME_NUM );
                        
            return 1;
        }
        
        dis_num_pos++;
        i++;
    }
    return 0;
}

/*******************************************************************************
* ��    �ƣ� BSP_DispClr
* ��    �ܣ� �����ʾ������,������ʾ��־λ����ʾ����
* ��ڲ����� �ڼ�����ʾ������
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_DispClr(uint8_t order)
{
    if( order < sizeof(LedDispCtrl) / sizeof(StrLedDisp) ) {
        LedDispCtrl[order].Flag = 0;
    }
}

/*******************************************************************************
* ��    �ƣ� BSP_DispClrAll
* ��    �ܣ� ���������ʾ����������
* ��ڲ����� 
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_DispClrAll(void)
{
    uint8_t i;
    
    //��ʾλ������
    dis_num_pos = 0;
    
    for(i=0;i<sizeof(LedDispCtrl)/sizeof(StrLedDisp);i++) {
        LedDispCtrl[i].Flag = 0;
    }
}

/*******************************************************************************
* ��    �ƣ� BSP_DispSetBrightness
* ��    �ܣ� 7219��������
* ��ڲ����� 
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-12
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_DispSetBrightness ( uint8_t bl )
{    
    static uint8_t   last;
    
    if ( bl > 15 )
        bl  = 15;
    if ( last != bl ) {
        last    = bl;
        LED_SPI_SendData( MAX7279_BRIGHTNESS,bl );      // ��������
    }
}

/*******************************************************************************
* ��    �ƣ� BSP_DispInit
* ��    �ܣ� 7219��ʼ��
* ��ڲ����� 
* ���ڲ����� 
* ���� ���ߣ� wumingshen.
* �������ڣ� 2015-12-08
* ��    �ģ�
* �޸����ڣ�
* ��    ע��
*******************************************************************************/
void BSP_DispInit (void)
{
    BSP_MAX7219Init();                                              // ��ʼ��Ӳ��
    
    LED_SPI_SendData( MAX7279_DISP_TEST,0x00 );                         // ���ù���ģʽ
    LED_SPI_SendData( MAX7279_SCAN,MAX7279_8_DIGIT_SCAN );              // ����ɨ�����
    LED_SPI_SendData( MAX7279_DECODE_MODE,MAX7279_DECODE_SET );         // ��������ģʽ
    LED_SPI_SendData( MAX7279_BRIGHTNESS,MAX7279_BRIGHTNESS_LEVEL );    // ��������
    LED_SPI_SendData( MAX7279_LOW_PWR,MAX7279_NORMAL_MODE );            // ����Ϊ��������ģʽ
    
    BSP_DispClrAll();                                               // ����
}

/*******************************************************************************
* 				                end of file                                    *
*******************************************************************************/
#endif