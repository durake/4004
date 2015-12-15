/******************************************************************************

版权所有 (C), 1958-2015, 长虹软服中心-云服-数字家庭

******************************************************************************
文 件 名   : CloudMessage.h
版 本 号   : 初稿
作    者   : Fiona
生成日期   : 2015年9月8日
最近修改   :
功能描述   :
函数列表   :
修改历史   :
1.日    期   :
作    者   :
修改内容   : 创建文件
******************************************************************************/
#include <base.h>
#include <stdlib.h>
#include <string.h>
#include"CloudMessage.h"
#include"IPPUserList.h"
#include"SelfDeviceInfo.h"
#include "ipp_adapter.h"
#include "ipp_defines.h"
#include "ipp_util.h"
#include "ipp_stub_def.h"
#include "middleware.h"
#include "ReceiveMessage.h"

CH_MSGS_Account stLocalXmppAccount;
BOOL bXmppConnectedFlag = FALSE;
XmppOnlineUser gOnlineUser;
char* pchFromDomain = NULL;
char* pchToDomain = NULL;
const char IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL = 0x41;
char* gpMsgCloudUserId = "1006";
char* gpHttpIp = "10.9.6.34";
int gnHttppPort = 8080;
const char* pServerAccount = "fiona";






void CH_MSGS_IConnection_t(int ConStatus)
{
//	int nRet = -1;
	switch (ConStatus)
	{
		case 1:                         //1表示连接
			bXmppConnectedFlag = TRUE;
			ipp_LogI("File:%s,%s函数执行，连接成功\n",__FILE__,__func__);
			break;
		case 2:							//2表示断开
			bXmppConnectedFlag = FALSE;
			ipp_LogI("File:%s,%s函数执行，连接失败\n",__FILE__,__func__);
			break;
		case 3:							//3表示连接异常
			bXmppConnectedFlag = FALSE;
			ipp_LogI("File:%s,%s函数执行，连接异常\n",__FILE__,__func__);
//			nRet = CH_MSGS_Init(gpMsgCloudUserId,gpHttpIp,8080,CH_MSGS_IReceiver_t,CH_MSGS_IConnection_t);
//			if (nRet  < 0) {
//				ipp_LogE("File:%s,%s函数执行，初始化失败\n",__FILE__,__func__);
//			}
			
			break;
		default:
			break;
	}
}

void xmppMessageInit(void)
{
	int nRet = -1;
	stLocalXmppAccount.id = gpMsgCloudUserId;   //here need init localAccount
	stLocalXmppAccount.uiName = NULL;
	nRet = CH_MSGS_Init(gpMsgCloudUserId,gpHttpIp,8080,CH_MSGS_IReceiver_t,CH_MSGS_IConnection_t);
	if (nRet  < 0) {
		ipp_LogE("%s函数执行，初始化失败\n",__func__);
	}
	else
	{
		ipp_LogI("%s函数执行，初始化成功\n",__func__);
	}
}
void XmppUserListInit()
{
	gOnlineUser.nUserSize = 0;
	initList(&gOnlineUser.stUserList);
}

XmppOnlineUser* GetUserListHead()
{
	return &gOnlineUser;
}

void xmppMessageDeinit(void)
{
	if (gOnlineUser.stUserList)
	{
		clearList(&gOnlineUser.stUserList);
		gOnlineUser.nUserSize = 0;

	}
	FREE_POINTER(pchToDomain);
	FREE_POINTER(pchFromDomain);
}


void CH_MSGS_IReceiver_t(CH_MSGS_ReceiveMessage* msg)
{
	int nLen = 0;
	ipp_LogI("%s函数执行\n",__func__);
		
		
	if (!strcmp(msg->from->id,pServerAccount))
	{
		if((msg->content != NULL))
		{
			ipp_LogI("%s函数执行,userid keep\n",__func__);
			KeepXmppOnlineList(msg);
		}

		//CH_MSGS_Send();
	}
	else
	{
		if(msg->content != NULL)
		{
			if(msg->fromDomain)
			{
				FREE_POINTER(pchToDomain);
				nLen = strlen(msg->fromDomain);
				pchToDomain = calloc(1, nLen + 1);
				strcpy(pchToDomain, msg->fromDomain);
			}
			if(msg->toDomain)
			{
				FREE_POINTER(pchFromDomain);
				nLen = strlen(msg->toDomain);
				pchFromDomain = calloc(1, nLen + 1);
				strcpy(pchFromDomain, msg->toDomain);
			}
			XmppMessageHandle(msg);
		}
	}
	FREE_POINTER(msg->messageId);
	FREE_POINTER(msg->title);
	FREE_POINTER(msg->description);
	FREE_POINTER(msg->from->id);
	FREE_POINTER(msg->from->uiName);
	FREE_POINTER(msg->from);
	FREE_POINTER(msg->content);
	FREE_POINTER(msg->onlineList);
	FREE_POINTER(msg->fromDomain);
	FREE_POINTER(msg->toDomain);
	FREE_POINTER(msg->error);
	

}


void KeepXmppOnlineList(CH_MSGS_ReceiveMessage* msg)
{
	ElemType*  pUserAccount = NULL;
	ElemType* pUserAct = NULL;
	char* pStr1 = NULL;
	char* pStr2 = NULL;
	int nPos = 0;
	int nLen = 0;
	//start below maybe need
	stXmppDataList  stXmppRecDataList;//提取存储xmpp原始数据
	int nErrorCode;
	stXmppRecDataList.chXmppDataList = NULL;
	nErrorCode = getXmppMsgContext(msg->content, &stXmppRecDataList);
	if (nErrorCode != RESULT_OK)
	{
		return;
	}
	//end maybe need
	if(msg->content != NULL)
	{	
		nLen = strlen(msg->content);
		pStr1 = strstr(msg->content,"msg");
		if(pStr1 != NULL)
		{
			pStr2 = strstr(pStr1,"adduser");
			if(pStr2 != NULL)
			{
				pStr1 = strstr(pStr2,"devid");
				if(pStr1 != NULL)
				{
					pStr2 = strstr(pStr1,getSelfDeviceSN());
					while(pStr2 != NULL)
					{
						pStr1 = strstr(pStr2,"userid");
						if((pStr1 !=NULL)&&(pStr1 - msg->content + 9) < nLen)
						{
							pStr2 = strstr(pStr1+9,",");
							if(pStr2 != NULL)
							{
								pUserAccount = calloc(1,sizeof(ElemType));
								pUserAccount->pstMsgSAccount.id = calloc(pStr2-pStr1-9, sizeof(char));
								memcpy(pUserAccount->pstMsgSAccount.id,pStr1+9,pStr2-pStr1-9-1);
								pStr1 = strstr(pStr2,"bind");
								if(pStr1 != NULL)
								{
									pUserAct = getSpecElementVal(GetUserListHead()->stUserList,RELATION_BIND,&nPos);
									if(pUserAct == NULL)
									{
										pUserAccount->nRelation = RELATION_BIND;
					 					gOnlineUser.nUserSize += insertLastList(&GetUserListHead()->stUserList, pUserAccount);
										ipp_LogI("%s函数执行，insert bind userid success\n",__func__);
									}
									pStr2 = pStr1;
								}
								else
								{
									pStr1 = strstr(pStr2,"share");
									if(pStr1 != NULL)
									{
										pUserAccount->nRelation = RELATION_SHARE;
										gOnlineUser.nUserSize += FindInsertList(&GetUserListHead()->stUserList,pUserAccount,1);
										ipp_LogI("%s函数执行，insert share userid success\n",__func__);
									}
									pStr2 = pStr1;
								}
								FREE_POINTER(pUserAccount);
								FREE_POINTER(pUserAccount->pstMsgSAccount.id);	
							}
						}
						else
						{
							pStr2 = pStr1;
						}
						
					}
					
				}
			}
			else
			{
				pStr2 = strstr(pStr1,"deleteuser");
				if(pStr2 != NULL)
				{
					pStr1 = strstr(pStr2,"devid");
					if(pStr1 != NULL)
					{
						pStr2 = strstr(pStr1,getSelfDeviceSN());
						while(pStr2 != NULL)
						{
							pStr1 = strstr(pStr2,"userid");
							if((pStr1 !=NULL)&&(pStr1 - msg->content + 9) < nLen)
							{
								pStr2 = strstr(pStr1+9,",");
								if(pStr2 != NULL)
								{
									pUserAccount = calloc(1,sizeof(ElemType));
									pUserAccount->pstMsgSAccount.id = calloc(pStr2-pStr1-9, sizeof(char));
									memcpy(pUserAccount->pstMsgSAccount.id,pStr1+9,pStr2-pStr1-9-1);
									pStr1 = strstr(pStr2,"bind");
									if(pStr1 != NULL)
									{
										pUserAccount->nRelation = RELATION_BIND;
										pUserAct = getElemAddr(GetUserListHead()->stUserList,pUserAccount,&nPos);
										if(pUserAct != NULL)
										{
											clearList(&gOnlineUser.stUserList);
											gOnlineUser.nUserSize = 0;
											ipp_LogI("%s函数执行，unbind userid success,clear all userid\n",__func__);
										}
										pStr2 = pStr1;
									}
									else
									{
										pStr1 = strstr(pStr2,"share");
										if(pStr1 != NULL)
										{
											pUserAccount->nRelation = RELATION_SHARE;
											if(DelListElem(GetUserListHead()->stUserList,pUserAccount)  == TRUE)
											{
												gOnlineUser.nUserSize -= 1;
												ipp_LogI("%s函数执行，remove share userid success\n",__func__);
											}
										}
										pStr2 = pStr1;
									}
									FREE_POINTER(pUserAccount);
									FREE_POINTER(pUserAccount->pstMsgSAccount.id);
								}
							}
							else
							{
								pStr2 = pStr1;
							}
						}
						
					}
				}
			}
		}
	}
}

void XmppMessageHandle(CH_MSGS_ReceiveMessage* msg)
{
	int ret = -1;
	int nErrorCode;
	stXmppDataList  stXmppRecDataList;//提取存储xmpp原始数据
	XmppRequest stXmppRequestData;//提取解析xmpp接收数据
	stXmppDataList stXmppResponseDatalist;//回复xmpp待发送处理后数据
	CH_MSGS_Message stXmppSendMessage;//xmpp待发送的的消息
	CH_MSGS_Result* pResult = NULL;

	stXmppRecDataList.chXmppDataList = NULL;
	stXmppRequestData.pchDeviceGuid = NULL;
	stXmppRequestData.puchRequest = NULL;
	stXmppResponseDatalist.chXmppDataList = NULL;

	pResult = calloc(1,sizeof(CH_MSGS_Result));
	nErrorCode = getXmppMsgContext(msg->content, &stXmppRecDataList);
	if (nErrorCode != RESULT_OK)
	{
		ipp_LogE("%s:getXmppMsgContext函数执行 error:%d\n",__func__,nErrorCode);
		goto error;
	}

	
	nErrorCode = getXmppDataStruct(&stXmppRecDataList, &stXmppRequestData);
	if (nErrorCode != RESULT_OK)
	{
		ipp_LogE("%s:getXmppDataStruct函数执行 error:%d\n",__func__,nErrorCode);
		goto error;
	}
	nErrorCode = handleServiceRequest(&stXmppRequestData, &stXmppResponseDatalist);
	if (nErrorCode != RESULT_OK)
	{
		ipp_LogE("%s:handleServiceRequest函数执行 error:%d\n",__func__,nErrorCode);
		goto error;
	}
	if (stXmppResponseDatalist.chXmppDataList == NULL){
		nErrorCode = ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE;
		ipp_LogE("%s:stXmppResponseDatalist is null \n",__func__);
		goto error;
	}
	formXmppSendMsg(msg, &stXmppSendMessage, &stXmppResponseDatalist);
	
	ret = CH_MSGS_Send(&stXmppSendMessage, pResult);
	if (ret)
	{
		handleXmppSendResult(pResult);
	}
	goto end;


error:

	formSendMsgContent(stXmppRequestData.pchDeviceGuid, TYPE_ERROR, stXmppRequestData.nServiceId, (char*)&nErrorCode, 4, &stXmppResponseDatalist);
	formXmppSendMsg(msg, &stXmppSendMessage, &stXmppResponseDatalist);
	CH_MSGS_Send(&stXmppSendMessage, pResult);

end:

	if (stXmppResponseDatalist.chXmppDataList != NULL) {
		free(stXmppResponseDatalist.chXmppDataList);
		stXmppResponseDatalist.chXmppDataList = NULL;
		stXmppSendMessage.content = NULL;
	}
	FREE_POINTER(stXmppRequestData.pchDeviceGuid);
	FREE_POINTER(stXmppRequestData.puchRequest);
	FREE_POINTER(stXmppRecDataList.chXmppDataList);
   //针对发送消息，只有在此处回复发送才执行
  
   if (stXmppSendMessage.target)
   {
    	FREE_POINTER(stXmppSendMessage.target->id);
		FREE_POINTER(stXmppSendMessage.target->uiName);
	   	free(stXmppSendMessage.target);
	  	stXmppSendMessage.target = NULL;
   }
   FREE_POINTER(stXmppSendMessage.title);
   FREE_POINTER(stXmppSendMessage.description);
   FREE_POINTER(stXmppSendMessage.userRange);
   FREE_POINTER(stXmppSendMessage.version);

   FREE_POINTER(pResult->reason);	
   FREE_POINTER(pResult);

}
int getXmppMsgContext(const char* pchMsgContent, stXmppDataList* pstDataList)
{
	int nMsgLen;
	char high_half_byte;
	char low_half_byte;
	unsigned char byte_value;
	int i = 0;

	if (NULL == pchMsgContent) {
		return ERROR_IPP_PROTOCOL_BUFFER_BUFFER_IS_NULL;
	}
	nMsgLen = strlen(pchMsgContent);
	if ((nMsgLen % 2 != 0)) {
		return ERROR_IPP_PROTOCOL_BUFFER_OUT_VAL_IS_NULL;
	}
	int data_size = nMsgLen / 2;
	if (pstDataList->chXmppDataList)
	{

		free(pstDataList->chXmppDataList);
		pstDataList->chXmppDataList = NULL;
		pstDataList->nListSize = 0;
	}
	pstDataList->nListSize = data_size;
	pstDataList->chXmppDataList = (unsigned char*)calloc(1,data_size+1);

	for (i = 0; i < data_size; ++i) {
		high_half_byte = pchMsgContent[i * 2 + 0];//here seems represent bigendian
		low_half_byte = pchMsgContent[i * 2 + 1];

		if (high_half_byte - IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL > 16
			|| high_half_byte - IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL
			< 0) {
			return ERROR_IPP_PROTOCOL_BUFFER_OUT_VAL_IS_NULL;
		}

		if (low_half_byte - IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL > 16
			|| low_half_byte - IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL
			< 0) {
			return ERROR_IPP_PROTOCOL_BUFFER_OUT_VAL_IS_NULL;
		}

		byte_value = (low_half_byte - IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL)
			| ((high_half_byte - IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL)
			<< 4);
		pstDataList->chXmppDataList[i] = byte_value;
	}
	ipp_LogD("%s函数 analyed datasize:%d\n",__func__,pstDataList->nListSize);
	return RESULT_OK;
}

int getXmppDataStruct(stXmppDataList* pstXmppRecDataList, XmppRequest* pstXmppRequestData)
{
	int val_size = 0;
	int nIndex = 0;
	int nCopyLen = 0;
	BYTE* pchTmp = NULL;


	pstXmppRequestData->chType = TYPE_ERROR;
	pstXmppRequestData->nServiceId = -1;
	pstXmppRequestData->nReqBuffSize = 0;


	nCopyLen = sizeof(int) + sizeof(pstXmppRequestData->chType) + sizeof(pstXmppRequestData->nServiceId);

	if (pstXmppRecDataList->nListSize<(nCopyLen))
	{
		return ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE;
	}
	//FREE_POINTER(pstXmppRequestData->pchDeviceGuid);
	//FREE_POINTER(pstXmppRequestData->puchRequest);

//	pXmppRequestData = (pXmppRequestData*)calloc(1,sizeof(XmppRequest));
	val_size = ((int*)pstXmppRecDataList->chXmppDataList)[0];
	pstXmppRequestData->pchDeviceGuid = (char*)malloc(val_size + 1);
	memset(pstXmppRequestData->pchDeviceGuid, '\0', val_size + 1);
	nIndex = sizeof(int);
	pchTmp = pstXmppRecDataList->chXmppDataList + nIndex;
	memcpy(pstXmppRequestData->pchDeviceGuid, (char*)pchTmp, val_size);
	nIndex += val_size;
	if (nIndex >= pstXmppRecDataList->nListSize)
	{
		return ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE;
	}
	pstXmppRequestData->chType = *((char*)pstXmppRecDataList->chXmppDataList + nIndex);
	if (pstXmppRequestData->chType != TYPE_REQUEST) {
		return ERROR_IPP_CLOUD_MESSAGE_MANAGER_SERVICE_REQUEST_TYPE;
	}
	nIndex += sizeof(pstXmppRequestData->chType);
	if (nIndex >= pstXmppRecDataList->nListSize)
	{
		return ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE;
	}
	pstXmppRequestData->nServiceId = *((int*)((char*)pstXmppRecDataList->chXmppDataList + nIndex));
	//需要保留serviceId给控制函数   nIndex += sizeof(gstrXmppRequestData.nServiceId);
	if (nIndex >= pstXmppRecDataList->nListSize)
	{
		return ERROR_IPP_CLOUD_MESSAGE_MANAGER_PARSE_MESSAGE;
	}
	nCopyLen = pstXmppRecDataList->nListSize - nIndex;
	pstXmppRequestData->puchRequest = (BYTE*)malloc(nCopyLen);
	memset(pstXmppRequestData->puchRequest, '\0', nCopyLen);
	memcpy(pstXmppRequestData->puchRequest, pstXmppRecDataList->chXmppDataList + nIndex, nCopyLen);
	pstXmppRequestData->nReqBuffSize = nCopyLen;
	ipp_LogD("%s函数 RequestData:Type:%d,ServiceId:%d,ReqBuffSize:%d\n",__func__,pstXmppRequestData->chType,pstXmppRequestData->nServiceId,pstXmppRequestData->nReqBuffSize);
	return RESULT_OK;
}
int handleServiceRequest(XmppRequest* pstRequestData, stXmppDataList* pstResponseDatalist)
{

	int nReturnLen = 0;
	char * pchReturnBuffer = NULL;
	int nStrLen = 0;
	BOOL ret = FALSE;

	ipp_LogI("########## service_id : %08X\n", pstRequestData->nServiceId);
	if (pstRequestData->nServiceId == SERVICE_ID_LIST){
		nStrLen = strlen(g_SelfDeviceInfo.SN);
		nReturnLen = sizeof(int) * 2 + nStrLen;
		pchReturnBuffer = (char*)malloc(nReturnLen);
		memset(pchReturnBuffer, '\0', nReturnLen);
		((int*)pchReturnBuffer)[0] = 1;
		((int*)pchReturnBuffer)[1] = nStrLen;
		memcpy(pchReturnBuffer + sizeof(int) * 2, g_SelfDeviceInfo.SN, nStrLen);
		formSendMsgContent(pstRequestData->pchDeviceGuid, TYPE_RESPONSE, pstRequestData->nServiceId, pchReturnBuffer, nReturnLen, pstResponseDatalist);
		FREE_POINTER(pchReturnBuffer);
		return RESULT_OK;
	}
	//BOOL ret = ControlDevice(pstRequestData->pchDeviceGuid, (char*)pstRequestData->puchRequest, pstRequestData->nReqBuffSize, nReturnLen, pchReturnBuffer);
	 ret = control_device(pstRequestData->pchDeviceGuid, (char*)pstRequestData->puchRequest, pstRequestData->nReqBuffSize, &pchReturnBuffer, &nReturnLen);
	if (!ret){
		if (pstResponseDatalist->chXmppDataList != NULL){
			free(pstResponseDatalist->chXmppDataList);
			pstResponseDatalist->chXmppDataList = NULL;
			pstResponseDatalist->nListSize = 0;
			}
		ipp_LogE("########## control device return FALSE\n");
		return ERROR_IPP_DEVICE_LOCAL_SERVICE_ACCESS_SERVICE;
	}
	formSendMsgContent(pstRequestData->pchDeviceGuid, TYPE_RESPONSE, pstRequestData->nServiceId, pchReturnBuffer, nReturnLen,pstResponseDatalist);

	FREE_POINTER(pchReturnBuffer);
	ipp_LogD("########## control success\n");
	return RESULT_OK;
}


void ConvertASCstring(char* pchRawData, int nRawLen, stXmppDataList* pstResponseDatalist)
{
	char high_half_byte;
	char low_half_byte;
	BYTE byte_value;
	int i = 0;
	
	FREE_POINTER(pstResponseDatalist->chXmppDataList);
	pstResponseDatalist->nListSize = nRawLen * 2 + 1;
	pstResponseDatalist->chXmppDataList = (BYTE*)malloc(pstResponseDatalist->nListSize);
	memset(pstResponseDatalist->chXmppDataList, '\0', pstResponseDatalist->nListSize);

	while (i < nRawLen) {
		byte_value = pchRawData[i];
		low_half_byte = (byte_value & 0x0F)
			+ IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL;
		high_half_byte = ((byte_value >> 4) & 0x0F)
			+ IPP_PROTOCOL_BUFFER_TO_ASCII_CHANGE_VAL;
		pstResponseDatalist->chXmppDataList[i * 2] = high_half_byte;
		pstResponseDatalist->chXmppDataList[i * 2 + 1] = low_half_byte;
		++i;
	}
}

void formXmppSendMsg(CH_MSGS_ReceiveMessage* pstrRecMsg, CH_MSGS_Message* pstXmppSendMessage, stXmppDataList* pstResponseDatalist)
{

	int nStrLen = 0;
	Node* pIndex = NULL;
	CH_MSGS_Account* pNodeTmp = NULL;
	int i = 0;

	//note1:fromDomain,toDomain,from account(include from,from->id,from->uiName) point global var,do not need free the mem;
	// when pstrRecMsg is null,target->id,target->uiName  also point global var,do not need free the mem,but target need free mem
	pstXmppSendMessage->passthrough = 1;
	pstXmppSendMessage->notifyType = -1;
	pstXmppSendMessage->isEncrypt = 1;
	pstXmppSendMessage->heart = 1;
	pstXmppSendMessage->timeTolive = 0;
	pstXmppSendMessage->target_size = 0;        // 账号集合大小
	pstXmppSendMessage->fromDomain = pchFromDomain;         // 发送者域ID
	pstXmppSendMessage->toDomain = pchToDomain;          //  接收者域ID
	//pstXmppSendMessage->title = NULL;             //  标题
	pstXmppSendMessage->title = (char*)calloc(20, sizeof(char));
	memcpy(pstXmppSendMessage->title,"4004_test",strlen("4004_test"));
	//pstXmppSendMessage->description = NULL;       //  描述
	pstXmppSendMessage->description = (char*)calloc(20, sizeof(char));
	memcpy(pstXmppSendMessage->description,"4004_test descript",strlen("4004_test descript"));
	pstXmppSendMessage->version = (char*)calloc(20, sizeof(char));
	memcpy(pstXmppSendMessage->version,"1.0",strlen("1.0"));
	pstXmppSendMessage->userRange = NULL;
	pstXmppSendMessage->userRange_size = 0;


	if (pstrRecMsg)
	{
		pstXmppSendMessage->target = (CH_MSGS_Account*)calloc(1, sizeof(CH_MSGS_Account));

		nStrLen = strlen(pstrRecMsg->from->id);
		if(nStrLen >0)
		{
			pstXmppSendMessage->target->id = (char*)malloc(nStrLen + 1);
			memset(pstXmppSendMessage->target->id, '\0', nStrLen + 1);
			memcpy(pstXmppSendMessage->target->id, pstrRecMsg->from->id, nStrLen);
		}
		
		nStrLen = strlen(pstrRecMsg->from->uiName);
		if(nStrLen >0)
		{
			pstXmppSendMessage->target->uiName = (char*)malloc(nStrLen + 1);
			memset(pstXmppSendMessage->target->uiName, '\0', nStrLen + 1);
			memcpy(pstXmppSendMessage->target->uiName, pstrRecMsg->from->uiName, nStrLen);
		}
		
		pstXmppSendMessage->target_size = 1;
	}
	else
	{
		
		nStrLen = 0;
		pIndex = gOnlineUser.stUserList;
		nStrLen = gOnlineUser.nUserSize;
		pstXmppSendMessage->target = (CH_MSGS_Account*)calloc(1,sizeof(CH_MSGS_Account)*nStrLen);
		pstXmppSendMessage->target_size = nStrLen;
		for (i = 0; i < nStrLen; i++)
		{
			pNodeTmp = pstXmppSendMessage->target + i;//need to test
			pNodeTmp = &pIndex->Element.pstMsgSAccount;
			pIndex = pIndex->next;
		}
	}
	pstXmppSendMessage->content = (char*)pstResponseDatalist->chXmppDataList;
	pstXmppSendMessage->from = &stLocalXmppAccount;
}

void formSendMsgContent(char* device_guid, char type, int service_id, char* pchContent, int nContentSize, stXmppDataList* pstResponseDatalist)
{

	int ntmp = 0, nIndex = 0;
	int nStrlen = 0;
	char* pchBuff = NULL;
	if(nContentSize > 0)
	{
		ntmp = sizeof(service_id) + strlen(device_guid) + sizeof(type) + nContentSize + sizeof(int);//content behand service_id need not set it's contentsize(but neet set sub string's size in content)
	}
	else
	{
		ntmp = sizeof(service_id) + strlen(device_guid) + sizeof(type) + sizeof(int);
	}
	
	pchBuff = (char*)calloc(1,ntmp);
	nStrlen = strlen(device_guid);
	*((int*)pchBuff) = nStrlen;
	nIndex = sizeof(int);
	memcpy(pchBuff + nIndex, device_guid, nStrlen);
	nIndex += nStrlen;
	pchBuff[nIndex] = (char)type;
	nIndex += sizeof(type);
	*((int*)(pchBuff + nIndex)) = service_id;
	nIndex += sizeof(service_id);
	if(nContentSize > 0){
//		*((int*)(pchBuff + nIndex)) = nContentSize;
//		nIndex += sizeof(int);
		memcpy((pchBuff+nIndex), pchContent, nContentSize);
	}
	ConvertASCstring(pchBuff, ntmp, pstResponseDatalist);
	FREE_POINTER(pchBuff);
}


void handleXmppSendResult(CH_MSGS_Result* pResult)
{
	switch (pResult->code)
	{
	case 100001:
		ipp_LogE("发送xmpp消息返回错误：%s", pResult->reason);
		break;

	case 100002:
		ipp_LogE("发送xmpp消息返回错误：%s", pResult->reason);
		break;

	case 100003:
		ipp_LogE("发送xmpp消息返回错误：%s", pResult->reason);
		break;

	default:
		break;
	}

}
