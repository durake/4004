/* 
 * ============================================================================
 * Filename    : uart.c
 * Author      : huangbin
 * Created     : 2014-10-31
 * Description : 
 * 
 * ============================================================================
 */
#include "ipp_stub_def.h"
#include "./jdef.h"
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
#include"./SelfService/SelfDeviceInfo.h"
#include"CloudMessage.h"

//#include"./IPPThinCloudManager/CloudMessage.h"


#define DELAY_1_SECOND	1000
#define DELAY_BETWEEN_PROECT	10
/******************************************************
 *                    Constants
 ******************************************************/
extern DevInfo dev_test;
FridgeNVM_read_write_t FridgeNVM;
char	FG_SN[24];				//snÐòÁÐºÅ
char	FG_NAME[10];			//êÇ³Æ
uint8_t DEVICE_ID = 0;
extern ipp_deviceId;


extern void IPPThin_main();


/******************************************************
 *               Function Declarations
 ******************************************************/
void UartComThread(ULONG which_thread);
void StateTimeThread(ULONG which_thread);
void wifi_init();
void devReg(DevInfo *devList);
void dev_update(DevInfo *devList, const char *ver);
void dev_upload_status(char *info, const char *sn);
void dev_getuserlist(const char *deviceID);
void dev_clear(const char *deviceID);
//void httpc_method();
//void test_connect();
/*
void wifi_init()
{
	uint8_t my_mac[6];
	GetMacAddress(DEVICE_ID,my_mac);
	EnableSoftAP(DEVICE_ID, FG_SN, 0, FridgeNVM.appasswd, 100);   	
	return;
}
*/
void nvm_init()
{
	char IDf[24] = { 'S','M','A','R','T','-','F','r','i','d','g','e',
									 '-','1','1','1','1','1','1','1','1','2','3','4' };
	char FridgeName[10] = { 'C','H','F','R','G','-','1','2','3','4' };

	init_all_dct();
	SetAirconditionSN(IDf,FridgeName);
	
	memset(&FridgeNVM,0,sizeof(FridgeNVM));	
	load_dct_config();
	print_param_config_dct();
	return;
}

void UartComThread(ULONG which_thread)
{
	//nvm_init();
	//wifi_init();
	while (1)
	{
			qcom_thread_msleep(10000);
			//A_PRINTF("\r\nUartComThread Alive!!!");
	}
}
/*****************************************************************/
/*****************************************************************/
int g_uart_fd_com = -1;
int g_uart_fd_dbg = -1;

void uart_set_baudrate(void)
{

    qcom_uart_para dbg_uart_cfg,com_uart_cfg;

    dbg_uart_cfg.BaudRate=     115200;
    dbg_uart_cfg.number=       8;
    dbg_uart_cfg.StopBits =    1;
    dbg_uart_cfg.parity =      0;
    dbg_uart_cfg.FlowControl = 0;

    com_uart_cfg.BaudRate=     9600;
    com_uart_cfg.number=       8;
    com_uart_cfg.StopBits =    1;
    com_uart_cfg.parity =      0;
    com_uart_cfg.FlowControl = 0;

	//Uart_Rx_Pin_Set(2,10);         
	//Uart_Tx_Pin_Set(7,11);
	//qcom_uart_rx_pin_set(10,6); 
	//qcom_uart_tx_pin_set(11,7); 
	//qcom_uart_init();
	//g_uart_fd_dbg = qcom_uart_open((A_CHAR *)"UART0");
	//g_uart_fd_com = qcom_uart_open((A_CHAR *)"UART1");
	//qcom_set_uart_config((A_CHAR *)"UART1",&dbg_uart_cfg);
    qcom_set_uart_config((A_CHAR *)"UART0",&com_uart_cfg);

}

/*****************************************************************/
/*****************************************************************/
void StateTimeThread(ULONG which_thread)
{
	extern void user_pre_init();
	int8_t Seconds = 0;
	int8_t Minutes = 0;
	int8_t Hours = 0;
	int8_t Day = 0;
	int8_t count = 0;
//	uint8_t set_flag=0;
	int ii = 10;
	int net_abled_flag = 0;
//	char chIP[16] = "\0";
//	A_UINT32 Address = 0,Submask = 0,Gateway = 0;


	
	user_pre_init();
	qcom_enable_print(1);
	qcom_thread_msleep(5000);
	qcom_uart_rx_pin_set(6, 10);
  	qcom_uart_tx_pin_set(7, 11);	
	qcom_uart_init();
	uart_set_baudrate();
//	nvm_init();
	wifi_init();

	IPPThin_main();
	


	while(ii--)
	{
		if(qcom_ping(inet_addr("202.108.22.5"),32) == A_OK)
		{
			printf("\r\nping succeed with 32 bytes\r\n");
			net_abled_flag = 1;
			break;
		}else{
			printf("\r\nping failed\r\n");	
		     }
		qcom_thread_msleep(1000);
	}

//	qcom_ip_address_get(DEVICE_ID,&Address,&Submask,&Gateway);
//	A_PRINTF("Address = %u\n", Address);	
//	sprintf(chIP,"%u.%u.%u.%u",((Address)>>24)&0xff,((Address)>>16)&0xff,((Address)>>8)&0xff,(Address)&0xff);
//	A_PRINTF("chIP = %s\n", chIP);	
//	setSelfDeviceIP(chIP);

	if(net_abled_flag = 1)
	{
	//xmppMessageInit();
	
	devReg(&dev_test);
	dev_update(&dev_test, "ver2.1");
	dev_upload_status("hello", ipp_deviceId);
	dev_getuserlist(ipp_deviceId);
	//dev_clear("QCM4004");
	}
	  
	while(1)
	{
		if (Seconds < 60)
		{
			qcom_thread_msleep(DELAY_1_SECOND);
			if (count % 5 == 0) {
				int left_mem = qcom_mem_heap_get_free_size();
				A_PRINTF("\r\nTime=%dDay %d:%d:%d  mem_left=%d\r\n",Day,Hours,Minutes,Seconds,left_mem);
				A_PRINTF("\r\nFridgeNVM.colddoorclosedsec=%d\r\n",FridgeNVM.colddoorclosedsec);
				//load_dct_config();
				//print_param_config_dct();
				count = 0;
			}
			Seconds ++;
			count ++;
		}

		if (Seconds >= 60)
		{
			Seconds = 0;
			Minutes ++;
		}

		if (Minutes >= 60)
		{
			Seconds = 0;
			Minutes = 0;
			Hours ++;
		}

		if (Hours >= 24)
		{
			Seconds = 0;
			Minutes = 0;
			Hours = 0;
			Day ++;
		}
	}

}


