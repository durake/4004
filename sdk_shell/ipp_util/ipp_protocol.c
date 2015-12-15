/******************************************************************************

                  版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

 ******************************************************************************
  文 件 名   : ipp_protocol.c
  版 本 号   : 初稿
  作    者   : 陈梁 20167633
  生成日期   : 2015年10月13日
  最近修改   :
  功能描述   : ipp协议组装类
  函数列表   : 略
  修改历史   :
  1.日    期   : 2015年10月13日
    作    者   : 陈梁 20167633
    修改内容   : 创建文件
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ipp_stub_def.h"
#include "ipp_defines.h"
#include "ipp_util.h"
#include "ipp_protocol.h"
#include "ipp_protocal_helper.h"

#define PUT_INT_BUFFER_NUMBER_ARRAY(numberType, putFunc)\
int i = 0;\
int32_t error_code = put_int32(protocol, array_size);\
if (protocol_success != error_code) {\
	return error_code;\
}\
\
for (;i < array_size; ++i)\
{\
	error_code = putFunc(protocol, array[i]);\
	if (protocol_success != error_code)\
	{\
		return error_code;\
	}\
}\
\
return protocol_success


#define GET_FROM_BUFFER_BUMBER(numberType, transFunc) \
numberType temp;\
int32_t error_code = get(protocol, &temp, sizeof(numberType));\
if (protocol_success != error_code) {\
	return error_code;\
}\
\
*data = transFunc(temp);\
return protocol_success

#define GET_FROM_BUFFER_NUMBER_ARRAY(numberType, getFunc) \
int i = 0;\
int32_t data_size = sizeof(numberType);\
int32_t error_code = get_int32(protocol, array_size);\
if (protocol_success != error_code) {\
	return error_code;\
}\
\
*array = (numberType*)malloc(data_size * (*array_size));\
if (NULL == (*array)) {\
	ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);\
	return protocol_alloc_failed;\
}\
\
for (i = 0; i < (*array_size); ++i) {\
	error_code = getFunc(protocol, *array + i);\
	if (protocol_success != error_code) {\
		return error_code;\
	}\
}\
\
return protocol_success

//-----------------------------------------内部函数-----------------------------------------//
// 增加Buffer
void increase_protocol(ipp_protocol* protocol, int32_t increase_size) {
	char *pTemp = NULL;
	if (protocol->buffer_size >= protocol->buffer_index + increase_size)
	{
		return;
	}

	pTemp = (char*)realloc((void*)(protocol->buffer), protocol->buffer_index + increase_size);
	if (NULL == pTemp) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return;
	}
	protocol->buffer = pTemp;
	protocol->buffer_size = protocol->buffer_index + increase_size;
}

int32_t put(ipp_protocol* protocol, void* data, int32_t data_size) {
	int32_t error_code = check_protocol(protocol);
	if (protocol_success != error_code) {
		return error_code;
	}

	increase_protocol(protocol, data_size);

	memcpy(protocol->buffer + protocol->buffer_index, data, data_size);
	protocol->buffer_index += data_size;

	return protocol_success;
}

int32_t get(ipp_protocol* protocol, void* data, int32_t data_size) {
	int32_t error_code = check_protocol_size(protocol, data_size);
	if (protocol_success != error_code) {
		return error_code;
	}

	memcpy(data, protocol->buffer + protocol->buffer_index, data_size);
	protocol->buffer_index += data_size;

	return protocol_success;
}

int32_t get_array(ipp_protocol* protocol, void** array, int32_t ele_size, int32_t* array_size) {
	int32_t error_code = get_int32(protocol, array_size);
	if (protocol_success != error_code) {
		return error_code;
	}

	*array = (char*)malloc(ele_size * (*array_size));
	if (NULL == (*array)) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return protocol_alloc_failed;
	}

	error_code = get(protocol, *array, ele_size * (*array_size));
	if (protocol_success != error_code) {
		return error_code;
	}

	return protocol_success;
}

//-----------------------------------------外部函数-----------------------------------------//
// 创建IPP Protocol Buffer
ipp_protocol* create_protocol(void) {
	ipp_protocol* protocol = (ipp_protocol *)malloc(sizeof(ipp_protocol));

	if (NULL == protocol) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return NULL;
	}

	protocol->buffer_size = PROTOCOL_BUFFER_INIT_SIZE;
	protocol->buffer =(char*)malloc(protocol->buffer_size);
	protocol->buffer_index = 0;
	if (NULL == protocol->buffer) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return NULL;
	}
	memset(protocol->buffer, 0, protocol->buffer_size);

	return protocol;
}

// 克隆IPP Protocol Buffer
ipp_protocol* clone_protocol(ipp_protocol* protocol) {
	ipp_protocol* clone = NULL;
	if (NULL == protocol) {
		return NULL;
	}
	clone = create_protocol_size(protocol->buffer_size);
	clone->buffer_size = protocol->buffer_size;
	clone->buffer_index = protocol->buffer_index;
	memcpy(clone->buffer, protocol->buffer, protocol->buffer_size);

	return clone;
}

// 创建IPP Protocol Buffer指定大小
ipp_protocol* create_protocol_size(int32_t size) {
	ipp_protocol* protocol = (ipp_protocol *)malloc(sizeof(ipp_protocol));
	if (NULL == protocol) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return NULL;
	}
	protocol->buffer_size = size;
	protocol->buffer =(char*)malloc(protocol->buffer_size);
	protocol->buffer_index = 0;
	if (NULL == protocol->buffer) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return NULL;
	}
	memset(protocol->buffer, 0, protocol->buffer_size);

	return protocol;
}

// 释放IPP Protocol Buffer
void free_protocol(ipp_protocol* protocol) {
	if (protocol != NULL) {
		FREE_POINTER(protocol->buffer);
		FREE_POINTER(protocol);
	}
}

// 在IPP Protocol Buffer放入int8数据
int32_t put_char(ipp_protocol* protocol, char data) {
	return put(protocol, &data, sizeof(data));
}

int32_t put_int16(ipp_protocol* protocol, int16_t data) {
	int16_t dataTrans = ipp_htons(data);
	return put(protocol, &dataTrans, sizeof(dataTrans));
}

int32_t put_int32(ipp_protocol* protocol, int32_t data) {
	int32_t dataTrans = ipp_htonl(data);
	return put(protocol, &dataTrans, sizeof(dataTrans));
}

int32_t put_int64(ipp_protocol* protocol, int64_t data) {
	int64_t dataTrans = ipp_htonll(data);
	return put(protocol, &dataTrans, sizeof(dataTrans));
}

int32_t put_bool(ipp_protocol* protocol, BOOL data) {
	int32_t dataTrans = ipp_htonl(data);
	return put(protocol, &dataTrans, sizeof(dataTrans));
}

int32_t put_float(ipp_protocol* protocol, float data) {
	int32_t dataTrans = ipp_htonf(data);
	return put(protocol, &dataTrans, sizeof(dataTrans));
}

int32_t put_double(ipp_protocol* protocol, double data) {
	int64_t dataTrans = ipp_htond(data);
	return put(protocol, &dataTrans, sizeof(dataTrans));
}

int32_t put_array(ipp_protocol* protocol, void* array, int32_t ele_size, int32_t array_size) {
	int32_t error_code = put_int32(protocol, array_size);
	if (protocol_success != error_code) {
		return error_code;
	}

	return put(protocol, array, ele_size * array_size);
}

int32_t put_string(ipp_protocol* protocol, char* data) {
	return put_array(protocol, data, sizeof(char), strlen(data) + 1);
}

// 在IPP Protocol Buffer放入数据数组
int32_t put_char_array(ipp_protocol* protocol, char* array, int32_t array_size) {
	return put_array(protocol, array, sizeof(array[0]), array_size);
}

int32_t put_int16_array(ipp_protocol* protocol, int16_t* array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(int16, put_int16);
}

int32_t put_int32_array(ipp_protocol* protocol, int32_t* array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(int32, put_int32);
}

int32_t put_int64_array(ipp_protocol* protocol, int64_t* array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(int64, put_int64);
}

int32_t put_bool_array(ipp_protocol* protocol, BOOL* array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(BOOL, put_bool);
}

int32_t put_float_array(ipp_protocol* protocol, float* array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(float, put_float);
}

int32_t put_double_array(ipp_protocol* protocol, double* array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(double, put_double);
}

int32_t put_string_array(ipp_protocol* protocol, char** array, int32_t array_size) {
	PUT_INT_BUFFER_NUMBER_ARRAY(string, put_string);
}

// 从IPP Protocol Buffer获取int8数据
int32_t get_char(ipp_protocol* protocol, char* data) {
	return get(protocol, data, sizeof(char));
}

int32_t get_int16(ipp_protocol* protocol, int16_t* data) {
	GET_FROM_BUFFER_BUMBER(int16_t, ipp_ntohs);
}

int32_t get_int32(ipp_protocol* protocol, int32_t* data) {
	GET_FROM_BUFFER_BUMBER(int32_t, ipp_ntohl);
}

int32_t get_int64(ipp_protocol* protocol, int64_t* data) {
	GET_FROM_BUFFER_BUMBER(int64_t, ipp_ntohll);
}

int32_t get_bool(ipp_protocol* protocol, BOOL* data) {
	GET_FROM_BUFFER_BUMBER(int32_t, ipp_ntohl);
}

int32_t get_float(ipp_protocol* protocol, float* data) {
	GET_FROM_BUFFER_BUMBER(int32_t, ipp_ntohf);
}

int32_t get_double(ipp_protocol* protocol, double* data) {
	GET_FROM_BUFFER_BUMBER(int64_t, ipp_ntohd);
}

int32_t get_string(ipp_protocol* protocol, char** data) {
	int32_t str_size = 0;
	return get_array(protocol, (void **)data, 1, &str_size);
}

// 从IPP Protocol Buffer获取数据数组
int32_t get_char_array(ipp_protocol* protocol, char** array, int32_t* array_size) {
	return get_array(protocol, (void **)array, sizeof(char), array_size);
}

int32_t get_int16_array(ipp_protocol* protocol, int16_t** array, int32_t* array_size) {
	GET_FROM_BUFFER_NUMBER_ARRAY(int16_t, get_int16);
}

int32_t get_int32_array(ipp_protocol* protocol, int32_t** array, int32_t* array_size) {
	GET_FROM_BUFFER_NUMBER_ARRAY(int32_t, get_int32);
}

int32_t get_int64_array(ipp_protocol* protocol, int64_t** array, int32_t* array_size) {
	GET_FROM_BUFFER_NUMBER_ARRAY(int64_t, get_int64);
}
int32_t get_bool_array(ipp_protocol* protocol, BOOL** array, int32_t* array_size) {
	GET_FROM_BUFFER_NUMBER_ARRAY(BOOL, get_bool);
}

int32_t get_float_array(ipp_protocol* protocol, float** array, int32_t* array_size) {
	GET_FROM_BUFFER_NUMBER_ARRAY(float, get_float);
}

int32_t get_double_array(ipp_protocol* protocol, double** array, int32_t* array_size) {
	GET_FROM_BUFFER_NUMBER_ARRAY(double, get_double);
}

int32_t get_string_array(ipp_protocol* protocol, char*** array, int32_t* array_size)  {
	GET_FROM_BUFFER_NUMBER_ARRAY(char*, get_string);
}
