/*******************************************************************************
 *   Filename:      bsp_FRAM.c
 *   Revised:       $Date: 2017-05-15$
 *   Revision:      $
 *   Writer:	    redmorningcn.
 *
 *   Description:
 *   Notes:
 *     				E-mail:redmorningcn@qq.com
 *
 *   All copyrights reserved to redmorningcn.
 *
 *******************************************************************************/

/*******************************************************************************
* INCLUDES
*/
#include <includes.h>
#include "bsp_FRAM.h"
#include "App_ctrl.h"
					  

/***********************************************
* ����: OS�ӿ�
*/
#if UCOS_EN     == DEF_ENABLED
    #if OS_VERSION > 30000U
    static  OS_SEM			Bsp_Fram_Sem;    	//�ź���
    #else
    static  OS_EVENT		*Bsp_Fram_Sem;    //�ź���
    #endif
#endif
    

#if (UCOS_EN     == DEF_ENABLED)
/*******************************************************************************
* ��    �ƣ� 		FRAM_WaitEvent
* ��    �ܣ� 		�ȴ��ź���
* ��ڲ����� 	��
* ���ڲ�����  	0���������󣩣�1�������ɹ���
* ���� ���ߣ� 	redmorningcn
* �������ڣ� 	2017-05-15
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ����ʹ��UCOS����ϵͳʱʹ��
*******************************************************************************/
static uint8_t FRAM_WaitEvent(void)
{
    /***********************************************
    * ������ OS�ӿ�
    */

//#if OS_VERSION > 30000U
//    return BSP_OS_SemWait(&Bsp_Fram_Sem,0);           	// �ȴ��ź���
//#else
//    uint8_t       err;
//    OSSemPend(Bsp_Fram_Sem,0,&err);                   		// �ȴ��ź���
//    if ( err = OS_ERR_NONE )
//      return TRUE;
//    else
//      return FALSE;
//#endif
}

/*******************************************************************************
* ��    �ƣ�	 	FRAM_SendEvent
* ��    �ܣ� 		�ͷ��ź���
* ��ڲ����� 	��
* ���ڲ����� 	��
* ���� ���ߣ� 	redmorningcn
* �������ڣ� 	2017-05-15
* ��    �ģ�
* �޸����ڣ�
* ��    ע�� ����ʹ��UCOS����ϵͳʱʹ��
*******************************************************************************/
static void FRAM_SendEvent(void)
{
//    /***********************************************
//    * ������ OS�ӿ�
//    */
//#if OS_VERSION > 30000U
//    BSP_OS_SemPost(&Bsp_Fram_Sem);                        	// �����ź���
//#else
//    uint8_t       err;
//    OSSemPost(Bsp_Fram_Sem);                             		 // �����ź���
//#endif
}

#endif /* end of (UCOS_EN     == DEF_ENABLED)*/


//-------------------------------------------------------------------------------------------------------
//��������: 		WriteFM24CL16()
//��    ��:			��FM24CL16ָ����ַ����д����
//��ڲ���:         ADDR:       ������ַ    ��ַ��0 ~ sizeof(FM24CL16)
//                  		*DataBuf:   ���ݻ���
//                  Len: 	���ݳ���
//���� ���ߣ� 	redmorningcn
//�������ڣ� 	2017-05-15
//���ڲ���:    	��
//˵����            
//--------------------------------------------------------------------------------------------------------
uint8 WriteFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen)            
{
    uint32  i = 0;
    uint8   SlaveAddr;                                      //�ӻ���ַ
    uint16  AddrTemp = 0;                                   //��ַ����
    
    AddrTemp = Addr;
    AddrTemp += FRAM_START_ADDR;                            //�����ַ

    if( (uint16)AddrTemp + DataBufLen > FRAM_END_ADDR ) 
    {
        return  FALSE;                                      			//��ַδ����
    }
        
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //��FM24CL64�豸д��ַ
    
    StartI2C();                                             		//����IIC����
    
    WriteByteWithI2C(SlaveAddr);                            //дFM24CL64��ַ
    CheckSlaveAckI2C();
 
    WriteByteWithI2C(Addr >> 8);                            //дFM24CL64��λ��ַ
    CheckSlaveAckI2C();
    
    WriteByteWithI2C( Addr );                               //дFM24CL64��λ��ַ
    CheckSlaveAckI2C();     
  
    for(i = 0; i < DataBufLen; i++)                         //��������
    {
        WriteByteWithI2C(DataBuf[i]);                       //д����
        CheckSlaveAckI2C();                                 //���ӻ�Ӧ���ź�
    }
    
    StopI2C();                                              //ֹͣIIC����   
    
    return  TRUE;                                           //��ȷ
}

//-------------------------------------------------------------------------------------------------------
//��������:         ReadFM24CL16()
//��    ��:         ��ȡFM24CL16ָ����ַ��������
//��ڲ���:         ADDR:       ������ַ   ��ַ��0 ~ sizeof(FM24CL16)
//                  *DataBuf:   ���ݻ��� 
//                  Len:        ���ݳ���
//���ڲ���:         ��
//���� ���ߣ� 	redmorningcn
//�������ڣ� 	2017-05-15
//˵����            
//--------------------------------------------------------------------------------------------------------
uint8 ReadFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen)            
{
    uint32  i = 0;
    uint8   SlaveAddr;                                      //�ӻ���ַ
    uint16  AddrTemp;                                       //��ַ����
    
    AddrTemp = Addr;
    
    AddrTemp += FRAM_START_ADDR;                            //�����ַ
    
    if( (uint16)AddrTemp + DataBufLen > FRAM_END_ADDR ) 
    {
        return  FALSE;                                      //��ַδ����
    }
    
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //��FM24CL64�豸д��ַ
    
    StartI2C();                                             //����IIC����
    
    WriteByteWithI2C(SlaveAddr);                            //дFM24CL64�豸д��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
    
    WriteByteWithI2C(Addr >> 8 );                           //д���ݸ�λ��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
    
    WriteByteWithI2C( Addr );                               //д���ݵ�λ��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
        
    SlaveAddr = (FRAM_DIVICE_ADDR)|(0x01);                  //��FM24CL64�豸����ַ
    
    StartI2C();                                             //����IIC����
    
    WriteByteWithI2C(SlaveAddr);                            //дFM24CL16��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
   
    for(i = 0; i < (DataBufLen -1); i++)                    //��������
    {
        DataBuf[i] = ReadByteWithI2C();                     //д����
        MasterAckI2C();                                     //����Ӧ��ӻ�
    }
    DataBuf[i] = ReadByteWithI2C();                         //д����
    
    MasterNoAckI2C();                                       //����Ӧ��ӻ�
    
    StopI2C();
    
    return  TRUE;                                           //��ȷ
}


//  RecNumMgr
//
//-------------------------------------------------------------------------------------------------------
//��������	:       FRAM_StoreRecNumMgr()
//��    		��	:       �洢���ݼ�¼�����ַ
//��ڲ���	:       ���洢�����ݼ�¼ָ��
//���ڲ���  :       �ɹ�TURE��ʧ��FALSE
//���� ���ߣ� 	redmorningcn
//�������ڣ� 	2017-05-15
//˵		 ����            
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_StoreRecNumMgr(StrRecNumMgr  *SRecNumMgr)
{
	uint8	flg = TRUE;
	
//	FRAM_WaitEvent();
    
    CPU_SR  cpu_sr;
CPU_CRITICAL_ENTER() ;
	if(!WriteFM24CL64(FRAM_RECNUM_MGR_ADDR, (uint8 *)SRecNumMgr, sizeof(StrRecNumMgr)))		//�����ݹ���
		flg = FALSE;
CPU_CRITICAL_EXIT();
//	FRAM_SendEvent();
	return	flg;
}


//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_ReadRecNumMgr()
//��    		��	:      �����ݼ�¼����ָ��
//��ڲ���	:      ����ȡ�����ݼ�¼�Ĵ���λ��
//���ڲ���  :      �ɹ�TURE��ʧ��FALSE
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_ReadRecNumMgr(StrRecNumMgr  *SRecNumMgr)
{
	uint8	flg = TRUE;
	
//	FRAM_WaitEvent();
    
    CPU_SR  cpu_sr;
CPU_CRITICAL_ENTER() ;
	if(!ReadFM24CL64(FRAM_RECNUM_MGR_ADDR, (uint8 *)SRecNumMgr, sizeof(StrRecNumMgr)))		//�����ݹ���
		flg = FALSE;
CPU_CRITICAL_EXIT();	
//	FRAM_SendEvent();
	return	flg;
}

//  ProductInfo
//
//-------------------------------------------------------------------------------------------------------
//��������:       FRAM_StoreProductInfo()
//��    ��:       ���Ʒ��Ϣ
//��ڲ���:      
//���ڲ���:       
//���� ���ߣ� 	    redmorningcn
//�������ڣ� 	    2017-05-15
//˵		 ����            
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_StoreProductInfo(StrProductInfo  *sProductInfo)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	if(!WriteFM24CL64(FRAM_PRODUCT_INFO_ADDR, (uint8 *)sProductInfo, sizeof(StrProductInfo)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_ReadProductInfo()
//��    		��	:      ����Ʒ��Ϣ
//��ڲ���	:      ��Ʒ��
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_ReadProductInfo(StrProductInfo  *sProductInfo)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	if(!ReadFM24CL64(FRAM_PRODUCT_INFO_ADDR, (uint8 *)sProductInfo, sizeof(StrProductInfo)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}



//  currecord
//
//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_StoreCurRecord()
//��    		��	:      �浱ǰ��¼�� 
//��ڲ���	:      
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����            
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_StoreCurRecord(stcFlshRec  *sFlshRec)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	if(!WriteFM24CL64(FRAM_REC_ADDR, (uint8 *)sFlshRec, sizeof(stcFlshRec)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_ReadProductInfo()
//��    		��	:      ����ǰ��¼�� 
//��ڲ���	:      ��Ʒ��
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_ReadCurRecord(stcFlshRec  *sFlshRec)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	if(!ReadFM24CL64(FRAM_REC_ADDR, (uint8 *)sFlshRec, sizeof(stcFlshRec)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//  oilpara
//
//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_StoreOilPara()
//��    		��	:      
//��ڲ���	:      
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����            
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_StoreOilPara(StrOilPara  *SOilPara)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	if(!WriteFM24CL64(FRAM_OIL_PARA_ADDR, (uint8 *)SOilPara, sizeof(StrOilPara)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_ReadOilPara()
//��    		��	:      
//��ڲ���	:     
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_ReadOilPara(StrOilPara  *SOilPara)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	if(!ReadFM24CL64(FRAM_OIL_PARA_ADDR, (uint8 *)SOilPara, sizeof(StrOilPara)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}


//  runpara
//
//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_StoreRunPara()
//��    		��	:      
//��ڲ���	:      
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����            
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_StoreRunPara(stcRunPara  *sRunPara)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	
	if(!WriteFM24CL64(FRAM_RUN_PARA_ADDR, (uint8 *)sRunPara, sizeof(stcRunPara)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_ReadRunPara()
//��    		��	:      
//��ڲ���	:     
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_ReadRunPara(stcRunPara  *sRunPara)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	
	if(!ReadFM24CL64(FRAM_RUN_PARA_ADDR, (uint8 *)sRunPara, sizeof(stcRunPara)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//  calcmodel
//
//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_StoreCalcModel()
//��    		��	:      
//��ڲ���	:      
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����            
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_StoreCalcModel(stcCalcModel  *sCalcModel)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	
	if(!WriteFM24CL64(FRAM_CALC_MODEL_ADDR, (uint8 *)sCalcModel, sizeof(stcCalcModel)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      FRAM_ReadRunPara()
//��    		��	:      
//��ڲ���	:     
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8 FRAM_ReadCalcModel(stcCalcModel  *sCalcModel)
{
	uint8	flg = TRUE;
	
	FRAM_WaitEvent();
	
	if(!ReadFM24CL64(FRAM_CALC_MODEL_ADDR, (uint8 *)sCalcModel, sizeof(stcCalcModel)))		
		flg = FALSE;
	
	FRAM_SendEvent();
	return	flg;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      GetOilBoxModelsModel()
//��         ��	:  ��������ģ������Ѱ����Ч������ģ�͡� 
//��ڲ���	:     
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8	GetOilBoxModelsModel(stcModel * sModel)
{
	  uint32	i;
	  uint32	ModelNumAdd;
	  uint32	ModelAdd;
	  uint8		ModelNum;
	  uint16	CrcCheck;
	  uint8		OilBoxTypCod;

	  OilBoxTypCod	= GetOilBoxCod(); 

	  for(i = 0; i < 18;i++)
	  {
	      ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*i + sizeof(stcModPot)*50 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

//		  printfcom0("\r\n 11 OilBoxTypCod == ModelNum %d ,i = %d",ModelNum,i);

		  if(OilBoxTypCod == ModelNum)
		  {
//		  	  printfcom0("\r\n 2OilBoxTypCod == ModelNum %d,i = %d",ModelNum,i);
			  
			  ModelAdd = OIL_BOX_MODEL_ADDR + sizeof(stcModel)*i;		  		
		      ReadFM24CL64(ModelAdd,(uint8 *)sModel,sizeof(stcModel));
//			  printfcom0("\r\n ModelAdd == ModelNum %d,i = %d",ModelAdd);
//			  for(i = 0;i < sModel->PotNum;i++)
//			  {
//			  	printfcom0("\r\n  gaodu %d,youliang %d",sModel->sModPot[i].HigVal,sModel->sModPot[i].DipVal);
//			  }

			  CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);

			  if(CrcCheck == sModel->CrcCheck)
			  {
			  	 //printfcom0("\r\n 3PotNum %d",sModel->PotNum);	
			  	 return  1;
			  }
		  }
	  }

	  return  0;
}

//-------------------------------------------------------------------------------------------------------
//��������	:      GetOilBoxModelsModelSemple()
//��    		��	:     ��������ģ������Ѱ����Ч������ģ�͡�  
//��ڲ���	:     
//���ڲ���  :       
//���� ���� �� 	redmorningcn
//��������  �� 	2017-05-15
//˵		 ����  
//--------------------------------------------------------------------------------------------------------
uint8	GetOilBoxModelsModelSemple(stcModelSemple * sModelSemple)
{
	  uint32	i;
	  uint32	ModelNumAdd;
	  uint32	ModelAdd;
	  uint8		ModelNum;
	  uint16	CrcCheck;
	  uint8		OilBoxTypCod;

	  OilBoxTypCod	= GetOilBoxCod(); 

	  for(i = 0; i < 46;i++)
	  {
		  ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18 
		  				+ sizeof(stcModelSemple)*i + sizeof(stcModPot)*10 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

		  //printfcom0("\r\n 22 OilBoxTypCod == ModelNum %d, %d",ModelNum,OilBoxTypCod);

		  if(OilBoxTypCod == ModelNum)
		  {
			  ModelAdd = OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18  
			  			+ sizeof(stcModelSemple)*i ;
		
		      ReadFM24CL64(ModelAdd,(uint8 *)sModelSemple,sizeof(stcModelSemple));

			  CrcCheck = GetCrc16Check((uint8 *)sModelSemple,sizeof(stcModelSemple) - 2);

//			  printfcom0("\r\n 22 CrcCheck == CrcCheck %d, %d",CrcCheck,sModelSemple->CrcCheck);
			  if(CrcCheck == sModelSemple->CrcCheck)
			  {
			  	 return  1;
			  }
		  }
	  }

	  return  0;
}

//#endif
    
