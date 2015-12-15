#ifndef _ac_TCP_CLIENT_
#define _ac_TCP_CLIENT_
#include "ipp_stub_def.h"
#include "jdef.h"
#ifdef LINUX
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define BUFFER_SIZE 1024
typedef struct _ac_tcpclient{
	int socket;
	int remote_port;     
	char remote_ip[16];  
	struct sockaddr_in _addr; 
	int connected;       
} ac_tcpclient;

int ac_tcpclient_create(ac_tcpclient *,const char *host, int port);
int ac_tcpclient_create_t(ac_tcpclient *pclient,const char *host, int port);

int ac_tcpclient_conn(ac_tcpclient *);
int ac_tcpclient_recv(ac_tcpclient *,char **lpbuff,int size);
int ac_tcpclient_send(ac_tcpclient *,char *buff,int size);
int ac_tcpclient_close(ac_tcpclient *);
int ac_tcpclient_init();
int http_post(ac_tcpclient *pclient,char *page,char *request,char **response);
int http_get(ac_tcpclient *pclient,char *page,char *request,char **response);
#endif
