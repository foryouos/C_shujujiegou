#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#define MAXSIZE 100  //顺序表的大小
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;   //函数的类型，其值是函数结果的状态代码
typedef int ElemType;
//链栈的结构体---受限的单链表
typedef struct StackNode
{
	ElemType data;
	struct StackNode* next;
}StackNode,*LinkStack;

Status InitStack(LinkStack& S)
{
	//构造空战
	S = NULL;
	return OK;
}
//判断链栈是否为空
Status StackEmpty(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	else
		return FALSE;
}
//链栈的入栈
Status Push(LinkStack& S, ElemType e)
{
	LinkStack p;
	p = (StackNode*)malloc(sizeof(StackNode));  //生成新结点p
	p->data = e;			//将新结点数据置为e
	p->next = S;			//将新结点插入栈顶
	S = p;					//修改栈顶指针
	return OK;

}

//链栈的出栈
Status Pop(LinkStack& S, ElemType& e)
{
	LinkStack p;
	if (S == NULL)
		return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	free(p);
	return OK;

}
//去栈顶元素
ElemType GetTop(LinkStack S)
{
	if (S != NULL)
		return S->data;
}

int main(void)
{
	LinkStack S;
	InitStack(S);
	StackEmpty(S);

	return 0;
}