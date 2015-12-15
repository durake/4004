/******************************************************************************

版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

******************************************************************************
文 件 名   : CloudMessage.h
版 本 号   : 初稿
作    者   : Fiona
生成日期   : 2015年8月8日
最近修改   :
功能描述   :
函数列表   :
修改历史   :
1.日    期   :
作    者   :
修改内容   : 创建文件
******************************************************************************/
#ifndef CLOUDMESSAGE_H_
#define CLOUDMESSAGE_H_



#ifdef __cplusplus
extern "C" {
#endif

#include "IPPUserList.h"
#include "ipp_defines.h"
#include"common.h"


typedef unsigned char BYTE;

#define SERVICE_ID_LIST			0x20000003


typedef enum {
	RESULT_OK = 0, // 成功

	// IPP Device
	ERROR_IPP_DEVICE_SERVICE_REQUEST_HANDLER_IS_NULL = -1001, // 服务处理器为空
	ERROR_IPP_DEVICE_DO_NOT_SURPPORT_SERVICE_ID = -1002, // 不支持服务ID
	ERROR_IPP_DEVICE_LOCAL_SERVICE_ACCESS_SERVICE = -1003, // 访问本地服务出错

	// IPP Protocol Buffer
	ERROR_IPP_PROTOCOL_BUFFER_OUT_VAL_IS_NULL = -2001, // 解析结果指针为空
	ERROR_IPP_PROTOCOL_BUFFER_BUFFER_IS_NULL = -2002, // buffer为空
	ERROR_IPP_PROTOCOL_BUFFER_BUFFER_NOT_ENOUGH = -2003, // buffer空间不足
	ERROR_IPP_PROTOCOL_BUFFER_IN_VAL_IS_NULL = -2004, // 封装数据指针为空

	// IPP Cloud Message Manager
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE = -3001, // 解析数据
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_SERVICE_REQUEST_TYPE = -3002, // 服务请求类型
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_SERVICE_REQUEST_HANDLER_IS_NULL = -3003, // 服务处理器为空
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_RESPONSE_IS_NULL = -3004 // 反馈为空
} emXmppErrorCode;

typedef enum{

	TYPE_EVENT = 1,
	TYPE_REQUEST = 2,
	TYPE_RESPONSE = 3,
	TYPE_ERROR = 4
}emXmppMsgType;

typedef enum{

	EVENT_UPLINE = 0x100001,
	EVENT_OFFLINE = 0x100002

}emEventType;


//below for cloud message


typedef struct _XmppRequest{
	char* pchDeviceGuid;
	char chType;
	int nServiceId;
	BYTE* puchRequest;
	int nReqBuffSize;
}XmppRequest;
typedef struct _stXmppDataList{

	int nListSize;
	unsigned char* chXmppDataList;
}stXmppDataList;

typedef struct _XmppOnlineUser{
	Node* stUserList;
	int nUserSize;
}XmppOnlineUser;



//below 函数下层库提供

void CH_MSGS_IReceiver_t(CH_MSGS_ReceiveMessage* msg);
void CH_MSGS_IConnection_t(int ConStatus);



//需要的函数
/***
**  函数名：ConvertASCstring
 ** 功能：对指定的内存中数据经ascii转换成A-Z范围数据
 ** 入参：pchRawData	待转换数据；nRawLen带转换数据长度；
 ** 出参:    pstResponseDatalist存储转换后数据和长度?
 **返回值：	无
***/
void ConvertASCstring(char* pchRawData, int nRawLen, stXmppDataList* pstResponseDatalist);
/***
**  函数名：KeepXmppOnlineList
 ** 功能：维护xmpp用户端账号信息
 ** 入参:    msg接收到的消息
 ** 出参:    无
 **返回值：无
***/
void KeepXmppOnlineList(CH_MSGS_ReceiveMessage* msg);
/***
**  函数名：XmppMessageHandle
 ** 功能：处理接收到的xmpp消息
 ** 入参:    msg接收到的消息
 ** 出参:    无
 **返回值：无
***/
void XmppMessageHandle(CH_MSGS_ReceiveMessage* msg);
/***
**  函数名：getXmppMsgContext
 ** 功能：解析接收到的消息内容
 ** 入参:    pchMsgContent接收到的消息内容
 ** 出参:    pstDataList解析后的内容和长度信息
 **返回值：解析结果状态
***/
int getXmppMsgContext(const char* pchMsgContent, stXmppDataList* pstDataList);
/***
**  函数名：getXmppDataStruct
 ** 功能：对解析后的内容根据实际应用定义再次解析
 ** 入参:    pstXmppRecDataList接收消息经解析后的内容
 ** 出参:    pstXmppRequestData根据实际应用定义解析后的内容结构体
 **返回值：解析状态
***/
int getXmppDataStruct(stXmppDataList* pstXmppRecDataList, XmppRequest* pstXmppRequestData);
/***
**  函数名：handleServiceRequest
 ** 功能：处理实际接收消息
 ** 入参:   pstRequestData实际接收到的消息内容结构体
 ** 出参:    pstResponseDatalist对消息处理后的结果返回数据和长度
 **返回值：处理结果
***/
int handleServiceRequest(XmppRequest* pstRequestData, stXmppDataList* pstResponseDatalist);
/***
**  函数名：formXmppSendMsg
 ** 功能：组织打包发送消息结构
 ** 入参:    pstrRecMsg该次发送消息对应的接收消息
 ** 出参:    pstXmppSendMessage待发送的消息结构
 **返回值：无
***/
void formXmppSendMsg(CH_MSGS_ReceiveMessage* pstrRecMsg, CH_MSGS_Message* pstXmppSendMessage, stXmppDataList* pstResponseDatalist);
/***
**  函数名：formSendMsgContent
 ** 功能：打包待发送消息内容
 ** 入参:    device_guid设备guid；type消息类型; service_id服务id； pchContent消息内容;nContentSize内容长度
 ** 出参:    pstResponseDatalist打包组织完成的待发送消息内容
 **返回值：无
***/
void formSendMsgContent(char* device_guid, char type, int service_id, char* pchContent, int nContentSize, stXmppDataList* pstResponseDatalist);
/***
**  函数名：xmppMessageInit
 ** 功能：xmpp消息云模块相关初始化
 ** 入参:    无
 ** 出参:    无
 **返回值：无
***/
void xmppMessageInit(void);
/***
**  函数名：xmppMessageDeinit
 ** 功能：xmpp消息云退出时处理
 ** 入参:    无
 ** 出参:    无
 **返回值：无
***/
void xmppMessageDeinit(void);
/***
**  函数名：handleXmppSendResult
 ** 功能：根据发送xmpp消息返回结果处理
 ** 入参:    pResult返回结果
 ** 出参:    无
 **返回值：无
***/
void handleXmppSendResult(CH_MSGS_Result* pResult);

/***
**  函数名：GetUserListHead
 ** 功能：获取在线用户列表信息
 ** 入参:    无
 ** 出参:    无
 **返回值：在线用户列表信息
***/
XmppOnlineUser* GetUserListHead();


void XmppUserListInit();
extern Node* listOnlineUser;
extern BOOL bXmppConnectedFlag;




#ifdef __cplusplus
}
#endif
#endif

