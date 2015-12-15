#ifndef _IPP_PROTOCOL_BUFFER_HELPER_H_
#define _IPP_PROTOCOL_BUFFER_HELPER_H_

#define PROTOCOL_BUFFER_INIT_SIZE           50					 // buffer��ʼ����С

//16Bit�������ֽ���ת���������ֽ���
int16_t ipp_htons(int16_t val);
//16Bit�������ֽ���ת���ɱ����ֽ���
int16_t ipp_ntohs(int16_t val);

//32Bit�������ֽ���ת���������ֽ���
int32_t ipp_htonl(int32_t val);
//32Bit�������ֽ���ת���ɱ����ֽ���
int32_t ipp_ntohl(int32_t val);

//64Bit�������ֽ���ת���������ֽ���
int64_t ipp_htonll(int64_t val);
//64Bit�������ֽ���ת���ɱ����ֽ���
int64_t ipp_ntohll(int64_t val);

//float�������ֽ���ת���������ֽ���
int32_t ipp_htonf(float val);
//float�������ֽ���ת���ɱ����ֽ���
float ipp_ntohf(int32_t val);

//double�������ֽ���ת���������ֽ���
int64_t ipp_htond(double val);
//double�������ֽ���ת���ɱ����ֽ���
double ipp_ntohd(int64_t val);

// ���IPP Protocol Buffer�Ϸ���
int32_t check_protocol(ipp_protocol* protocol);

// ���IPP Protocol Buffer�Ϸ���
int32_t check_protocol_size(ipp_protocol* protocol, int32_t data_size);

//��ipp_protocolת����ascii�ַ���
int32_t get_ascii_from_protocol(ipp_protocol* protocol, char** ascii_string);

//��ascii�ַ���ת����ipp_protocol
int32_t get_protocol_from_ascii(char* ascii_string, ipp_protocol** protocol);

#endif
