#ifndef  _Card_h_
#define  _Card_h_

#include	"DataCard.h"
#include	"ParaCard.h"

#define		DATA_CARD           0x0001			//数据卡
#define		DENSITY_CARD		0x0020			//密度卡
#define		MODEL_CARD			0x0040			//参数模型卡
#define		TIME_CARD           0x0100			//时间卡
#define		COM_MODEL_CARD	    0x0100		    //参数复杂邮箱模型
#define		HIGHT_CARD			0x0200			//高度调整卡
#define		COPY_CARD           0x0400			//FLASH复制卡
#define		MODEL_SELECT_CARD	0x1000			//模型选择卡
#define		FIX_CARD            0x2000			//装车卡
#define		COPY_FRAM_CARD	    0x4000			//铁电拷贝卡

#define		SET_DATA_CARD		0x0080			//置数卡
#define		DEBUG_CARD			0x0800			//调试复制卡

#define		EXPAND_CARD			0x8000			//扩展卡

#define		DATA_CARD_DIS		0x10000			//数据卡
#define		DATA_CARD_FIN		0x20000			//数据卡
#define		SYS_RUN_PARA		0x40000			//设置运行参数
#define		CLEAR_ALL			0x80000			//设置运行参数

#define		RST_SYS				0x100000		//系统复位
#define		CALC_PARA           0x200000		//油量计算系数

#define		RUN_MODEL_PARA      0x400000		//运算模型卡


#define		CARD_DATA_ADDR	    5120			//IC卡 数据起始地址
#define		CARD_FLG_ADDR		0				//IC卡 标识起始地址

//--------------------------------------------------------------------------------------------
//函数名称:             WriteNormCard(void)   
//函数功能:             StartCardRecNum:开始流水号,EndCardRecNum:结束流水号
//入口参数:             流水号
//出口参数:             无
//说明:                 
////---------------------------------------------------------------------------------------------
//extern	void    WriteCardFlg(stcCardFlg	* sCardFlg)  ;
//
////-------------------------------------------------------------------------------------------------
////函数名称:             CardTask(void)    
////函数功能:             操作IC卡任务
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern	void    CardTask(void); 
//
////-------------------------------------------------------------------------------
////函数名称:        	uint8	JudgeCardEvt(void)
////函数功能:       	判断Flsh事件
////入口参数:        	无
////出口参数:      	无
////-------------------------------------------------------------------------------
//extern	uint8	JudgeCardEvt(void);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             ReadCardFlg()
////函数功能:             读分区卡标识页,进行求要分区号
////入口参数:             无
////出口参数:             IC卡首页读取
////说明:                 
////--------------------------------------------------------------------------------------------------
////extern	uint8	ReadCardFlg(stcCardFlg * sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void	GetUnFihCardEvtFlg(void)
////函数功能:             取未完成数据转储标识
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern	uint8	GetUnFihCardEvtFlg(void);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	DebugCard(stcCardFlg	* sCardFlg)
////函数功能:             高度修正卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern	uint8	DebugCard(stcCardFlg	* sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	SetDataCard(stcCardFlg	* sCardFlg)
////函数功能:             置数据卡
////入口参数:             整个卡结构体
////出口参数:             是否成功
////--------------------------------------------------------------------------------------------------
//extern	uint8	SetDataCard(stcCardFlg	* sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	DataCopyCard(stcCardFlg	* sCardFlg)
////函数功能:             置数据卡
////入口参数:             整个卡结构体
////出口参数:             是否成功
////--------------------------------------------------------------------------------------------------
//extern	uint8	DataCopyCard(stcCardFlg	* sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	ModelSelectCard(stcCardFlg	* sCardFlg)
////函数功能:             模型选择卡
////入口参数:             整个卡结构体
////出口参数:             是否成功
////--------------------------------------------------------------------------------------------------
//extern	uint8	ModelSelectCard(stcCardFlg	* sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	FixCard(stcCardFlg	* sCardFlg)
////函数功能:             高度修正卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern	uint8	FixCard(stcCardFlg	* sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             uint8	CopyFramCard(stcCardFlg	* sCardFlg)
////函数功能:             高度修正卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern	uint8	CopyFramCard(stcCardFlg	* sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             void	DataCardPartRead(void)
////函数功能:             普通卡处理
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern	void	DataCardPartRead(void);
//
////-------------------------------------------------------------------------------------------------
////函数名称:             OperationCOM0ModelCard(void)    
////函数功能:             操作从串口0接受到的数据
////入口参数:             无
////出口参数:             无
////--------------------------------------------------------------------------------------------------
//extern  void    OperationCOM0ModelCard(void);
//
////--------------------------------------------------------------------------------------------
////函数名称:             uint8    CheckWriteCardFlgCrc(uint16 Crc16)    
////函数功能:             读标志页校验
////入口参数:             无
////出口参数:             标志页校验,正确返回1，否则为零
////说明:                 
////---------------------------------------------------------------------------------------------
//extern	uint8    CheckWriteCardFlgCrc(uint16 Crc16);
#endif
