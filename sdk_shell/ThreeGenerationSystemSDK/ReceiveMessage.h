/*
 * ReceiveMessage.h
 *
 *  Created on: Oct 29, 2015
 *      Author: ghy
 */
//#include "ch_msgs_account.h"
#ifndef RECEIVEMESSAGE_H_
#define RECEIVEMESSAGE_H_

typedef struct {
	char* id;
	char* uiName;
} CH_MSGS_Account, *pCH_MSGS_Account;

typedef struct {
	int code;
	char* reason;
	char* address;
	char* authCode;
	int port;

} CH_MSGS_Result, *pCH_MSGS_Result;

typedef struct {
	char* messageId;
	char* content;
	char* title;
	char* description;
	CH_MSGS_Account* from;
	char* fromDomain;
	char* toDomain;
	int passthrough;
	int notifyType;
	CH_MSGS_Account* onlineList;
	int onlineList_size;
	int heart;
	int flag;
	CH_MSGS_Result* error;

} CH_MSGS_ReceiveMessage, *pCH_MSGS_ReceiveMessage;



//发送的消息结构体
typedef struct {
	CH_MSGS_Account* target; //接收消息的账号集合
	int target_size; //账号集合大小
	char* content; //消息内容
	CH_MSGS_Account* from; //发送者账号
	char* fromDomain; //发送者域ID
	char* toDomain; //接收者域ID
	char* title; //标题
	char* description; //描述
	int passthrough; //传输方式，1表示透传消息，2表示通知栏消息
	int notifyType; //提醒方式。type的值可以是DEFAULT_ALL或者以下其他几种的OR组合： notifytype
//	DEFAULT_ALL = -1;
//	DEFAULT_SOUND  = 1;   // 使用默认提示音提示
//	DEFAULT_VIBRATE = 2;   // 使用默认震动提示
//	DEFAULT_LIGHTS = 4;    // 使用默认led灯光提示
	CH_MSGS_Account* userRange; //用户在线列表的好友集合
	int userRange_size; //用户在线列表的好友集合
	unsigned char isEncrypt; //是否对接收方收到的内容加密 1 - 是  	0 - 否

	int heart; //心跳间隔，单位秒
	int timeTolive; //离线消息保存时间，单位秒
	char* version; //版本号

} CH_MSGS_Message, *pCH_MSGS_Message;


typedef void (*CH_MSGS_IReceiver_t_CB)(CH_MSGS_ReceiveMessage* );
typedef void (*CH_MSGS_IConnection_t_CB)(int );





#endif /* RECEIVEMESSAGE_H_ */
