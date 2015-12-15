/*
 * ipp_stub_def.h.c
 *
 *  Created on: 2015��8��19��
 *      Author: jiao
 */
#include "ipp_stub_def.h"

#if defined MARVELL
#include <wm_os.h>
#include <wmstdio.h>
#include <stdio.h>

void alwz_print(char *content){
	while(1){
	wmprintf("content:%s\r\n",content);
	os_thread_sleep(os_msec_to_ticks(4000));
	}
}

void* j_calloc(size_t count,size_t alsize){
	return os_mem_calloc(count*alsize);
}

int vasprintf (char **ptr, const char *format, va_list ap)
{
  va_list ap_copy;

  /* Make sure it is determinate, despite manuals indicating otherwise */
  *ptr = 0;

  va_copy(ap_copy, ap);
  int count = vsnprintf(NULL, 0, format, ap);
  if (count >= 0)
        {
          char* buffer = (char*)malloc(count + 1);
          if (buffer != NULL)
                {
                  count = vsnprintf(buffer, count + 1, format, ap_copy);
                  if (count < 0)
                        free(buffer);
                  else
                        *ptr = buffer;
                }
        }
  va_end(ap_copy);

  return count;

}

#elif defined QCOM4004

#include "qcom/qcom_ssl.h"
#include "qcom/qcom_scan.h"
#include "qcom/qcom_gpio.h"

extern A_INT32 isdigit(A_INT32 c);

A_INT32 qcom_inet_aton(const char *name,
          /* [IN] dotted decimal IP address */
          in_addr *ipaddr_ptr
          /* [OUT] binary IP address */
    )
{                               /* Body */

    A_INT8 ipok = FALSE;

    A_UINT32 dots;

    A_UINT32 byte;

    A_UINT32 addr;

    addr = 0;

    dots = 0;

    for (;;) {

        if (!isdigit(*name))
            break;

        byte = 0;

        while (isdigit(*name)) {

            byte *= 10;

            byte += *name - '0';

            if (byte > 255)
                break;

            name++;

        }                       /* Endwhile */

        if (byte > 255)
            break;

        addr <<= 8;

        addr += byte;

        if (*name == '.') {

            dots++;

            if (dots > 3)
                break;

            name++;

            continue;

        }



      if ((*name == '\0') && (dots == 3)) {

         ipok = TRUE;

      } /* Endif */



      break;



   } /* Endfor */



   if (!ipok) {

      return 0;

   } /* Endif */



   if (ipaddr_ptr) {

	ipaddr_ptr->s_addr = addr;

   } /* Endif */



    return -1;

}                               /* Endbody */
//this founction has problems 
//it only works for string-type pointer 
//
void *realloc(void* ptr, size_t size){
	if(!ptr){	
	  return malloc(size);
	}

	void *new_ptr;
	new_ptr = malloc(size);
	if(!new_ptr){
		return NULL;
	}
	memcpy(new_ptr,ptr,strlen(ptr));
	free(ptr);
	return new_ptr;
	
}

char *qcom_strdup_t(const char *str){
	int len = strlen(str) + 1;
	char* new_str = (char*)malloc(len);
        if(!new_str){
	   printf("malloc error 'jdef.c':ln180\r\n");
	   return  NULL;
	}
 	memcpy(new_str,str,len-1);
		*(new_str+len-1) = '\0';
	return new_str;
}

char * qcom_strdup(const char *s){
   size_t  len = strlen(s) +1;
   void *new = malloc(len);
   if (new == NULL){
	printf("strdup mem error\r\n");
      	return NULL;
	}
   return (char *)memcpy(new,s,len);
}
/*
//define the malloc warpped by calloc 
void *malloc(size_t size){
	void *new = calloc(1,size);
	if(!new)
	   return NULL;
	return new;
}
*/

int qcom_vsnprintf(char *buf,size_t size,const char *formet,va_list ap)
{
	return snprintf(buf,size,formet,ap);

}

int vasprintf (char **ptr, const char *format, va_list ap)
{
  va_list ap_copy;


  *ptr = 0;

  va_copy(ap_copy, ap);
  int count = qcom_vsnprintf(NULL, 0, format, ap);
  if (count >= 0)
        {
          char* buffer = (char*)malloc(count + 1);
          if (buffer != NULL)
                {
                  count = qcom_vsnprintf(buffer, count + 1, format, ap_copy);
                  if (count < 0)
                        free(buffer);
                  else
                        *ptr = buffer;
                }
        }
  va_end(ap_copy);

  return count;

}

char* AJ_strcat(char* dest, const char* source)
{
    char* tail = dest;
    while(*tail) {
        tail++;
    }

    strcpy(tail, source);
    return dest;
}

int absolute(int charA, int charB){
	int re = charA - charB;
	if(re < 0)
		return -re;
	return re;
}

int qcom_strncasecmp(const char * str1, const char * str2, int maxLen)
{
    if(!maxLen)
        return 0;
 
    while(--maxLen && *str1 && ((*str1 == *str2)||(absolute(*str1, *str2)) == 32))
    {
        str1++;
        str2++;
    }
 
    return *str1-*str2;
}

A_UINT32 qcom_inet_addr(A_CHAR *str)
{
    A_UINT32 ipaddr;
    A_UINT32 data[4];
    A_UINT32 ret;

    ret = A_SSCANF(str, "%3d.%3d.%3d.%3d", data, data + 1, data + 2, data + 3);
    if (ret < 0) {
        return 0;
    } else {
        ipaddr = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
    }
    return ipaddr;
}

A_CHAR * qcom_inet_ntoa(A_UINT32 ip)
{
    static char str[20];
    memset(str, 0, sizeof (str));
    qcom_sprintf(str, "%u.%u.%u.%u",
            (unsigned) (ip >> 24),
            (unsigned) ((ip >> 16) & 0xff), (unsigned) ((ip >> 8) & 0xff), (unsigned) (ip & 0xff));
    return str;
}

int qcom_index(int num){
	int tal = 1;
	int i = 0;
	for(;i<num;i++){
	tal *=10; 	
	}
	return tal;	
}
	
int qcom_atoi(char* strnum)
{
	int len = strlen(strnum);
	int i = len;
	int num = 0;
	for(;i > 0; i--){
		num += (*(strnum+(len - i)) - '0') * qcom_index(i-1);
			
	}
	return num;

}


#endif


