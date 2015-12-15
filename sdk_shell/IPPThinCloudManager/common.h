#ifndef COMMON_H_
#define COMMON_H_



#ifdef __cplusplus
extern "C" {
#endif
#include "ReceiveMessage.h"



/*	//below for cloud message
	typedef struct _MSGS_Account{
		char*  id;	//�˻���
		char* uiName;		//��ʾ��
	}CH_MSGS_Account, *PCH_MSGS_Account;

	typedef struct _MSGS_Result{
		int	code;   //���״̬��
		char*  reason;	//	ԭ��
	}CH_MSGS_Result, *PCH_MSGS_Result;


	//���սṹ��
	typedef struct _ReceiveMessage{
		char*				messageId;      				//��ϢID
		char*               content;             // ��Ϣ����
		char*                 title;                // ����
		char*                 description;          // ����
		CH_MSGS_Account*      from;                 // �������˺�
		char*                 fromDomain;           // ��������ID
		char*                 toDomain;             // ��������ID
		int                   passthrough;          // ���䷽ʽ��1��ʾ͸����Ϣ��2��ʾ֪ͨ����Ϣ
		int                   notifyType;     		//		���ѷ�ʽ��type��ֵ������DEFAULT_ALL���������������ֵ�OR��ϣ� DEFAULT_ALL = -1; DEFAULT_SOUND = 1;   // ʹ��Ĭ����ʾ����ʾ DEFAULT_VIBRATE = 2;   // ʹ��Ĭ������ʾ DEFAULT_LIGHTS = 4;    // ʹ��Ĭ��led�ƹ���ʾ
		CH_MSGS_Account*      onlineList;     		//		�����û��б�
		int                   onlineList_size;  //     �����û��б��С
		int                   heart;            //     �����������λ��
		int                   flag;             //     ��ʶ����Ϣ��1��ͨ��Ϣ������2�����б����Ϣ������������б�����ҵ��ϵͳ�ʺ�(��, �ָ�), ȱʡΪ1����ѡ
		CH_MSGS_Result*       error;            //       ���
		//_ReceiveMessage()
		//{
		//	passthrough = 1;
		//	notifyType = -1;
		//	heart = 0.01;
		//	flag = 1;
		//}

	}CH_MSGS_ReceiveMessage, *PCH_MSGS_ReceiveMessage;

	//���ͽṹ��
	typedef struct _MSGS_SendMessage{
		CH_MSGS_Account*		target;       // 		������Ϣ���˺ż���
		int                 target_size;        // �˺ż��ϴ�С
		char*               content;            // ��Ϣ����
		CH_MSGS_Account*    from;                //�������˺�
		char*               fromDomain;         // ��������ID
		char*               toDomain;          //  ��������ID
		char*               title;             //  ����
		char*               description;       //  ����
		int                 passthrough;       //  ���䷽ʽ��1��ʾ͸����Ϣ��2��ʾ֪ͨ����Ϣ
		int                 notifyType;        //  ���ѷ�ʽ��type��ֵ������DEFAULT_ALL���������������ֵ�OR��ϣ�
												//	 DEFAULT_ALL = -1;
												//	DEFAULT_SOUND = 1;   // ʹ��Ĭ����ʾ����ʾ                   
												//	DEFAULT_VIBRATE = 2;   // ʹ��Ĭ������ʾ                    
												//	DEFAULT_LIGHTS = 4;    // ʹ��Ĭ��led�ƹ���ʾ                 
		CH_MSGS_Account*    userRange;        // �û������б�ĺ��Ѽ���
		int                 userRange_size;   // �û������б�ĺ��Ѽ���
		unsigned char             isEncrypt;//        �Ƿ�Խ��շ��յ������ݼ���
												//1 - ��
												//0 - ��
		int                 heart;            //�����������λ��
		int                 timeTolive;                                     //   ������Ϣ����ʱ�䣬��λ��
		char*               version;                                         //  �汾��
		//_MSGS_SendMessage()
		//{
		//	passthrough = 1;
		//	notifyType = -1;
		//	isEncrypt = 1;
		//	heart = 0.01;
		//	timeTolive = 0;
		//}
	}CH_MSGS_Message, *PCH_MSGS_Message;
*/


	typedef struct _XmppUserAccount{
	CH_MSGS_Account pstMsgSAccount;
	int nRelation;
	}XmppUserAccount;

	typedef enum{
		 RELATION_BIND = 1,
		 RELATION_SHARE = 2,
	}emUserRalation;

	typedef XmppUserAccount ElemType;

	//�⺯��

/*	typedef void (*QC4004_CH_MSGS_IReceiver_t)(CH_MSGS_ReceiveMessage* msg);
	typedef void (*QC4004_CH_MSGS_IConnection_t)(int ConStatus);
	void CH_MSGS_Init(char* userid,char* httpid, int httpport, QC4004_CH_MSGS_IReceiver_t  CH_MSGS_IReceiver_t_CB, QC4004_CH_MSGS_IConnection_t  CH_MSGS_IConnection_t);
	int CH_MSGS_Send(CH_MSGS_Message* msg, CH_MSGS_Result* result);*/
	




#ifdef __cplusplus
}
#endif
#endif

