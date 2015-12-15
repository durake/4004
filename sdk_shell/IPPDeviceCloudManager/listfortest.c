/*
 * listfortest.c
 *
 *  Created on: 2015年9月2日
 *      Author: jiao
 */
#include <stddef.h>
#include "ipp_stub_def.h"
#include "jdef.h"
#include "SelfDeviceInfo.h"
char ipp_deviceId[24] = "qca4004";
//DevInfo dev_test = {1,1,"jiao_xc0","AB:CD:EF:29",1,1,123,"ch-10012304-10000002","12","vcode","CHTVTEST1",1,"model","name","factory","version1.0","my",1,NULL,NULL};
DevInfo dev_test = {1,1,ipp_deviceId,"AB:CD:EF:29",1,1,123,"ch-10012304-10000002","12","vcode","CHTVTEST1",1,"model","name","factory","version1.0","my",1,NULL,NULL};

//DevInfo dev_test;

extern SelfDeviceInfo g_SelfDeviceInfo;
void initinfo(){

	dev_test.m_IsOnline = g_SelfDeviceInfo.IsOnline;
	dev_test.m_IsMaster = 1;
	dev_test.m_SN = g_SelfDeviceInfo.SN;
	dev_test.m_MAC = g_SelfDeviceInfo.MAC;
	dev_test.m_Type = g_SelfDeviceInfo.Type;
	//dev_test.m_DeviceSource = ;
	dev_test.m_DeviceID = g_SelfDeviceInfo.DeviceId;
	//dev_test.m_GateWaySN = ;
	//dev_test.m_UserID = ;
	dev_test.m_VCode = g_SelfDeviceInfo.VCode;
	dev_test.m_ProductID = g_SelfDeviceInfo.ProductID;
	dev_test.m_ConnectType = g_SelfDeviceInfo.ConnectType;
	dev_test.m_Model = g_SelfDeviceInfo.Model;
	dev_test.m_Name = g_SelfDeviceInfo.Name;
	dev_test.m_Factory = g_SelfDeviceInfo.Factory;
	dev_test.m_SoftwareVersion = g_SelfDeviceInfo.SoftwareVersion;
	dev_test.m_Location = g_SelfDeviceInfo.Location;
	dev_test.m_FunctionSize = g_SelfDeviceInfo.FunctionSize;
	dev_test.m_FunctionCode = g_SelfDeviceInfo.FunctionCode;

	dev_test.pNext = NULL;
}

//typedef  struct Device {
//		BOOL m_IsOnline;
//		BOOL m_IsMaster;
//		char* m_SN;
//		char* m_MAC;
//		int32_t m_Type;
//		int32_t m_DeviceSource;
//		int32_t m_DeviceID;
//		char* m_GateWaySN;
//		char* m_UserID;
//		char* m_VCode;
//		char* m_ProductID;
//		int32_t m_ConnectType;
//		char* m_Model;
//		char* m_Name;
//		char* m_Factory;
//		char* m_SoftwareVersion;
//		char* m_Location;
//		size_t m_FunctionSize;
//		int32_t *m_FunctionCode;
//
//		struct Device *pNext;
//
//}DevInfo;
//int listconstructor(){
//
//
//
//	DevInfo *delist1 = devlist_create(4);
//
//	delist1->m_DeviceID = 123;
//	delist1->m_IsMaster = TRUE;
//	delist1->m_GateWaySN = "ch-10012304-10000002";
//	delist1->m_MAC = "AB:CD:EF:29";
//	delist1->m_SoftwareVersion = "version 1.0";
//	delist1->m_VCode = "895624";
//	delist1->m_SN = "jiao1";
//	delist1->m_ProductID = "1B24_0";
//
//	DevInfo *delist2 = delist1->pNext;
//
//	delist2->m_DeviceID = 1234;
//		delist2->m_IsMaster = FALSE;
//		delist2->m_GateWaySN = "ch-10012304-10000003";
//		delist2->m_MAC = "AB:CD:EF:39";
//		delist2->m_SoftwareVersion = "version 1.0";
//		delist2->m_VCode = "895624";
//		delist2->m_SN = "jiao2";
//		delist2->m_ProductID = "1B24_0";
//
//		DevInfo *delist3 = delist2->pNext;
//
//		delist3->m_DeviceID = 1235;
//		delist3->m_IsMaster = FALSE;
//		delist3->m_GateWaySN = "ch-10012304-10000004";
//		delist3->m_MAC = "AB:CD:EF:49";
//		delist3->m_SoftwareVersion = "version 1.0";
//		delist3->m_VCode = "895624";
//		delist3->m_SN = "jiao3";
//		delist3->m_ProductID = "1B24_0";
//
//		DevInfo *delist4 = delist3->pNext;
//
//		delist4->m_DeviceID = 12356;
//		delist4->m_IsMaster = FALSE;
//		delist4->m_GateWaySN = "ch-10012304-10000005";
//		delist4->m_MAC = "AB:CD:EF:59";
//		delist4->m_SoftwareVersion = "version 1.0";
//		delist4->m_VCode = "895624";
//		delist4->m_SN = "jiao4";
//		delist4->m_ProductID = "1B24_0";
//
//
//		DevInfo *test_copydev = devInfo_copy(delist2);
//		DevInfo *target_SN;
//		 devlist_findDevBySN(delist1,"jiao3",&target_SN);
//		printf("%s %s %s\n",target_SN->m_SN,target_SN->m_GateWaySN,target_SN->m_ProductID);
//		printf("%d %s %s",test_copydev->pNext->m_DeviceID,test_copydev->pNext->m_GateWaySN,test_copydev->pNext->m_ProductID);
//		return 0;
//}
