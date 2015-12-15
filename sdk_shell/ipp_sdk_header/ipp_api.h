/******************************************************************************

                  版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

 ******************************************************************************
  文 件 名   : ipp_api.h
  功能描述   : IPP SDK对外提供的函数接口
 ******************************************************************************/
#ifndef _IPP_API_H_
#define _IPP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ipp_protocol.h"

//设备属性结构体
typedef struct
{
	char guid[32];
	char product_id[30];
	int32_t device_type;
}ipp_device_profile;

//设备收到消息处理回调函数，返回的ipp_protocol指针，由回调函数内部申请内存，IPP SDK使用后自动释放
typedef ipp_protocol *(*message_handler)(ipp_protocol *msg);

/*
  函数名：	ipp_init
  功能：	初始化并启动IPP
  入参：	无
  出参：	无
  返回值：	成功返回TRUE，失败FALSE
*/
BOOL ipp_init();

/*
  函数名：	ipp_deinit
  功能：	停止IPP并释放资源
  入参：	无
  出参：	无
  返回值：	无
*/
void ipp_deinit();

/*
  函数名：	set_device_info
  功能：	设置设备属性
  入参：	ipp_device_profile *info
  出参：	无
  返回值：	无
*/
void set_device_info(ipp_device_profile *profile);

/*
  函数名：	send_event
  功能：	发送设备事件(如设备状态变化等)
  入参：	ipp_protocol *eve
  出参：	无
  返回值：	无
*/
void send_event(ipp_protocol *eve);

/*
  函数名：	reg_message_handler
  功能：	注册设备收到消息处理回调函数
  入参：	message_handler handler
  出参：	无
  返回值：	无
*/
void reg_message_handler(message_handler handler);

#ifdef __cplusplus
}
#endif

#endif
