/******************************************************************************

                  ��Ȩ���� (C), 1958-2015, �����������-�Ʒ�-���ּ�ͥ

 ******************************************************************************
  �� �� ��   : ipp_api.h
  ��������   : IPP SDK�����ṩ�ĺ����ӿ�
 ******************************************************************************/
#ifndef _IPP_API_H_
#define _IPP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ipp_protocol.h"

//�豸���Խṹ��
typedef struct
{
	char guid[32];
	char product_id[30];
	int32_t device_type;
}ipp_device_profile;

//�豸�յ���Ϣ����ص����������ص�ipp_protocolָ�룬�ɻص������ڲ������ڴ棬IPP SDKʹ�ú��Զ��ͷ�
typedef ipp_protocol *(*message_handler)(ipp_protocol *msg);

/*
  ��������	ipp_init
  ���ܣ�	��ʼ��������IPP
  ��Σ�	��
  ���Σ�	��
  ����ֵ��	�ɹ�����TRUE��ʧ��FALSE
*/
BOOL ipp_init();

/*
  ��������	ipp_deinit
  ���ܣ�	ֹͣIPP���ͷ���Դ
  ��Σ�	��
  ���Σ�	��
  ����ֵ��	��
*/
void ipp_deinit();

/*
  ��������	set_device_info
  ���ܣ�	�����豸����
  ��Σ�	ipp_device_profile *info
  ���Σ�	��
  ����ֵ��	��
*/
void set_device_info(ipp_device_profile *profile);

/*
  ��������	send_event
  ���ܣ�	�����豸�¼�(���豸״̬�仯��)
  ��Σ�	ipp_protocol *eve
  ���Σ�	��
  ����ֵ��	��
*/
void send_event(ipp_protocol *eve);

/*
  ��������	reg_message_handler
  ���ܣ�	ע���豸�յ���Ϣ����ص�����
  ��Σ�	message_handler handler
  ���Σ�	��
  ����ֵ��	��
*/
void reg_message_handler(message_handler handler);

#ifdef __cplusplus
}
#endif

#endif
