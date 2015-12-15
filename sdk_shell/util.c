/* 
 * ============================================================================
 * Filename    : util.c
 * Author      : huangbin
 * Created     : 2014-11-4
 * Description : 
 * 
 * ============================================================================
 */
#include <base.h>
#include <stdint.h>
#include <qcom_misc.h>
#include <qcom_system.h>
#include <qcom_utils.h>
#include <qcom_common.h>
#include <qcom_nvram.h>
#include "util.h"

/*
typedef struct
{
	uint8_t	mode;					//ap.sta.smartconfig标志 0,1,2 QCA_NVM_OFFSET
	uint8_t	registerFlag;	//冰箱注册标记								 QCA_NVM_OFFSET+1
	char	upgrade_flag;		//升级标志位									 QCA_NVM_OFFSET+2
	uint8_t lowstart_hour;		//分时计价格低开始小时		 QCA_NVM_OFFSET+3
	uint8_t lowstart_minute;	//分时计价格低开始分钟		 QCA_NVM_OFFSET+4
	uint8_t lowend_hour;			//分时计价格低结束小时		 QCA_NVM_OFFSET+5
	uint8_t lowend_minute;		//分时计价格低结束分钟		 QCA_NVM_OFFSET+6
	uint8_t	connectcnt;				//断网重连次数						 QCA_NVM_OFFSET+7
	uint8_t	colddoorclosedhour;  	//冷藏门未开小时数		 QCA_NVM_OFFSET+8
	uint16_t colddoorclosedsec;		//冷藏门未开秒数			 QCA_NVM_OFFSET+9
	char	appasswd[64]	//Ap模式密码										 QCA_NVM_OFFSET+11
	char	ssid[32];			//wifi ssid											 QCA_NVM_OFFSET+75
	char	passwd[64];		//wifi passwd										 QCA_NVM_OFFSET+107
} FridgeNVM_read_write_t;
*/
#define QCA_NVM_OFFSET 0x7E000
#define QCA_NVM_OFFSET_SN 0x7F000

extern FridgeNVM_read_write_t FridgeNVM;
extern char	FG_SN[24];				//sn序列号
extern char	FG_NAME[10];			//昵称

/*
 * 获取MAC地址
 */

void GetMacAddress(uint8_t device_id, char* mac)
{
	uint8_t my_mac[6];
	if(qcom_mac_get(device_id, &my_mac) != A_OK)
	{
		A_PRINTF("Couldn't get MAC address\r\n");
		return;
	}
	sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",my_mac[0],
			my_mac[1],
			my_mac[2],
			my_mac[3],
			my_mac[4],
			my_mac[5]);
	A_PRINTF("\r\nMAC %s\r\n",mac);
}


int EnableSoftAP(uint8_t device_id, const char* ssid, uint8_t hidden, const char* passphrase, uint32_t timeout)
{
    uint8_t  connectState =0;
    WLAN_AUTH_MODE authMode = WLAN_AUTH_NONE;
    WLAN_CRYPT_TYPE encryptMode = WLAN_CRYPT_NONE;
    
    const char* pKey = "4008111666";

#define startIP 0xC0A80164
#define endIP   0xC0A801C7

#define IP_LEASE    (60 * 60 * 1000)

     A_PRINTF("AJ_EnableSoftAP\n");
    /*
     * Clear the current connection
     */
  
    /* assign the global values so WiFiCallback can tell if security is needed */
/*    AJ_WiFisecType = AJ_WIFI_SECURITY_NONE;*/
/*    AJ_WiFicipherType = AJ_WIFI_CIPHER_NONE;*/

    if (passphrase == NULL) {
        passphrase = "";
    }

    if (passphrase && strlen(passphrase) > 0) {
        authMode = WLAN_AUTH_WPA2_PSK;
        encryptMode = WLAN_CRYPT_AES_CRYPT;
        pKey = passphrase;
    }

    A_PRINTF("AJ_EnableSoftAP: ssid=%s, key=%s, auth=%d, encrypt=%d\n", ssid, pKey, authMode, encryptMode);
    connectState = 0;

    //qcom_set_connect_callback(device_id, SoftAPCallback);
    qcom_op_set_mode(device_id, QCOM_WLAN_DEV_MODE_AP);

    if (hidden) {
        qcom_ap_hidden_mode_enable(device_id, hidden);
    }

    if (authMode != WLAN_AUTH_NONE) {
        qcom_sec_set_auth_mode(device_id, authMode);
        qcom_sec_set_encrypt_mode(device_id, encryptMode);
        qcom_sec_set_passphrase(device_id, (char*) pKey);
    }

    /*
     * Set the IP range for DHCP
     */
    qcom_dhcps_set_pool(device_id, startIP, endIP, IP_LEASE);
		qcom_ap_start(device_id, (char *)ssid);
    tx_thread_sleep(10);
    connectState = 1;

/*
    do {
				qcom_get_state(qcom_DeviceId, &connected_status);
				tx_thread_sleep(100);
    } while (connected_status == QCOM_WLAN_LINK_STATE_DISCONNECTED_STATE);
*/

    return connectState;
}


A_STATUS SetAirconditionSN(char* sn,char* fridgename)
{
	if(sn == NULL)
	{
		return A_ERROR;
	}
	qcom_nvram_erase(QCA_NVM_OFFSET_SN,4096);
	memset(FG_SN,0,sizeof(FG_SN));
	strncpy(FG_SN,sn,24);
	memset(FG_NAME,0,sizeof(FG_NAME));
	strncpy(FG_NAME,fridgename,10);
	qcom_nvram_write(QCA_NVM_OFFSET_SN, FG_SN, 24);
	qcom_nvram_write(QCA_NVM_OFFSET_SN+24, FG_NAME, 10);
	return A_OK;
}

void load_dct_config()
{
	qcom_nvram_read(QCA_NVM_OFFSET, &FridgeNVM, sizeof( FridgeNVM ));
	qcom_nvram_read(QCA_NVM_OFFSET_SN, &FG_SN, sizeof( FG_SN ));
	qcom_nvram_read(QCA_NVM_OFFSET_SN+24, &FG_NAME, sizeof( FG_NAME ));
  return;
}

/*
 * 模块参数初始化，和SN一起写入
 */
int init_all_dct()
{
	qcom_nvram_erase(QCA_NVM_OFFSET,4096);
	FridgeNVM.mode = 1;
	FridgeNVM.registerFlag = 0;
	FridgeNVM.upgrade_flag = 0;
	FridgeNVM.lowstart_hour = 23;
	FridgeNVM.lowstart_minute = 30;
	FridgeNVM.lowend_hour = 8;
	FridgeNVM.lowend_minute = 30;
	FridgeNVM.connectcnt = 0;
	FridgeNVM.colddoorclosedhour = 25;
	FridgeNVM.colddoorclosedsec = 3120;
	memset(FridgeNVM.appasswd, 0, sizeof(FridgeNVM.appasswd));
	memcpy(FridgeNVM.appasswd, "4008111666", 10);
	memset(FridgeNVM.ssid, 0, sizeof(FridgeNVM.ssid));
	memcpy(FridgeNVM.ssid, "Smart-PBQC", 10);
	memset(FridgeNVM.passwd, 0, sizeof(FridgeNVM.passwd));
	memcpy(FridgeNVM.passwd, "1234567890123", 13);
	qcom_nvram_write(QCA_NVM_OFFSET, &FridgeNVM, sizeof(FridgeNVM));
	return 0;
}

/*
 * 打印应用程序DCT配置
 */
A_STATUS print_param_config_dct()
{
  A_PRINTF( "\r\nNVM Config Section---------------------------------------------\r\n");
	A_PRINTF("\r\nwifi mode = %d",FridgeNVM.mode);
	A_PRINTF("\r\nfridge registerFlag = %d",FridgeNVM.registerFlag);
	A_PRINTF("\r\nfridge upgradeFlag = %d",FridgeNVM.upgrade_flag);
	A_PRINTF("\r\nfridge name = %s",FG_NAME);
	A_PRINTF("\r\nfridge sn = %s",FG_SN);
	A_PRINTF("\r\nAP passwd = %s",FridgeNVM.appasswd);
	A_PRINTF("\r\nwifi ssid = %s",FridgeNVM.ssid);
	A_PRINTF("\r\nwifi passwd = %s",FridgeNVM.passwd);
	A_PRINTF("\r\nfridge lowstart_hour = %d",FridgeNVM.lowstart_hour);
	A_PRINTF("\r\nfridge lowstart_minute = %d",FridgeNVM.lowstart_minute);
	A_PRINTF("\r\nfridge lowend_hour = %d",FridgeNVM.lowend_hour);
	A_PRINTF("\r\nfridge lowend_minute = %d",FridgeNVM.lowend_minute);
	A_PRINTF("\r\nfridge colddoorclosedhour = %d",FridgeNVM.colddoorclosedhour);
	A_PRINTF("\r\nfridge colddoorclosedsec = %d",FridgeNVM.colddoorclosedsec);
	return A_OK;
}
