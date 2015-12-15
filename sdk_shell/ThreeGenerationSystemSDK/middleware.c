/*
 * middleware.c
 *
 *  Created on: Nov 3, 2015
 *      Author: ghy
 */

#include "xmpp.h"
#include "middleware.h"
#include "http.h"
#include "ReceiveMessage.h"
int strcat_from(char* dist, CH_MSGS_Account* source, char* name, int num);
void strcat_string(char* dist, char* source, char* name);
void strcat_int(char* dist, int source, char* name);
void strcat_int_end(char* dist, int source, char* name);
extern int gIsInited;

CH_MSGS_IReceiver_t_CB gCH_MSGS_IReceiver_t_CB = NULL;
CH_MSGS_IConnection_t_CB gCH_MSGS_IConnection_t_CB = NULL;

int CH_MSGS_Init(char* userid, char* httpip, int httpport,
		CH_MSGS_IReceiver_t_CB callbackFun,
		CH_MSGS_IConnection_t_CB connectState_CB) {
	int ret = -1;

	if (userid == NULL || httpip == NULL || httpport < 0) {
		return CH_MSGS_ERROR_CODE_MIDWARE_SERPAR;
	}

	ret = init(userid, httpip, httpport);
	if (ret < 0) {
		CH_MSGS_DEBUG("CH_MSGS_Init is error \n");
		return ret;
	}
	if (callbackFun != NULL) {
		gCH_MSGS_IReceiver_t_CB = callbackFun;

	}
	if (connectState_CB != NULL) {
		gCH_MSGS_IConnection_t_CB = connectState_CB;
	}
	return ret;

}

int CH_MSGS_Send(pCH_MSGS_Message pMsg, CH_MSGS_Result* pResult) {
	int ret = -1;
	char request[1024] = { 0 };
	if(gIsInited != 1)
	{
		return CH_MSGS_ERROR_CODE_MIDWARE_CONNECT_ERROR;
	}

	ret = checkMsg(pMsg);
	if (ret < 0) {
		return ret;
	}

	sprintf(request, "{\"data\":\"{");
	ret = strcat_from(request, pMsg->from, "from", 1);
	if(ret < 0)
	{
		return CH_MSGS_ERROR_CODE_MIDWARE_MSG_NULL;
	}

	strcat_int(request, pMsg->timeTolive, "timetolive");
	strcat_string(request, pMsg->toDomain, "todomain");
	strcat_string(request, pMsg->content, "content");
	ret = strcat_from(request, pMsg->target, "target", pMsg->target_size);
	if(ret < 0)
	{
			return CH_MSGS_ERROR_CODE_MIDWARE_MSG_NULL;
	}

	strcat_string(request, pMsg->title, "title");
	strcat_int(request, pMsg->passthrough, "passthrough");
	strcat_int(request, pMsg->notifyType, "notifytype");
	strcat_string(request, pMsg->version, "version");
	strcat_string(request, pMsg->description, "description");
	strcat_int_end(request, pMsg->isEncrypt, "isencrypt");
	strcat(request, "\"domainid\":\"test1.com\",\"source\":\"0\"}");

	ret = creatConnect();
	if (ret < 0) {
		CH_MSGS_DEBUG("line:%d error\n", __LINE__);
		return ret;
	}

	ret = httpSendMsg(request);
	if (ret < 0) {
		return ret;
	}
	//char* recvData = recvHttpData();
	char recvData[3072] = { 0 };
	int recvLen = 0;
	recvLen = recvHttpData(recvData);
	if (recvLen < 6) {
		return CH_MSGS_ERROR_CODE_MIDWARE_RCV_NULL;
	}

	char* temp = NULL;
	char* temp1 = NULL;
	temp = strstr(recvData, "reason");
	if (temp == NULL) {
		CH_MSGS_DEBUG("line:%d  data is error \n", __LINE__);
		return CH_MSGS_ERROR_CODE_MIDWARE_RCV_NULL;
	}
	temp1 = strstr(temp, "\",\"");
	CH_MSGS_DEBUG("line:%d   \n", __LINE__);
	if (temp == NULL || temp1 == NULL) {
		CH_MSGS_DEBUG("recv data:is error :line:%d \n", __LINE__);
		return CH_MSGS_ERROR_CODE_MIDWARE_RCV_DATA;
	}
	pResult->reason = NULL;
	pResult->reason = (char*) CH_MSGS_MALLOC(temp1 - temp - 6 - 3 + 1);
	if (pResult->reason == NULL) {
		CH_MSGS_DEBUG("malloc is error :line:%d \n", __LINE__);
		return CH_MSGS_ERROR_CODE_MIDWARE_MALLOC;
	}
	strncpy(pResult->reason, temp + 9, temp1 - temp - 6 - 3);
	pResult->reason[temp1 - temp - 6 - 3] = '\0';

	return CH_MSGS_ERROR_CODE_OK;

}

void strcat_string(char* dist, char* source, char* name) {
	char temp[200] = { 0 };

	sprintf(temp, "\\\"%s\\\":\\\"%s\\\",", name, source);
	strcat(dist, temp);

}

void strcat_int(char* dist, int source, char* name) {
	char temp[100] = { 0 };
	sprintf(temp, "\\\"%s\\\":\\\"%d\\\",", name, source);
	strcat(dist, temp);

}

void strcat_int_end(char* dist, int source, char* name) {
	char temp[100] = { 0 };
	sprintf(temp, "\\\"%s\\\":\\\"%d\\\"}\",", name, source);
	strcat(dist, temp);

}

int strcat_from(char* dist, CH_MSGS_Account* source, char* name, int num) {
	char temp[200] = { 0 };
	char temp1[200] = { 0 };
	int len = 0;

	int i = 0;
	for (i = 0; i < num; i++) {
		if((source[i].id == NULL)||(source[i].id == NULL))
		{
			return CH_MSGS_ERROR_CODE_MIDWARE_MSG_NULL;
		}

		memcpy(temp1 + len, source[i].id, strlen(source[i].id));
		len = len + strlen(source[i].id);
		memcpy(temp1 + len, "|", 1);
		len = len + 1;
		memcpy(temp1 + len, source[i].uiName, strlen(source[i].uiName));
		len = len + strlen(source[i].uiName);
		if (i != num - 1)
			memcpy(temp1 + len, ",", 1);
		len = len + 1;
	}

	sprintf(temp, "\\\"%s\\\":\\\"%s\\\",", name, temp1);
	strcat(dist, temp);
	return CH_MSGS_ERROR_CODE_OK;
}

void strcat_target(char* dist, int source, char* name) {
	char temp[100] = { 0 };
	sprintf(temp, "\\\"%s\\\":\\\"%d\\\"}\",", name, source);
	strcat(dist, temp);

}

int checkMsg(pCH_MSGS_Message pMsg) {
	int ret = CH_MSGS_ERROR_CODE_MIDWARE_MSG_NULL;

	if (pMsg->toDomain == NULL) {
		return ret;
	}

	if (pMsg->content == NULL) {
		return ret;
	}

	if (pMsg->title == NULL) {
		return ret;
	}

	if (pMsg->version == NULL) {
		return ret;
	}

	if (pMsg->description == NULL) {
		return ret;
	}

	if (pMsg->target == NULL) {
		return ret;
	}
	if (pMsg->from == NULL) {
		return ret;
	}

	return CH_MSGS_ERROR_CODE_OK;

}

char* strcat(char* dest, const char* source) {
	char* tail = dest;
	while (*tail) {
		tail++;
	}
	strcpy(tail, source);
	return dest;
}

