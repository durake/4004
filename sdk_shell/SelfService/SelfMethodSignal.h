/******************************************************************************

版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

******************************************************************************
文 件 名   : SelfDeviceInfo.h
版 本 号   : 初稿
作    者   : Fiona
生成日期   : 2015年8月8日
最近修改   :
功能描述   :
函数列表   :
修改历史   :
1.日    期   :l
作    者   :
修改内容   : 创建文件
******************************************************************************/
#ifndef SELFMETHODSIGNAL_H_
#define SELFMETHODSIGNAL_H_


#ifdef __cplusplus
extern "C" {
#endif

#include"SelfDeviceInfo.h"
#include "ipp_defines.h"



	/*设备控制函数指针类型*/
	typedef BOOL(*DeviceControlCB)(char* request, int reqlen, char** reply, int* replen);
	/*注册设备控制函数*/
	void RegisterDevControlHandler(DeviceControlCB handler);
	/*远程获取设备信息*/
	SelfDeviceInfo* RemoteGetDeviceInfo();
	/*远程控制请求*/
	BOOL RemoteControlRequst(const char *sn, char* request, int reqlen, char** reply, int* replen);

	extern DeviceControlCB DeviceControlHandler;

#ifdef __cplusplus
}
#endif
#endif

