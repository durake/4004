/*
 * IPPDeviceFounction.h
 *
 *  Created on: 2015年9月2日
 *      Author: jiao
 */

#ifndef JSON_IPPDEVICEFOUNCTION_H_
#define JSON_IPPDEVICEFOUNCTION_H_
#include "ipp_stub_def.h"
#include "./jdef.h"
#include "./json.h"

#define MAX_URL 2*1024
#define MAX_BUF 4*1024

#ifdef IPP2
#define IPP "2.0"
#define KEY "key2.0"
#else
#define IPP "3.0"
#define KEY "key3.0"
#endif

#define DEVICE_NOT_REGISTER		"3002"
#define DEVICE_NOT_BIND			"3007"
#define DEVICE_LIST_PART_FAILED	        "1001"
#define DEVICE_REQ_SUC			"1000"
#define DEVICE_ALREADY_REGISTED	        "3001"
#define DEVICE_ALREADY_BINDED	        "3006"
#define D_NULL_STR			""

#define DEV_REGISTER 			1
#define DEV_UPDATESOFT			2
#define DEV_USER_BIND			3
#define DEV_UNBIND			4
#define DEV_UPLOAD_SATATE		5
#define DEV_UPLOAD_ARCHITECH		6
#define DEV_GETUSERLIST			7
#define DEV_CLEAR			8



void dev_upload_netowrk_architech(DevInfo *devList);
int sendJson(URL_strc *url,const char *all_obj,int fnc);
void initxmpp(char * SN);
void devReg(DevInfo *devList);
void dev_update(DevInfo *devList, const char *ver);
void dev_user_bind(DevInfo *devList, const char *authName);
void dev_upload_status(char *info, const char *sn);
void dev_getuserlist(const char *deviceID);
void dev_clear(const char *deviceID);

int handleresult(char *result_hex,int fnc);
#endif /* JSON_IPPDEVICEFOUNCTION_H_ */
