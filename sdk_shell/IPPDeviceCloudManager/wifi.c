//时间线程while循环前面调用wifi_init(),ssid传路由器ssid,passwd传路由器密码

#include "base.h"
#include "stdint.h"
#include "qcom_misc.h"
#include "qcom_system.h"
#include "qcom_utils.h"
#include "qcom_common.h"
#include "qcom_nvram.h"
#include "qcom_wlan.h"
#include "qcom_internal.h"
#include "qcom_sec.h"

extern uint8_t DEVICE_ID;
//const char* ssid = "CHGW_800000";
const char* ssid = "QCA4004_TEST";//"KCZX-WLAN";
//const char* passwd = "00000000";
const char* passwd = "QCA4004_TEST";//"kczx2015";

void WiFiCallback(A_UINT8 device_id,A_INT32 value)
{

	if(value == 1)
		printf("reconnect succeess\r\n");
	else if(value == 0)
		printf("reconnetc failed\r\n");

}


int WifiScan(uint8_t qcom_DeviceId,const char* ssid,int *secType,int *cipherType)
{
	
    QCOM_BSS_SCAN_INFO *info;
    A_UINT16 count;
    uint8_t findssidflag = 0;

    /*Set the SSID*/
    qcom_set_ssid(qcom_DeviceId, ssid);
    /*Start scan*/

    qcom_start_scan_params_t scanParams;
    scanParams.forceFgScan  = 1;
    scanParams.scanType     = WMI_LONG_SCAN;
    scanParams.numChannels  = 0;
    scanParams.forceScanIntervalInMs = 1;
    scanParams.homeDwellTimeInMs = 0;       
    qcom_set_scan(qcom_DeviceId, &scanParams);

    /*Get scan results*/
    if(qcom_get_scan(qcom_DeviceId, &info, &count) == 0){ 
      int i,j;

      tx_thread_sleep(1000);
      for (i = 0; i < count; i++)
      {
        printf("ssid = ");
        for(j = 0;j < info[i].ssid_len;j++)
        {
            printf("%c",info[i].ssid[j]);
        }
        printf("\n");
        printf("bssid = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",info[i].bssid[0],info[i].bssid[1],info[i].bssid[2],info[i].bssid[3],info[i].bssid[4],info[i].bssid[5]);
        printf("channel = %d\n",info[i].channel);
        printf("rssi = %d\n",info[i].rssi);
        findssidflag = 1;
        if(info[i].security_enabled)
        {
        	 if (info[i].rsn_auth) {
              *secType = 0;//WPA2
              if (info[i].rsn_cipher & ATH_CIPHER_TYPE_CCMP) {
                  *cipherType = 0;//AES
              } else if (info[i].rsn_cipher & ATH_CIPHER_TYPE_TKIP) {
                  *cipherType = 1;//TKIP
              }
          } else if (info[i].wpa_auth) {
              *secType = 1;//WPA
              if (info[i].wpa_cipher & ATH_CIPHER_TYPE_CCMP) {
                  *cipherType = 0;//AES
              } else if (info[i].wpa_cipher & ATH_CIPHER_TYPE_TKIP) {
                  *cipherType = 1;//TKIP
              }
          } else {
              *secType = 2;//WEP
              *cipherType = 2;//WEP
          }
		    }else{
	        printf("NONE! \n");
		    }
    	}
    }
    
		//mem_free(info);//do not free
    if(findssidflag == 0){
	  	A_PRINTF("find %s failed,secType=%d,cipherType=%d!!\r\n",ssid,*secType,*cipherType);
	  	return -1;
	  }else if(findssidflag == 1){
	  	A_PRINTF("find %s seccuss,secType=%d,cipherType=%d!!\r\n",ssid,*secType,*cipherType);
	  	return 0;
	  }
}

int ConnectWifi(uint8_t qcom_DeviceId, const char* ssid,const char* passphrase)
{
	uint8_t connected_status;
	int32_t timeout = 7000;
	int ret = -1;
	int secType;
	int cipherType;	


	ret = WifiScan(qcom_DeviceId,ssid,&secType,&cipherType);
	if(ret == -1){
		A_PRINTF("find %s failed!\r\n",ssid);
		return -2;
	}else if(ret == 0){
		A_PRINTF("find %s success,connect wifi later!!!\r\n",ssid);
	}
	
	qcom_set_connect_callback(qcom_DeviceId, WiFiCallback);
	
	qcom_op_set_mode(qcom_DeviceId, QCOM_WLAN_DEV_MODE_STATION);
  switch (secType) {
  	case 0://WPA2 PSK
  	{
  		A_PRINTF("******WPA2 PSK\r\n");
  		qcom_sec_set_auth_mode(qcom_DeviceId, WLAN_AUTH_WPA2_PSK);
      qcom_sec_set_passphrase(qcom_DeviceId, passphrase);
      break;
  	}
  	case 1://WPA PSK
  	{
  		A_PRINTF("******WPA PSK\r\n");
  		qcom_sec_set_auth_mode(qcom_DeviceId, WLAN_AUTH_WPA_PSK);
      qcom_sec_set_passphrase(qcom_DeviceId, passphrase);
      break;
  	}
  	case 2://WEP
		{
			A_PRINTF("******WEP\r\n");
      qcom_disconnect(qcom_DeviceId);
      qcom_sec_set_wepkey(qcom_DeviceId, 1, passphrase);
      qcom_sec_set_wepkey_index(qcom_DeviceId, 1);
      qcom_sec_set_wep_mode(qcom_DeviceId, 2);
      break;
		}
		default:
		{
			A_PRINTF("******default\r\n");
      break;
    }
  }
  A_PRINTF("3-----------------------------\r\n");
  switch (cipherType) {
  	case 0://AES
		{
			A_PRINTF("------AES\r\n");
			qcom_sec_set_encrypt_mode(qcom_DeviceId, WLAN_CRYPT_AES_CRYPT);
      break;
		}
  	case 1://TKIP
  	{
  		A_PRINTF("------TKIP\r\n");
  		qcom_sec_set_encrypt_mode(qcom_DeviceId, WLAN_CRYPT_TKIP_CRYPT);
      break;
  	}
  	case 2://WEP
  	{
  		A_PRINTF("------WEP\r\n");
  		qcom_sec_set_encrypt_mode(qcom_DeviceId, WLAN_CRYPT_WEP_CRYPT);
      break;
  	}
		default:
		{
			A_PRINTF("------default\r\n");
      break;
    }
  }
	
	A_PRINTF("4-----------------------------\r\n");
	qcom_set_ssid(qcom_DeviceId, ssid);
	A_PRINTF("5-----------------------------\r\n");
	qcom_commit(qcom_DeviceId);
	do {
		A_PRINTF("6-----------------------------\r\n");
    qcom_get_state(qcom_DeviceId, &connected_status);
    if (connected_status == QCOM_WLAN_LINK_STATE_CONNECTED_STATE) {
      A_PRINTF("7-----------------------------\r\n");
      break;
    }
    qcom_thread_msleep(200);
    timeout -= 200;
  } while ((connected_status != QCOM_WLAN_LINK_STATE_CONNECTED_STATE) && (timeout > 0));
	A_PRINTF("8----timeout = %d----\r\n",timeout);
	if (connected_status == QCOM_WLAN_LINK_STATE_CONNECTED_STATE) {
    A_PRINTF("9-----------------------------\r\n");
    qcom_dhcpc_enable(qcom_DeviceId, 1);  //turn on dhcp client 
    A_PRINTF("------connect success------\r\n");
    return 0;
  } else {
  	A_PRINTF("------connect failed------\r\n");
    return -1;
  }
}

void wifi_init()
{
			uint8_t connect_count = 4;

			while(connect_count > 0){
				int ret = ConnectWifi(DEVICE_ID, ssid, passwd);
				connect_count--;
				if(ret == 0){
					break;
				}
				qcom_thread_msleep(1000);
			}
	return;
}
