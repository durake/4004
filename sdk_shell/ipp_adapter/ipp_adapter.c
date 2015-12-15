#include "ipp_adapter.h"
#include "ipp_defines.h"
#include "ipp_util.h"
#include "../SelfService/SelfMethodSignal.h"

static master_result_cb g_master_result_cb = NULL;
static adp_message_handler g_adp_message_handler = NULL;
static cloud_send_event_cb g_cloud_send_event_cb = NULL;
BOOL device_control_cb(char* request, int reqlen, char** reply, int* replen);

void adp_init()
{
	RegisterDevControlHandler(device_control_cb);
	if (NULL != g_master_result_cb)
	{
		g_master_result_cb(FALSE);
	}
}

/*-----------------------------------------对云平台模块提供-----------------------------------------*/
//网关发现结果回调
void reg_master_result_cb(master_result_cb cb)
{
	g_master_result_cb = cb;
}

//发送Event处理回调
void reg_cloud_send_event_cb(cloud_send_event_cb cb)
{
	g_cloud_send_event_cb = cb;
}

//获取设备属性
ipp_device_info get_device_info(void)
{
	ipp_device_info info;
	memset(&info, 0, sizeof(info));

	memcpy(info.sn, getSelfDeviceSN(), strlen(getSelfDeviceSN()));
	info.role[0] = strcmp(getSelfDeviceRole(), "A") == 0 ? 'A' : 'B';
	memcpy(info.product_id, getSelfDeviceProductID(), strlen(getSelfDeviceProductID()));
	memcpy(info.ip, getSelfDeviceIP(), strlen(getSelfDeviceIP()));
	info.is_online = geSelfDevicetIsOnline();
	info.device_type = getSelfDeviceType();
	info.device_id = getSelfDeviceDeviceId();
	info.connection_type = getSelfDeviceConnectType();
	memcpy(info.model, getSelfDeviceModel(), strlen(getSelfDeviceModel()));
	memcpy(info.name, getSelfDeviceName(), strlen(getSelfDeviceName()));
	memcpy(info.factory, getSelfDeviceFactory(), strlen(getSelfDeviceFactory()));
	memcpy(info.softwareVersion, getSelfDeviceSoftwareVersion(), strlen(getSelfDeviceSoftwareVersion()));
	memcpy(info.location, getSelfDeviceLocation(), strlen(getSelfDeviceLocation()));
	memcpy(info.flag, getSelfDeviceFlag(), strlen(getSelfDeviceFlag()));
	memcpy(info.mac, getSelfDeviceMac(), strlen(getSelfDeviceMac()));
	memcpy(info.valid_code, getSelfDeviceVCode(), strlen(getSelfDeviceVCode()));

	return info;
}

//控制设备接口
BOOL control_device(const char *sn, char *request, int request_len, char** reply, int* reply_len)
{
	RemoteControlRequst(sn, request, request_len, reply, reply_len);
	if (NULL != reply && reply_len > 0)
	{
		return TRUE;
	}

	ipp_LogE("Error:%s(%d)-%s:control_device is NULL!\n",__FILE__,__LINE__,__FUNCTION__);
	return FALSE;
}

/*-----------------------------------------对统一接口模块提供-----------------------------------------*/
BOOL device_control_cb(char* request, int reqlen, char** reply, int* replen)
{
	ipp_protocol *p_request = NULL;
	ipp_protocol *p_reply = NULL;
	int32_t ret = protocol_success;
	*reply = NULL;
	*replen = 0;

	if (NULL != g_adp_message_handler)
	{
		p_request = create_protocol_size(reqlen);
		if (NULL == p_request)
		{
			ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
			return FALSE;
		}

		ret = put_char_array(p_request, request, reqlen);
		if (protocol_success != ret)
		{
			ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
			free_protocol(p_request);
			return FALSE;
		}

		p_reply = g_adp_message_handler(p_request);
		free_protocol(p_request);

		if (NULL == p_reply)
		{
			ipp_LogE("Error:%s(%d)-%s\n",__FILE__,__LINE__,__FUNCTION__);
			return FALSE;
		}

		get_char_array(p_reply, reply, replen);
		free_protocol(p_reply);
		return TRUE;
	}

	ipp_LogE("Error:%s(%d)-%s:g_adp_message_handler is NULL!\n",__FILE__,__LINE__,__FUNCTION__);
	return FALSE;
}

//收到消息的处理回调
void reg_adp_message_handler(adp_message_handler cb)
{
	g_adp_message_handler = cb;
}

//设置设备属性
void set_adp_deviceInfo(ipp_device_info *info)
{
	setSelfDeviceSN(info->sn);
	setSelfDeviceProductID(info->product_id);
	setSelfDeviceType(info->device_type);
}

//发送Event
void send_adp_event(ipp_protocol *eve)
{
	g_cloud_send_event_cb(getSelfDeviceSN(), getSelfDeviceType(), eve->buffer_size, eve->buffer);
}
