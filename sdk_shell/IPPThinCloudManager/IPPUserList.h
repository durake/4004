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
#ifndef IPPUSERLIST_H_
#define IPPUSERLIST_H_



#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include"CloudMessage.h"
#include"common.h"
#include "ipp_defines.h"




	/************************************************************************/
	typedef struct _Node{    /* ���嵥���������� */
		ElemType Element;
		struct _Node *next;
	}Node;

	/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
	void initList(Node **pNode);
	/* 2.�������Ա��˺������븺����ֹ��ȡ����*/
	Node *creatList(Node *pHead, ElemType* pMsgAcount, int nAcountSize);
	/* 3.��ӡ��������ı���*/
	int GetListElemNum(Node *pHead);
	/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
	void clearList(Node **pHead);
	/* 5.���ص�����ĳ��� */
	int sizeList(Node *pHead);
	/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
	int isEmptyList(Node *pHead);
	/* 7.���ص������е�pos������е�Ԫ�أ���pos������Χ����ֹͣ�������� */
	ElemType* getElement(Node* pHead, int pos);
	/* 8.�ӵ������в��Ҿ��и���ֵx�ĵ�һ��Ԫ�أ������ҳɹ��򷵻ظý��data��Ĵ洢��ַ�����򷵻�NULL */
	ElemType* getElemAddr(Node* pHead, ElemType* x, int* nPos);
	/* 11.ɾ�����б��е�ָ��Ԫ�� */
	BOOL DelListElem(Node *pHead, ElemType* pDelElem);
	/* 9.�������ĩβ���һ��Ԫ�� *,�������Ϊ*/
	int insertLastList(Node **ppNode, ElemType* insertElem);
	/* 10.�ڵ�������в��Ҳ���Ӷ��Ԫ�� */
	int FindInsertList(Node **pNode, ElemType* pinsertElem, int nElemSize);
	/*11,����ָ��ֵ����Ԫ��λ�ã�����Ԫ��*/
	ElemType* getSpecElementVal(Node* pHead,int nRelation, int* nPos);



#ifdef __cplusplus
}
#endif
#endif

