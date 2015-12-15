/*
 * device_cloud.c
 *
 *  Created on: 2015年9月27日
 *      Author: jiao
 */
#include "IPPDeviceFunction.h"
#include <base.h>
#include <stdint.h>
#include <qcom_misc.h>
#include <qcom_system.h>
#include <qcom_utils.h>
#include <qcom_common.h>
#include <qcom_nvram.h>
#include "jdef.h"

extern DevInfo dev_test;

void localReportThread(ULONG which_thread)
{
	dev_upload_netowrk_architech(&dev_test);

}
