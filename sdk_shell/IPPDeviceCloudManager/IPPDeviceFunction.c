/*
 * IPPDeviceFounction.c
 *
 *  Created on: 2015年8月31日
 *      Author: jiao
 */

#include "IPPDeviceFunction.h"
#include "ipp_adapter.h"
#include "tcp_client.h"
#include "TEA.h"
#include"common.h"
#include"CloudMessage.h"
#include"SelfDeviceInfo.h"
#include"ipp_defines.h"
#include "IPPUserList.h"
#include "common.h"
#include "CloudMessage.h"
#include "jdef.h"
#include "middleware.h"
#include "ReceiveMessage.h"
#include "ipp_stub_def.h"

//#include <stdio.h>
//#include <stddef.h>





extern DevInfo dev_test;

char g_wr_buf[MAX_BUF + 1];
int g_timeout = 0;

const char *g_tea_key = "chdevicecloud";
const int   g_tea_round = 16;

#ifdef IPP2
//ipp 2.0 request info

 char *g_host = "202.98.157.48";//ipp 2.0
 int g_port = 8080;
 char *g_register = "/ippcdc/device/register";
 char *g_update = "/ippcdc/device/update";
 char *g_bind = "/ippcdc/device/bind";
 char *g_unbind = "/ippcdc/device/unbind";
 char *g_upload_status = "/ippcdc/status/save";
 char *g_upload_netarch = "/ippcdc/device/masterreport";
#else
//ipp 3.0
char *g_host = "10.3.93.215";
int g_port = 8081;

char *g_register = "/cdc/device/register";
char *g_update = "/cdc/device/update";
char *g_upload_status = "/cdc/device/upstatus";
char *g_getusrlist = "/cdc/device/getuserlist";
char *g_devclear = "/cdc/device/remove";

char *g_bind = "/cdc/user/binddevice";
#endif

//void initxmpp(char * SN){
//	printf("init xmpp with SN:%s\n",SN);
//}

int spaceremover(char *in){

	if(in == NULL)
		return -1;

	int i = 0;
	int j;
	while(in[i] != '\0')
	{
		if(in[i] == 32)
		{
			j = i;
			while(in[j] != '\0')
			{
				char temp;
				temp = in[j+1];
				in[j] = temp;
				j++;
			}
			i--;
		}
	i++;
	}
	return 0;
}

char* jsonformator(struct json_object *json){
	 char *temp = (char *)json_object_to_json_string(json);
	 spaceremover((char*)temp);
	 return temp;
}


int sendJson(URL_strc *url,const char *jsonstr,int fnc){//use a strc to store the network Info

	ac_tcpclient ac_tcp;
	char *response = NULL;
	int retVal = 0;
	
	int result = ac_tcpclient_create(&ac_tcp,url->IP,url->port);		//ALex IPP2.0 Test
			if(result){
				printf("ac_tcpclient_create error\r\n");
				return -1;
			}
	char *encry = tea_encry(jsonstr, g_tea_key,g_tea_round);

	if(http_post(&ac_tcp,url->page,encry,&response) != 0){
				printf("Http post error\r\n");
					retVal = -1;
			}
	handleresult(response,fnc);
	free(response);
	ac_tcpclient_close(&ac_tcp);
	return retVal;
}
/*
int sendJson_t(URL_strc *url,char *all_obj,int fnc)
{
	printf("++++++++++++++sendJson_t0\r\n");
	ac_tcpclient ac_tcp;
	char *response = NULL;
	int retVal = 0;
	//struct printbuf *buf = printbuf_new();

	//json_object_object_to_json_string(all_obj,buf);
	printf("++++++++++++++sendJson_t0\r\n");
	int result = ac_tcpclient_create(&ac_tcp,url->IP,url->port);		//ALex IPP2.0 Test
			if(result){
				printf("ac_tcpclient_create error\r\n");
				return -1;
			}
	//char *encry = tea_encry(buf->buf, g_tea_key,g_tea_round);
	//ac_tcpclient_conn(&ac_tcp);
	//connect(pclient->socket, (struct sockaddr *)&pclient->_addr,sizeof(struct sockaddr_in));
	printf("++++++++++++++sendJson_t0\r\n");
	if(http_post(&ac_tcp,url->page,all_obj,&response) != 0){
				printf("Http post error\r\n");
					retVal = -1;
			}
	printf("response:%s\r\n",response);
	handleresult(response,fnc);
	printf("++++++++++++++sendJson_t0\r\n");
	free(response);
	//printbuf_free(buf);
	//json_object_put(all_obj);
	ac_tcpclient_close(&ac_tcp);
	return retVal;

}
*/
void devReg(DevInfo *devList){//xuyao there isnot a devlist but a single device
	printf("=================device register=================\n");
	  	URL_strc url;
	  	memset(&url,0,sizeof(url));
		url.IP = g_host;
		url.page = g_register;
		url.port = g_port;
		
		struct json_object *all_obj;
		struct json_object *system, *request, *dlist;
		struct json_object *json_ipp, *json_key;
		dlist = json_object_new_array();
		system = json_object_new_object();
		request = json_object_new_object();
		all_obj = json_object_new_object();
		const char *ipp = IPP;
		const char *key = KEY;
		json_ipp = json_object_new_string(ipp);
		json_key = json_object_new_string(key);
		json_object_object_add(system, "ipp", json_ipp);
		json_object_object_add(system, "key", json_key);
		DevInfo *ptmp = devList;
		while(ptmp != NULL) {
			struct json_object *device = json_object_new_object();
			struct json_object *json_devid = json_object_new_string(ptmp->m_SN);
			struct json_object *json_sn = json_object_new_string(ptmp->m_SN);
			struct json_object *json_productid = json_object_new_string(ptmp->m_ProductID);
			struct json_object *json_swver = json_object_new_string(ptmp->m_SoftwareVersion);
			struct json_object *json_mac = json_object_new_string(ptmp->m_MAC);
			//struct json_object *json_vcode = json_object_new_string(ptmp->m_VCode);
			//struct json_object *json_boxid = json_object_new_string(ptmp->m_GateWaySN);
			json_object_object_add(device, "devid", json_devid);
			json_object_object_add(device, "sn", json_sn);
			json_object_object_add(device, "productid", json_productid);
			json_object_object_add(device, "swver", json_swver);
			json_object_object_add(device, "mac", json_mac);
			//json_object_object_add(device, "vcode", json_vcode);
			//json_object_object_add(device, "boxid", json_boxid);
			json_object_array_add(dlist, device);
			ptmp = ptmp->pNext;
		}
		json_object_object_add(request, "devlist", dlist);
		json_object_object_add(all_obj, "system", system);
		json_object_object_add(all_obj, "request", request);
		printf("whole:%s\n",json_object_to_json_string(all_obj));

		char *jsontosend = jsonformator(all_obj);
		sendJson(&url, jsontosend, DEV_REGISTER);//
		json_object_put(all_obj);//release json object
}


void dev_update(DevInfo *devList, const char *ver){//xuyao
	printf("=================device update=================\n");

	URL_strc url;
	memset(&url,0,sizeof(url));
	url.IP = g_host;
	url.page = g_update;
	url.port = g_port;

	struct json_object *system, *request, *device, *whole;
	struct json_object *json_ipp, *json_key;
	struct json_object *json_devid, *json_swver;
//	struct json_object *json_sn, *json_productid, *json_mac;

	system = json_object_new_object();
	request = json_object_new_object();
	device = json_object_new_object();
	whole = json_object_new_object();

	const char *ipp = IPP;
	const char *key = KEY;
	json_ipp = json_object_new_string(ipp);
	json_key = json_object_new_string(key);
	json_object_object_add(system, "ipp", json_ipp);
	json_object_object_add(system, "key", json_key);

	json_devid = json_object_new_string(devList->m_SN);
	json_swver = json_object_new_string(devList->m_SoftwareVersion);
	//json_vcode = json_object_new_string(devList->m_VCode);
	json_object_object_add(device, "devid", json_devid);
	json_object_object_add(device, "swver", json_swver);
	//json_object_object_add(device, "vcode", json_vcode);

	json_object_object_add(request, "device", device);
	json_object_object_add(whole, "request", request);
	json_object_object_add(whole, "system", system);

	printf("whole:%s\n",json_object_to_json_string(whole));

	char *jsontosend = jsonformator(whole);
	sendJson(&url, jsontosend, DEV_UPDATESOFT);//
	json_object_put(whole);
}
/*
void dev_user_bind(DevInfo *devList, const char *authName){//buxuyao
	printf("=================device user bind=================\n");
//	gAuthName = authName;
//	printf("gAuthName=%s\n", gAuthName);

	URL_strc url;
	memset(&url,0,sizeof(url));
	url.IP = g_host;
	url.page = g_bind;
	url.port = g_port;

	struct json_object *all_obj;
	struct json_object *system, *request, *dlist, *device;
	struct json_object *json_ipp, *json_key;

	dlist = json_object_new_array();
	system = json_object_new_object();
	request = json_object_new_object();
	all_obj = json_object_new_object();

	const char *ipp = IPP;
	const char *key = KEY;
	json_ipp = json_object_new_string(ipp);
	json_key = json_object_new_string(key);
	json_object_object_add(system, "ipp", json_ipp);
	json_object_object_add(system, "key", json_key);

	   DevInfo *ptmp = devList;
		while(ptmp->pNext != NULL) {

		struct json_object *json_devid = json_object_new_string(ptmp->m_SN);
		printf("json_devid=%s\n", json_object_to_json_string(json_devid));
		struct json_object *json_userid = json_object_new_string(ptmp->m_UserID);

		device = json_object_new_object();
		json_object_object_add(device, "devid", json_devid);
		json_object_object_add(device, "userid", json_userid);
		json_object_array_add(dlist, device);
		ptmp = ptmp->pNext;
	}
	json_object_object_add(request, "bindlist", dlist);

	json_object_object_add(all_obj, "system", system);
	json_object_object_add(all_obj, "request", request);
	printf("whole:%s\n",json_object_to_json_string(all_obj));

	char *jsontosend = jsonformator(all_obj);
	sendJson(&url, jsontosend, DEV_USER_BIND);//
	json_object_put(all_obj);
	//return bindresult;
}
*/

void dev_upload_status(char *info, const char *sn){//xuyao
	printf("=================device report status=================\n");

	URL_strc url;
	memset(&url,0,sizeof(url));
	url.IP = g_host;
	url.page = g_upload_status;
	url.port = g_port;

	struct json_object *system, *request, *devid, *state, *whole;
	struct json_object *json_ipp, *json_key;
	struct json_object *json_devid;
	struct json_object *j_mode;

	system = json_object_new_object();
	request = json_object_new_object();
	devid = json_object_new_object();
	state = json_object_new_object();
	whole = json_object_new_object();

	const char *ipp = IPP;
	const char *key = KEY;
	json_ipp = json_object_new_string(ipp);
	json_key = json_object_new_string(key);
	json_object_object_add(system, "ipp", json_ipp);
	json_object_object_add(system, "key", json_key);

	json_devid = json_object_new_string(sn);
	json_object_object_add(request, "devid", json_devid);

	j_mode = json_object_new_string(info);
//	j_speed = json_object_new_string(status.GetLocation().c_str());
//	j_power = json_object_new_string(status.GetName().c_str());
	json_object_object_add(state, "data", j_mode);
//	json_object_object_add(state, "speed", j_speed);
//	json_object_object_add(state, "power", j_power);

	json_object_object_add(request, "status", state);
	json_object_object_add(whole, "request", request);
	json_object_object_add(whole, "system", system);

	printf("whole:%s\n",json_object_to_json_string(whole));

	char *jsontosend = jsonformator(whole);
	sendJson(&url, jsontosend, DEV_UPLOAD_SATATE);//
	json_object_put(whole);
}
/*
void dev_upload_netowrk_architech(DevInfo *devList){//xuyao  reoport the itslf
	printf("=================device report master=================\n");
	URL_strc url;
	memset(&url,0,sizeof(url));
	url.IP = g_host;
	url.page = g_upload_netarch;
	url.port = g_port;
	struct json_object *system, *request, *whole, *slavelist;
	struct json_object *json_ipp, *json_key;
	system = json_object_new_object();
	request = json_object_new_object();
//	devid = json_object_new_object();
//	master = json_object_new_object();
	whole = json_object_new_object();
	slavelist = json_object_new_array();
	const char *ipp = IPP;
	const char *key = KEY;
	json_ipp = json_object_new_string(ipp);
	json_key = json_object_new_string(key);
	json_object_object_add(system, "ipp", json_ipp);
	json_object_object_add(system, "key", json_key);
	//struct json_object *json_devid;
	printf("=================device report master 1!!!!!=================\n");
	DevInfo *ptmp = devList;
	while(ptmp != NULL) {


		struct json_object *json_devid;
		json_devid = json_object_new_string(devList->m_SN);
//		printf("%s\n",  json_object_to_json_string(json_devid));
		if (ptmp->m_IsMaster) {
//			printf("master\n");
			json_object_object_add(request, "master", json_devid);//只有一个master
		}
		else {
			json_object_array_add(slavelist, json_devid);//组装成slave json数组
////			printf("slave%s\n", json_object_to_json_string(slavelist));
		}

		ptmp = ptmp->pNext;
	}
	json_object_object_add(request, "slave", slavelist);//组装到request
	json_object_object_add(whole, "request", request);
	json_object_object_add(whole, "system", system);
	//printf("slave list: %s\n",  json_object_to_json_string(slavelist));
//	printf("%s\n",  json_object_to_json_string(system));
	printf("whole:%s\r\n",json_object_to_json_string(whole));

	A_PRINTF("\r\nmem_left=%d\r\n",qcom_mem_heap_get_free_size());
	sendJson(&url, whole, DEV_UPLOAD_ARCHITECH);
	json_object_put(whole);//release json object


}
*/
/*
void dev_upload_netowrk_architech_t(DevInfo *devList){

	URL_strc url;
	memset(&url,0,sizeof(url));
	url.IP = g_host;
	url.page = g_upload_netarch;
	url.port = g_port;
	 char* whole = "7D7D7D7D7D7D7D7D3AA1F32EA789FAE9E68D09AC2892ADA0468E7CE0BD9A2AD718CB179FA2808FB73EED2DB7763F34860CE10D203C4A693308447084A646B167A8433349693B4BB2FA58517B86EDA7BB7FE2BA48E51AD8FEC2FD8DE7D9D3E18B";
	printf("whole:%slen:%d\r\n",whole,strlen(whole));
	sendJson_t(&url, whole, DEV_UPLOAD_ARCHITECH);
}
*/
#ifndef IPP2
void dev_getuserlist(const char *deviceID)
{
	printf("=================device getuserlist master=================\n");
		URL_strc url;
		memset(&url,0,sizeof(url));
		url.IP = g_host;
		url.page = g_getusrlist;
		url.port = g_port;

		struct json_object *system, *request, *whole;
		struct json_object *json_ipp, *json_key;
		struct json_object *json_devid;

		system = json_object_new_object();
		request = json_object_new_object();
		whole = json_object_new_object();

		const char *ipp = IPP;
		const char *key = KEY;
		json_ipp = json_object_new_string(ipp);
		json_key = json_object_new_string(key);

		json_object_object_add(system, "ipp", json_ipp);
		json_object_object_add(system, "key", json_key);

		json_devid = json_object_new_string(deviceID);

		json_object_object_add(request, "devid", json_devid);

		json_object_object_add(whole, "system", system);
		json_object_object_add(whole, "request", request);

		printf("whole:%s\n",json_object_to_json_string(whole));


		char *jsontosend = jsonformator(whole);
		sendJson(&url, jsontosend, DEV_REGISTER);//
		json_object_put(whole);

}
#endif
void dev_clear(const char *deviceID)
{
	printf("=================device clear up=================\n");
		URL_strc url;
		memset(&url,0,sizeof(url));
		url.IP = g_host;
		url.page = g_devclear;
		url.port = g_port;


		struct json_object *system, *request, *whole;
		struct json_object *json_ipp, *json_key;
		struct json_object *json_devid;

		system = json_object_new_object();
		request = json_object_new_object();
		whole = json_object_new_object();

		const char *ipp = IPP;
		const char *key = KEY;
		json_ipp = json_object_new_string(ipp);
		json_key = json_object_new_string(key);

		json_object_object_add(system, "ipp", json_ipp);
		json_object_object_add(system, "key", json_key);

		json_devid = json_object_new_string(deviceID);

		json_object_object_add(request, "devid", json_devid);

		json_object_object_add(whole, "system", system);
		json_object_object_add(whole, "request", request);

		printf("whole:%s\n",json_object_to_json_string(whole));
		char *jsontosend = jsonformator(whole);
		printf("whole:%s\n",jsontosend);
		sendJson(&url, jsontosend, DEV_CLEAR);

		json_object_put(whole);

}


void handle_getuserlist(const char *code,struct json_object *result){
	if(!strcmp(code,DEVICE_REQ_SUC)){
		printf("add\n");
		XmppUserListInit();
		XmppOnlineUser *listhead = GetUserListHead();
		int index = 0;
		struct json_object *userlist,*tempuser,*temprelation;
		json_object_new_object();
		userlist = json_object_object_get(result, "userlist");
		int len = json_object_array_length(userlist);
		listhead->nUserSize = len;
		if(len > 0){
		for(;index < len;index++){
			struct json_object *tempuserobj = json_object_array_get_idx(userlist, index);
			tempuser = json_object_object_get(tempuserobj,"userid");
			temprelation = json_object_object_get(tempuserobj,"relation");
			const char *userID = json_object_to_json_string(tempuser);
			const char *relation = json_object_to_json_string(temprelation);
			
			ElemType insertElemtemp;
			if(userID != NULL && relation !=NULL)
			{
				printf("userID:%s,relation:%s\n",userID,relation);
				memset(&insertElemtemp,0,sizeof(ElemType));
				strcpy(insertElemtemp.pstMsgSAccount.id,userID); 
				
				if(!strcmp(relation,"share"))
					insertElemtemp.nRelation = RELATION_SHARE; 
				else if(!strcmp(relation,"bind"))
					insertElemtemp.nRelation = RELATION_BIND;
				else 
					printf("error type\r\n");

				insertLastList(&(listhead->stUserList),&insertElemtemp);
			//TODO add the bind relationship info into the fan's list
			}
		}
		}
	}

}

void handle_devReg(const char *code){

	if(!strcmp(code, DEVICE_REQ_SUC) || !strcmp(code, DEVICE_ALREADY_REGISTED)||!strcmp(code, DEVICE_LIST_PART_FAILED)){//device register suc, init xmpp account masterid
		xmppMessageInit();
	}

}

void handle_dev_upload_netowrk_architech(const char *code){
	if(!strcmp(code,DEVICE_NOT_REGISTER)){//part list fail bu chu li
		devReg(&dev_test);
	}else if(!strcmp(code,DEVICE_REQ_SUC)){
		xmppMessageInit();
	}
}


int handleresult(char *result_hex,int fnc){//parse the json string handle result

	char*content = tea_decry(result_hex, g_tea_key, g_tea_round);
	printf("result json:  %s\n", content);
	if(content){
		struct json_object *json_code, *json_errlist;
		struct json_object *result = json_tokener_parse(content);
		json_code = json_object_object_get(result, "code");
		json_errlist = json_object_object_get(result, "errorlist");
		const char *code = json_object_get_string(json_code);
	if(fnc == DEV_REGISTER)
		handle_devReg(code);
	//else if(fnc == DEV_UPLOAD_ARCHITECH )
	//	handle_dev_upload_netowrk_architech(code);
	else if(fnc == DEV_GETUSERLIST)
		handle_getuserlist(code,result);
	return 0;
}
	printf("NULL content\r\n");
	return -1;
}

///
/**
 * report device state
 */
void DeviceStateEnQueqe(const char *sn,
		int32_t deviceType, size_t dataLen, char *datas) {
	printf("=================DeviceStateReportCallBack=================\n");

	CH_MSGS_Message stXmppSendMessage;//xmpp待发送的的消息
	stXmppDataList stXmppResponseDatalist;//回复xmpp待发送处理后数据
	CH_MSGS_Result* pResult = 0;
	int event_id = 0;
	char *pa = NULL;

	stXmppResponseDatalist.chXmppDataList = NULL;

	memcpy(&event_id, datas, 4);
	printf("event_id = %08X\n", event_id);
	printf("data length:%d\n", dataLen);

	if(dataLen > 4 && datas != NULL){
		pa = (char *) malloc(dataLen - 4);
		memset(pa, 0, dataLen - 4);
		memcpy(pa, datas + 4, dataLen - 4);

//		for(int i=0;i<dataLen - 4;i++){
//			printf("lw-------pastr:%02X\n",pa[i]);
//		}
		formSendMsgContent((char*)sn, (char)TYPE_EVENT, event_id, pa, dataLen - 4, &stXmppResponseDatalist);
		formXmppSendMsg(NULL, &stXmppSendMessage, &stXmppResponseDatalist);

		pResult = (CH_MSGS_Result*)calloc(1,sizeof(CH_MSGS_Result));
		int ret = CH_MSGS_Send(&stXmppSendMessage, pResult);
		if (ret)
		{
			handleXmppSendResult(pResult);
		}
		FREE_POINTER(pa);
		FREE_POINTER(stXmppResponseDatalist.chXmppDataList);
		stXmppSendMessage.content = NULL;
		FREE_POINTER(stXmppSendMessage.target);
		FREE_POINTER(stXmppSendMessage.title);
	   FREE_POINTER(stXmppSendMessage.description);
	   FREE_POINTER(stXmppSendMessage.userRange);
	   FREE_POINTER(stXmppSendMessage.version);
	   FREE_POINTER(pResult->reason);
	   FREE_POINTER(pResult);
		dev_upload_status(datas, sn);
	}
}

/**
 * update device software version
 */
void DeviceSoftWareUpdate(const char *swVer,
		DevInfo *devList) {
	printf("=================DeviceSoftWareUpdateCallBack=================\n");
	dev_update(devList, swVer);
}

/**
 * device online report master slave
 */
void DeviceUpline(DevInfo *devList) {
	printf("=================DeviceOnlineCallBack=================\n");
	//IPPEvent event(dInfo.GetSN(), EVENT_UPLINE);
	//gMessageManager->sendEvent(&event);

	CH_MSGS_Message stXmppSendMessage;//xmpp待发送的的消息
	stXmppDataList stXmppResponseDatalist;//回复xmpp待发送处理后数据
	CH_MSGS_Result* pResult = 0;

	stXmppResponseDatalist.chXmppDataList = NULL;

		formSendMsgContent((char*)getSelfDeviceSN(), (char)TYPE_EVENT, (int)EVENT_UPLINE, NULL, 0, &stXmppResponseDatalist);
		formXmppSendMsg(NULL, &stXmppSendMessage, &stXmppResponseDatalist);

		pResult = (CH_MSGS_Result*)calloc(1,sizeof(CH_MSGS_Result));
		int ret = CH_MSGS_Send(&stXmppSendMessage, pResult);
		if (ret)
		{
			handleXmppSendResult(pResult);
		}
		FREE_POINTER(stXmppResponseDatalist.chXmppDataList);
		stXmppSendMessage.content = NULL;
		FREE_POINTER(stXmppSendMessage.target);
		FREE_POINTER(stXmppSendMessage.title);
	   FREE_POINTER(stXmppSendMessage.description);
	   FREE_POINTER(stXmppSendMessage.userRange);
	   FREE_POINTER(stXmppSendMessage.version);
		FREE_POINTER(pResult->reason);
	   FREE_POINTER(pResult);
	devReg(devList); //

}

/**
 * device offline report master slave
 */
void DeviceOffline(DevInfo *devList) {
	printf("=================DeviceOfflineCallBack=================\n");
	//IPPEvent event(dInfo.GetSN(), EVENT_OFFLINE);
	//gMessageManager->sendEvent(&event);

	dev_upload_netowrk_architech(devList);
}

void cloudinit_cb(BOOL havemaster){
	extern void initinfo();
	initinfo();
	if(!havemaster)
		DeviceUpline(&dev_test);
	reg_cloud_send_event_cb(DeviceStateEnQueqe);	

}


void cloudinit(){
	reg_master_result_cb(cloudinit_cb);
}


