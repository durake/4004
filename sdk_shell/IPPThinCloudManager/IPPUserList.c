
#include <base.h>
#include <stdlib.h>
#include <string.h>
#include"CloudMessage.h"
#include "IPPUserList.h"
#include "common.h"
#include "ipp_util.h"
#include "ipp_defines.h"
#include "ipp_stub_def.h"

/* 1.初始化线性表，即置单链表的表头指针为空 */
void initList(Node **pNode)
{
	*pNode = NULL;
	ipp_LogE("initList函数执行，初始化成功\n");
}

/* 2.创建线性表*/
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
	while (i < nAcountSize)        //输入的值大于0则继续，直到输入的值为负
	{

		//申请一个节点
		p1 = (Node *)calloc(1, sizeof(Node)); //申请新节点
		if (p1 == NULL)
		{
			ipp_LogE("内存分配失败:%s(%s)-%d\n",__FILE__, __FUNCTION__, __LINE__);
			return NULL;
		}
		p1->Element.pstMsgSAccount.id = (char*)calloc(1,strlen(pAcountMsg->pstMsgSAccount.id) + 1);
		if (p1->Element.pstMsgSAccount.id == NULL)
		{
			ipp_LogE("内存分配失败:%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
			return NULL;
		}
		p1->Element.pstMsgSAccount.uiName = (char*)calloc(1,strlen(pAcountMsg->pstMsgSAccount.uiName) + 1);
		if (p1->Element.pstMsgSAccount.uiName == NULL)
		{
			ipp_LogE("内存分配失败%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
			return NULL;
		}
		strcpy(p1->Element.pstMsgSAccount.id, pAcountMsg->pstMsgSAccount.id);
		strcpy(p1->Element.pstMsgSAccount.uiName, pAcountMsg->pstMsgSAccount.uiName);
		p1->Element.nRelation = pAcountMsg->nRelation;
		p1->next = NULL;
		if (pHead == NULL)       //空表，接入表头
		{
			pHead = p1;
		}
		else
		{
			p2->next = p1;       //非空表，接入表尾
		}
		p2 = p1;
		pAcountMsg = (ElemType*)pAcountMsg + 1;
		i++;
	}
	ipp_LogI("creatList函数执行，链表创建成功\n");
	return pHead;           //返回链表的头指针
}

/* 3.计算链表长度，打印链表，链表的遍历*/
int GetListElemNum(Node *pHead)
{

	Node* pNodeTmp;
	pNodeTmp = pHead;
	int nNum = 0;
	if (NULL == pNodeTmp)   //链表为空
	{
		ipp_LogI("PrintList函数执行，链表为空\n");
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

/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
void clearList(Node **pHead)
{
	Node* pNext;            //定义一个与pHead相邻节点


	if (*pHead == NULL)
	{
		ipp_LogI("clearList函数执行，链表为空\n");
		return;
	}

	while ((*pHead)->next != NULL)
	{
		pNext = (*pHead)->next;//保存下一结点的指针
		FREE_POINTER((*pHead)->Element.pstMsgSAccount.id);
		FREE_POINTER((*pHead)->Element.pstMsgSAccount.uiName);

		free(*pHead);
		*pHead = pNext;      //表头下移
	}
	FREE_POINTER((*pHead)->Element.pstMsgSAccount.id);
	FREE_POINTER((*pHead)->Element.pstMsgSAccount.uiName);
	FREE_POINTER(*pHead);
	ipp_LogI("clearList函数执行，链表已经清除\n");
}

/* 5.返回单链表的长度 */
int sizeList(Node *pHead)
{
	int size = 0;
	Node* pNodeTmp;
	pNodeTmp = pHead;

	while (pNodeTmp != NULL)
	{
		size++;         //遍历链表size大小比链表的实际长度小1
		pNodeTmp = pNodeTmp->next;
	}
	ipp_LogI("sizeList函数执行，链表长度 %d \n", size);
	return size;    //链表的实际长度
}

/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
int isEmptyList(Node *pHead)
{
	if (pHead == NULL)
	{
		ipp_LogI("isEmptyList函数执行，链表为空\n");
		return 1;
	}
	ipp_LogI("isEmptyList函数执行，链表非空\n");

	return 0;
}

/* 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行 */
ElemType* getElement(Node *pHead, int pos)
{
	int i = 0;
	Node* pNode;
	pNode = pHead;

	if (pos < 1)
	{
		ipp_LogE("getElement函数执行，pos值非法\n");
		return NULL;
	}
	if (pNode == NULL)
	{
		ipp_LogI("getElement函数执行，链表为空\n");
		return NULL;
	}
	while (pNode != NULL)
	{
		++i;
		if (i == pos)
		{
			break;
		}
		pNode = pNode->next; //移到下一结点
	}
	if (i < pos)                  //链表长度不足则退出
	{
		ipp_LogE("getElement函数执行，pos值超出链表长度\n");
		return NULL;
	}

	return &pNode->Element;
}

/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
ElemType* getElemAddr(Node *pHead, ElemType* x, int* nPos)
{
	Node* pNodeTmp;
	pNodeTmp = pHead;
	*nPos = 1;

	if (NULL == pNodeTmp)
	{
		ipp_LogI("getElemAddr函数执行，链表为空\n");
		*nPos = 0;
		return NULL;

	}
	if (x == NULL)
	{
		ipp_LogE("getElemAddr函数执行，给定值X不合法\n");
		*nPos = 0;
		return NULL;
	}
	while ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, x->pstMsgSAccount.id)) && (NULL != pNodeTmp->next)) //判断是否到链表末尾，以及是否存在所要找的元素
	{
		pNodeTmp = pNodeTmp->next;
		(*nPos)++;
	}
	if ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, x->pstMsgSAccount.id)) && (pNodeTmp != NULL))
	{
		ipp_LogE("%s函数执行，在链表中未找到x值\n",__FUNCTION__);
		*nPos = 0;
		return NULL;
	}
	if (!strcmp(pNodeTmp->Element.pstMsgSAccount.id, x->pstMsgSAccount.id))
	{
		ipp_LogV("%s函数执行，元素 %s 的地址为 0x%d\n", __FUNCTION__,x->pstMsgSAccount.id, *nPos);
	}

	return &(pNodeTmp->Element);//返回元素的地址
}

/* 9.向单链表的末尾添加一个元素 */
int insertLastList(Node **ppHead, ElemType* insertElem)
{
	Node *pInsert;
	Node *pHead;
	Node *pTmp; //定义一个临时链表用来存放第一个节点

	pHead = *ppHead;
	pTmp = *ppHead;
	pInsert = (Node *)calloc(1,sizeof(Node)); //申请一个新节点


	pInsert->Element.pstMsgSAccount.id = (char*)calloc(1,strlen(insertElem->pstMsgSAccount.id) + 1);
	if (pInsert->Element.pstMsgSAccount.id == NULL)
	{
		ipp_LogE("内存分配失败%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
		return 0;
	}
	pInsert->Element.pstMsgSAccount.uiName = (char*)calloc(1,strlen(insertElem->pstMsgSAccount.uiName) + 1);
	if (pInsert->Element.pstMsgSAccount.uiName == NULL)
	{
		ipp_LogE("内存分配失败%s(%s)-%d\n",__FILE__,__FUNCTION__,__LINE__);
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
	pHead->next = pInsert;   //将链表末尾节点的下一结点指向新添加的节点
	*ppHead = pTmp;
	ipp_LogI("insertLastList函数执行，向表尾插入元素成功\n");

	return 1;
}


/*10.在单链表的中查找并添加多个元素 */
int FindInsertList(Node **pNode, ElemType* pinsertElem, int nElemSize)
{
	Node *pHead;//定义一个临时链表用来存放第一个节点
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

/* 11.删除在线列表中的指定元素 */
BOOL DelListElem(Node *pHead, ElemType* pDelElem)
{

	Node* pNodeTmp;
	Node* pNodeLast;
	pNodeTmp = pHead;
	pNodeLast = pHead;

	if (NULL == pNodeTmp)
	{
		ipp_LogI("%s函数执行，链表为空\n",__FUNCTION__);
		return FALSE;

	}
	if (pDelElem == NULL)
	{
		ipp_LogE("%s函数执行，给定值pinsertElem不合法\n",__FUNCTION__);
		return FALSE;
	}
	while ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, pDelElem->pstMsgSAccount.id)) && (NULL != pNodeTmp->next)) //判断是否到链表末尾，以及是否存在所要找的元素
	{
		pNodeLast = pNodeTmp;
		pNodeTmp = pNodeTmp->next;
	}
	if ((strcmp(pNodeTmp->Element.pstMsgSAccount.id, pDelElem->pstMsgSAccount.id)) && (pNodeTmp != NULL))
	{
		ipp_LogE("%s函数执行，在链表中未找到x值\n",__FUNCTION__);
		return FALSE;
	}
	if (!strcmp(pNodeTmp->Element.pstMsgSAccount.id, pDelElem->pstMsgSAccount.id))
	{
		pNodeLast->next = pNodeTmp->next;
		FREE_POINTER(pNodeTmp->Element.pstMsgSAccount.id);
		FREE_POINTER(pNodeTmp->Element.pstMsgSAccount.uiName);
		FREE_POINTER(pNodeTmp);
		ipp_LogI("%s函数执行，元素 %s 的地址为 0x%s\n", __FUNCTION__, pDelElem->pstMsgSAccount.id, (pNodeTmp->Element.pstMsgSAccount.id));
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
		ipp_LogI("%s函数执行，链表为空\n",__FUNCTION__);
		*nPos =0;
		return NULL;

	}
	if (nRelation == RELATION_BIND)
	{
		while ((pNodeTmp->Element.nRelation != RELATION_BIND) && (NULL != pNodeTmp->next)) //判断是否到链表末尾，以及是否存在所要找的元素
		{
			pNodeLast = pNodeTmp;
			pNodeTmp = pNodeTmp->next;
			*nPos += 1;
		}
		if ((pNodeTmp->Element.nRelation != RELATION_BIND) && (pNodeTmp != NULL))
		{
			ipp_LogE("%s函数执行，在链表中未找到x值\n",__FUNCTION__);
			*nPos =0;
			return NULL;
		}
		if(pNodeTmp->Element.nRelation == RELATION_BIND)
		{
			ipp_LogI("%s函数执行，元素 %s 的地址为 0x%d\n", __FUNCTION__, pNodeTmp->Element.pstMsgSAccount.id, (*nPos));
			return &pNodeTmp->Element;
		}
		
	}
	if (nRelation == RELATION_SHARE)
	{
		while ((pNodeTmp->Element.nRelation != RELATION_SHARE) && (NULL != pNodeTmp->next)) //判断是否到链表末尾，以及是否存在所要找的元素
		{
			pNodeLast = pNodeTmp;
			pNodeTmp = pNodeTmp->next;
			*nPos += 1;
		}
		if ((pNodeTmp->Element.nRelation != RELATION_SHARE) && (pNodeTmp != NULL))
		{
			ipp_LogE("%s函数执行，在链表中未找到x值\n",__FUNCTION__);
			*nPos =0;
			return NULL;
		}
		if (pNodeTmp->Element.nRelation == RELATION_SHARE)
		{
			ipp_LogI("%s函数执行，元素 %s 的地址为 0x%d\n", __FUNCTION__,(pNodeTmp->Element.pstMsgSAccount.id),*nPos);
			return &pNodeTmp->Element;
		}
	}
}
