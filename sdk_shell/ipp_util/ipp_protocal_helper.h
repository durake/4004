#ifndef _IPP_PROTOCOL_BUFFER_HELPER_H_
#define _IPP_PROTOCOL_BUFFER_HELPER_H_

#define PROTOCOL_BUFFER_INIT_SIZE           50					 // buffer初始化大小

//16Bit，本地字节序转换成网络字节序
int16_t ipp_htons(int16_t val);
//16Bit，网络字节序转换成本地字节序
int16_t ipp_ntohs(int16_t val);

//32Bit，本地字节序转换成网络字节序
int32_t ipp_htonl(int32_t val);
//32Bit，网络字节序转换成本地字节序
int32_t ipp_ntohl(int32_t val);

//64Bit，本地字节序转换成网络字节序
int64_t ipp_htonll(int64_t val);
//64Bit，网络字节序转换成本地字节序
int64_t ipp_ntohll(int64_t val);

//float，本地字节序转换成网络字节序
int32_t ipp_htonf(float val);
//float，网络字节序转换成本地字节序
float ipp_ntohf(int32_t val);

//double，本地字节序转换成网络字节序
int64_t ipp_htond(double val);
//double，网络字节序转换成本地字节序
double ipp_ntohd(int64_t val);

// 检查IPP Protocol Buffer合法性
int32_t check_protocol(ipp_protocol* protocol);

// 检查IPP Protocol Buffer合法性
int32_t check_protocol_size(ipp_protocol* protocol, int32_t data_size);

//将ipp_protocol转化成ascii字符串
int32_t get_ascii_from_protocol(ipp_protocol* protocol, char** ascii_string);

//将ascii字符串转化成ipp_protocol
int32_t get_protocol_from_ascii(char* ascii_string, ipp_protocol** protocol);

#endif
