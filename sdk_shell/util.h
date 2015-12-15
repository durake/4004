/* 
 * ============================================================================
 * Filename    : util.h
 * Author      : huangbin
 * Created     : 2014-11-4
 * Description : 
 * 
 * ============================================================================
 */
 //�洢����
typedef struct
{
	uint8_t	mode;						//ap.sta.smartconfig��־ 0,1,2
	uint8_t	registerFlag;		//����ע����
	uint8_t	upgrade_flag;		//������־λ
	uint8_t lowstart_hour;		//��ʱ�Ƽ۸�Ϳ�ʼСʱ
	uint8_t lowstart_minute;	//��ʱ�Ƽ۸�Ϳ�ʼ����
	uint8_t lowend_hour;			//��ʱ�Ƽ۸�ͽ���Сʱ
	uint8_t lowend_minute;		//��ʱ�Ƽ۸�ͽ�������
	uint8_t	connectcnt;				//������������
	uint8_t	colddoorclosedhour;  	//�����δ��Сʱ��
	uint16_t colddoorclosedsec;		//�����δ������
	char	appasswd[64];		//Apģʽ����
	char	ssid[32];				//wifi ssid
	char	passwd[64];			//wifi passwd
} FridgeNVM_read_write_t;

void GetMacAddress(uint8_t device_id, char* mac);
int EnableSoftAP(uint8_t device_id, const char* ssid, uint8_t hidden, const char* passphrase, uint32_t timeout);
void load_dct_config();
int init_all_dct();
A_STATUS SetAirconditionSN(char* sn,char* fridgename);
A_STATUS print_param_config_dct();
