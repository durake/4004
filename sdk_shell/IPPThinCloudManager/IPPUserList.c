
#include <base.h>
#include <stdlib.h>
#include <string.h>
#include"CloudMessage.h"
#include "IPPUserList.h"
#include "common.h"
#include "ipp_util.h"
#include "ipp_defines.h"
#include "ipp_stub_def.h"

/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
void initList(Node **pNode)
{
	*pNode = NULL;
	ipp_LogE("initList����ִ�У���ʼ���ɹ�\n");
}

/* 2.�������Ա�*/
Node *creatList(Node *pHead, ElemType* pMsgAcount, int nAcountSize)
{
	Node *p1 = NULL;
	Node *p2 = NULL;
	ElemType* pAcountMsg;
	if (nAcountSize <=0)
	{
		return NULL;
	}
	pHead = NULL;


	pAcountMsg = pMsgAcount;
	int i = 0;
	while (i < nAcountSize)        //�����ֵ����0�������ֱ�������ֵΪ��
	{

		//����һ���ڵ�
		p1 = (Node *)calloc(1, sizeof(Node)); //�����½ڵ�
		if (p1 == NULL)
		{
			ipp_LogE("�ڴ����ʧ��:%s(%s)-%d\n",__FILE__, __FUNCTION__, __LINE__);
			return NULL;
		}
		p1->Element.pstMsgSAccount.id = (char*)calloc(1,strlen(pAcountMsg->pstMsgSAccount.id) + 1);
		if (p1->Element.pstMsgSAccount.id == NULL)
		{
			ipp_LogE("�ڴ����ʧ��:%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
			return NULL;
		}
		p1->Element.pstMsgSAccount.uiName = (char*)calloc(1,strlen(pAcountMsg->pstMsgSAccount.uiName) + 1);
		if (p1->Element.pstMsgSAccount.uiName == NULL)
		{
			ipp_LogE("�ڴ����ʧ��%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
			return NULL;
		}
		strcpy(p1->Element.pstMsgSAccount.id, pAcountMsg->pstMsgSAccount.id);
		strcpy(p1->Element.pstMsgSAccount.uiName, pAcountMsg->pstMsgSAccount.uiName);
		p1->Element.nRelation = pAcountMsg->nRelation;
		p1->next = NULL;
		if (pHead == NULL)       //�ձ������ͷ
		{
			pHead = p1;
		}
		else
		{
			p2->next = p1;       //�ǿձ������β
		}
		p2 = p1;
		pAcountMsg = (ElemType*)pAcountMsg + 1;
		i++;
	}
	ipp_LogI("creatList����ִ�У��������ɹ�\n");
	return pHead;           //���������ͷָ��
}

/* 3.���������ȣ���ӡ��������ı���*/
int GetListElemNum(Node *pHead)
{

	Node* pNodeTmp;
	pNodeTmp = pHead;
	int nNum = 0;
	if (NULL == pNodeTmp)   //����Ϊ��
	{
		ipp_LogI("PrintList����ִ�У�����Ϊ��\n");
	}
	else
	{
		while (NULL != pNodeTmp)
		{
			nNum++;
			ipp_LogV("%s\n ", pNodeTmp->Element.pstMsgSAccount.id);
			ipp_LogV("%s\n ", pNodeTmp->Element.pstMsgSAccount.uiName);
			pNodeTmp = pNodeTmp->next;
		}
	}
	return nNum;
}

/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
void clearList(Node **pHead)
{
	Node* pNext;            //����һ����pHead���ڽڵ�


	if (*pHead == NULL)
	{
		ipp_LogI("clearList����ִ�У�����Ϊ��\n");
		return;
	}

	while ((*pHead)->next != NULL)
	{
		pNext = (*pHead)->next;//������һ����ָ��
		FREE_POINTER((*pHead)->Element.pstMsgSAccount.id);
		FREE_POINTER((*pHead)->Element.pstMsgSAccount.uiName);

		free(*pHead);
		*pHead = pNext;      //��ͷ����
	}
	FREE_POINTER((*pHead)->Element.pstMsgSAccount.id);
	FREE_POINTER((*pHead)->Element.pstMsgSAccount.uiName);
	FREE_POINTER(*pHead);
	ipp_LogI("clearList����ִ�У������Ѿ����\n");
}

/* 5.���ص�����ĳ��� */
int sizeList(Node *pHead)
{
	int size = 0;
	Node* pNodeTmp;
	pNodeTmp = pHead;

	while (pNodeTmp != NULL)
	{
		size++;         //��������size��С�������ʵ�ʳ���С1
		pNodeTmp = pNodeTmp->next;
	}
	ipp_LogI("sizeList����ִ�У������� %d \n", size);
	return size;    //�����ʵ�ʳ���
}

/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
int isEmptyList(Node *pHead)
{
	if (pHead == NULL)
	{
		ipp_LogI("isEmptyList����ִ�У�����Ϊ��\n");
		return 1;
	}
	ipp_LogI("isEmptyList����ִ�У�����ǿ�\n");

	return 0;
}

/* 7.���ص������е�pos������е�Ԫ�أ���pos������Χ����ֹͣ�������� */
ElemType* getElement(Node *pHead, int pos)
{
	int i = 0;
	Node* pNode;
	pNode = pHead;

	if (pos < 1)
	{
		ipp_LogE("getElement����ִ�У�posֵ�Ƿ�\n");
		return NULL;
	}
	if (pNode == NULL)
	{
		ipp_LogI("getElement����ִ�У�����Ϊ��\n");
		return NULL;
	}
	while (pNode != NULL)
	{
		++i;
		if (i == pos)
		{
			break;
		}
		pNode = pNode->next; //�Ƶ���һ���
	}
	if (i < pos)                  //�����Ȳ������˳�
	{
		ipp_LogE("getElement����ִ�У�posֵ����������\n");
		return NULL;
	}

	return &pNode->Element;
}

/* 8.�ӵ������в��Ҿ��и���ֵx�ĵ�һ��Ԫ�أ������ҳɹ��򷵻ظý��data��Ĵ洢��ַ�����򷵻�NULL */
ElemType* getElemAddr(Node *pHead, ElemType* x, int* nPos)
{
	Node* pNodeTmp;
	pNodeTmp = pHead;
	*nPos = 1;

	if (NULL == pNodeTmp)
	{
		ipp_LogI("getElemAddr����ִ�У�����Ϊ��\n");
		*nPos = 0;
		return NULL;

	}
	if (x == NULL)
	{
		ipp_LogE("getElemAddr����ִ�У�����ֵX���Ϸ�\n");
		*nPos = 0;
		return NULL;
	}
	while ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, x->pstMsgSAccount.id)) && (NULL != pNodeTmp->next)) //�ж��Ƿ�����ĩβ���Լ��Ƿ������Ҫ�ҵ�Ԫ��
	{
		pNodeTmp = pNodeTmp->next;
		(*nPos)++;
	}
	if ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, x->pstMsgSAccount.id)) && (pNodeTmp != NULL))
	{
		ipp_LogE("%s����ִ�У���������δ�ҵ�xֵ\n",__FUNCTION__);
		*nPos = 0;
		return NULL;
	}
	if (!strcmp(pNodeTmp->Element.pstMsgSAccount.id, x->pstMsgSAccount.id))
	{
		ipp_LogV("%s����ִ�У�Ԫ�� %s �ĵ�ַΪ 0x%d\n", __FUNCTION__,x->pstMsgSAccount.id, *nPos);
	}

	return &(pNodeTmp->Element);//����Ԫ�صĵ�ַ
}

/* 9.�������ĩβ���һ��Ԫ�� */
int insertLastList(Node **ppHead, ElemType* insertElem)
{
	Node *pInsert;
	Node *pHead;
	Node *pTmp; //����һ����ʱ����������ŵ�һ���ڵ�

	pHead = *ppHead;
	pTmp = *ppHead;
	pInsert = (Node *)calloc(1,sizeof(Node)); //����һ���½ڵ�


	pInsert->Element.pstMsgSAccount.id = (char*)calloc(1,strlen(insertElem->pstMsgSAccount.id) + 1);
	if (pInsert->Element.pstMsgSAccount.id == NULL)
	{
		ipp_LogE("�ڴ����ʧ��%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
		return 0;
	}
	pInsert->Element.pstMsgSAccount.uiName = (char*)calloc(1,strlen(insertElem->pstMsgSAccount.uiName) + 1);
	if (pInsert->Element.pstMsgSAccount.uiName == NULL)
	{
		ipp_LogE("�ڴ����ʧ��%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
		return 0;
	}
	strcpy(pInsert->Element.pstMsgSAccount.id, insertElem->pstMsgSAccount.id);
	strcpy(pInsert->Element.pstMsgSAccount.uiName, insertElem->pstMsgSAccount.uiName);
	pInsert->Element.nRelation = insertElem->nRelation;

	if(pHead == NULL)
	{
		pHead = pInsert;
		*ppHead = pHead;
		return 1;
	}

	while (pHead->next != NULL)
	{
		pHead = pHead->next;
	}
	pHead->next = pInsert;   //������ĩβ�ڵ����һ���ָ������ӵĽڵ�
	*ppHead = pTmp;
	ipp_LogI("insertLastList����ִ�У����β����Ԫ�سɹ�\n");

	return 1;
}


/*10.�ڵ�������в��Ҳ���Ӷ��Ԫ�� */
int FindInsertList(Node **pNode, ElemType* pinsertElem, int nElemSize)
{
	Node *pHead;//����һ����ʱ����������ŵ�һ���ڵ�
	pHead = *pNode;
	ElemType* ElemTmp = NULL;
	ElemType* pFindedElem = NULL;
	ElemTmp = pinsertElem;
	int nPos = 0;
	int i = 0; 
	int nInserNum = 0;
	if(pHead == NULL)
	{
		for (i = 0; i < nElemSize; i++)
		{
			insertLastList(&pHead, ElemTmp);
			ElemTmp = (ElemType*)ElemTmp + 1;
			i++;
		}
		*pNode = pHead;
		nInserNum = nElemSize;
		return nInserNum;
	}
	for (i = 0; i < nElemSize; i++)
	{
		pFindedElem = getElemAddr(pHead, ElemTmp, &nPos);
		if (!pFindedElem)
		{
			insertLastList(&pHead, ElemTmp);
			nInserNum++;
		}
		ElemTmp = (ElemType*)ElemTmp + 1;
		i++;
	}
	return nInserNum;
}

/* 11.ɾ�������б��е�ָ��Ԫ�� */
BOOL DelListElem(Node *pHead, ElemType* pDelElem)
{

	Node* pNodeTmp;
	Node* pNodeLast;
	pNodeTmp = pHead;
	pNodeLast = pHead;

	if (NULL == pNodeTmp)
	{
		ipp_LogI("%s����ִ�У�����Ϊ��\n",__FUNCTION__);
		return FALSE;

	}
	if (pDelElem == NULL)
	{
		ipp_LogE("%s����ִ�У�����ֵpinsertElem���Ϸ�\n",__FUNCTION__);
		return FALSE;
	}
	while ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, pDelElem->pstMsgSAccount.id)) && (NULL != pNodeTmp->next)) //�ж��Ƿ�����ĩβ���Լ��Ƿ������Ҫ�ҵ�Ԫ��
	{
		pNodeLast = pNodeTmp;
		pNodeTmp = pNodeTmp->next;
	}
	if ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, pDelElem->pstMsgSAccount.id)) && (pNodeTmp != NULL))
	{
		ipp_LogE("%s����ִ�У���������δ�ҵ�xֵ\n",__FUNCTION__);
		return FALSE;
	}
	if (!strcmp(pNodeTmp->Element.pstMsgSAccount.id, pDelElem->pstMsgSAccount.id))
	{
		pNodeLast->next = pNodeTmp->next;
		FREE_POINTER(pNodeTmp->Element.pstMsgSAccount.id);
		FREE_POINTER(pNodeTmp->Element.pstMsgSAccount.uiName);
		FREE_POINTER(pNodeTmp);
		ipp_LogI("%s����ִ�У�Ԫ�� %s �ĵ�ַΪ 0x%s\n", __FUNCTION__, pDelElem->pstMsgSAccount.id, (pNodeTmp->Element.pstMsgSAccount.id));
		return TRUE;
	}
}

ElemType* getSpecElementVal(Node* pHead,int nRelation, int* nPos)
{
	Node* pNodeTmp;
	Node* pNodeLast;
	pNodeTmp = pHead;
	pNodeLast = pHead;
	*nPos =1;
	
	if (NULL == pNodeTmp)
	{
		ipp_LogI("%s����ִ�У�����Ϊ��\n",__FUNCTION__);
		*nPos =0;
		return NULL;

	}
	if (nRelation == RELATION_BIND)
	{
		while ((pNodeTmp->Element.nRelation != RELATION_BIND) && (NULL != pNodeTmp->next)) //�ж��Ƿ�����ĩβ���Լ��Ƿ������Ҫ�ҵ�Ԫ��
		{
			pNodeLast = pNodeTmp;
			pNodeTmp = pNodeTmp->next;
			*nPos += 1;
		}
		if ((pNodeTmp->Element.nRelation != RELATION_BIND) && (pNodeTmp != NULL))
		{
			ipp_LogE("%s����ִ�У���������δ�ҵ�xֵ\n",__FUNCTION__);
			*nPos =0;
			return NULL;
		}
		if(pNodeTmp->Element.nRelation == RELATION_BIND)
		{
			ipp_LogI("%s����ִ�У�Ԫ�� %s �ĵ�ַΪ 0x%d\n", __FUNCTION__, pNodeTmp->Element.pstMsgSAccount.id, (*nPos));
			return &pNodeTmp->Element;
		}
		
	}
	if (nRelation == RELATION_SHARE)
	{
		while ((pNodeTmp->Element.nRelation != RELATION_SHARE) && (NULL != pNodeTmp->next)) //�ж��Ƿ�����ĩβ���Լ��Ƿ������Ҫ�ҵ�Ԫ��
		{
			pNodeLast = pNodeTmp;
			pNodeTmp = pNodeTmp->next;
			*nPos += 1;
		}
		if ((pNodeTmp->Element.nRelation != RELATION_SHARE) && (pNodeTmp != NULL))
		{
			ipp_LogE("%s����ִ�У���������δ�ҵ�xֵ\n",__FUNCTION__);
			*nPos =0;
			return NULL;
		}
		if (pNodeTmp->Element.nRelation == RELATION_SHARE)
		{
			ipp_LogI("%s����ִ�У�Ԫ�� %s �ĵ�ַΪ 0x%d\n", __FUNCTION__,(pNodeTmp->Element.pstMsgSAccount.id),*nPos);
			return &pNodeTmp->Element;
		}
	}
}
