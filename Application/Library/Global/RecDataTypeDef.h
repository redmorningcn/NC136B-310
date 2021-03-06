#ifndef  _RecDataTypeDef_h_
#define  _RecDataTypeDef_h_

#include "app_tax.h"

typedef __packed struct _stcFlshRec   	//定义油尺记录数据结构
{
	uint32	StoreCnt;         	//存储流水号    		4   追踪记录用

	uint8	RecTypCod;       	//记录类型          	1   数据类型（开机、上班卡、下班卡、数据记录）
	uint8	RelSpeed[3];      	//实速              	3   D9~D0：实速，D19~D10：预留

	uint32	Time;          	    //月/日/时/分/秒      	4   D5~D0:秒,D11~D6:分,D16~D12:时D21~D17：日，
	                               	//                      	D25~D22：月 ;D26~D31:年
	uint8	LocoTyp;          	//机车型号          	1   
	uint8	E_LocoTyp;        	//机车型号扩展字节  	1   机车型号扩充字节,定义与LKJ2000格式相同
	uint16 	LocoNum;       	    //机车号            	2	

	uint32 	TrainTyp;     	    //车次种类          	4   车次种类,车次编码新方案(铁运[2005]72号文件)
	                             	//                      	的车次种类标识符,定义与LKJ2000格式相同
	                             	
	uint8	TrainNum[3];     	//车次数字部分      	3   车次编码新方案(铁运[2005]72号文)的车次数据部分
	uint8 	Car_Truck;       	//本/补、客/货       	1   D0＝0/1 → 货/客   D1＝0/1 → 本/补   
	 
	uint8 	VoitureCnt;       	//辆数              	1	
	uint8 	KmMark[3];   		//公里标            	3   单位：米

	uint16 	Weight;       	    //总重              	2
	uint16 	PlanLen;       	    //计长              	2   单位：0.1   

	uint16 	MstDriverNum;  	    //司机号            	2	
	uint8 	E_MstDriverNum; 	//司机号扩展字节    	1   
	uint8 	E_SlvDriverNum;   	//副司机号扩展字节  	1   

	uint16 	SlvDriverNum;  	    //副司机号          	2   
	uint16	DriverUnitNum;  	//司机单位编号      	2   //用来唯一确定司机

	uint8 	RoadNum;          	//区段号(交路号)     	1	
	uint8  	RelRoadNum;     	//实际交路号         	1   定义格式与LKJ2000相同   
	uint8  	StationNum;     	//车站号            	1
	uint8  	E_StationNum;   	//车站号扩展字节    	1   车站号扩展字节

	uint8 	SignalTyp;        	//信号机类型        	1   B2-B0 :2-出站,3-进站,4-通过,5-预告,6-容许
	uint8 	LocoSign;        	//机车信号          	1   B4 = 0/1  单灯/多灯;   B3~B0 0-无灯,1-绿,2-黄, 
	                            	//                      	3-双黄,4-红黄,5-红,6-白,7-绿黄,8-黄
	uint8 	LocoWorkState;    	//机车工况          	1   b0-零位,B1-向后,B2-向前,B3-制动,B4-牵引
	uint8 	LocoState;      	//装置状态          	1   B0 = 1/0 - 降级/监控; B2 = 1/0 - 调车/非调车

//	uint8 	SignalNum[2];      	//信号机编号        	2   
//	uint8 	LocoPipePress[2]; 	//列车管压          	2   B9-B0:管压(单位:1kPa)

	uint16	Myspeed1;			//自测速度1				2
	uint16	Myspeed2;			//自测速度2				2	
	  
	uint32 	MstDip;           	//主机油量          	4   主油尺油量(主从机级联时为主机油量,否则为本机车油量)

//	uint32 	SlvDip;           	//从机油量          	4   主油尺油量(主从机级联时为从机油量,否则此油量值为空)
	uint32	MyKileMeter;		//总里程				4
		
	int32 	MyMstLocoPower;     //主机机车功率       	4   主机外接设备测量

//	int32 	SlvLocoPower;     	//从机机车功率       	4   从机外接设备测量
	uint32	MyPower;			//累计电量				4	
	//090901
 	//uint16	MstDip1Prs;        	//压强            		2   主机油尺1压强值
	//uint16	MstDip2Prs;        	//压强            		2   主机油尺2压强值
	int16		Myhig1;				//液位高度1				2	
	int16		Myhig2;				//液位高度2				2							

	uint16	SlvDip1Prs;       	//压强            		2   从机油尺1压强值
	uint16 	SlvDip2Prs;       	//压强            		2   从机油尺2压强值
	
	uint8  	MyYear;           	//年      				1   装置时间的年
	uint8 	MyMonth;         	//月      				1   装置时间的月
	uint8 	MyData;          	//日      				1   装置时间的日
	uint8 	MyHour;           	//时      				1   装置时间的时
	
	uint8 	MyMinute;     		//分      				1   装置时间的分
	uint8 	MySecond;       	//秒       				1   装置时间的秒
	uint16	MstDensity;			//密度							2	主机燃油密度
	
//	uint16	SlvDensity;			//密度						2	从机燃油密度
//	uint16	GpsHeight;			//高度						2	地理高度
	int16	MyAddspeed;			//自测加速度					2
	uint16	MyDip;				//自测油量							2
		
	int32	GpsLongitude;		//经度					4	地理经度
	int32	GpsLatitude;		//纬度					4	地理纬度
		
	int16	MstEngRotSpd;		//主机柴油机转速		2	主机柴油机转速
//	int16	SlvEngRotSpd;		//从机柴油机转速		2	从机柴油机转速
	int16	MyEngRotSpd;		//从机柴油机转速		2	从机柴油机转速

	//补充内容 
	//与自加时钟芯片配套的数据有
	uint16 	JcRealType;			//机车型号				2   外部设置的机车型号
	uint16 	JcRealNo;			//机车编号				2   外部设置的机车编号
	
//	uint16 	MstPotPress;		//主机缸压				2	预留接监控	
//	uint16 	SlvPotPress;		//从机缸压				2	预留接监控	
	uint16	MyDip1Tmp;	  		//油尺1温度
	uint16	MyDip2Tmp;			//油尺2温度
		
//	uint16 	MstPot1;			//主机均缸1				2	预留接监控	
//	uint16 	MstPot2;			//主机均缸2				2	预留接监控
	uint16	MyDip1Den;
	uint16	MyDip2Den;	

//	uint16 	SlvPot1;			//从机均缸1				2	预留接监控		
//	uint16 	SlvPot2;			//从机均缸2				2	预留接监控
	uint16	MyDip1Err;
	uint16	MyDip2Err;
	
	uint16 	MaxSpeed;			//限速					2	预留接监控	
//	uint16 	MstOcurrent;		//主机原边电流   		2	预留接监控
	uint16	ErrNum;				//现有故障条数			2	
	
	
	uint8	ErrorCode;			//故障代码				1   0~255
//	uint8 	DipValChgState;  	//油量变化状态   		1   油量变化情况分：两油尺增加/减小、变化平稳、轻微波动、剧烈波动
	uint8	MyLocoWorkState;	//自测机车状态			1
	//090901
	uint8	MstDipTemp;			//温度					1	主机温度
	uint8	OilBoxModel;		//油箱模型				1	机车油箱代码
	
	uint8	SoftVes;        	//软件版本          	1   
	uint8	Reserve1;        	//预留          		1  	
//	uint16	Reserve0;        	//预留          		2   
	uint16 	CrcCheck;         	//存储的校验和    		2   Flash记录存储CRC校验
}stcFlshRec;




typedef __packed struct _stcFlshRecNDP02B  //定义油尺记录数据结构（20170921 新数 油尺据结构）
{
    uint8				CmdTpye		      ;//命令类型       1     		        	
    uint8				EvtType           ;//事件类型       1                  
    uint16				LocoType          ;//机车型号       2                  
    uint16				LocoNum           ;//机 车 号       2                     
    uint32				SysID             ;//记录流水号     4                   
    uint16				Oil               ;//油量           2                    
    uint16				Hight1            ;//高度1          2                    
    uint16				Hight2            ;//高度2          2                    
    uint16				Pressure1         ;//压力1          2                    
    uint16				Pressure2         ;//压力2          2                    
    uint16				Density1          ;//密度1          2                    
    uint16				Density2          ;//密度2          2                    
    uint8				TempOil           ;//油箱温度       1                  
    uint8				TempEnv           ;//环境温度       1                  
    uint32				Degree            ;//电量           4                    
    uint16				Power             ;//功率           2                    
    uint16				Voltage           ;//电压           2                    
    uint16				Current           ;//电流           2                    
    uint16				EngineSpeed       ;//柴速           2                    
    uint32				Longitude         ;//经度           4                    
    uint32  			Latitude	      ;//纬度           4                    
    uint16				AddSpeed          ;//加速度         2                     
    uint32				Rssi    : 6       ;//信号强度       1                  
    uint32				ErrCode : 24      ;//故障代码       3                  
    uint8				ModelCode         ;//模型编号       1                  
    uint8				DevConfig         ;//通讯设备配      1                   
    uint16				Recv              ;//预留           6                    
    struct _sSysTime {
        uint32      Sec                 : 6;        // D05~D00：秒
        uint32      Min                 : 6;        // D11~D06：分
        uint32      Hour                : 5;        // D16~D12：时
        uint32      Day                 : 5;        // D21~D17：日
        uint32      Mon                 : 4;        // D25~D22：月
        uint32      Year                : 6;        // D31~D26：年
    } SysTime;                                          // 04 LKJ时间
    uint8				TaxType                         ;//TAX特征码      1                     
    uint8				TaxFlg                           ;//TAX特征码      64       
    /***************************************************
    * 描述： TAX:64 bytes
    */
    union __uTAX__ {
    _StrTax_II_Rec      Tax2;                           // 记录数据     
    struct __sTAX_III__ {
    StrTaxVariable      Vari;
    StrTaxConstant      Cons;
    } Tax3;
    uint8_t             buf1[64];
    uint16_t            buf2[64/2];
    uint32_t            buf3[64/4];
    } Tax;    
    
    uint16				CrcCheck                        ;//校验   2                 
}stcFlshRecNDP02B;



typedef struct _stcLog_							//Fram日志索引   12
{
	uint16			DriveNum;					//设备编号	   2 
	uint8			LocoTyp[2];					//机车型号     2
	uint8			LocoNum[2];					//机车编号     2
	uint8			ErrorCode;					//故障代码     1
	uint8			RecTypCod;					//记录类型	   1
	uint32			StoreCnt;					//流水号       4
}stcLog;

typedef struct _stcLogZone_			//Fram日志区间
{
	stcLog			sLog[100];
	uint16			Times;						//预留
	uint16			CrcCheck;					//CRC检验
}stcLogZone;



#endif
