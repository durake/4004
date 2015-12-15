
#include "tcp_client.h"

#ifdef LINUX
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
//#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#endif

#include <qcom/socket.h>
#include "ipp_stub_def.h"
#include "base.h"
#include "stdint.h"
#include "socket.h"
#include "socket_api.h"
#include "select_api.h"
#include "qcom_mem.h"
#include "qcom_common.h"
#include "qcom_internal.h"
#include "threadx/tx_thread.h"
#include "threadx/tx_api.h"
#include <qcom/socket.h>
#include <qcom/select_api.h>
#include "ipp_stub_def.h"
#include "xmpp.h"
#define 	NS_INADDRSZ     4
#define		RECV_SERV_BUF_SIZE	(1024*3)
static char gServXmppIP[32] = {0};
static short gServXmppPort = 0;
static uint32_t addr_ip4 = 0;
char * gServXmpp = "202.98.157.48:8080";
uint8_t online_flag = 0; //huangbin
uint8_t xmpp_run_flag = 0; //xmpp thread run
uint8_t xmpp_alive_flag = 0; //xmpp if alive
uint8_t heart_alive_flag = 0;//heart if alive
static uint8_t connect_err_count = 0;
int send_heart_count = 0;
int rcv_heart_count = 0;
uint8_t xmpp_sock_close_flag = 0;

int sock_back = -1;

/*static int inet_pton4(src, dst)
const char *src;
unsigned char *dst;
{
    static const char digits[] = "0123456789";
    int saw_digit, octets, ch;
    unsigned char tmp[NS_INADDRSZ], *tp;

    saw_digit = 0;
    octets = 0;
    *(tp = tmp) = 0;
    while ( (ch = *src++) != '\0' ) {
        const char *pch;

        if ( (pch = strchr(digits, ch)) != NULL )
        {
            unsigned int new = *tp * 10 + (pch - digits);

            if ( new > 255 )
                return(0);
            *tp = new;
            if ( ! saw_digit ) {
                if ( ++octets > 4 )
                    return(0);
                saw_digit = 1;
            }
        } else if ( ch == '.' && saw_digit ) {
            if ( octets == 4 )
                return(0);
            *++tp = 0;
            saw_digit = 0;
        } else
            return(0);
    }
    if ( octets < 4 )
        return(0);
    memcpy(dst, tmp, NS_INADDRSZ);
    return(1);
} // end inet_pton4
static int inet_pton(int af, const char *src, void *dst) {
    switch ( af ) {
        case AF_INET:
            return(inet_pton4(src, dst));
        default:
            return 0;
    }
    // NOTREACHED
} // end inet_pton*/

static unsigned int get_ip4(char *host)
{
		uint32_t ipAddress;
    struct sockaddr_in addr4;

    //bzero(&addr4, sizeof(struct sockaddr_in));
 		memset(&addr4,0,sizeof(struct sockaddr_in));
    if (1 == inet_pton(AF_INET, host, &(addr4.sin_addr)))
  	{
  		A_PRINTF("addr4.sin_addr.s_addr = %lu\r\n",addr4.sin_addr.s_addr);
      return (addr4.sin_addr.s_addr);
    }

		if (qcom_dnsc_get_host_by_name(host, &ipAddress) != A_OK)
    {A_PRINTF("ipAddress = 0\r\n");
       ipAddress = 0;
    }
    A_PRINTF("ipAddress = %u\r\n",ipAddress);
		return (ipAddress);
}




static int parse_ip_addr_from_string(const char *string, char *ip, short *port)
{
   char *p = NULL;
    struct in_addr addr;
    char str_tmp[256] = { 0 };

    if (string == NULL || ip == NULL)
        return -1;
    p = strchr(string, ':');
    *port = atoi(p + 1);
    memcpy(str_tmp, string, p - string);
    addr.s_addr = get_ip4(str_tmp);
		A_PRINTF("addr.s_addr = %ld\r\n", addr.s_addr);
    if (addr.s_addr == 0)
    {
        return -1;
    }
/*
    char *ipstr = inet_ntoa(addr);
    strcpy(ip, ipstr);
    A_PRINTF("ip=%s,port=%d\r\n", ip, *port);
*/
		char i4 = addr.s_addr >> 24 & 0xFF;
		char i3 = addr.s_addr >> 16 & 0xFF;
		char i2 = addr.s_addr >> 8 & 0xFF;
		char i1 = addr.s_addr & 0xFF;
//  j = (i1<<24)|(i2<<16)|(i3<<8)|i4;

		addr_ip4 = (i1<<24)|(i2<<16)|(i3<<8)|i4;//by lm
    return 0;

}


static int set_socket_timeout(int fd, int time)
{
    int32_t				ret = -1;
    struct timeval 		timeout;

    if(fd < 0 || time < 0)
    {
        return (-1);
    }

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = qcom_setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    if(ret < 0)
	  {
  			A_PRINTF("---%s---%d---",__FUNCTION__,__LINE__);
  			qcom_socket_close(fd);
				return (-1);
  	}
    return 0;
}
int test_connect(){
	//left_len = 0;
   //recv_len = 0;
  // memset(recv_buf, 0, RECV_SERV_BUF_SIZE);
	struct sockaddr_in serv_addr;

	 q_fd_set fd_read;
	 struct timeval tv;
	int gServConnected = 0;
 char *recv_buf = NULL;
int left_len = 0;
char * gServXmpp = "202.98.157.48:8080";




	while(1)
		{
		  	int ret = parse_ip_addr_from_string(gServXmpp, gServXmppIP, &gServXmppPort);
		  	if(ret == 0)
				  	break;
		  	A_PRINTF("err:parse_ip_addr_from_string:%s:%d\r\n", __func__, __LINE__);
				qcom_thread_msleep(1000);
		}

start:
   	A_PRINTF("xmpp start\r\n");
   	int gServSock = qcom_socket(AF_INET, SOCK_STREAM, 0);
		A_PRINTF("gServSock = %d\r\n",gServSock);
   	if (gServSock < 0)
   	{
   		A_PRINTF("gServSock 1875 err:socket()\r\n");
   		qcom_socket_close(gServSock);
     	goto start;
   	}
   	A_PRINTF("gServSock end \r\n");

   	//set_socket_timeout(gServSock, 30);/*30s*/
//    set_socket_noblock(gServSock);/*set the socket to no-block type*/
//    A_PRINTF("%s:%d\r\n", __func__, __LINE__);
   	serv_addr.sin_family = AF_INET;
  // A_PRINTF("111%lu\r\n",addr_ip4);
   serv_addr.sin_addr.s_addr = htonl(addr_ip4);//_inet_addr(gServXmppIP);//htonl(address);//0x2be37b76;
   	//serv_addr.sin_addr.s_addr = inet_addr(g_host);
   	A_PRINTF("%s        22222\r\n",gServXmppIP);
   	serv_addr.sin_port = htons(gServXmppPort);
   	A_PRINTF("3333333333333333\r\n");
   	int ret = qcom_connect(gServSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
   	A_PRINTF("4444444444444444\r\n");
   	connect_err_count ++;
		if (ret < 0 && connect_err_count > 20)
		{
				A_PRINTF("Can't connect xmpp server !!!\r\n");
				//save_dct_config();//duizhe
				goto end;

		}
   	if (ret == -1 )
   	{
      	 gServConnected = -1;
       //wiced_rtos_delay_milliseconds(1000);
				qcom_thread_msleep(1000);
				A_PRINTF("qcom_connect back -1 !!!\r\n");
				qcom_socket_close(gServSock);
      	 goto start;
  	 }
   	else if (ret == 0)
   	{
   		A_PRINTF("\r\n  connect xmpp server!!!\r\n");
   		connect_err_count = 0;
   		gServConnected = 1;
		return 0;
       //gServLiveTime = get_current_time();
   	}
//    A_PRINTF("%s:%d\r\n", __func__, __LINE__);

//   if (InitInfoToServer() == 0)
//   {
//   	A_PRINTF("InitInfoToServer():%s:%d\r\n", __func__, __LINE__);
//   }
//    A_PRINTF("%s:%d\r\n", __func__, __LINE__);

  	 FD_ZERO(&fd_read);
   	FD_SET(gServSock, &fd_read);
  	 tv.tv_sec = 10;
   	tv.tv_usec = 0;

  	 while ( 1)
   	{
       		FD_SET(gServSock, &fd_read);/*the argument is a must, or select() will error*/
       		xmpp_alive_flag = 1;
      	 	tv.tv_sec = 10;
       		tv.tv_usec = 0;
/*
				if (xmpp_heart_send_flag == 1){
		     		send_heartbeat();
		     		xmpp_heart_send_flag = 0;
				}
*/
  			if (send_heart_count > (rcv_heart_count + 5))
  			{
          	A_PRINTF("heart send but no receive in 150s,reboot and save_dct!!!\r\n");
          	//save_dct_config();
          	//Save_NVM_flag = 1;
          	//Reboot_flag = 1;
  			}

       ret = qcom_select(gServSock + 1, &fd_read, NULL, NULL, &tv);
       if(xmpp_sock_close_flag == 1){
  				xmpp_sock_close_flag = 0;
  				goto restarxmpp;
  			}
       if (ret == -1)
       {
       		A_PRINTF("err: select() fail\r\n");
           //perror("select");
           continue;
       }
       else if (ret > 0)    /*something can be read*/
       {
           if (FD_ISSET(gServSock, &fd_read))
           {
           		//wiced_rtos_lock_mutex(&gServLock);
        				//mutex_status = tx_mutex_get(&gServLock, TX_WAIT_FOREVER);
			  				//if (mutex_status != TX_SUCCESS) {
			    					//A_PRINTF("lock the gServLock mutex failed !!!\n");
			  				//}
//            	A_PRINTF("%s %d   \r\n", __func__, __LINE__);

           		int recv_len = qcom_recv(gServSock, recv_buf + left_len,
                               RECV_SERV_BUF_SIZE - left_len, 0);
               //wiced_rtos_unlock_mutex(&gServLock);
             //  mutex_status = tx_mutex_put(&gServLock);
			  				//if (mutex_status != TX_SUCCESS) {
   								//A_PRINTF("unlock the gServLock mutex failed !!!\n");
 							//}

               if (recv_len > 0)
               {
               	A_PRINTF("server packet p=######  %s  ######\r\n", recv_buf);
                  // gServLiveTime = get_current_time();
                 //  left_len = handlexmpp(recv_buf, recv_len + left_len);
//                    A_PRINTF("%s %d left_len %d \r\n", __func__, __LINE__, left_len);

//                   if(left_len == 0)
//                   {
//                       memset(recv_buf, 0, RECV_SERV_BUF_SIZE);
//                   }
               }
               else if (recv_len == 0)    /*network disconnect*/
               {
                   gServConnected = -1;
                   A_PRINTF("info: recv_len = 0 ,network is cut off:%s:%d\r\n", __func__,__LINE__);
               }
               else    /*recv_len<0*/
               {
               		/*
                   if (errno == EINTR || errno == EWOULDBLOCK
                           || errno == EAGAIN)
                   {
                   	A_PRINTF("info: recv() encounter with some problem:%s:%d\r\n",__func__, __LINE__);
                   }
                   else
                   {
                   		online_flag = -1;
                       gServConnected = -1;
                       A_PRINTF("info: network is cut off:%s:%d\r\n", __func__,__LINE__);
                   }*/
                		online_flag = -1;
                   gServConnected = -1;
                   A_PRINTF("info: network is cut off:%s:%d\r\n", __func__,__LINE__);
               }
           }
       }
       else    /*select() time out*/
       {
           //	A_PRINTF("select timeout...\r\n");
       }
       if (gServConnected == -1)  /*network is been cut off, try to connect again*/
       {
restarxmpp:
       		A_PRINTF("qcom_connect close gServConnected==-1 !!!\r\n");
           qcom_socket_close(gServSock);
           A_PRINTF("network is been cut off,connect fail,xmpp thread start again!!\r\n");
           send_heart_count = 3;
						rcv_heart_count = 3;
						online_flag = -1;
           //wiced_rtos_delay_milliseconds(5000);/*wait for 5s because of the Server*/
						qcom_thread_msleep(5000);
           connect_err_count=0;
           goto start;
       }
   }
end:
   if (recv_buf != NULL)
   mem_free(recv_buf);
   A_PRINTF("qcom_connect close at end!!!\r\n");
   qcom_socket_close(gServSock);
   gServConnected = 0;
   online_flag = 0;
   gServSock = -1;
//    A_PRINTF("info: server_thread exit\r\n");
}

int ac_tcpclient_select(int sock){
         q_fd_set fd_write;
	 struct timeval tv;

	 FD_ZERO(&fd_write);
   	 FD_SET(sock, &fd_write);
  	 tv.tv_sec = 10;
   	 tv.tv_usec = 0;

 	while ( 1){
       	    FD_SET(sock, &fd_write);/*the argument is a must, or select() will error*/
            xmpp_alive_flag = 1;
      	    tv.tv_sec = 10;
       	    tv.tv_usec = 0;
		//int _qcom_select(int max, q_fd_set * in, q_fd_set * out, q_fd_set * ev, struct timeval *timeout);
		int ret = qcom_select(sock + 1, NULL, &fd_write, NULL, &tv);

			if (ret == -1)
	      		 {
	       		 printf("err: select() fail\r\n");
		  	 continue;
	       		 }
		  	else if (ret > 0)    /*something can be read*/
	      		 {
		   		if (FD_ISSET(sock, &fd_write))
		  		 {
		   		
					printf("ok to write\r\n");
					return 0;
		   		
		   		 }
	      	        }
	       		else    /*select() time out*/
	       		{
		  		printf("select timeout...\r\n");
				return -1;
	       		}	

		}


	}
//域名修改
/*
int ac_tcpclient_create_t(ac_tcpclient *pclient,const char *host, int port){

	struct hostent *hp;
	struct in_addr in;
	struct sockaddr_in local_addr;
	if(!(hp = gethostbyname(host)))
	{
		printf(("gethostbyname error\r\n"));
		return -1;
	}
	//printf("%s\n",hp->h_name);
	//printf("%s\n",*(hp->h_aliases));

	memcpy(&local_addr.sin_addr.s_addr,hp->h_addr,4);
	in.s_addr = local_addr.sin_addr.s_addr;

	if(pclient == NULL) return -1;
	memset(pclient,0,sizeof(ac_tcpclient));

	pclient->remote_port = port;

	strncpy(pclient->remote_ip,inet_ntoa(in),sizeof(pclient->remote_ip) - 1);

	pclient->_addr.sin_family = AF_INET;
	pclient->_addr.sin_port = htons(port);
	pclient->_addr.sin_addr.s_addr = inet_addr(pclient->remote_ip);
	//固定服务器ip地址
//	pclient->_addr.sin_addr.s_addr = inet_addr(host);

	if((pclient->socket = socket(AF_INET,SOCK_STREAM,0) )== -1){
		return -3;
	}
	return 0;
}
*/
//modified by jiao 9/27

int ac_tcpclient_create(ac_tcpclient *pclient,const char *host, int port){

	struct in_addr in;
	
	while(1)
		{
		  	int ret = parse_ip_addr_from_string(gServXmpp, gServXmppIP, &gServXmppPort);
		  	if(ret == 0)
				  	break;
		  	A_PRINTF("err:parse_ip_addr_from_string:%s:%d\r\n", __func__, __LINE__);
				qcom_thread_msleep(1000);
		}


	in.s_addr = inet_addr((char*)host);
	//in.s_addr = local_addr.sin_addr.s_addr;

	if(pclient == NULL) return -1;
	memset(pclient,0,sizeof(ac_tcpclient));

	pclient->remote_port = port;

	strncpy(pclient->remote_ip,inet_ntoa(in.s_addr),sizeof(pclient->remote_ip) - 1);

	pclient->_addr.sin_family = AF_INET;
	pclient->_addr.sin_port = htons(gServXmppPort);
	pclient->_addr.sin_addr.s_addr = htonl(addr_ip4);//inet_addr(pclient->remote_ip);
	//固定服务器ip地址
//	pclient->_addr.sin_addr.s_addr = inet_addr(host);

	if((pclient->socket = socket(AF_INET,SOCK_STREAM,0) )== -1){

		return -3;
	}
	sock_back = pclient->socket;

	set_socket_timeout(pclient->socket, 30);/*30s*/
	return 0;
}


int ac_tcpclient_conn(ac_tcpclient *pclient){
	if(pclient->connected)
		return 1;

	int retry = 0;
	int ret ;
	do{	

		ret = connect(pclient->socket, (struct sockaddr *)&(pclient->_addr),sizeof(struct sockaddr_in));
		printf("socket : %d,addr: %s,port: %d connect : %d\r\n",pclient->socket,inet_ntoa(pclient->_addr.sin_addr.s_addr),ntohs(pclient->_addr.sin_port),ret);
		retry++;
	}while((ret != 0) && (retry < 3));
	if(ret < 0)
	{	
		printf("connect failed\r\n");
		return -1;
	}
	pclient->connected = 1;
	return 0;
}

int ac_tcpclient_recv(ac_tcpclient *pclient,char **lpbuff,int size){
	int recvnum = 0,tmpres = 0;
	char buff[BUFFER_SIZE];
	memset(buff,0,BUFFER_SIZE);
	*lpbuff = NULL;

	while(recvnum < size || size == 0){
		tmpres = recv(sock_back, buff,BUFFER_SIZE,0);
		if(tmpres <= 0)
			break;
		recvnum += tmpres;

		if(*lpbuff == NULL)
		{
			*lpbuff = (char*)malloc(recvnum);
			if(*lpbuff == NULL)
				return -2;
		}
		else
		{
			*lpbuff = (char*)realloc(*lpbuff,recvnum);
			if(*lpbuff == NULL)
				return -2;
		}
		memcpy(*lpbuff+recvnum-tmpres,buff,tmpres);
	}
	printf("%d bytes recv success\n",recvnum);
	
	return recvnum;
}

int ac_tcpclient_send(ac_tcpclient *pclient,char *buff,int size){
	int sent=0,tmpres=0;

	int ii = 0;
	printf("send:\n");
	for(;ii<size;ii++)
	{	
		printf("%c",buff[ii]);
	}

	while(sent < size){

		tmpres = send(sock_back,buff+sent,size-sent,0);

		printf("tmres:%d\r\n",tmpres);
		if(tmpres == -1)
		{
			return -1;
		}
		sent += tmpres;
	}
	return sent;
}

int ac_tcpclient_close(ac_tcpclient *pclient){
	close(pclient->socket);
	pclient->connected = 0;
	return 0;
}

/*****************************************************************************
 函 数 名  : http_request
 功能描述  : http请求
 输入参数  : ac_tcpclient *pclient
             char *lpbuf            
             int len                
             char **response      访问成功会分配内存，使用者需要释放
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 
 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : 陈梁 20167633
    修改内容   : 新生成函数
*****************************************************************************/
int http_request(ac_tcpclient *pclient,char *lpbuf, int len, char **response) 
{
	char *ptmp = NULL;
	char post[300];
	char *recvbuf = NULL;
	if(!pclient->connected){
		//if(ac_tcpclient_conn(pclient))
		if(ac_tcpclient_conn(pclient))
		{
			//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
			return -1;
		}
	}
	printf("ac_tcpclient_conn success\n");
	if( ac_tcpclient_select(pclient->socket))
	{
		printf("select time out or failed\r\n");
		return -1;
	}

	if(ac_tcpclient_send(pclient,lpbuf,len)<0){
		//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
		return -1;
	}
	printf("%s\n",lpbuf);

	if(ac_tcpclient_recv(pclient,&recvbuf,0) <= 0){
		//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
		free(recvbuf);
		return -1;
	}

	int ii = 0;
	printf("recv:\n");
	for(;ii<553;ii++)
	{	
		printf("%c",*(recvbuf+ii));
	}

	//printf("Recieve Response:\n%s\n",recvbuf);

	/*响应代码,|HTTP/1.0 200 OK|
	*从第10个字符开始,三个字节
	* */
	memset(post,0,sizeof(post));
	strncpy(post,recvbuf + 9,3);
	if(atoi(post)!= 200){
		//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
		free(recvbuf);
		return atoi(post);
	}
	printf("code ok\r\n");
#ifdef IPP2
	ptmp = (char*)strstr(recvbuf,"\r\n\r\n");
	if(ptmp == NULL){
		//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
		free(recvbuf);
		return -3;
	}
	printf("response ok\r\n");
	ptmp += 4;/*跳过\r\n*/

	len = strlen(ptmp)+1;
	*response=(char*)malloc(len);
	if(*response == NULL){
	printf("malloc err\r\n");
		free(recvbuf);
		return -1;
	}
	memset(*response,0,len);
	memcpy(*response,ptmp,len-1);

	/*从头域找到内容长度,如果没有找到则不处理*/
	ptmp = (char*)strstr(recvbuf,"Content-Length:");
	if(ptmp != NULL){
		char *ptmp2;
		ptmp += 15;
		ptmp2 = (char*)strstr(ptmp,"\r\n");
/*
		int i = 0;
		while(!(*(ptmp + i)))
{

		printf("%c",*(ptmp + i));

}		
printf("\r\n");
 i = 0;
		while(!(*(ptmp2 + i)))
{

		printf("%c",*(ptmp2 + i));

}		
printf("\r\n");
*/
		if(ptmp2 != NULL){
			memset(post,0,sizeof(post));
			strncpy(post,ptmp,ptmp2 - ptmp);
			if(atoi(post)<len)
				(*response)[atoi(post)] = '\0';
		}
	}
#else
	ptmp = strstr(recvbuf,"7D7D7D7D7D7D7D7D");
	char *ptmp2 = strstr(ptmp,"\r\n");
	size_t contentlen = ptmp2 - ptmp;
	*response=(char*)malloc(contentlen + 1);
	if(*response != NULL){
		memset(*response,0,contentlen);
		memcpy(*response,ptmp,contentlen );
		*((*response) + contentlen ) = '\0';
	}else{
		free(recvbuf);
		return  -1;
	}
#endif
	free(recvbuf);
	return 0;
}

/*****************************************************************************
 函 数 名  : http_request_post_buf
 功能描述  : 生成POST请求缓存
 输入参数  : char **lpbuf           成功会分配内存，需要使用者释放
             ac_tcpclient *pclient  
             char *page             访问页面
             char *request          请求内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 
 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : 陈梁 20167633
    修改内容   : 新生成函数
*****************************************************************************/
int http_request_post_buf(char **lpbuf, ac_tcpclient *pclient,char *page,char *request)
{
	int len = 0;
	char post[300];
	char host[100];
	//char connect[100];
	char content_len[100];

	int num = sprintf(post,"POST %s HTTP/1.1\r\n",page);
	post[num] = '\0';
	printf("%d\n",num); 
		printf("post : %d,%s\n",strlen(post),post);

	 num = sprintf(host,"HOST: %s:%d\r\n",pclient->remote_ip,pclient->remote_port);
	host[num] = '\0';
	printf("%d\n",num);
		printf("host : %d,%s\n",strlen(host),host);

	const char *accept = "Accept: */*\r\n";
		printf("accept : %d\n",strlen(accept));

	 num = sprintf(content_len,"Content-Length: %d\r\n",strlen(request));
	content_len[num] = '\0';
	printf("%d\n",num);
		printf("content_len : %d,%s\n",strlen(content_len),content_len);

	const char *header2="Content-Type: application/x-www-form-urlencoded\r\n\r\n";
		printf("header2 len : %d\n",strlen(header2));
	//sprintf(connect,"Connection: keep-alive\r\n\r\n");

		
	len = strlen(post) + strlen(host) + strlen(header2) + strlen(content_len) + strlen(request)+strlen(accept)+1;
	*lpbuf = (char*)malloc(len);
	if(*lpbuf == NULL){
		//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
		return -1;
	}
	memset(*lpbuf,0,len);
	printf("%s\n",*lpbuf);
  	strcpy(*lpbuf,post);
	printf("%s\n",*lpbuf);
	strcat(*lpbuf,host);
	printf("%s\n",*lpbuf);
	strcat(*lpbuf,accept);
	printf("%s\n",*lpbuf);
	strcat(*lpbuf,content_len);
	printf("%s\n",*lpbuf);
	strcat(*lpbuf,header2);
	printf("%s\n",*lpbuf);
	//strcat(*lpbuf,connect);
	strcat(*lpbuf,request);
	printf("%s\n",*lpbuf);


	return len;
}

/*****************************************************************************
 函 数 名  : http_post
 功能描述  : POST请求
 输入参数  : ac_tcpclient *pclient
             char *page             
             char *request          
             char **response        成功会分配内存，需要使用者释放
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 
 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : 陈梁 20167633
    修改内容   : 新生成函数
*****************************************************************************/
int http_post(ac_tcpclient *pclient,char *page,char *request,char **response)
{
	char *lpbuf = NULL;
	int ret = http_request_post_buf(&lpbuf, pclient, page, request);
	printf("retlen:%d\r\n",ret);
 	ret = (ret > 0) ? http_request(pclient, lpbuf, ret, response) : ret;
	printf("ret:%d\n",ret);
	free(lpbuf);
	return ret;
}

/*****************************************************************************
 函 数 名  : http_request_get_buf
 功能描述  : 生成GET请求内容
 输入参数  : char **lpbuf           成功会分配内存，需要使用者释放
             ac_tcpclient *pclient  
             char *page             
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 
 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : 陈梁 20167633
    修改内容   : 新生成函数
*****************************************************************************/
int http_request_get_buf(char **lpbuf, ac_tcpclient *pclient,char *page)
{
	char get[300];
	char host[100];
	char connet[100];
	int len = 0;

	sprintf(get,"GET %s HTTP/1.1\r\n",page);
	sprintf(host,"Host: %s:%d\r\n",pclient->remote_ip,pclient->remote_port);
	sprintf(connet,"Connection: Close\r\n\r\n");

	len = strlen(get) + strlen(host) + strlen(connet) + 1;
	*lpbuf = (char*)malloc(len);
	if(*lpbuf == NULL){
		//printf(("function = %s,line= %d\r\n",__FUNCTION__,__LINE__));
		return -1;
	}
	memset(*lpbuf,0,len);

	strcpy(*lpbuf,get);
	strcat(*lpbuf,host);
	strcat(*lpbuf,connet);

	return len;
}

/*****************************************************************************
 函 数 名  : http_get
 功能描述  : GET请求
 输入参数  : ac_tcpclient *pclient
             char *page             
             char *request          
             char **response        成功会分配内存，需要使用者释放
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 
 修改历史      :
  1.日    期   : 2015年1月14日
    作    者   : 陈梁 20167633
    修改内容   : 新生成函数
*****************************************************************************/
int http_get(ac_tcpclient *pclient,char *page,char *request,char **response)
{
	(void)request;
	char *lpbuf = NULL;
	int ret = http_request_get_buf(&lpbuf, pclient, page);
	ret = (ret > 0) ? http_request(pclient, lpbuf, ret, response) : ret;
	free(lpbuf);
	return ret;
}

