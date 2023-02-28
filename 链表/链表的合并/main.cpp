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

typedef struct Lnode	//声明单链表的结构类型
{
	ElemType data;		//数据域
	struct Lnode* next;		//下一个结点的指针域，嵌套定义
}Lnode, * LinkList;  //LinkList为指向结构体Lnode的指针类型

//单链表初始化
Status InitList(LinkList& L)
{
	L = (LinkList)malloc(sizeof(Lnode)); //或者用C++: new Lnode
	L->next = NULL;  //下一个结点为空
	return OK;
}



//返回长度值
int ListLength(Lnode* L)
{
	LinkList p;
	p = L->next;
	int length = 0;
	while (p)
	{
		length++;
		p = p->next;
	}
	return length;
}



//尾插法
void CreateList_R(LinkList& L, int n)
{
	Lnode* r;
	L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	r = L;
	for (int i = 0; i < n; i++)
	{
		Lnode* p;
		p = (Lnode*)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = NULL;
		r->next = p;
		r = p;
	}
}

//顺序链表的合并
void seq_uion(LinkList la, LinkList lb,LinkList &lc)
{
	LinkList p = la->next; //存入p
	LinkList q = lb->next; 
	LinkList c = lc;
	while(p&&q) //当任何一个链表变为空
	{
		if (p->data <= q->data)    //先将小的值插入，尾插
		{
			c->next = p;
			c = p;
			p = p->next;
		}
		else  
		{
			c->next = q;
			c = q;
			q = q->next;
		}
	}
	c->next = p ? p : q; //将最后的为输入完毕的全部加入链表
}
void Print_seq(LinkList L)
{
	printf("输出合并后的顺序链表:\n");
	L = L->next;
	for (int i = 0; i < ListLength(L); i++)
	{
		printf("%d ", L->data);
		L = L->next;
	}
}

int main(void)
{
	LinkList la;  //相当于Lnode* L;
	LinkList lb;
	LinkList lc;
	printf("la数据5个，用空格隔开:");
	CreateList_R(la, 5); //头插法
	printf("lb数据4个，用空格隔开:");
	CreateList_R(lb, 4);
	InitList(lc);
	seq_uion(la, lb, lc);
	Print_seq(lc);
	return 0;
}