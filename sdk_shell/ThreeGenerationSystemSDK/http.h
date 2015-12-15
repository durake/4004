/*
 * http.h
 *
 *  Created on: Nov 3, 2015
 *      Author: ghy
 */

#ifndef HTTP_H_
#define HTTP_H_

extern char gxmppUserName[64] ;
extern char gxmppPassWd[64] ;
extern char gxmppServIP[64];
extern int  gxmppServPort;

extern char ghttpServIP[64] ;
extern short ghttpServPort ;
extern char ghttpUserID[20] ;

int creatConnect();
int httpSendMsg(char* request);
int recvHttpData(char*);





#endif /* HTTP_H_ */
