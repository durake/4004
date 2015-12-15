#include "base.h"
#include "stdint.h"
#include "qcom_system.h"
#include "qcom_utils.h"
#include "qcom_common.h"
#include "qcom_gpio.h"
#include "qcom_uart.h"
#include "qcom_mem.h"
#include "select_api.h"
#include "qcom_wlan.h"
#include "qcom_internal.h"
#include "util.h"
#include"qcom_network.h"
#include"SelfMethodSignal.h"
#include"SelfDeviceInfo.h"
#include"CloudMessage.h"
#include"ipp_adapter.h"

extern char	FG_SN[24];				//snÐòÁÐºÅ
extern char	FG_NAME[10];			//êÇ³Æ
extern uint8_t DEVICE_ID;


void IPPThin_main()
{

//	char my_mac[18] = "\0";

//	int chSnSize = 0;
//	char* pTmp = NULL;

//	InitDevInfo();
//	chSnSize = sizeof(FG_SN)+1;
//	pTmp = mem_calloc(1,chSnSize);
//	strncpy(pTmp,FG_SN,chSnSize-1);
//	setSelfDeviceSN(pTmp);
//	mem_free(pTmp);

	
//	chSnSize = sizeof(FG_NAME)+1;
//	pTmp = mem_calloc(1,chSnSize);
//	strncpy(pTmp,FG_NAME,chSnSize-1);
//	setSelfDeviceName(pTmp);
//	mem_free(pTmp);
	//chSnSize = sizeof(my_mac)+1;
	//pTmp = mem_calloc(1,chSnSize);
//	GetMacAddress(DEVICE_ID,my_mac);
//	my_mac[17] = '\0';
 //	setSelfDeviceMac(my_mac);
//	setSelfDeviceProductID("ffyycc");
	InitDevInfo();
	adp_init();

}
