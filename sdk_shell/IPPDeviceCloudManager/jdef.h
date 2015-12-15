/*
 * jdef.h
 *
 *  Created on: 2015��8��19��
 *      Author: jiao
 */
#ifndef SAMPLE_APPS_TEST_TEA_SRC_JDEF_H_
#define SAMPLE_APPS_TEST_TEA_SRC_JDEF_H_

#include "ipp_defines.h"

//#define MAX_BUF 4*1024
//#define MAX_URL 2*1024
//#define IPP "2.0"
//#define KEY "key2.0"

typedef  struct Device{
		BOOL m_IsOnline;
		BOOL m_IsMaster;
		char* m_SN;
		char* m_MAC;
		int32_t m_Type;
		int32_t m_DeviceSource;
		int32_t m_DeviceID;
		char* m_GateWaySN;
		char* m_UserID;
		char* m_VCode;
		char* m_ProductID;
		int32_t m_ConnectType;
		char* m_Model;
		char* m_Name;
		char* m_Factory;
		char* m_SoftwareVersion;
		char* m_Location;
		size_t m_FunctionSize;
		int32_t *m_FunctionCode;

		struct Device *pNext;

}DevInfo;

typedef struct  {
	char* IP;
	int port;
	char* page;
}URL_strc;

#endif /* SAMPLE_APPS_TEST_TEA_SRC_JDEF_H_ */
