/******************************************************************************

��Ȩ���� (C), 1958-2015, �����������-�Ʒ�-���ּ�ͥ

******************************************************************************
�� �� ��   : CloudMessage.h
�� �� ��   : ����
��    ��   : Fiona
��������   : 2015��8��8��
����޸�   :
��������   :
�����б�   :
�޸���ʷ   :
1.��    ��   :
��    ��   :
�޸�����   : �����ļ�
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
	RESULT_OK = 0, // �ɹ�

	// IPP Device
	ERROR_IPP_DEVICE_SERVICE_REQUEST_HANDLER_IS_NULL = -1001, // ��������Ϊ��
	ERROR_IPP_DEVICE_DO_NOT_SURPPORT_SERVICE_ID = -1002, // ��֧�ַ���ID
	ERROR_IPP_DEVICE_LOCAL_SERVICE_ACCESS_SERVICE = -1003, // ���ʱ��ط������

	// IPP Protocol Buffer
	ERROR_IPP_PROTOCOL_BUFFER_OUT_VAL_IS_NULL = -2001, // �������ָ��Ϊ��
	ERROR_IPP_PROTOCOL_BUFFER_BUFFER_IS_NULL = -2002, // bufferΪ��
	ERROR_IPP_PROTOCOL_BUFFER_BUFFER_NOT_ENOUGH = -2003, // buffer�ռ䲻��
	ERROR_IPP_PROTOCOL_BUFFER_IN_VAL_IS_NULL = -2004, // ��װ����ָ��Ϊ��

	// IPP Cloud Message Manager
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE = -3001, // ��������
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_SERVICE_REQUEST_TYPE = -3002, // ������������
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_SERVICE_REQUEST_HANDLER_IS_NULL = -3003, // ��������Ϊ��
	ERROR_IPP_CLOUD_MESSAGE_MANAGER_RESPONSE_IS_NULL = -3004 // ����Ϊ��
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



//below �����²���ṩ

void CH_MSGS_IReceiver_t(CH_MSGS_ReceiveMessage* msg);
void CH_MSGS_IConnection_t(int ConStatus);



//��Ҫ�ĺ���
/***
**  ��������ConvertASCstring
 ** ���ܣ���ָ�����ڴ������ݾ�asciiת����A-Z��Χ����
 ** ��Σ�pchRawData	��ת�����ݣ�nRawLen��ת�����ݳ��ȣ�
 ** ����:    pstResponseDatalist�洢ת�������ݺͳ���?
 **����ֵ��	��
***/
void ConvertASCstring(char* pchRawData, int nRawLen, stXmppDataList* pstResponseDatalist);
/***
**  ��������KeepXmppOnlineList
 ** ���ܣ�ά��xmpp�û����˺���Ϣ
 ** ���:    msg���յ�����Ϣ
 ** ����:    ��
 **����ֵ����
***/
void KeepXmppOnlineList(CH_MSGS_ReceiveMessage* msg);
/***
**  ��������XmppMessageHandle
 ** ���ܣ�������յ���xmpp��Ϣ
 ** ���:    msg���յ�����Ϣ
 ** ����:    ��
 **����ֵ����
***/
void XmppMessageHandle(CH_MSGS_ReceiveMessage* msg);
/***
**  ��������getXmppMsgContext
 ** ���ܣ��������յ�����Ϣ����
 ** ���:    pchMsgContent���յ�����Ϣ����
 ** ����:    pstDataList����������ݺͳ�����Ϣ
 **����ֵ���������״̬
***/
int getXmppMsgContext(const char* pchMsgContent, stXmppDataList* pstDataList);
/***
**  ��������getXmppDataStruct
 ** ���ܣ��Խ���������ݸ���ʵ��Ӧ�ö����ٴν���
 ** ���:    pstXmppRecDataList������Ϣ�������������
 ** ����:    pstXmppRequestData����ʵ��Ӧ�ö������������ݽṹ��
 **����ֵ������״̬
***/
int getXmppDataStruct(stXmppDataList* pstXmppRecDataList, XmppRequest* pstXmppRequestData);
/***
**  ��������handleServiceRequest
 ** ���ܣ�����ʵ�ʽ�����Ϣ
 ** ���:   pstRequestDataʵ�ʽ��յ�����Ϣ���ݽṹ��
 ** ����:    pstResponseDatalist����Ϣ�����Ľ���������ݺͳ���
 **����ֵ��������
***/
int handleServiceRequest(XmppRequest* pstRequestData, stXmppDataList* pstResponseDatalist);
/***
**  ��������formXmppSendMsg
 ** ���ܣ���֯���������Ϣ�ṹ
 ** ���:    pstrRecMsg�ôη�����Ϣ��Ӧ�Ľ�����Ϣ
 ** ����:    pstXmppSendMessage�����͵���Ϣ�ṹ
 **����ֵ����
***/
void formXmppSendMsg(CH_MSGS_ReceiveMessage* pstrRecMsg, CH_MSGS_Message* pstXmppSendMessage, stXmppDataList* pstResponseDatalist);
/***
**  ��������formSendMsgContent
 ** ���ܣ������������Ϣ����
 ** ���:    device_guid�豸guid��type��Ϣ����; service_id����id�� pchContent��Ϣ����;nContentSize���ݳ���
 ** ����:    pstResponseDatalist�����֯��ɵĴ�������Ϣ����
 **����ֵ����
***/
void formSendMsgContent(char* device_guid, char type, int service_id, char* pchContent, int nContentSize, stXmppDataList* pstResponseDatalist);
/***
**  ��������xmppMessageInit
 ** ���ܣ�xmpp��Ϣ��ģ����س�ʼ��
 ** ���:    ��
 ** ����:    ��
 **����ֵ����
***/
void xmppMessageInit(void);
/***
**  ��������xmppMessageDeinit
 ** ���ܣ�xmpp��Ϣ���˳�ʱ����
 ** ���:    ��
 ** ����:    ��
 **����ֵ����
***/
void xmppMessageDeinit(void);
/***
**  ��������handleXmppSendResult
 ** ���ܣ����ݷ���xmpp��Ϣ���ؽ������
 ** ���:    pResult���ؽ��
 ** ����:    ��
 **����ֵ����
***/
void handleXmppSendResult(CH_MSGS_Result* pResult);

/***
**  ��������GetUserListHead
 ** ���ܣ���ȡ�����û��б���Ϣ
 ** ���:    ��
 ** ����:    ��
 **����ֵ�������û��б���Ϣ
***/
XmppOnlineUser* GetUserListHead();


void XmppUserListInit();
extern Node* listOnlineUser;
extern BOOL bXmppConnectedFlag;




#ifdef __cplusplus
}
#endif
#endif

