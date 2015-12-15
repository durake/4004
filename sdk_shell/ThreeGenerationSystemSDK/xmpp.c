#include "xmpp.h"
#include "DealXmppData.h"
#include "middleware.h"

#define 	NS_INADDRSZ     4
#define PSEUDO_HOST_STACK_SIZE_6K (6 * 1024 )
#define PSEUDO_HOST_STACK_SIZE_8K (8 * 1024 )
#define RECV_SERV_BUF_SIZE (1024*3)
#define N 7//固定长度为7
#define BYTE_POOL_SIZE_6K (6*1024 + 256 )

static uint8_t connect_err_count = 0;

#ifdef CH_MSGS_VER_QCA4004
TX_BYTE_POOL pool3;
TX_THREAD xmppRecvTid;
#endif

#ifdef CH_MSGS_VER_LINUX
pthread_t gServTid = 0;
void* server_thread_linux(void* arg);

#endif

//ghy add
char gxmppUserName[64] = { 0 };
char gxmppPassWd[64] = { 0 };

static uint32_t addr_ip4 = 0;

char gxmppServIP[64] = { 0 };
short gxmppServPort = 0;

char ghttpServIP[64] = { 0 };
short ghttpServPort = 0;
char ghttpUserID[20] = { 0 };

int gHttpIsInited = 1;

static int gServLiveTime = 0;

int gServConnected = CONSTATE_DISCONNECT;/*-1:error,0:disconnect,1:connect */
int gServSock = -1;
int gIsInited = 1;
int gStatus = 0; //used for add and delete friends
int gDelStatus = 0;
extern CH_MSGS_IReceiver_t_CB gCH_MSGS_IReceiver_t_CB;
extern CH_MSGS_IConnection_t_CB gCH_MSGS_IConnection_t_CB;

int get_ip_addr_from_string(const char *string);

#ifdef CH_MSGS_VER_LINUX

unsigned int get_ip4(char *host) {
	char dns_buff[8192];
	struct hostent hostinfo, *phost;
	struct sockaddr_in addr4;
	int rc;

	//time_t now;
	unsigned int ip4;

	bzero(&addr4, sizeof(struct sockaddr_in));
	if (1 == inet_pton(AF_INET, host, &(addr4.sin_addr)))
	return (addr4.sin_addr.s_addr);

	if (0 == gethostbyname_r(host, &hostinfo, dns_buff, 8192, &phost, &rc)) {
		ip4 = *(unsigned int *) (hostinfo.h_addr);
	} else {
		ip4 = 0;
	}
	return (ip4);

}

#endif

#ifdef CH_MSGS_VER_QCA4004
unsigned int get_ip4(char *host) {

	uint32_t ipAddress;
	struct sockaddr_in addr4;

	memset(&addr4, 0, sizeof(struct sockaddr_in));
	if (1 == inet_pton(AF_INET, host, &(addr4.sin_addr))) {
		CH_MSGS_DEBUG("addr4.sin_addr.s_addr = %lu\r\n", addr4.sin_addr.s_addr);
		return (addr4.sin_addr.s_addr);
	}

	if (qcom_dnsc_get_host_by_name(host, &ipAddress) != A_OK) {
		CH_MSGS_DEBUG("ipAddress = 0\r\n");
		ipAddress = 0;
	}
	CH_MSGS_DEBUG("ipAddress = %u\r\n", ipAddress);
	return (ipAddress);

}
#endif

static int xmpp_parse_ip_addr_from_string(const char *string, char *ip, short *port) {
	/*
	 char *p = NULL;
	 struct in_addr addr;
	 char str_tmp[256] = { 0 };
	 //"10.3.93.241:5222";
	 if (string == NULL || ip == NULL)
	 return -1;
	 p = strchr(string, ':');
	 *port = atoi(p + 1);
	 memcpy(str_tmp, string, p - string);
	 addr.s_addr = get_ip4(str_tmp);
	 if (addr.s_addr == 0) {
	 return -1;
	 }

	 char* ipstr = inet_ntoa(addr);
	 strcpy(ip, ipstr);
	 CH_MSGS_DEBUG("ip=%s,port=%d\n", ip, *port);*/
	return 0;
}

int parse_ip_addr_from_string(const char *string, char *ip, short *port) {
	/*
	 char *p = NULL;
	 struct in_addr addr;
	 char str_tmp[256] = { 0 };
	 //"10.3.93.241:5222";
	 if (string == NULL || ip == NULL)
	 return -1;
	 p = strchr(string, ':');
	 *port = atoi(p + 1);
	 memcpy(str_tmp, string, p - string);
	 addr.s_addr = get_ip4(str_tmp);
	 if (addr.s_addr == 0) {
	 return -1;
	 }

	 char* ipstr = inet_ntoa(addr);
	 strcpy(ip, ipstr);
	 CH_MSGS_DEBUG("ip=%s,port=%d\n", ip, *port);*/

	return 0;
}

int InitInfoToServer() {

	return 0;
}

#ifdef CH_MSGS_VER_LINUX
void* server_thread_linux(void* arg) {
#endif
#ifdef CH_MSGS_VER_QCA4004
void server_thread() {
#endif

	int ret = 0;
	int recv_len = 0;
	int left_len = 0;
	char* recv_buf = NULL;

	int oldtime = 0;
	int newtime = 0;
	int disTime = 0;


	struct timeval tv;
	CH_MSGS_FD_SET fd_read;
	gServConnected = CONSTATE_CONNECT_ERROR;

	struct sockaddr_in serv_addr;

	recv_buf = (char*) CH_MSGS_MALLOC(RECV_SERV_BUF_SIZE);
	memset(recv_buf, 0, RECV_SERV_BUF_SIZE);

	start: recv_len = 0;
	left_len = 0;
	memset(recv_buf, 0, RECV_SERV_BUF_SIZE);

	gServSock = CH_MSGS_SOCKET(AF_INET, SOCK_STREAM, 0);
	if (gServSock < 0) {
		CH_MSGS_DEBUG("err:socket():%s:%d\n", __func__, __LINE__);
		CH_MSGS_SOCKET_CLOSE(gServSock);
		goto start;
	}

	set_socket_timeout(gServSock, 30);/*30s*/

	serv_addr.sin_family = AF_INET;
	get_ip_addr_from_string(gxmppServIP);

	CH_MSGS_DEBUG("addr_ip4:0x%08x  port:%d\n", addr_ip4, gxmppServPort);
	serv_addr.sin_addr.s_addr = htonl(addr_ip4); // inet_addr
	serv_addr.sin_port = htons(gxmppServPort);

	CH_MSGS_DEBUG("socket:%d %s:%d\n", gServSock, __func__, __LINE__);
	ret = CH_MSGS_CONNECT(gServSock, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr));
//	CH_MSGS_DEBUG("ret:%d\n", ret);

	connect_err_count++;
	if (ret < 0 && connect_err_count > 20) {

		CH_MSGS_DEBUG("Can't connect xmpp server !!!\r\n");
		goto end;

	}
	if (ret == -1) {
		gServConnected = CONSTATE_CONNECT_ERROR;
#ifdef CH_MSGS_VER_QCA4004
		qcom_thread_msleep(1 * 1000);
#endif

#ifdef CH_MSGS_VER_LINUX
		sleep(1);
#endif

		CH_MSGS_SOCKET_CLOSE(gServSock);
		goto start;
	} else if (ret == 0) {
		gServConnected = CONSTATE_CONNECT;

		gCH_MSGS_IConnection_t_CB(CONSTATE_CONNECT);
		connect_err_count = 0;
		//gServLiveTime = get_current_time();
	}

	FD_ZERO(&fd_read);
	FD_SET(gServSock, &fd_read);

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	oldtime = get_current_time();
	newtime = get_current_time();

	while (gIsInited == 1) {
		FD_SET(gServSock, &fd_read);

		/*the argument is a must, or select() will error*/
		tv.tv_sec = 10;
		tv.tv_usec = 0;

		ret = CH_MSGS_SELECT(gServSock + 1, &fd_read, NULL, NULL, &tv);
		if (ret < 0) {
			CH_MSGS_DEBUG("err: select() fail\n");

			continue;
		} else if (ret > 0) { /*something can be read*/

			if (FD_ISSET(gServSock, &fd_read)) {

				recv_len = CH_MSGS_RECV(gServSock, recv_buf + left_len,
						RECV_SERV_BUF_SIZE - left_len, 0);

				if (recv_len > 0) {
					//CH_MSGS_DEBUG("p=######leftLen:%d ::  %s  ######\n", left_len,
					//	recv_buf);
					CH_MSGS_DEBUG("\n recv_len:%d\n", recv_len);
					//gServLiveTime = get_current_time();
					left_len = handlexmpp(recv_buf, left_len + recv_len);

				}

				else if (recv_len == 0) { //link is off 连接关闭
					gServConnected = CONSTATE_DISCONNECT;
					CH_MSGS_DEBUG(
							"info: recv_len = 0 ,network is cut off:%s:%d\n",
							__func__, __LINE__);
//TODO
					//gCH_MSGS_IConnection_t_CB(CONSTATE_DISCONNECT);
				}

				else { //*recv_len<0  error.

//					if (errno == EINTR || errno == EWOULDBLOCK
//							|| errno == EAGAIN) {
//						CH_MSGS_DEBUG(
//								"info: recv() encounter with some problem:%s:%d\n",
//								__func__, __LINE__);
//					} else {
//						gServConnected = -1;
					CH_MSGS_DEBUG("info: network is cut off:%s:%d\n", __func__,
							__LINE__);

					gServConnected = CONSTATE_CONNECT_ERROR;
					//gCH_MSGS_IConnection_t_CB(2);
					//	gCH_MSGS_IConnection_t_CB(CONSTATE_CONNECT_ERROR);

//					}

				}
			}

		} else {/*select() time out*/
			CH_MSGS_DEBUG("select timeout...\n");
			//sendHeart();

		}

		newtime = get_current_time();

		if (newtime > oldtime) {

			disTime = newtime - oldtime;

		} else {
			disTime = oldtime - newtime;
		}

		if(disTime> 10*1000)
		{
			oldtime = newtime;
			sendHeart();
		}


		if (gServConnected != CONSTATE_CONNECT) {/*network is been cut off, try to connect again*/
			CH_MSGS_SOCKET_CLOSE(gServSock);
			//CH_MSGS_DEBUG("\nnetwork is been cut off,connect fail");
//#ifdef CH_MSGS_VER_QCA4004
//			qcom_thread_msleep(30 * 1000);
//#endif
//
//#ifdef CH_MSGS_VER_LINUX
//			sleep(30);
//#endif
			break;
//        goto start;
		}

	}

	end: if (recv_buf != NULL)
		CH_MSGS_FREE(recv_buf);
	CH_MSGS_SOCKET_CLOSE(gServSock);
	gIsInited = -1;

	gCH_MSGS_IConnection_t_CB(gServConnected);
	gServConnected = CONSTATE_DISCONNECT;
	gServSock = -1;
	CH_MSGS_DEBUG("info: server_thread exit\n");

#ifdef CH_MSGS_VER_LINUX
	return ((void*)0);
#endif

}

int init(char* userId, char* http_ip, int http_port) {
//	char* xmppPassWd = "@776#059";
	char* xmppPassWd = "6@#12591";
	strcpy(gxmppPassWd, xmppPassWd);
	strcpy(ghttpServIP, http_ip);
	ghttpServPort = http_port;
	strcpy(ghttpUserID, userId);

	int ret = getXmppAddr(userId, http_ip, http_port);
	if (ret < 0) {
		CH_MSGS_DEBUG("get xmppserver ip port error\n");
		return ret;
	}

#ifdef CH_MSGS_VER_QCA4004
	tx_byte_pool_create(&pool3, "xmpp recv", TX_POOL_CREATE_DYNAMIC,
			BYTE_POOL_SIZE_6K);
	{
		CHAR *pointer;
		tx_byte_allocate(&pool3, (VOID **) &pointer, PSEUDO_HOST_STACK_SIZE_6K,
				TX_NO_WAIT);
		tx_thread_create(&xmppRecvTid, "xmpp recv thread", server_thread, 0,
				pointer, PSEUDO_HOST_STACK_SIZE_6K, 16, 16, 4, TX_AUTO_START);
	}
#endif

#ifdef CH_MSGS_VER_LINUX

	if (pthread_create(&gServTid, NULL, server_thread_linux, 0) != 0) {
		CH_MSGS_DEBUG("err: xmpp_thread_start error! :%s:%d\n", __func__, __LINE__);
	} else {
		CH_MSGS_DEBUG("info:xmpp_thread_start success\n");
	}

#endif

	return ret;

}

int inet_pton(int af, const char *src, void *dst) {
	switch (af) {
	case AF_INET:
		return (inet_pton4(src, dst));
	default:
		return 0;
	}
	/* NOTREACHED */
} // end inet_pton

static int set_socket_timeout(int fd, int time) {
	int32_t ret = -1;
	struct timeval timeout;

	if (fd < 0 || time < 0) {
		return (-1);
	}

	timeout.tv_sec = time;
	timeout.tv_usec = 0;
#ifdef CH_MSGS_VER_QCA4004
	ret = qcom_setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
			sizeof(timeout));
#endif

#ifdef CH_MSGS_VER_LINUX
	int opt = 1;
	ret = setsockopt(gServSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
#endif
	if (ret < 0) {
		CH_MSGS_DEBUG("---%s---%d---", __FUNCTION__, __LINE__);
		CH_MSGS_SOCKET_CLOSE(fd);
		return (-1);
	}
	return 0;
}

//GHY
long get_current_time() {
#ifdef CH_MSGS_VER_LINUX
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec*1000;
#endif

#ifdef CH_MSGS_VER_QCA4004
	long mTime = time_ms();
	return mTime;
#endif

}

int inet_pton4(src, dst)
	const char *src;unsigned char *dst; {
	static const char digits[] = "0123456789";
	int saw_digit, octets, ch;
	unsigned char tmp[NS_INADDRSZ], *tp;

	saw_digit = 0;
	octets = 0;
	*(tp = tmp) = 0;
	while ((ch = *src++) != '\0') {
		const char *pch;

		if ((pch = strchr(digits, ch)) != NULL) {
			unsigned int new = *tp * 10 + (pch - digits);

			if (new > 255)
				return (0);
			*tp = new;
			if (!saw_digit) {
				if (++octets > 4)
					return (0);
				saw_digit = 1;
			}
		} else if (ch == '.' && saw_digit) {
			if (octets == 4)
				return (0);
			*++tp = 0;
			saw_digit = 0;
		} else
			return (0);
	}
	if (octets < 4)
		return (0);
	memcpy(dst, tmp, NS_INADDRSZ);
	return (1);
} // end inet_pton4

//addr_ip4

int get_ip_addr_from_string(const char *string) {

	struct in_addr addr;
	char str_tmp[256] = { 0 };

	memcpy(str_tmp, string, strlen(string));
	addr.s_addr = get_ip4(str_tmp);
	CH_MSGS_DEBUG("addr.s_addr =0x %08x\r\n", addr.s_addr);
	if (addr.s_addr == 0) {
		return -1;
	}

//	addr_ip4 = addr.s_addr;
	char i4 = addr.s_addr >> 24 & 0xFF;
	char i3 = addr.s_addr >> 16 & 0xFF;
	char i2 = addr.s_addr >> 8 & 0xFF;
	char i1 = addr.s_addr & 0xFF;
//  j = (i1<<24)|(i2<<16)|(i3<<8)|i4;

	addr_ip4 = (i1 << 24) | (i2 << 16) | (i3 << 8) | i4; //by lm

	return 0;
}

int sendHeart() {
	char* send_buf = "<p/>";
	int ret = -1;
	int bufLen = 0;
	bufLen = strlen(send_buf);

	if (gServSock != -1 && gServConnected == CONSTATE_CONNECT) {/*send the data*/

		//CH_MSGS_DEBUG("====== %s\n", send_buf);
		CH_MSGS_DEBUG("--sendHeart--\n");
		CH_MSGS_SEND(gServSock, send_buf, bufLen, 0);

		ret = 0;
	} else {

		ret = -1;
	}

	return ret;

}

int handlexmpp(char* xmpp, int xmpplen) {

	char* xmlheadptr = NULL;
	int DelLen = 0;
	int leftDataLen = 0;

	xmlheadptr = strstr(xmpp, "<?xml");

	if (xmlheadptr != NULL) {

		DelLen = dealXmppHead(xmlheadptr);
		memcpy(xmlheadptr, xmlheadptr + DelLen,
				xmpplen - DelLen - (xmlheadptr - xmpp));
		memset(xmlheadptr + xmpplen - DelLen - (xmlheadptr - xmpp), 0, DelLen);
		leftDataLen = xmpplen - DelLen;

	}

	DelLen = 0;
	char* regResponse = NULL;

	regResponse = strstr(xmpp, "<success xmlns=");
	if (regResponse != NULL) {
//deal success
		DelLen = dealsuccess(regResponse);

		memcpy(regResponse, regResponse + DelLen,
				xmpplen - DelLen - (regResponse - xmpp));
		memset(regResponse + xmpplen - DelLen - (regResponse - xmpp), 0,
				DelLen);
		leftDataLen = xmpplen - DelLen;

	}

	char* requestResponse = NULL;

	requestResponse = strstr(xmpp, "<iq");
	if (requestResponse != NULL) {
//deal success
		DelLen = dealrequestResponse(requestResponse);

		memcpy(requestResponse, requestResponse + DelLen,
				xmpplen - DelLen - (requestResponse - xmpp));
		memset(requestResponse + xmpplen - DelLen - (requestResponse - xmpp), 0,
				DelLen);
		leftDataLen = xmpplen - DelLen;
	}

	char* presencePtr = NULL;

	presencePtr = strstr(xmpp, "<presence");
	if (presencePtr != NULL) {
		//deal presence
		DelLen = dealpresence(presencePtr);

		memcpy(presencePtr, presencePtr + DelLen,
				xmpplen - DelLen - (presencePtr - xmpp));
		memset(presencePtr + xmpplen - DelLen - (presencePtr - xmpp), 0,
				DelLen);
		leftDataLen = xmpplen - DelLen;

	}

	char* messagePtrStart = NULL;
	char* messagePtrEnd = NULL;
	messagePtrStart = strstr(xmpp, "<message");
	messagePtrEnd = strstr(xmpp, "</message>");
	int tempLen = xmpplen;

	while ((messagePtrStart != NULL) && (messagePtrEnd != NULL)) {
		//deal message
		//CH_MSGS_DEBUG("xmpp:\n====== %s\n", xmpp);
		DelLen = dealmessage(messagePtrStart);
		//CH_MSGS_DEBUG("line   %d \n",__LINE__);
		memcpy(messagePtrStart, messagePtrStart + DelLen,
				xmpplen - DelLen - (messagePtrStart - xmpp));
		memset(messagePtrStart + xmpplen - DelLen - (messagePtrStart - xmpp), 0,
				DelLen);

		leftDataLen = tempLen - DelLen;
		tempLen = leftDataLen;
		//messagePtrStart = strstr(xmpp, "<message");
		messagePtrStart = NULL;
		messagePtrEnd = NULL;
		//	CH_MSGS_DEBUG("*********************** %s \n",xmpp);
		xmpp = xmpp + DelLen;
		messagePtrStart = strstr(xmpp, "<message");
		messagePtrEnd = strstr(xmpp, "</message>");

	}

	return leftDataLen;

}

