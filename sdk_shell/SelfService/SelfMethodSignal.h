/******************************************************************************

��Ȩ���� (C), 1958-2015, �����������-�Ʒ�-���ּ�ͥ

******************************************************************************
�� �� ��   : SelfDeviceInfo.h
�� �� ��   : ����
��    ��   : Fiona
��������   : 2015��8��8��
����޸�   :
��������   :
�����б�   :
�޸���ʷ   :
1.��    ��   :l
��    ��   :
�޸�����   : �����ļ�
******************************************************************************/
#ifndef SELFMETHODSIGNAL_H_
#define SELFMETHODSIGNAL_H_


#ifdef __cplusplus
extern "C" {
#endif

#include"SelfDeviceInfo.h"
#include "ipp_defines.h"



	/*�豸���ƺ���ָ������*/
	typedef BOOL(*DeviceControlCB)(char* request, int reqlen, char** reply, int* replen);
	/*ע���豸���ƺ���*/
	void RegisterDevControlHandler(DeviceControlCB handler);
	/*Զ�̻�ȡ�豸��Ϣ*/
	SelfDeviceInfo* RemoteGetDeviceInfo();
	/*Զ�̿�������*/
	BOOL RemoteControlRequst(const char *sn, char* request, int reqlen, char** reply, int* replen);

	extern DeviceControlCB DeviceControlHandler;

#ifdef __cplusplus
}
#endif
#endif

