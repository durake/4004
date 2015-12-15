/******************************************************************************

                  ��Ȩ���� (C), 1958-2015, �����������-�Ʒ�-���ּ�ͥ

 ******************************************************************************
  �� �� ��   : ipp_protocol.h
  ��������   : IP SDK��Ϣ���洦����
 ******************************************************************************/
#ifndef _IPP_PROTOCOL_H_
#define _IPP_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif
/*--------------------------------------��Ϣ�ṹ��--------------------------------------*/
typedef enum
{
	protocol_success,									// �ɹ�
	protocol_is_null,									// protocolΪ��
	protocol_buffer_is_null,							// protocol�л���Ϊ��
	protocol_buffer_not_enough,							// protocol�����С����
	protocol_buffer_size_error,							// protocol�����С����
	protocol_alloc_failed,								// �����ڴ�ʧ��
}protocol_result;

typedef struct {
	char* buffer;			//����
	int32_t buffer_size;	//�����ܳ���
	int32_t buffer_index;	//��ǰ���ʵ��α꣬put���get��������ᵼ���α�����
}ipp_protocol;

/*--------------------------------------ipp_protocol�������ͷ�--------------------------------------*/
/*
  ��������	create_protocol
  ���ܣ�	����ipp_protocol�������ڴ棬��Ҫʹ�����ͷ�
  ��Σ�	��
  ���Σ�	��
  ����ֵ��	ipp_protocol* ����ɹ�����ipp_protocolָ�룬����ʧ�ܣ�����NULL
*/
ipp_protocol* create_protocol(void);

/*
  ��������	clone_protocol
  ���ܣ�	��ָ����ipp_protocol���п�¡���������ݣ����ȣ�ƫ�ƾ�������ȫ����
			��¡��ɺ�ԭ����ipp_protocol��������ͷ�

  ��Σ�	ipp_protocol* �������п�¡��ipp_protocol
  ���Σ�	��
  ����ֵ��	ipp_protocol* ��¡�ɹ�����ipp_protocolָ�룬����ʧ�ܣ�����NULL
*/
ipp_protocol* clone_protocol(ipp_protocol* protocol);

/*
  ��������	create_protocol_size
  ���ܣ�	����ָ�����ȴ���ipp_protocol�������ڴ棬��Ҫʹ�����ͷ�
  ��Σ�	int32_t size��Ҫ����ĳ���
  ���Σ�	��
  ����ֵ��	ipp_protocol* ����ɹ�����ipp_protocolָ�룬����ʧ�ܣ�����NULL
*/
ipp_protocol* create_protocol_size(int32_t size);

/*
  ��������	free_protocol
  ���ܣ�	�ͷ�ipp_protocol���˺���ͬʱ�ͷ�ipp_protocol��ipp_protocol�еĻ��棬���ҽ�ָ����ΪNULL
  ��Σ�	ipp_protocol* protocol ��Ҫ�ͷŵ�ipp_protocol
  ���Σ�	��
  ����ֵ��	��
*/
void free_protocol(ipp_protocol* protocol);

/*--------------------------------------ipp_protocol���(put�����)--------------------------------------*/
/*
  ��������	put_char
  ���ܣ�	��ָ����ipp_protocol���һ��char��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			char data			   ����char
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_char(ipp_protocol* protocol, char data);

/*
  ��������	put_int16
  ���ܣ�	��ָ����ipp_protocol���һ��int16��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			int16_t data			   ����int16
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_int16(ipp_protocol* protocol, int16_t data);

/*
  ��������	put_int32
  ���ܣ�	��ָ����ipp_protocol���һ��int32��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			int32_t data			   ����int32
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_int32(ipp_protocol* protocol, int32_t data);

/*
  ��������	put_int64
  ���ܣ�	��ָ����ipp_protocol���һ��int64��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			int64_t data			   ����int64
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_int64(ipp_protocol* protocol, int64_t data);

/*
  ��������	put_bool
  ���ܣ�	��ָ����ipp_protocol���һ��BOOL��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			BOOL data			   ����BOOL
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_bool(ipp_protocol* protocol, BOOL data);

/*
  ��������	put_float
  ���ܣ�	��ָ����ipp_protocol���һ��float��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			float data			   ����float
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_float(ipp_protocol* protocol, float data);

/*
  ��������	put_double
  ���ܣ�	��ָ����ipp_protocol���һ��double��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			double data			   ����double
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_double(ipp_protocol* protocol, double data);

/*
  ��������	put_string
  ���ܣ�	��ָ����ipp_protocol���һ����'0'�������ַ�����ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			char* data			   �����ַ���
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_string(ipp_protocol* protocol, char* data);

/*
  ��������	put_char_array
  ���ܣ�	��ָ����ipp_protocol���char���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			char* array			   char����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_char_array(ipp_protocol* protocol, char* array, int32_t array_size);

/*
  ��������	put_int16_array
  ���ܣ�	��ָ����ipp_protocol���int16���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			int16_t* array		   int16����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_int16_array(ipp_protocol* protocol, int16_t* array, int32_t array_size);

/*
  ��������	put_int32_array
  ���ܣ�	��ָ����ipp_protocol���int32���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			int32_t* array		   int32����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_int32_array(ipp_protocol* protocol, int32_t* array, int32_t array_size);

/*
  ��������	put_int64_array
  ���ܣ�	��ָ����ipp_protocol���int64���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			int64_t* array		   int64����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_int64_array(ipp_protocol* protocol, int64_t* array, int32_t array_size);

/*
  ��������	put_bool_array
  ���ܣ�	��ָ����ipp_protocol���BOOL���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			BOOL* array		       BOOL����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_bool_array(ipp_protocol* protocol, BOOL* array, int32_t array_size);

/*
  ��������	put_float_array
  ���ܣ�	��ָ����ipp_protocol���float���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			float* array		   float����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_float_array(ipp_protocol* protocol, float* array, int32_t array_size);

/*
  ��������	put_double_array
  ���ܣ�	��ָ����ipp_protocol���double���飬ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			double* array		   double����
			int32_t array_size     ���鳤��
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_double_array(ipp_protocol* protocol, double* array, int32_t array_size);

/*
  ��������	put_string_array
  ���ܣ�	��ָ����ipp_protocol����ַ������飬ÿ���ַ�����'0'��β��ipp_protocol���Ȳ���ʱ�����Զ����ӳ���
  ��Σ�	ipp_protocol* protocol ��Ҫ����ipp_protocol
			char** array		   �ַ�������
			int32_t array_size     �ַ�������
  ���Σ�	��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t put_string_array(ipp_protocol* protocol, char** array, int32_t array_size);

/*--------------------------------------ipp_protocol��ȡ(get�����)--------------------------------------*/
/*
  ��������	get_char
  ���ܣ�	��ָ����ipp_protocol����ȡһ��char
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	char* data		       ���ڴ����ȡ�������ַ�����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_char(ipp_protocol* protocol, char* data);

/*
  ��������	get_int16
  ���ܣ�	��ָ����ipp_protocol����ȡһ��int16
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	int16* data		       ���ڴ����ȡ������int16����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_int16(ipp_protocol* protocol, int16_t* data);

/*
  ��������	get_int32
  ���ܣ�	��ָ����ipp_protocol����ȡһ��int32
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	int32* data		       ���ڴ����ȡ������int32����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_int32(ipp_protocol* protocol, int32_t* data);

/*
  ��������	get_int64
  ���ܣ�	��ָ����ipp_protocol����ȡһ��int64
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	int64* data		       ���ڴ����ȡ������int64����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_int64(ipp_protocol* protocol, int64_t* data);

/*
  ��������	get_bool
  ���ܣ�	��ָ����ipp_protocol����ȡһ��BOOL
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	BOOL* data		       ���ڴ����ȡ������BOOL����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_bool(ipp_protocol* protocol, BOOL* data);

/*
  ��������	get_float
  ���ܣ�	��ָ����ipp_protocol����ȡһ��float
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	float* data		       ���ڴ����ȡ������float����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_float(ipp_protocol* protocol, float* data);

/*
  ��������	get_double
  ���ܣ�	��ָ����ipp_protocol����ȡһ��double
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	double* data		   ���ڴ����ȡ������double����Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_double(ipp_protocol* protocol, double* data);

/*
  ��������	get_string
  ���ܣ�	��ָ����ipp_protocol����ȡһ���ַ���
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	char** data		       ���ڴ����ȡ�������ַ������ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								   ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_string(ipp_protocol* protocol, char** data);

/*
  ��������	get_char_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��char����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	char** array		       ���ڴ����ȡ������char���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_char_array(ipp_protocol* protocol, char** array, int32_t* array_size);

/*
  ��������	get_int16_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��int16����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	int16** array		       ���ڴ����ȡ������int16���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_int16_array(ipp_protocol* protocol, int16_t** array, int32_t* array_size);

/*
  ��������	get_int32_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��int32����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	int32** array		       ���ڴ����ȡ������int32���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_int32_array(ipp_protocol* protocol, int32_t** array, int32_t* array_size);

/*
  ��������	get_int64_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��int64����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	int64** array		       ���ڴ����ȡ������int64���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_int64_array(ipp_protocol* protocol, int64_t** array, int32_t* array_size);

/*
  ��������	get_bool_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��BOOL����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	BOOL** array		       ���ڴ����ȡ������BOOL���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_bool_array(ipp_protocol* protocol, BOOL** array, int32_t* array_size);

/*
  ��������	get_float_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��float����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	float** array		       ���ڴ����ȡ������float���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_float_array(ipp_protocol* protocol, float** array, int32_t* array_size);

/*
  ��������	get_double_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ��double����
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	double** array		       ���ڴ����ȡ������double���飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_double_array(ipp_protocol* protocol, double** array, int32_t* array_size);

/*
  ��������	get_string_array
  ���ܣ�	��ָ����ipp_protocol����ȡһ���ַ�������
  ��Σ�	ipp_protocol* protocol ��Ҫ������ȡ��ipp_protocol
  ���Σ�	char*** array		       ���ڴ����ȡ�������ַ������飬�ɺ����ڲ��������룬��Ҫʹ�����ͷš�
								       ע�⣺һ��Ҫ�����ָ�룬����ԭ�����ڴ��й¶��
			int32_t* array_size		   ���ڴ�����鳤�ȣ���Ҫʹ����Ԥ�ȷ����ڴ�
  ����ֵ��	�ɹ�����protocol_success��ʧ�ܷ��ش�����
*/
int32_t get_string_array(ipp_protocol* protocol, char*** array, int32_t* array_size);

#ifdef __cplusplus
}
#endif

#endif /* _PROTOCOL_BUFFER_H_ */
