#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
/*
#include "base.h"
#include "socket_api.h"
#include "select_api.h"
#include "qcom_mem.h"
#include "qcom_common.h"
#include "qcom_internal.h"
#include "threadx/tx_thread.h"
#include "threadx/tx_api.h"
*/
#include "xmpp.h"
#include <string.h>
#include "middleware.h"


const char base[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
char* base64_encode(const char* data, int data_len);
char *base64_decode(const char* data, int data_len);
static char find_pos(char ch);

char ret[256] = {0};

/* */
char *base64_encode(const char* data, int data_len) {
	//int data_len = strlen(data);
	CH_MSGS_DEBUG("%d enc:%s \n", __LINE__,__func__);
	int prepare = 0;
	int ret_len;
	int temp = 0;
	//CH_MSGS_DEBUG("%d enc:%s \n", __LINE__,__func__);
	memset(ret,0,256);
//	char ret[256] = {0};
	//CH_MSGS_DEBUG("%d enc:%s \n", __LINE__,__func__);
	char *f = NULL;
	int tmp = 0;
	char changed[4];
	int i = 0;
	ret_len = data_len / 3;
	temp = data_len % 3;
	if (temp > 0) {
		ret_len += 1;
	}
	ret_len = ret_len * 4 + 1;
	//CH_MSGS_DEBUG("%d enc:%s \n", __LINE__,__func__);
	//memset(ret, 0, 128);
	f = ret;
	while (tmp < data_len) {
		temp = 0;
		prepare = 0;
		memset(changed, '\0', 4);
		while (temp < 3) {
			//CH_MSGS_DEBUG("tmp = %d\n", tmp);
			if (tmp >= data_len) {
				break;
			}
			prepare = ((prepare << 8) | (data[tmp] & 0xFF));
			tmp++;
			temp++;
		}
		prepare = (prepare << ((3 - temp) * 8));
		//CH_MSGS_DEBUG("before for : temp = %d, prepare = %d\n", temp, prepare);
		for (i = 0; i < 4; i++) {
			if (temp < i) {
				changed[i] = 0x40;
			} else {
				changed[i] = (prepare >> ((3 - i) * 6)) & 0x3F;
			}
			*f = base[changed[i]];
			//CH_MSGS_DEBUG("%.2X", changed[i]);
			f++;
		}
	}
	*f = '\0';
CH_MSGS_DEBUG("%d %s ret:%s \n", __LINE__,__func__,ret);
	return ret;

}
/* */
static char find_pos(char ch) {
	char *ptr = (char*) strrchr(base, ch); //the last position (the only) in base[]
	return (ptr - base);
}
/* */
char *base64_decode(const char *data, int data_len) {
	int ret_len = (data_len / 4) * 3;
	int equal_count = 0;
	char *ret = NULL;
	char *f = NULL;
	int tmp = 0;
	int temp = 0;
	char need[3];
	int prepare = 0;
	int i = 0;
	if (*(data + data_len - 1) == '=') {
		equal_count += 1;
	}
	if (*(data + data_len - 2) == '=') {
		equal_count += 1;
	}
	if (*(data + data_len - 3) == '=') { //seems impossible
		equal_count += 1;
	}
	switch (equal_count) {
	case 0:
		ret_len += 4; //3 + 1 [1 for NULL]
		break;
	case 1:
		ret_len += 4; //Ceil((6*3)/8)+1
		break;
	case 2:
		ret_len += 3; //Ceil((6*2)/8)+1
		break;
	case 3:
		ret_len += 2; //Ceil((6*1)/8)+1
		break;
	}
	ret = (char *) CH_MSGS_MALLOC(ret_len);
	if (ret == NULL) {
		CH_MSGS_DEBUG("No enough memory.\n");
		//exit(0);
		return NULL;
	}
	memset(ret, 0, ret_len);
	f = ret;
	while (tmp < (data_len - equal_count)) {
		temp = 0;
		prepare = 0;
		memset(need, 0, 4);
		while (temp < 4) {
			if (tmp >= (data_len - equal_count)) {
				break;
			}
			prepare = (prepare << 6) | (find_pos(data[tmp]));
			temp++;
			tmp++;
		}
		prepare = prepare << ((4 - temp) * 6);
		for (i = 0; i < 3; i++) {
			if (i == temp) {
				break;
			}
			*f = (char) ((prepare >> ((2 - i) * 8)) & 0xFF);
			f++;
		}
	}
	*f = '\0';
	return ret;
}
