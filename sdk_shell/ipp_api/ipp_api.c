#include "ipp_defines.h"
#include "ipp_api.h"
#include "ipp_adapter.h"
#include "SelfDeviceInfo.h"

BOOL ipp_init()
{
	adp_init();
	return TRUE;
}

void ipp_deinit()
{

}

void set_device_info(ipp_device_profile *profile)
{
	ipp_device_info info;
	memcpy(info.sn, profile->guid, sizeof(profile->guid));
	memcpy(info.product_id, profile->product_id, sizeof(profile->product_id));
	info.device_type = profile->device_type;
	set_adp_deviceInfo(&info);
}

void send_event(ipp_protocol *eve)
{
	send_adp_event(eve);
}

void reg_message_handler(message_handler handler)
{
	reg_adp_message_handler(handler);
}
