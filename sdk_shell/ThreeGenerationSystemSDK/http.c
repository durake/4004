/*
 * http.c
 *
 *  Created on: Nov 2, 2015
 *      Author: ghy
 */
/*
 #include "base.h"
 #include "stdint.h"
 #include "socket.h"
 #include "socket_api.h"
 #include "select_api.h"
 #include "qcom_mem.h"
 #include "qcom_common.h"
 #include "qcom_internal.h"
 */
#include "xmpp.h"
#include "DealXmppData.h"
#include "http.h"
#include "middleware.h"

#define RECV_SERV_BUF_SIZE (1024*3)
char httpRcv_buf[RECV_SERV_BUF_SIZE] = { 0 };

int ghttpSocketfd = -1;

int connectHttpServer(int sockfd, char* userid, char* ip, int port);
int handleDada(char* data);

/**
 * qcom_tcp_conn_timeout(10);
 * */


//int httpSocketCreat(){
int creatConnect() {


	struct sockaddr_in httpserv_addr;
	int ret = -1;
	int num = 15;

	while (num > 0) {

		if ((ghttpSocketfd = CH_MSGS_SOCKET(AF_INET, SOCK_STREAM, 0)) < 0) {
			CH_MSGS_DEBUG("creat---socket error!\n");
			CH_MSGS_SOCKET_CLOSE(ghttpSocketfd);
			return CH_MSGS_ERROR_CODE_HTTP_SOCKET;
		};

		CH_MSGS_DEBUG("httpip:%s   httpport:%d\n", ghttpServIP, ghttpServPort);

		httpserv_addr.sin_family = AF_INET;
		httpserv_addr.sin_port = htons(ghttpServPort);





	if (inet_pton(AF_INET, ghttpServIP, &httpserv_addr.sin_addr) <= 0) {
		A_PRINTF("--inet_pton error!\n");
		return CH_MSGS_ERROR_CODE_HTTP_IP;
	};

#ifdef CH_MSGS_VER_QCA4004
		qcom_tcp_conn_timeout(10); //connect 10s超时退出
#endif
		//while(num > 0)
		//{
		ret = CH_MSGS_CONNECT(ghttpSocketfd, (struct sockaddr *) &httpserv_addr,
				sizeof(httpserv_addr));

		if (ret >= 0) {
			CH_MSGS_DEBUG("http connect ok!\n");
			//return CH_MSGS_ERROR_CODE_HTTP_CONNECT;
			break;
		}
		//num--;
		CH_MSGS_DEBUG("http connect  %d\n", __LINE__);
		CH_MSGS_SOCKET_CLOSE(ghttpSocketfd);
#ifdef CH_MSGS_VER_QCA4004
		qcom_thread_msleep(2 * 1000);
#endif

#ifdef CH_MSGS_VER_LINUX
		sleep(2);
#endif
		//}

		num--;

	}
	CH_MSGS_DEBUG("-creatConnect is ok!\n");
	//return CH_MSGS_ERROR_CODE_OK;	//TODO
	return ret;
}

int recvHttpData(char* rcvdata) {

	int h = 0;
	int recvLen = 0;
	memset(httpRcv_buf, 0, RECV_SERV_BUF_SIZE);
	CH_MSGS_FD_SET t_set1;
	struct timeval tv;

	FD_ZERO(&t_set1);
	FD_SET(ghttpSocketfd, &t_set1);
	CH_MSGS_DEBUG("socketfd:%d %d %s \n", ghttpSocketfd, __LINE__, __func__);
	//while (1) {
	//sleep(2);
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	h = 0;

	h = CH_MSGS_SELECT(ghttpSocketfd + 1, &t_set1, NULL, NULL, &tv);
//
//		if (h == 0) {
//			CH_MSGS_DEBUG("time out http socket\n");
//			//break;
//		}
//		if (h < 0) {
//			CH_MSGS_SOCKET_close(ghttpSocketfd);
//
//			CH_MSGS_DEBUG("when read ,error .line:%d \n", __LINE__);
//
//		};

	if (h > 0) {
		memset(httpRcv_buf, 0, RECV_SERV_BUF_SIZE);
		recvLen = CH_MSGS_RECV(ghttpSocketfd, httpRcv_buf, 3071, 0);
		if (recvLen == 0) {
			//CH_MSGS_SOCKET_close(ghttpSocketfd);

			CH_MSGS_DEBUG("remote is cat off :line%d \n", __LINE__);

		}

		if (recvLen > 0) {
			//CH_MSGS_DEBUG("---line:%d  data:%s \n", __LINE__, httpRcv_buf);
			memcpy(rcvdata, httpRcv_buf, recvLen);
			//break;
		}

		CH_MSGS_DEBUG("%d %s recvLen:%d\n", __LINE__, __func__, recvLen);

	} else if (h == 0) {
		CH_MSGS_DEBUG("time out http socket\n");
	} else {
		CH_MSGS_DEBUG("when read ,error .line:%d \n", __LINE__);
	}
	//}
	CH_MSGS_SOCKET_CLOSE(ghttpSocketfd);
	ghttpSocketfd = -1;
	return recvLen;
}

int getXmppAddr(char* userid, char* ip, int port) {

	int ret = -1;
	int recvLen = 0;

	ret = creatConnect();
	if (ret < 0) {
		return ret;
	}

	//TODO POST
	ret = connectHttpServer(ghttpSocketfd, userid, ip, port);
	if (ret < 0) {
		return ret;
	}
//	if (ret > 0) {
//		gHttpIsInited = 1;
//	}

//	char* recvData = recvHttpData();
	char recvData[3072] = { 0 };
	recvLen = recvHttpData(recvData);

	if (recvLen > 0) {
		CH_MSGS_DEBUG("%d  %s \n", __LINE__, __func__);
		ret = handleDada(recvData);
		CH_MSGS_DEBUG("%d  %s \n", __LINE__, __func__);
		//CH_MSGS_FREE(recvData);

	}

	return ret;

}

//TODO POST
int connectHttpServer(int sockfd, char* userid, char* ip, int port) {

	//int retVal = 0;
	int ret = 0;
	char post[300], host[100], content_len[100];
	char request[200] = { 0 };
	char *lpbuf;
	int len = 0;
	lpbuf = NULL;
	const char *header2 = "Accept: */*\r\nContent-Type: application/json\r\n";

	//page
	memset(content_len, 0, 100);
	sprintf(content_len, "http://%s:%d/msgmain/terminal/connect", ip, port);

	sprintf(request,
			"{\"data\":\"{\\\"isencrypt\\\":\\\"0\\\",\\\"userid\\\":\\\"%s\\\",\\\"version\\\":\\\"v1.0\\\",\\\"termtype\\\":\\\"3\\\",\\\"deviceid\\\":\\\"null\\\"}\",\"source\":\"0\",\"domainid\":\"test1.com\"}",
			userid);

	memset(post, 0, 300);
	memset(host, 0, 100);
	sprintf(post, "POST %s HTTP/1.1\r\n", content_len);
	sprintf(host, "Host: %s:%d\r\n", ip, port);

	memset(content_len, 0, 100);
	sprintf(content_len, "Content-Length: %d\r\n\r\n", strlen(request));
	len = strlen(post) + strlen(host) + strlen(header2) + strlen(content_len)
			+ strlen(request) + 1;
	CH_MSGS_DEBUG("http_post lpbuf len = %d\r\n", len);
	lpbuf = (char*) CH_MSGS_MALLOC(len);
	//CH_MSGS_DEBUG("lpbuf = %x\r\n", lpbuf);
	if (lpbuf == NULL) {
		CH_MSGS_DEBUG("function = %s,line= %d\r\n", __FUNCTION__, __LINE__);
		ret = -1;
		//goto OUT;
	}
	memset(lpbuf, 0, len);
	//CH_MSGS_DEBUG("%d %s \n", __LINE__, __func__);
	strcpy(lpbuf, post);
	strcat(lpbuf, host);
	strcat(lpbuf, header2);
	strcat(lpbuf, content_len);
//	strcat(lpbuf,header2);
	strcat(lpbuf, request);
	CH_MSGS_DEBUG("http request: \n%s \n", request);

	CH_MSGS_DEBUG("%d %s \n", __LINE__, __func__);
	ret = CH_MSGS_SEND(sockfd, lpbuf, strlen(lpbuf), 0);
	if (ret < 0) {

		CH_MSGS_DEBUG("send ");
		//exit(0);
		ret = -1;
	} else {
		CH_MSGS_DEBUG("send success %d bytes锛乗n\n", ret);
	}
	//CH_MSGS_DEBUG("%d %s \n", __LINE__, __func__);
	CH_MSGS_FREE(lpbuf);
	return ret;

}

//TODO POST
int httpSendMsg(char* request) {
	int retVal = -1;
	int ret = 0;
	char post[300], host[100], content_len[100];
	char *lpbuf;
	int len = 0;
	lpbuf = NULL;
	const char *header2 = "Accept: */*\r\nContent-Type: application/json\r\n";

	memset(content_len, 0, 100);
	sprintf(content_len, "http://%s:%d/msgmain/msg/sendmsg", ghttpServIP,
			ghttpServPort);

	memset(post, 0, 300);
	memset(host, 0, 100);
	sprintf(post, "POST %s HTTP/1.1\r\n", content_len);
	sprintf(host, "Host: %s:%d\r\n", ghttpServIP, ghttpServPort);
	CH_MSGS_DEBUG("Host: %s:%d\r\n", ghttpServIP, ghttpServPort);

	memset(content_len, 0, 100);
	sprintf(content_len, "Content-Length: %d\r\n\r\n", strlen(request));

	len = strlen(post) + strlen(host) + strlen(header2) + strlen(content_len)
			+ strlen(request) + 1;

	lpbuf = (char*) CH_MSGS_MALLOC(len);
	if (lpbuf == NULL) {
		CH_MSGS_DEBUG("malloc is error  %s,line= %d\r\n", __FUNCTION__,
				__LINE__);
		return CH_MSGS_ERROR_CODE_HTTP_MALLOC;
	}
	memset(lpbuf, 0, len);
	strcpy(lpbuf, post);
	strcat(lpbuf, host);
	strcat(lpbuf, header2);
	strcat(lpbuf, content_len);
	strcat(lpbuf, request);
	//CH_MSGS_DEBUG("line:%d senddata:%s \n", __LINE__);
	ret = CH_MSGS_SEND(ghttpSocketfd, lpbuf, strlen(lpbuf), 0);
	if (ret < 0) {
		CH_MSGS_DEBUG("send error line: %d\n", __LINE__);
		ret = CH_MSGS_ERROR_CODE_HTTP_SNED;
	} else {
		CH_MSGS_DEBUG("send ok   %d bytes\n\n", ret);
	}

	CH_MSGS_FREE(lpbuf);

	return ret;

}

int handleDada(char* data) {
	//CH_MSGS_DEBUG(" data:%s\n", data);

	CH_MSGS_DEBUG("%d %s data:%s\n", __LINE__, __func__, data);
	char* port = NULL;
	char* authcode = NULL;
	char* address = NULL;
	char* end = NULL;
	char temp[10] = { 0 };
	CH_MSGS_DEBUG("%d %s \n", __LINE__, __func__);
	if (data == NULL) {
		CH_MSGS_DEBUG("line:%d data is null\n", __LINE__);
		return -1;
	}
	CH_MSGS_DEBUG("%d %s \n", __LINE__, __func__);
	/*	port = strstr(data, "port=");

		 authcode = strstr(data, "authcode=");
		 address = strstr(data, "address=");
		 end = strstr(data, "}\",");
		 if ((port == NULL) || (authcode == NULL) || (address == NULL)) {
		 A_PRINTF("line:%d data is null\n",__LINE__);//TODO chongxin jiexi
		 return -1;
		 }

		 strncpy(temp, port + 5, authcode - 7 - port);
		 gxmppServPort = atoi(temp);
		 strncpy(gxmppUserName, authcode + 9, address - authcode - 11);
		 strncpy(gxmppServIP, address + 8, end - address - 8);
		 */

	port = strstr(data, "port");

	authcode = strstr(data, "authcode");
	address = strstr(data, "address");
	end = strstr(data, "}\",");
	if ((port == NULL) || (authcode == NULL) || (address == NULL)) {
		CH_MSGS_DEBUG("line:%d data is null\n", __LINE__); //TODO chongxin jiexi
		return -1;
	}

	strncpy(temp, port + 9, authcode - 14 - port);
	CH_MSGS_DEBUG("port:%s \n", temp);
	gxmppServPort = atoi(temp);
	strncpy(gxmppUserName, authcode + 9 + 4, address - authcode - 11 - 7);
	strncpy(gxmppServIP, address + 8 + 4, end - address - 8 - 6);

	CH_MSGS_DEBUG("gxmppServPort:%d\n", gxmppServPort);
	CH_MSGS_DEBUG("gxmppUserName:%s\n", gxmppUserName);
	CH_MSGS_DEBUG("gxmppServIP:%s\n", gxmppServIP);

	return 1;

}

char* my_strcat(char* dest, const char* source) {
	char* tail = dest;
	while (*tail) {
		tail++;
	}
	strcpy(tail, source);
	return dest;
}

