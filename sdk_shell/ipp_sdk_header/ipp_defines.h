#ifndef _IPP_DEFINES_H_
#define _IPP_DEFINES_H_

#include <stdint.h>
typedef long long			int64_t;
typedef int32_t				BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef UBOUND
#define UBOUND(arr) ((sizeof(arr)) / (sizeof(arr[0])))
#endif

#ifndef FREE_POINTER
#define FREE_POINTER(p) \
do\
{\
	if (NULL != p)\
	{\
		free(p);\
		p = NULL;\
	}\
} while (0)
#endif

#endif
