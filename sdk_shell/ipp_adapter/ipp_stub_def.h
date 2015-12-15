#ifndef _IPP_STUB_DEF_H_
#define _IPP_STUB_DEF_H_

#define QCOM4004

#ifdef LINUX
#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#endif

#if defined MARVELL
void alwz_print(char *content);//for test

#define malloc(size) os_mem_alloc(size)
#define calloc(size) os_mem_calloc(size)
//#define calloc(count,alsize) j_calloc(count,alsize)
#define realloc(oldpt,newsize)  os_mem_realloc(oldpt,newsize)

#define free(ptr) os_mem_free(ptr)
#define exit(state) os_exit_critical_section(state)

void alwz_print(char *content);//for test
void* j_calloc(size_t count,size_t alsize);
int vasprintf (char **ptr, const char *format, va_list ap);

#elif defined QCOM4004
#define ULONG_MAX 4294967295UL
#include <qcom/socket_api.h>
#include <qcom/qcom_mem.h>
#include <qcom/basetypes.h>
#include <qcom/socket.h>
#include <qcom_common.h>
#include <qcom/qcom_utils.h>

//#define malloc(size) qcom_mem_alloc(size)
//#define realloc(oldpt,newsize)  os_mem_realloc(oldpt,newsize)//
#define calloc(count,alsize) qcom_mem_calloc(count,alsize)

void *realloc(void* ptr, size_t size);
//void *malloc(size_t size);
#define malloc(size) qcom_mem_alloc(size)
#define free(ptr) qcom_mem_free(ptr)

//#define exit(state) os_exit_critical_section(state)

//define socket api
#define socket(_fm, _type, _proto) qcom_socket(_fm, _type, _proto)
#define bind(_s, _addr, _len) qcom_bind(_s, _addr, _len)
#define listen(_s, _bklog) qcom_listen(_s, _bklog)
#define accept(_s, _addr, _len) qcom_accept(_s, _addr, _len)
#define connect(_s, _addr, _len) qcom_connect(_s, _addr, _len)
#define send(_s, _buf, _len, _flag) qcom_send(_s, _buf, _len, _flag)
#define sendto(_s, _buf, _len, _flag, _to, _tolen) qcom_sendto(_s, _buf, _len, _flag, _to, _tolen)
#define free_buf(_buf) qcom_free_buf(_buf)
#define recv(_s, _buf, _len, _flag) qcom_recv(_s, _buf, _len, _flag)
#define recvfrom(_s, _buf, _len, _flag, _from, _fromlen) qcom_recvfrom(_s, _buf, _len, _flag, _from, _fromlen)
#define close(_s) qcom_socket_close(_s)
//network API

typedef A_UINT32 in_addr_t;
typedef struct 
  {
    in_addr_t s_addr;
  }in_addr;
A_UINT32 qcom_inet_addr(A_CHAR *str);
A_CHAR * qcom_inet_ntoa(A_UINT32 ip);
#define inet_addr(str) qcom_inet_addr(str)
#define inet_ntoa(ulong) qcom_inet_ntoa(ulong)

//string api
char* AJ_strcat(char* dest, const char* source);
char *qcom_strdup(const char *str);
int qcom_strncasecmp(const char * str1, const char * str2, int maxLen);
#define strcat(str1,str2) AJ_strcat(str1,str2)
#define strdup(str1) qcom_strdup(str1)
#define strncasecmp(str1,str2,len) qcom_strncasecmp(str1,str2,len)
//formrt print
int qcom_vsnprintf(char *buf,size_t size,const char *formet,va_list ap);
#define vsnprintf(buf,size,formet,val_list) qcom_vsnprintf(buf,size,formet,val_list)
int vasprintf (char **ptr, const char *format, va_list ap);
void exit(int n);

int qcom_atoi(char* strnum);
#define atoi(strnum) qcom_atoi(strnum)
#endif

#endif /* _IPP_STUB_DEF_H_ */
