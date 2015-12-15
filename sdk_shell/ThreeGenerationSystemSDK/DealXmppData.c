#include <stdio.h>
#include <string.h>
#include "xmpp.h"
#include "DealXmppData.h"
#include "base64.h"
#include "TEA_beta_10.h"
#include "ReceiveMessage.h"


#include "middleware.h"

int LEN = 1024;

void printMsg(CH_MSGS_ReceiveMessage* Msg);
int analyze_msg(CH_MSGS_ReceiveMessage* msg, char* rawData);
extern CH_MSGS_IReceiver_t_CB gCH_MSGS_IReceiver_t_CB;

#define N 7//固定长度为7

void deapresence();
void reponseSuccess();
void RegisterDeviceInfo();
void RequestBind();
int dealsuccess(char* xmppHeadP);
int dealXmppHead(char* xmppHeadP);
int dealmessage(char* messagePtr);

int dealmessage(char* messagePtr) {
	int ret = 0;
	char* streamEnd = NULL;
	char* bodyStart = NULL;
	char* bodyEnd = NULL;
	int bodyLen = 0;
	char* body = NULL;
	CH_MSGS_ReceiveMessage rcvMsg;
	int idLen = 0;

	//CH_MSGS_DEBUG("messagePtr:%s\n", messagePtr);

	rcvMsg.content = NULL;
	rcvMsg.title = NULL;
	rcvMsg.messageId = NULL;
	rcvMsg.description = NULL;

	char* pTo = NULL;
	pTo = strstr(messagePtr, "to=");
	if (pTo != NULL) {
		idLen = pTo - 2 - (messagePtr + 13);
		CH_MSGS_DEBUG("idLen:%d\n", idLen);

		rcvMsg.messageId = (char*) CH_MSGS_MALLOC(idLen + 1);
		if (rcvMsg.messageId == NULL) {
			CH_MSGS_DEBUG("error CH_MSGS_MALLOC ,%d  %s \n", __LINE__, __func__);
		} else {

			memset(rcvMsg.messageId, 0, idLen + 1);
			memcpy(rcvMsg.messageId, messagePtr + 13, idLen); //151103152805002900001

			CH_MSGS_DEBUG("id=:%s\n", rcvMsg.messageId);

		}

	}

	bodyStart = strstr(messagePtr, "<body>");
	bodyEnd = strstr(messagePtr, "</body>");
	if (bodyEnd == NULL || bodyStart == NULL) {
		//	return 0;
		goto end;

	}

	bodyLen = bodyEnd - (bodyStart + strlen("<body>"));
	//CH_MSGS_DEBUG("bodyStart:0x%08x   bodyEnd:0x%08x     bodyLen:%d\n",
	//	(int) bodyStart, (int) bodyEnd, (int) bodyLen);
	if (bodyLen < 0)
		bodyLen = -bodyLen;

	body = (char*) CH_MSGS_MALLOC(bodyLen);
	if (body == NULL) {
		CH_MSGS_DEBUG("CH_MSGS_MALLOC is error .lien %d \n", __LINE__);
		//return 0;
		goto end;
	}

	memset(body, 0, bodyLen);
	memcpy(body, bodyStart + strlen("<body>"), bodyLen);

	analyze_msg(&rcvMsg, body);

	receipts(&rcvMsg);

	if (gCH_MSGS_IReceiver_t_CB != NULL) {

		gCH_MSGS_IReceiver_t_CB(&rcvMsg);

	}


	streamEnd = strstr(messagePtr, "</message>");

	ret = 0;

	ret = streamEnd + strlen("</message>") - messagePtr;

	if (ret < 0)
		ret = -ret;

	end: if (body != NULL) {
		CH_MSGS_FREE(body);
		body = NULL;
	}

	if (rcvMsg.messageId != NULL) {
		CH_MSGS_FREE(rcvMsg.messageId);
		rcvMsg.messageId = NULL;

	}

	return ret;

}

int dealpresence(char* presence) {

	char ret = -1;
	char* streamEnd = NULL;
	//ret = findStreamStart(xmppHeadP);
	streamEnd = strstr(presence, "/>");
	ret = 0;
	if (strstr(presence, "presence from")) {
		deapresence();
	}
	ret = streamEnd + strlen("/>") - presence;
	return ret;

}

void deapresence() {
	char* send_buf = "<presence id='MSv63-1'></presence>";
	int bufLen = 0;
	bufLen = strlen(send_buf);
	//int ret = -1;

	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/
		//pthread_mutex_lock(&gServLock);
		CH_MSGS_DEBUG("====== %s\n", send_buf);
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);

		//ret = 0;
	} else {

		//ret = -1;
	}

}

int dealrequestResponse(char* iq) {
	int ret = -1;
	char* streamEnd = NULL;
	//ret = findStreamStart(xmppHeadP);
	streamEnd = strstr(iq, "</iq>");
	ret = 0;

	ret = streamEnd + strlen("</iq>") - iq;
	if (ret < 0)
		ret = -ret;
	return ret;

}

void dealreques() {
	char* send_buf =
			"<iq id='WGGWl-0' type='set'><bind xmlns='urn:ietf:params:xml:ns:xmpp-bind'><resource>test1.com</resource></bind></iq>";
	int bufLen = 0;
	bufLen = strlen(send_buf);
	//int ret = -1;
//gServConnected == CONSTATE_CONNECT
	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/
		CH_MSGS_DEBUG("====== %s\n", send_buf);
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);
		//ret = 0;
	} else {

		//ret = -1;
	}

}

int dealsuccess(char* xmppHeadP) {

	int ret = 0;
	ret = strlen("<success xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\"/>");
	reponseSuccess();
	CH_MSGS_DEBUG("func:%s    delLen:%d\n", __func__, ret);
	return ret;

}

void reponseSuccess() {
	char* send_buf =
			"<stream:stream to=\"c\" xmlns=\"jabber:client\" xmlns:stream=\"http://etherx.jabber.org/streams\" version=\"1.0\">";
	int bufLen = 0;
	bufLen = strlen(send_buf);
	//int ret = -1;

	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/

		CH_MSGS_DEBUG("====== %s\n", send_buf);
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);

	//	ret = 0;
	} else {

		//ret = -1;
	}

}

int dealXmppHead(char* xmppHeadP) {
	int ret = -1;
	char* streamEnd = NULL;

	streamEnd = strstr(xmppHeadP, "</stream:features>");

	ret = 0;
	if (streamEnd != NULL) {

		if (strstr(xmppHeadP, "PLAIN")) {

			RegisterDeviceInfo();

		} else {
			RequestBind();

		}

		//	CH_MSGS_DEBUG("%s:%d \n", __func__, __LINE__);
		//CH_MSGS_DEBUG("end:0x%08x xmppheadp:0x%08x\n",
		//		streamEnd + strlen("</stream:features>"), xmppHeadP);
		ret = streamEnd + strlen("</stream:features>") - xmppHeadP;

	}

	CH_MSGS_DEBUG("%s:%d ret:%d\n", __func__, __LINE__, ret);
	if (ret < 0) {
		ret = -ret;
	}
	return ret;

}

//ok or not
int findStreamStart(char* xmppHeadP) {

	return 0;
}

void RegisterDeviceInfo() {
	char send_buf[256] = { 0 };

	int bufLen = 0;
	bufLen = strlen(send_buf);
	int ret = -1;

	char userLen = 0;
	char passwdLen = 0;
	char t_len = 0;
	char t_buf[50] = { 0 };
	//CH_MSGS_DEBUG("%s  :%s \n", gxmppUserName, gxmppPassWd);

	userLen = strlen(gxmppUserName);

	passwdLen = strlen(gxmppPassWd);

	t_len = userLen + passwdLen + 2;

	t_buf[0] = '\0';
	memcpy(t_buf + 1, gxmppUserName, userLen);
	t_buf[userLen + 1] = '\0';
	memcpy(t_buf + userLen + 2, gxmppPassWd, passwdLen);

	char* enc = NULL;

	enc = base64_encode(t_buf, t_len);

	if (enc == NULL) {
		CH_MSGS_DEBUG("encode is error\n");
		return;

	}

	strcat(send_buf,
			"<auth mechanism=\"PLAIN\" xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\">");
	strcat(send_buf, enc);
	strcat(send_buf, "</auth>");

	bufLen = strlen(send_buf);
	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/

		CH_MSGS_DEBUG("============send_buf:\n%s len:%d\n", send_buf, bufLen);
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);

		//ret = 0;
	} else {
		CH_MSGS_DEBUG("net work is error\n");
		//ret = -1;
	}

}

void RequestBind() {
	char* send_buf =
			"<iq id='WGGWl-0' type='set'><bind xmlns='urn:ietf:params:xml:ns:xmpp-bind'><resource>test1.com</resource></bind></iq>";

	int bufLen = 0;
	bufLen = strlen(send_buf);
	int ret = -1;

	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/

		CH_MSGS_DEBUG("============bind  send_buf:%s \n", send_buf);
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);

		ret = 0;
	} else {

		ret = -1;
	}

}

int analyze_msg(CH_MSGS_ReceiveMessage* msg, char* data) {
	//char* data = NULL;
	//char* temp = NULL;
	//int LEN = 1024;
	char tt[1024] = { 0 };
	char* id = NULL;
	int idLen = 0;


	//CH_MSGS_DEBUG("body:%s \n", data);

//-----------------------------------------------
	char* name = NULL;
	char* value = NULL;
	int len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "content");
	//CH_MSGS_DEBUG("name:%s---:%d \n",name, __LINE__);
	if (name != NULL) {
		value = strstr(name, "\",");
	}

	len = (int) value - (int) name - (strlen("content") + 3);

	strncpy(tt, name + (strlen("content") + 3), len);

	msg->content = (char*) CH_MSGS_MALLOC(strlen(tt) + 1);

	if (msg->content != NULL) {

		memset(msg->content, 0, strlen(tt) + 1);
		memcpy(msg->content, tt, strlen(tt) + 1);
		//CH_MSGS_DEBUG("len:%d =====  %s \n", strlen(msg->content),
		//		msg->content);
	}

	name = NULL;
	value = NULL;
	len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "title");
	value = strstr(name, "\",");
	len = (int) value - (int) name - strlen("title") - 3;
	strncpy(tt, name + (strlen("title") + 3), len);
	msg->title = (char*) CH_MSGS_MALLOC(strlen(tt) + 1);
	if (msg->title != NULL) {
		memset(msg->title, 0, strlen(tt) + 1);
		memcpy(msg->title, tt, strlen(tt) + 1);
		//CH_MSGS_DEBUG("len:%d =====  %s \n", strlen(msg->content),
		//		msg->content);
	}

	name = NULL;
	value = NULL;
	len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "description");
	value = strstr(name, "\",");
	len = (int) value - (int) name - strlen("description") - 3;
	strncpy(tt, name + (strlen("description") + 3), len);
	msg->description = (char*) CH_MSGS_MALLOC(strlen(tt) + 1);
	if (msg->description != NULL) {
		memset(msg->description, 0, strlen(tt) + 1);
		memcpy(msg->description, tt, strlen(tt) + 1);
		//CH_MSGS_DEBUG("len:%d =====  %s \n", strlen(msg->content),
		//		msg->content);
	}

//----------------from------------
	//	msg->from = (CH_MSGS_Account*) CH_MSGS_MALLOC(sizeof(CH_MSGS_Account));

	//CH_MSGS_DEBUG("---:%d \n", __LINE__);

	name = NULL;
	value = NULL;
	len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "from");

	value = strstr(name, "\"}");
	len = (int) value - (int) name - strlen("from") - 3;
	strncpy(tt, name + (strlen("from") + 3), len);
	msg->from = (CH_MSGS_Account*) CH_MSGS_MALLOC(sizeof(CH_MSGS_Account));
	id = strstr(tt, "|");
	idLen = id - tt;

	msg->from->id = (char*) CH_MSGS_MALLOC(idLen + 1);
	strncpy(msg->from->id, tt, idLen);
	msg->from->id[idLen] = '\0';

	msg->from->uiName = (char*) CH_MSGS_MALLOC(strlen(tt) - idLen + 1);
	strncpy(msg->from->uiName, tt + idLen + 1, strlen(tt) - idLen);
	msg->from->uiName[strlen(tt) - idLen] = '\0';

//-----------------from------------
//CH_MSGS_DEBUG("---:%d \n", __LINE__);
//	name = NULL;
//	value = NULL;
//	len = 0;
//	memset(tt, 0, 1024);
//	name = strstr(data, "heart");
//	value = strstr(name, "\",");
//	len = (int) value - (int) name - strlen("heart") - 3;
//	strncpy(tt, name+(strlen("heart") + 3), len);
	msg->heart = 0;
//	CH_MSGS_DEBUG("---:%d \n", __LINE__);

	name = NULL;
	value = NULL;
	len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "flag");
	value = strstr(name, "\",");
	len = (int) value - (int) name - strlen("flag") - 3;
	strncpy(tt, name + (strlen("flag") + 3), len);
	msg->flag = atoi(tt);
	//CH_MSGS_DEBUG("---:%d \n", __LINE__);
	name = NULL;
	value = NULL;
	len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "passthrough");
	value = strstr(name, "\",");
	len = (int) value - (int) name - strlen("passthrough") - 3;
	strncpy(tt, name + (strlen("passthrough") + 3), len);
	msg->passthrough = atoi(tt);
	//CH_MSGS_DEBUG("---:%d \n", __LINE__);
	name = NULL;
	value = NULL;
	len = 0;
	memset(tt, 0, 1024);
	name = strstr(data, "notifytype");
	value = strstr(name, "\",");
	len = (int) value - (int) name - strlen("notifytype") - 3;
	strncpy(tt, name+(strlen("notifytype") + 3), len);
	msg->notifyType = atoi(tt);

	//CH_MSGS_DEBUG("---:%d \n", __LINE__);

//
//	name = strstr(data, "\":\"");
//	while (name != NULL) {
//		num++;
//		memset(tt, 0, 100);
//		value = strstr(data, "\",\"");
//		if (value == NULL) {
//			value = strstr(data, "\"}");
//		}
//		memcpy(tt, name + 3, (value - (name + 3)));
//		//	CH_MSGS_DEBUG("num: %d len:%d   #%s# \n", num, strlen(tt), tt);
//
//		switch (num) {
//		case 1:
////
////			msg->content = (char*) CH_MSGS_MALLOC(strlen(tt) + 1);
////			if (msg->content != NULL) {
////				memset(msg->content, 0, strlen(tt) + 1);
////				memcpy(msg->content, tt, strlen(tt) + 1);
////				//CH_MSGS_DEBUG("len:%d =====  %s \n", strlen(msg->content),
////				//		msg->content);
////			}
////			break;
////		case 2:
////			msg->title = (char*) CH_MSGS_MALLOC(strlen(tt) + 1);
////			if (msg->title != NULL) {
////				memset(msg->title, 0, strlen(tt) + 1);
////				memcpy(msg->title, tt, strlen(tt) + 1);
////
////			}
////			break;
////		case 3:
////			msg->heart = atoi(tt);
////			break;
////		case 4:
////			msg->flag = atoi(tt);
////			break;
////		case 5:
////			msg->passthrough = atoi(tt);
////
////			break;
////		case 6:
////			msg->description = (char*) CH_MSGS_MALLOC(strlen(tt) + 1);
////			if (msg->description != NULL) {
////				memcpy(msg->description, tt, strlen(tt) + 1);
////				//CH_MSGS_DEBUG("=====  %s \n", msg->description);
////			}
////			break;
////		case 7:
////			msg->notifytype = atoi(tt);
//
//			break;
//		case 8: //TODO   #1001|1001_ui_name#
//			//	msg->from = ()
//
//			msg->from = (CH_MSGS_Account*) CH_MSGS_MALLOC(sizeof(CH_MSGS_Account));
//			id = strstr(tt, "|");
//			idLen = id - tt;
//
//			msg->from->id = (char*) CH_MSGS_MALLOC(idLen + 1);
//			strncpy(msg->from->id, tt, idLen);
//			msg->from->id[idLen] = '\0';
//
//			msg->from->uiName = (char*) CH_MSGS_MALLOC(strlen(tt) - idLen + 1);
//			strncpy(msg->from->uiName, tt + idLen + 1, strlen(tt) - idLen);
//			msg->from->uiName[strlen(tt) - idLen] = '\0';
//
//			break;
//
//		}
//
//		len = value + 3 - data;
//		memcpy(data, data + len, strlen(rawData));
//		name = strstr(data, "\":\"");
//
//	}
	//CH_MSGS_FREE(data);

	return 0;

}
//TODO

void printMsg(CH_MSGS_ReceiveMessage* Msg) {

	CH_MSGS_DEBUG("-------------Msg info------------------------\n");

	if (Msg->messageId != NULL) {
		CH_MSGS_DEBUG("messageId: %s\n", Msg->messageId);
		CH_MSGS_FREE(Msg->messageId);
	}

	if (Msg->content != NULL) {
		CH_MSGS_DEBUG("content: %s\n", Msg->content);
		CH_MSGS_FREE(Msg->content);
	}

	if (Msg->title != NULL) {
		CH_MSGS_DEBUG("title: %s\n", Msg->title);
		CH_MSGS_FREE(Msg->title);
	}

	CH_MSGS_DEBUG("heart:%d\n", Msg->heart);
	CH_MSGS_DEBUG("flag:%d\n", Msg->flag);
	CH_MSGS_DEBUG("passthrough:%d\n", Msg->passthrough);
	CH_MSGS_DEBUG("notifytype:%d\n", Msg->notifyType);

	if (Msg->description != NULL) {
		CH_MSGS_DEBUG("description: %s\n", Msg->description);
		CH_MSGS_FREE(Msg->description);
	}
//
	if (Msg->from != NULL) {
		CH_MSGS_DEBUG("from id: %s\n", Msg->from->id);
		CH_MSGS_DEBUG("from uiName: %s\n", Msg->from->uiName);
		CH_MSGS_FREE(Msg->from->id); //TODO
		CH_MSGS_FREE(Msg->from->uiName);
		Msg->from->id = NULL;
		Msg->from->uiName = NULL;
		CH_MSGS_FREE(Msg->from);
	}
	CH_MSGS_DEBUG("-------------Msg info------------------------\n");
}

char* create_random_num(char* ch) {
	int flag;
	int j, k = 0;

#ifdef CH_MSGS_VER_QCA4004
	int nTime = time_ms();
	CH_MSGS_DEBUG("********************%d", nTime);
	for (j = 0; j < N; j++) {
		qcom_thread_msleep(1);
		nTime = time_ms();
		flag = nTime % 2;
		if (flag)
			ch[k++] = 'A' +nTime % 26;
		else
			ch[k++] = 'a' + nTime % 26;
	}

	ch[k] = '\0';
#endif

#ifdef CH_MSGS_VER_LINUX
		srand((unsigned int) time((time_t*) NULL));

		for (j = 0; j < N; j++) {
			flag = rand() % 2;
			if (flag)
				ch[k++] = 'A' + rand() % 26;
			else
				ch[k++] = 'a' + rand() % 26;
		}

		ch[k] = '\0';
#endif



	return ch;
}

int receipts(CH_MSGS_ReceiveMessage* msg) { //TODO

	//char* send_buf = "<message id='p83rQ-3' to='1001#ipp.com@c/ipp.com'><received xmlns='urn:xmpp:receipts' id='as6I2-3'/></message>";
	char send_buf[256] = { 0 };

	//get random
	char *random_id = NULL;
	char ch[N + 1] = { 0 };
	random_id = create_random_num(ch);

	if (random_id == NULL) {
		CH_MSGS_DEBUG("create num fail!!\r\n");
		return 0;
	}

	strcat(send_buf, "<message id='");
	strcat(send_buf, random_id);
	strcat(send_buf, "' to='");
	strcat(send_buf, msg->from->id);
	//strcat(send_buf, msg->from->id);
	strcat(send_buf,
			"#test1.com@c/test1.com'><received xmlns='urn:xmpp:receipts' id='");
	strcat(send_buf, msg->messageId);
	strcat(send_buf, "'/></message>");






	int bufLen = 0;
	bufLen = strlen(send_buf);
	int ret = -1;

	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/

		CH_MSGS_DEBUG("==receipts==== \n");
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);

		ret = 0;
	} else {

		ret = -1;
	}

	return ret;

}

