/* 
 * ============================================================================
 * Filename    : util.h
 * Author      : huangbin
 * Created     : 2014-11-4
 * Description : 
 * 
 * ============================================================================
 */
 //存储参数
typedef struct
{
	uint8_t	mode;						//ap.sta.smartconfig标志 0,1,2
	uint8_t	registerFlag;		//冰箱注册标记
	uint8_t	upgrade_flag;		//升级标志位
	uint8_t lowstart_hour;		//分时计价格低开始小时
	uint8_t lowstart_minute;	//分时计价格低开始分钟
	uint8_t lowend_hour;			//分时计价格低结束小时
	uint8_t lowend_minute;		//分时计价格低结束分钟
	uint8_t	connectcnt;				//断网重连次数
	uint8_t	colddoorclosedhour;  	//冷藏门未开小时数
	uint16_t colddoorclosedsec;		//冷藏门未开秒数
	char	appasswd[64];		//Ap模式密码
	char	ssid[32];				//wifi ssid
	char	passwd[64];			//wifi passwd
} FridgeNVM_read_write_t;

void GetMacAddress(uint8_t device_id, char* mac);
int EnableSoftAP(uint8_t device_id, const char* ssid, uint8_t hidden, const char* passphrase, uint32_t timeout);
void load_dct_config();
int init_all_dct();
A_STATUS SetAirconditionSN(char* sn,char* fridgename);
A_STATUS print_param_config_dct();
