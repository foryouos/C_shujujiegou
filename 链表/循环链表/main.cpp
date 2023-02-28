#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#define List_INIT_SIZE 100  //顺序表的大小
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;   //函数的类型，其值是函数结果的状态代码
typedef int ElemType;

typedef struct DulNode
{
	ElemType data;
	struct DulNode* prior, * next;
}DulNode,*DuLinklist;
DulNode* GetElem_Dul(DuLinklist L, int i)
{
	DulNode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) //向后扫描，直到p指向第i个元素或p为空
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) //第i个元素不存在
		return ERROR;
	return p;
}
//双向循环链表的插入
int ListInsert_Dul(DuLinklist& L, int i, ElemType e)
{
	ElemType m;
	DulNode* p;
	if(!(p=GetElem_Dul(L,i)))
		return ERROR;
	DulNode* s;
	s = (DulNode*)malloc(sizeof(DulNode));
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->next = s;
	return OK;
}
//双向链表的删除,删除带头结点的双向循环链表L的第i个元素，并用e返回
int ListDelete_Dul(DuLinklist& L, int i, ElemType& e)
{
	DulNode* p;
	if (!(p = GetElem_Dul(L, i)))
		return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

int main(void)
{

	printf("hello word!\n");
	return 0;
}