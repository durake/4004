#ifndef _IPP_ADAPTER_H_
#define _IPP_ADAPTER_H_

#include "ipp_defines.h"
#include "ipp_protocol.h"

/*-----------------------------------------对外接口-----------------------------------------*/
typedef struct
{
	char sn[50];
	char role[1];
	char flag[20];
	char ip[40];
	char mac[30];
	char valid_code[20];
	char product_id[30];
	BOOL is_online;
	int32_t device_type;
	int32_t device_id;
	int32_t connection_type;
	char model[25];
	char name[25];
	char factory[50];
	char softwareVersion[30];
	char location[25];
	struct
	{
		int32_t functionSize;
		int32_t functionCode[4];
	}function;
}ipp_device_info;

void adp_init();

/*-----------------------------------------对云平台模块提供-----------------------------------------*/
//网关发现结果回调
typedef void (*master_result_cb)(BOOL);
void reg_master_result_cb(master_result_cb cb);

//发送Event处理回调
typedef void (*cloud_send_event_cb)(const char *sn, int32_t deviceType, size_t dataLen, char *datas);
void reg_cloud_send_event_cb(cloud_send_event_cb cb);

//获取设备属性
ipp_device_info get_device_info(void);

//控制设备接口
BOOL control_device(const char *sn, char *request, int request_len, char** reply, int* reply_len);

/*-----------------------------------------对统一接口模块提供-----------------------------------------*/
//收到消息的处理回调
typedef ipp_protocol *(*adp_message_handler)(ipp_protocol *msg);
void reg_adp_message_handler(adp_message_handler cb);

//设置设备属性
void set_adp_deviceInfo(ipp_device_info *info);

//发送Event
void send_adp_event(ipp_protocol *eve);

#endif
