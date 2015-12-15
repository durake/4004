/******************************************************************************

                  版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

 ******************************************************************************
  文 件 名   : ipp_protocol.h
  功能描述   : IP SDK消息缓存处理函数
 ******************************************************************************/
#ifndef _IPP_PROTOCOL_H_
#define _IPP_PROTOCOL_H_

#ifdef __cplusplus
extern "C" {
#endif
/*--------------------------------------消息结构体--------------------------------------*/
typedef enum
{
	protocol_success,									// 成功
	protocol_is_null,									// protocol为空
	protocol_buffer_is_null,							// protocol中缓存为空
	protocol_buffer_not_enough,							// protocol缓存大小不够
	protocol_buffer_size_error,							// protocol缓存大小错误
	protocol_alloc_failed,								// 分配内存失败
}protocol_result;

typedef struct {
	char* buffer;			//缓存
	int32_t buffer_size;	//缓存总长度
	int32_t buffer_index;	//当前访问的游标，put类和get类操作均会导致游标右移
}ipp_protocol;

/*--------------------------------------ipp_protocol创建和释放--------------------------------------*/
/*
  函数名：	create_protocol
  功能：	创建ipp_protocol，申请内存，需要使用者释放
  入参：	无
  出参：	无
  返回值：	ipp_protocol* 申请成功返回ipp_protocol指针，申请失败，返回NULL
*/
ipp_protocol* create_protocol(void);

/*
  函数名：	clone_protocol
  功能：	对指定的ipp_protocol进行克隆，包括数据，长度，偏移均进行完全复制
			克隆完成后，原来的ipp_protocol不会进行释放

  入参：	ipp_protocol* 即将进行克隆的ipp_protocol
  出参：	无
  返回值：	ipp_protocol* 克隆成功返回ipp_protocol指针，申请失败，返回NULL
*/
ipp_protocol* clone_protocol(ipp_protocol* protocol);

/*
  函数名：	create_protocol_size
  功能：	根据指定长度创建ipp_protocol，申请内存，需要使用者释放
  入参：	int32_t size需要申请的长度
  出参：	无
  返回值：	ipp_protocol* 申请成功返回ipp_protocol指针，申请失败，返回NULL
*/
ipp_protocol* create_protocol_size(int32_t size);

/*
  函数名：	free_protocol
  功能：	释放ipp_protocol，此函数同时释放ipp_protocol和ipp_protocol中的缓存，并且将指针置为NULL
  入参：	ipp_protocol* protocol 需要释放的ipp_protocol
  出参：	无
  返回值：	无
*/
void free_protocol(ipp_protocol* protocol);

/*--------------------------------------ipp_protocol填充(put类操作)--------------------------------------*/
/*
  函数名：	put_char
  功能：	向指定的ipp_protocol填充一个char，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			char data			   填充的char
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_char(ipp_protocol* protocol, char data);

/*
  函数名：	put_int16
  功能：	向指定的ipp_protocol填充一个int16，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			int16_t data			   填充的int16
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_int16(ipp_protocol* protocol, int16_t data);

/*
  函数名：	put_int32
  功能：	向指定的ipp_protocol填充一个int32，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			int32_t data			   填充的int32
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_int32(ipp_protocol* protocol, int32_t data);

/*
  函数名：	put_int64
  功能：	向指定的ipp_protocol填充一个int64，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			int64_t data			   填充的int64
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_int64(ipp_protocol* protocol, int64_t data);

/*
  函数名：	put_bool
  功能：	向指定的ipp_protocol填充一个BOOL，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			BOOL data			   填充的BOOL
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_bool(ipp_protocol* protocol, BOOL data);

/*
  函数名：	put_float
  功能：	向指定的ipp_protocol填充一个float，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			float data			   填充的float
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_float(ipp_protocol* protocol, float data);

/*
  函数名：	put_double
  功能：	向指定的ipp_protocol填充一个double，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			double data			   填充的double
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_double(ipp_protocol* protocol, double data);

/*
  函数名：	put_string
  功能：	向指定的ipp_protocol填充一个以'0'结束的字符串，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			char* data			   填充的字符串
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_string(ipp_protocol* protocol, char* data);

/*
  函数名：	put_char_array
  功能：	向指定的ipp_protocol填充char数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			char* array			   char数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_char_array(ipp_protocol* protocol, char* array, int32_t array_size);

/*
  函数名：	put_int16_array
  功能：	向指定的ipp_protocol填充int16数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			int16_t* array		   int16数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_int16_array(ipp_protocol* protocol, int16_t* array, int32_t array_size);

/*
  函数名：	put_int32_array
  功能：	向指定的ipp_protocol填充int32数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			int32_t* array		   int32数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_int32_array(ipp_protocol* protocol, int32_t* array, int32_t array_size);

/*
  函数名：	put_int64_array
  功能：	向指定的ipp_protocol填充int64数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			int64_t* array		   int64数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_int64_array(ipp_protocol* protocol, int64_t* array, int32_t array_size);

/*
  函数名：	put_bool_array
  功能：	向指定的ipp_protocol填充BOOL数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			BOOL* array		       BOOL数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_bool_array(ipp_protocol* protocol, BOOL* array, int32_t array_size);

/*
  函数名：	put_float_array
  功能：	向指定的ipp_protocol填充float数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			float* array		   float数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_float_array(ipp_protocol* protocol, float* array, int32_t array_size);

/*
  函数名：	put_double_array
  功能：	向指定的ipp_protocol填充double数组，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			double* array		   double数组
			int32_t array_size     数组长度
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_double_array(ipp_protocol* protocol, double* array, int32_t array_size);

/*
  函数名：	put_string_array
  功能：	向指定的ipp_protocol填充字符串数组，每个字符串以'0'结尾，ipp_protocol长度不够时，会自动增加长度
  入参：	ipp_protocol* protocol 需要填充的ipp_protocol
			char** array		   字符串数组
			int32_t array_size     字符串个数
  出参：	无
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t put_string_array(ipp_protocol* protocol, char** array, int32_t array_size);

/*--------------------------------------ipp_protocol提取(get类操作)--------------------------------------*/
/*
  函数名：	get_char
  功能：	从指定的ipp_protocol中提取一个char
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	char* data		       用于存放提取出来的字符，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_char(ipp_protocol* protocol, char* data);

/*
  函数名：	get_int16
  功能：	从指定的ipp_protocol中提取一个int16
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	int16* data		       用于存放提取出来的int16，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_int16(ipp_protocol* protocol, int16_t* data);

/*
  函数名：	get_int32
  功能：	从指定的ipp_protocol中提取一个int32
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	int32* data		       用于存放提取出来的int32，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_int32(ipp_protocol* protocol, int32_t* data);

/*
  函数名：	get_int64
  功能：	从指定的ipp_protocol中提取一个int64
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	int64* data		       用于存放提取出来的int64，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_int64(ipp_protocol* protocol, int64_t* data);

/*
  函数名：	get_bool
  功能：	从指定的ipp_protocol中提取一个BOOL
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	BOOL* data		       用于存放提取出来的BOOL，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_bool(ipp_protocol* protocol, BOOL* data);

/*
  函数名：	get_float
  功能：	从指定的ipp_protocol中提取一个float
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	float* data		       用于存放提取出来的float，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_float(ipp_protocol* protocol, float* data);

/*
  函数名：	get_double
  功能：	从指定的ipp_protocol中提取一个double
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	double* data		   用于存放提取出来的double，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_double(ipp_protocol* protocol, double* data);

/*
  函数名：	get_string
  功能：	从指定的ipp_protocol中提取一个字符串
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	char** data		       用于存放提取出来的字符串，由函数内部进行申请，需要使用者释放。
								   注意：一定要传入空指针，否则原来的内存会泄露。
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_string(ipp_protocol* protocol, char** data);

/*
  函数名：	get_char_array
  功能：	从指定的ipp_protocol中提取一个char数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	char** array		       用于存放提取出来的char数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_char_array(ipp_protocol* protocol, char** array, int32_t* array_size);

/*
  函数名：	get_int16_array
  功能：	从指定的ipp_protocol中提取一个int16数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	int16** array		       用于存放提取出来的int16数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_int16_array(ipp_protocol* protocol, int16_t** array, int32_t* array_size);

/*
  函数名：	get_int32_array
  功能：	从指定的ipp_protocol中提取一个int32数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	int32** array		       用于存放提取出来的int32数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_int32_array(ipp_protocol* protocol, int32_t** array, int32_t* array_size);

/*
  函数名：	get_int64_array
  功能：	从指定的ipp_protocol中提取一个int64数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	int64** array		       用于存放提取出来的int64数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_int64_array(ipp_protocol* protocol, int64_t** array, int32_t* array_size);

/*
  函数名：	get_bool_array
  功能：	从指定的ipp_protocol中提取一个BOOL数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	BOOL** array		       用于存放提取出来的BOOL数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_bool_array(ipp_protocol* protocol, BOOL** array, int32_t* array_size);

/*
  函数名：	get_float_array
  功能：	从指定的ipp_protocol中提取一个float数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	float** array		       用于存放提取出来的float数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_float_array(ipp_protocol* protocol, float** array, int32_t* array_size);

/*
  函数名：	get_double_array
  功能：	从指定的ipp_protocol中提取一个double数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	double** array		       用于存放提取出来的double数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_double_array(ipp_protocol* protocol, double** array, int32_t* array_size);

/*
  函数名：	get_string_array
  功能：	从指定的ipp_protocol中提取一个字符串数组
  入参：	ipp_protocol* protocol 需要从中提取的ipp_protocol
  出参：	char*** array		       用于存放提取出来的字符串数组，由函数内部进行申请，需要使用者释放。
								       注意：一定要传入空指针，否则原来的内存会泄露。
			int32_t* array_size		   用于存放数组长度，需要使用者预先分配内存
  返回值：	成功返回protocol_success，失败返回错误码
*/
int32_t get_string_array(ipp_protocol* protocol, char*** array, int32_t* array_size);

#ifdef __cplusplus
}
#endif

#endif /* _PROTOCOL_BUFFER_H_ */
