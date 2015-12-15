#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ipp_defines.h"
#include "ipp_util.h"
#include "ipp_protocol.h"
#include "ipp_protocal_helper.h"

#define PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL 'A'

#define SWAP_INT16(s)                \
	((((s) >> 8) & 0x00FFL ) |       \
	( ((s) << 8) & 0xFF00L ) )

#define SWAP_INT32(l)					  \
	((((l) >> 24) & 0x000000FFL ) |       \
	( ((l) >>  8) & 0x0000FF00L ) |       \
	( ((l) <<  8) & 0x00FF0000L ) |       \
	( ((l) << 24) & 0xFF000000L ) )

#define SWAP_INT64(ll)            \
	((((ll) >> 56) & 0x00000000000000FFLL ) |       \
	( ((ll) >> 40) & 0x000000000000FF00LL ) |       \
	( ((ll) >> 24) & 0x0000000000FF0000LL ) |       \
	( ((ll) >>  8) & 0x00000000FF000000LL ) |       \
	( ((ll) <<  8) & 0x000000FF00000000LL ) |       \
	( ((ll) << 24) & 0x0000FF0000000000LL ) |       \
	( ((ll) << 40) & 0x00FF000000000000LL ) |       \
	( ((ll) << 56) & 0xFF00000000000000LL ) )

//返回1，为小端；反之，为大端；
BOOL check_little_endian()
{
	return FALSE;

	//TODO:陈梁
	/*union
	{
	unsigned int  a;
	unsigned char b;
	}c;
	c.a = 1;

	return (1 == c.b) ? TRUE : FALSE;*/
}

//16Bit，本地字节序转换成网络字节序
int16_t ipp_htons(int16_t val)
{
	return check_little_endian() ?  SWAP_INT16(val) : val;
}

//16Bit，网络字节序转换成本地字节序
int16_t ipp_ntohs(int16_t val)
{
	return ipp_htons(val);
}

//32Bit，本地字节序转换成网络字节序
int32_t ipp_htonl(int32_t val)
{
	return check_little_endian() ?  SWAP_INT32(val) : val;
}

//32Bit，网络字节序转换成本地字节序
int32_t ipp_ntohl(int32_t val)
{
	return ipp_htonl(val);
}

//64Bit，本地字节序转换成网络字节序
int64_t ipp_htonll(int64_t val)
{
	return check_little_endian() ?  SWAP_INT64(val) : val;
}

//64Bit，网络字节序转换成本地字节序
int64_t ipp_ntohll(int64_t val)
{
	return ipp_htonll(val);
}

//float，本地字节序转换成网络字节序
int32_t ipp_htonf(float val)
{
	int32_t temp_val;
	int32_t return_val;
	temp_val = *(int32_t*)(&val);
	return_val = check_little_endian() ?  SWAP_INT32(temp_val) : temp_val;
	return return_val;
}

//float，网络字节序转换成本地字节序
float ipp_ntohf(int32_t val)
{
	const int32_t temp_val = check_little_endian() ?  SWAP_INT32(val) : val;
	float return_val;
	*((int32_t*)&return_val) = temp_val;
	return return_val;
}

//double，本地字节序转换成网络字节序
int64_t ipp_htond(double val)
{
	int64_t temp_val;
	int64_t return_val;
	temp_val = *(int64_t*)(&val);
	return_val = check_little_endian() ?  SWAP_INT64(temp_val) : temp_val;
	return return_val;
}

//double，网络字节序转换成本地字节序
double ipp_ntohd(int64_t val)
{
	const int64_t temp_val = check_little_endian() ?  SWAP_INT64(val) : val;
	double return_val;
	*((int64_t*)&return_val) = temp_val;
	return return_val;
}

// 检查IPP Protocol Buffer合法性
int32_t check_protocol(ipp_protocol* protocol) {
	if (NULL == protocol) {
		return protocol_is_null;
	}
	if (NULL == protocol->buffer) {
		return protocol_buffer_is_null;
	}

	return protocol_success;
}

// 检查IPP Protocol Buffer合法性
int32_t check_protocol_size(ipp_protocol* protocol, int32_t data_size) {
	if (NULL == protocol) {
		return protocol_is_null;
	}
	if (NULL == protocol->buffer) {
		return protocol_buffer_is_null;
	}
	if (data_size > (protocol->buffer_size - protocol->buffer_index)) {
		return protocol_buffer_not_enough;
	}

	return protocol_success;
}

// 转换buffer到ascii串
int32_t get_ascii_from_protocol(ipp_protocol* protocol, char** ascii_string) {
	int i;
	char high_half_byte;
	char low_half_byte;
	uint8_t byte_value;
	int32_t error_code = check_protocol(protocol);
	if (protocol_success != error_code) {
		return error_code;
	}

	(*ascii_string) = (char*)malloc((protocol->buffer_size) * 2 + 1);
	if (NULL == (*ascii_string)) {
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return protocol_alloc_failed;
	}

	for (i = 0; i < protocol->buffer_size; ++i) {
		byte_value = protocol->buffer[i];
		low_half_byte = (byte_value & 0x0F) + PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL;
		high_half_byte = ((byte_value >> 4) & 0x0F) + PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL;
		(*ascii_string)[i * 2 + 0] = high_half_byte;
		(*ascii_string)[i * 2 + 1] = low_half_byte;
	}

	(*ascii_string)[(protocol->buffer_size) * 2] = '\0';

	return protocol_success;
}

// 转换ascii串到buffer
int32_t get_protocol_from_ascii(char* ascii_string, ipp_protocol** protocol) {
	int i;
	char high_half_byte;
	char low_half_byte;
	uint8_t byte_value;
	int ascii_string_len;
	if (NULL == ascii_string) {
		return protocol_buffer_is_null;
	}

	ascii_string_len = strlen(ascii_string);
	if ((ascii_string_len % 2 != 0) || (ascii_string_len < PROTOCOL_BUFFER_INIT_SIZE * 2)) {
		return protocol_buffer_size_error;
	}

	(*protocol) = create_protocol_size(ascii_string_len / 2);

	if (NULL == (*protocol))
	{
		ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
		return protocol_alloc_failed;
	}

	for (i = 0; i < (*protocol)->buffer_size; ++i) {
		high_half_byte = ascii_string[i * 2 + 0];
		low_half_byte = ascii_string[i * 2 + 1];
		byte_value = (low_half_byte - PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL) |
			((high_half_byte - PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL) << 4);
		(*protocol)->buffer[i] = byte_value;
	}

	return protocol_success;
}
