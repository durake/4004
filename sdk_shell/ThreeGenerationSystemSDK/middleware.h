/*
 * middleware.h
 *
 *  Created on: Nov 3, 2015
 *      Author: ghy
 */

#include "ReceiveMessage.h"

#ifndef MIDDLEWARE_H_
#define MIDDLEWARE_H_


//// ------ SDK configure start
////#define CH_MSGS_VER_LINUX                                  1
//#define CH_MSGS_VER_QCA4004                                1
//


///////////////////////////////////////////////////////////////////////////////////////////////////////
// ------ linux ------
#ifdef CH_MSGS_VER_LINUX
// ------ print
#define CH_MSGS_DEBUG printf // printf

// ------ select
#define CH_MSGS_FD_SET fd_set // fd_set
#define CH_MSGS_SELECT select // select()

// ------ network
#define CH_MSGS_SOCKET socket // socket()
#define CH_MSGS_CONNECT connect // connect()
#define CH_MSGS_SEND send // send()
#define CH_MSGS_RECV recv // recv()
#define CH_MSGS_SOCKET_CLOSE close // close()

#define CH_MSGS_MALLOC malloc // close()
#define CH_MSGS_FREE free // close()CH_MSGS_FREE

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ------ qca4004 ------
#ifdef CH_MSGS_VER_QCA4004
// ------ print
#define CH_MSGS_DEBUG A_PRINTF // printf

// ------ select
#define CH_MSGS_FD_SET q_fd_set // fd_set
#define CH_MSGS_SELECT qcom_select // select()

// ------ network
#define CH_MSGS_SOCKET qcom_socket // socket()
#define CH_MSGS_CONNECT qcom_connect // connect()
#define CH_MSGS_SEND qcom_send // send()
#define CH_MSGS_RECV qcom_recv // recv()
#define CH_MSGS_SOCKET_CLOSE qcom_socket_close // close()
#define CH_MSGS_MALLOC mem_alloc // close()
#define CH_MSGS_FREE mem_free // CH_MSGS_FREE
#endif



//int CH_MSGS_Init(char* userid, char* httpip, int httpport,CH_MSGS_IReceiver_t_CB callbackFun);
int CH_MSGS_Init(char* userid, char* httpip, int httpport,CH_MSGS_IReceiver_t_CB callbackFun,CH_MSGS_IConnection_t_CB connectState_CB);
int CH_MSGS_Send(pCH_MSGS_Message pMsg, CH_MSGS_Result* pResult);



extern char ghttpServIP[64];
extern short ghttpServPort;

#endif /* MIDDLEWARE_H_ */
