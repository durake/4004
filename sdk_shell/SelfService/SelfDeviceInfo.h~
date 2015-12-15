/******************************************************************************
版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

******************************************************************************
文 件 名   : SelfDeviceInfo.h
版 本 号   : 初稿
作    者   : Fiona
生成日期   : 2015年7月8日
最近修改   :
功能描述   :
函数列表   :
修改历史   :
1.日    期   :
作    者   :
修改内容   : 创建文件
******************************************************************************/
#ifndef SelfDeviceInfo_H_
#define SelfDeviceInfo_H_
#include <string.h>



#ifdef __cplusplus
extern "C" {
#endif
#include"ipp_defines.h"
#define INFO_SIZE    50

	typedef struct _Device_Info{
		char MAC[30];
		char UserID[INFO_SIZE];
		char VCode[20];
		char ProductID[30];
		char role[20];
		char SN[INFO_SIZE];
		char flag[20];
		char IP[INFO_SIZE];
		BOOL IsOnline;
		int Type;
		int DeviceId;
		int ConnectType;
		char Model[25];
		char Name[25];
		char Factory[INFO_SIZE];
		char SoftwareVersion[30];
		char Location[25];
		int FunctionSize;
		int FunctionCode[4];
	}SelfDeviceInfo;


	/* 设置sn */
	void setSelfDeviceSN(const char* sn);
	/*获取sn */
	const char *getSelfDeviceSN();
	/*设置role */
	void setSelfDeviceRole(const char* role);
	/* 获取role*/
	const char *getSelfDeviceRole();
	/* 设置productID*/
	void setSelfDeviceProductID(const char* productid);
	/*获取productID */
	const char * getSelfDeviceProductID();
	/* 设置IP*/
	void setSelfDeviceIP(const char* ip);
	/*获取IP */
	const char *getSelfDeviceIP();
	/* 设置在线信息*/
	void setSelfDeviceIsOnline(BOOL isonline);
	/* 获取在线信息*/
	BOOL geSelfDevicetIsOnline();
	/* 设置设备类型*/
	void setSelfDeviceType(int type);
	/* 获取设备类型*/
	int getSelfDeviceType();
	/*设置DEVICEID */
	void setSelfDeviceDeviceId(int deviceid);
	/*获取DEVICEID */
	int getSelfDeviceDeviceId();
	/* 设置CONNECT TYPE*/
	void setSelfDeviceConnectType(int connecttpye);
	/* 获取CONNECT TYPE*/
	int getSelfDeviceConnectType();
	/* 设置model*/
	void setSelfDeviceModel(const char* model);
	/* 获取model*/
	const char *getSelfDeviceModel();
	/* 设置name*/
	void setSelfDeviceName(const char* name);
	/* 获取name*/
	const char * getSelfDeviceName();
	/* 设置factory*/
	void setSelfDeviceFactory(const char* factory);
	/* 设置factory*/
	const char *getSelfDeviceFactory();
	/*设置softwareversion */
	void setSelfDeviceSoftwareVersion(const char* softwareversion);
	/*获取softwareversion */
	const char *getSelfDeviceSoftwareVersion();
	/*设置device loctaion */
	void setSelfDeviceLocation(const char* location);
	/*获取device location */
	const char *getSelfDeviceLocation();
	/* 设置device flag*/
	void setSelfDeviceFlag(const char* flag);
	/*获取flag */
	const char *getSelfDeviceFlag();
	/*设置mac */
	void setSelfDeviceMac(const char* mac);
	/* 获取mac*/
	const char * getSelfDeviceMac();
	/*设置userid */
	void setSelfDeviceUserid(const char* userid);
	/*获取userid */
	const char * getSelfDeviceUserid();
	/* 设置vcode*/
	void setSelfDeviceVCode(const char* vcode);
	/*获取vcode */
	const char * getSelfDeviceVCode();
	/* 设备信息初始化*/
	void InitDevInfo();

	
	extern SelfDeviceInfo g_SelfDeviceInfo;


#ifdef __cplusplus
}
#endif
#endif

