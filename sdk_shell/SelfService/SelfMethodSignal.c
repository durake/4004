#include <stdio.h>
#include "ipp_stub_def.h"
#include "ipp_defines.h"
#include "ipp_util.h"
#include"SelfMethodSignal.h"
#include"SelfDeviceInfo.h"


DeviceControlCB DeviceControlHandler;


BOOL RemoteControlRequst(const char *sn, char* request, int reqlen, char** reply, int* replen)
{
	char* rep = NULL;
	BOOL ContrRet = FALSE;
	int nRLen = 0;
	if (DeviceControlHandler ==NULL)
	{
		return FALSE;
	}
	ipp_LogI("%s,sn:%s,request:%s,reqlen:%d\n",__func__,sn,request,reqlen);
	ContrRet = DeviceControlHandler((char*)request, reqlen, &rep, replen);
	nRLen = *replen;
	if (ContrRet)
	{
		ContrRet = 1;
	}
	*reply = (char*)calloc(1,sizeof(char)*(nRLen + 1));
	memcpy(*reply, &ContrRet, 1);
	memcpy(*reply + 1, rep, nRLen);
	*replen = nRLen + 1;
	FREE_POINTER(rep);
	return TRUE;
}
SelfDeviceInfo* RemoteGetDeviceInfo()
{
	return &g_SelfDeviceInfo;
}



void RegisterDevControlHandler(DeviceControlCB handler)
{
	DeviceControlHandler = handler;
}
