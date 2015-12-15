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
	typedef struct _Node{    /* 定义单链表结点类型 */
		ElemType Element;
		struct _Node *next;
	}Node;

	/* 1.初始化线性表，即置单链表的表头指针为空 */
	void initList(Node **pNode);
	/* 2.创建线性表，此函数输入负数终止读取数据*/
	Node *creatList(Node *pHead, ElemType* pMsgAcount, int nAcountSize);
	/* 3.打印链表，链表的遍历*/
	int GetListElemNum(Node *pHead);
	/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
	void clearList(Node **pHead);
	/* 5.返回单链表的长度 */
	int sizeList(Node *pHead);
	/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
	int isEmptyList(Node *pHead);
	/* 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行 */
	ElemType* getElement(Node* pHead, int pos);
	/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
	ElemType* getElemAddr(Node* pHead, ElemType* x, int* nPos);
	/* 11.删除在列表中的指定元素 */
	BOOL DelListElem(Node *pHead, ElemType* pDelElem);
	/* 9.向单链表的末尾添加一个元素 *,链表可以为*/
	int insertLastList(Node **ppNode, ElemType* insertElem);
	/* 10.在单链表的中查找并添加多个元素 */
	int FindInsertList(Node **pNode, ElemType* pinsertElem, int nElemSize);
	/*11,根据指定值查找元素位置，返回元素*/
	ElemType* getSpecElementVal(Node* pHead,int nRelation, int* nPos);



#ifdef __cplusplus
}
#endif
#endif

