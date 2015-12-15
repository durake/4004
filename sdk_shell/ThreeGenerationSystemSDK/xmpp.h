#ifndef XMPP_H_
#define XMPP_H_

// ------ SDK configure start
//#define CH_MSGS_VER_LINUX                                  1
#define CH_MSGS_VER_QCA4004                                1


#ifdef CH_MSGS_VER_LINUX

#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "datatype.h"


#endif

#ifdef CH_MSGS_VER_QCA4004

#include "base.h"
#include "stdint.h"
#include "qcom_system.h"
#include "qcom_utils.h"
#include "qcom_common.h"
#include "qcom_gpio.h"
#include "qcom_uart.h"
#include "qcom_mem.h"
#include "select_api.h"
#include "qcom_wlan.h"
#include "qcom_internal.h"
#include "socket_api.h"
#include "threadx/tx_thread.h"
#include "threadx/tx_api.h"
#include "qcom_misc.h"
#include "qcom_nvram.h"
#include "qcom_sec.h"
#include "middleware.h"

#endif






//#include "util.h"
//#include "xmpp.h" //ghy add 20151010

int inet_pton(int af, const char *src, void *dst);
int inet_pton4(const char *src, unsigned char *dst);
void connect_xmpp(char* strServXmpp, char* strUserName, char* strPassWord);
int handlexmpp(char* xmpp, int xmpplen);
int socket_send(const int s, const char *buf, const int len, const int flag);

/*
 * status:
 * 1 means connect complete
 * 0 means connect not complete
 *
 */
//int inform_connect_status(BOOL status);

int init(char* userId,char* http_ip,int http_port);
int dealXmppHead(char* xmppHeadP) ;
int dealsuccess(char* xmppHeadP);
int dealrequestResponse(char* iq);
int dealpresence(char* presence);
int dealmessage(char* messagePtr);
int getXmppAddr(char* userid, char* ip, int port);
static int set_socket_timeout(int fd, int time);
int set_socket_noblock(int fd);
long get_current_time();


//
//
//ConStatus
//
//1表示连接，2表示断开，3表示连接异常

//int gServConnected = 0;/*-1:error,0:disconnect,1:connect */

//#define CONSTATE_CONNECT 1
//#define CONSTATE_DISCONNECT 0
//#define CONSTATE_CONNECT_ERROR -1
#define CONSTATE_CONNECT 1
#define CONSTATE_DISCONNECT 2
#define CONSTATE_CONNECT_ERROR 3
#define CONSTATE_CONNECT_WIFI_ERROR 4

#define CH_MSGS_ERROR_CODE_OK                       0

#define CH_MSGS_ERROR_CODE_HTTP_SOCKET             -10001
#define CH_MSGS_ERROR_CODE_HTTP_IP             -10002
#define CH_MSGS_ERROR_CODE_HTTP_CONNECT          -10003
#define CH_MSGS_ERROR_CODE_HTTP_MALLOC          -10004
#define CH_MSGS_ERROR_CODE_HTTP_SNED          -10005


#define CH_MSGS_ERROR_CODE_MIDWARE_MSG_NULL          -20001
#define CH_MSGS_ERROR_CODE_MIDWARE_RCV_DATA         -20002
#define CH_MSGS_ERROR_CODE_MIDWARE_RCV_NULL        -20003
#define CH_MSGS_ERROR_CODE_MIDWARE_SERPAR        -20004
#define CH_MSGS_ERROR_CODE_MIDWARE_MALLOC          -20005
#define CH_MSGS_ERROR_CODE_MIDWARE_CONNECT_ERROR          -20006



//
//#define CH_MSGS_ERROR_CODE_NETWORK_CONNECT          -10003
//#define CH_MSGS_ERROR_CODE_NETWORK_SEND_SOCKET      -10003
//#define CH_MSGS_ERROR_CODE_NETWORK_SEND_DATA        -10004
//#define CH_MSGS_ERROR_CODE_NETWORK_SEND_SEND        -10005

#endif /* XMPP_H_ */
