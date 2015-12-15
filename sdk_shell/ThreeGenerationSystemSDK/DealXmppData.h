#ifndef DEALXMPPDATA_H_
#define DEALXMPPDATA_H_

#include "xmpp.h"

extern int gServConnected;/*-1:error,0:disconnect,1:connect */
extern int gServSock;
extern int gIsInited;
extern int gStatus; //used for add and delete friends
extern int gDelStatus;

//ghy add
extern char gxmppUserName[64];
extern char  gxmppPassWd[64];

int dealmessage(char* messagePtr);
int dealpresence(char* presence);
int dealrequestResponse(char* iq);
int dealsuccess(char* xmppHeadP);
int dealXmppHead(char* xmppHeadP);

#endif

