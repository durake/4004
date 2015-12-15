#ifndef COMMON_H_
#define COMMON_H_



#ifdef __cplusplus
extern "C" {
#endif
#include "ReceiveMessage.h"



/*	//below for cloud message
	typedef struct _MSGS_Account{
		char*  id;	//账户名
		char* uiName;		//显示名
	}CH_MSGS_Account, *PCH_MSGS_Account;

	typedef struct _MSGS_Result{
		int	code;   //结果状态码
		char*  reason;	//	原因
	}CH_MSGS_Result, *PCH_MSGS_Result;


	//接收结构体
	typedef struct _ReceiveMessage{
		char*				messageId;      				//消息ID
		char*               content;             // 消息内容
		char*                 title;                // 标题
		char*                 description;          // 描述
		CH_MSGS_Account*      from;                 // 发送者账号
		char*                 fromDomain;           // 发送者域ID
		char*                 toDomain;             // 接收者域ID
		int                   passthrough;          // 传输方式，1表示透传消息，2表示通知栏消息
		int                   notifyType;     		//		提醒方式。type的值可以是DEFAULT_ALL或者以下其他几种的OR组合： DEFAULT_ALL = -1; DEFAULT_SOUND = 1;   // 使用默认提示音提示 DEFAULT_VIBRATE = 2;   // 使用默认震动提示 DEFAULT_LIGHTS = 4;    // 使用默认led灯光提示
		CH_MSGS_Account*      onlineList;     		//		在线用户列表
		int                   onlineList_size;  //     在线用户列表大小
		int                   heart;            //     心跳间隔，单位秒
		int                   flag;             //     标识该消息是1普通消息，还是2在线列表的消息，如果是在线列表，返回业务系统帐号(用, 分隔), 缺省为1，可选
		CH_MSGS_Result*       error;            //       结果
		//_ReceiveMessage()
		//{
		//	passthrough = 1;
		//	notifyType = -1;
		//	heart = 0.01;
		//	flag = 1;
		//}

	}CH_MSGS_ReceiveMessage, *PCH_MSGS_ReceiveMessage;

	//发送结构体
	typedef struct _MSGS_SendMessage{
		CH_MSGS_Account*		target;       // 		接收消息的账号集合
		int                 target_size;        // 账号集合大小
		char*               content;            // 消息内容
		CH_MSGS_Account*    from;                //发送者账号
		char*               fromDomain;         // 发送者域ID
		char*               toDomain;          //  接收者域ID
		char*               title;             //  标题
		char*               description;       //  描述
		int                 passthrough;       //  传输方式，1表示透传消息，2表示通知栏消息
		int                 notifyType;        //  提醒方式。type的值可以是DEFAULT_ALL或者以下其他几种的OR组合：
												//	 DEFAULT_ALL = -1;
												//	DEFAULT_SOUND = 1;   // 使用默认提示音提示                   
												//	DEFAULT_VIBRATE = 2;   // 使用默认震动提示                    
												//	DEFAULT_LIGHTS = 4;    // 使用默认led灯光提示                 
		CH_MSGS_Account*    userRange;        // 用户在线列表的好友集合
		int                 userRange_size;   // 用户在线列表的好友集合
		unsigned char             isEncrypt;//        是否对接收方收到的内容加密
												//1 - 是
												//0 - 否
		int                 heart;            //心跳间隔，单位秒
		int                 timeTolive;                                     //   离线消息保存时间，单位秒
		char*               version;                                         //  版本号
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

	//库函数

/*	typedef void (*QC4004_CH_MSGS_IReceiver_t)(CH_MSGS_ReceiveMessage* msg);
	typedef void (*QC4004_CH_MSGS_IConnection_t)(int ConStatus);
	void CH_MSGS_Init(char* userid,char* httpid, int httpport, QC4004_CH_MSGS_IReceiver_t  CH_MSGS_IReceiver_t_CB, QC4004_CH_MSGS_IConnection_t  CH_MSGS_IConnection_t);
	int CH_MSGS_Send(CH_MSGS_Message* msg, CH_MSGS_Result* result);*/
	




#ifdef __cplusplus
}
#endif
#endif

