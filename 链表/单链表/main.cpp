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
}Lnode,*LinkList;  //LinkList为指向结构体Lnode的指针类型

//单链表初始化
Status InitList(LinkList& L)
{
	L = (LinkList)malloc(sizeof(Lnode)); //或者用C++: new Lnode
	L->next = NULL;  //下一个结点为空
	return OK;
}
//判断链表是否为空
int ListEmpty(LinkList L)
{
	if (L->next) //非空,存在
	{
		return 0;
	}
	else
		return 1;
}
//单链表的销毁：从头指针开始，依次释放所有结点
Status DestoryList_L(LinkList& L)
{
	Lnode* P;
	while (L)//当L不是空使
	{
		P = L;
		L = L->next;
		free(P);
	}
	return OK;
}
//清空链表，（头指针和头结点仍存在)
Status ClearList(LinkList& L)
{
	Lnode* p, * q;
	p = L->next;  //保留头指针
	while (p)   //到末尾
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL; //头结点指针域为空
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
//取值：取单链表中第i个元素，值返回给e
Status GetElem_L(LinkList L, int i, ElemType& e)
{
	Lnode* p;
	p = L->next;
	int j = 1;
	while (p && j < i) //向后扫描，直到p指向第i个元素或p为空
	{
		p = p->next;
		++j;
	}
	if (!p || j > i) //第i个元素不存在
		return ERROR;
	e = p->data;
	return OK;
}
//单链表的查找
/*在线性表L中查找值为e的数据元素，找到返回L中值为e的数据元素的地址，失败返回NULL*/
Lnode* LocateElem(LinkList L, ElemType e)
{
	Lnode* p;
	p = L->next;
	while (p && p->data != e)
	{
		p = p->next;
	}
	return p;  //返回数据元素的地址
}
//返回元素对应的序号
int LocateElem_L(LinkList L, ElemType e)
{
	Lnode* p;
	p = L->next;
	int j = 1;
	while (p && p->data != e)
	{
		p = p->next;
		j++;
	}
	if (p)
	{
		return j;
	}
	else
	{
		return 0;
	}
}
//在L中第i个元素之前插入数据元素e
Status ListInsert_L(LinkList& L, int i, ElemType e)
{
	Lnode* s;
	Lnode* p=L;
	int j= 0;
	while (p && j < i - 1)//当i大于L的长度，p循环到空。或者i为负数
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
	{
		return ERROR;
	}
	s = (Lnode*)malloc(sizeof(Lnode));  //生成新节点，将结点s的数据域置为e
	s->data = e;
	s->next = p->next; //将结点s插入L中
	p->next = s;
}
//将线性表L中第i个数据元素删除
Status ListDelete_L(LinkList& L, int i, ElemType& e)
{
	Lnode* p = L;
	int j = 0;
	while (p->next && j < i - 1) //将p指向其前驱
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)  //删除位置不合理
	{
		return ERROR;
	}
	Lnode* q = p->next;  //临时保存被删结点的地址以备释放
	p->next = q->next;
	e = p->data;
	free(p);
	return OK;
}
//头插法
void CreateList_L(LinkList& L, int n)
{
	L = (Lnode*)malloc(sizeof(Lnode));
	L->next = NULL;
	for (int i = n; i > 0; i--)
	{
		Lnode* p;
		p = (Lnode*)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
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
		p= (Lnode*)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = NULL;
		r->next = p;
		r = p;
	}
}
//线性表的合并
void Union(LinkList& la, LinkList lb)
{
	int e;
	int la_len =ListLength(la);
	int lb_len = ListLength(lb);
	for (int i = 1; i < lb_len; i++)
	{
		GetElem_L(lb, i, e);
		if (!LocateElem(la, e))
		{
			ListInsert_L(la, ++la_len, e);
		}
	}

}


int main(void)
{
	LinkList L;  //相当于Lnode* L;
	//单链表初始化
	//InitList(L);
	//判断链表是否为空 ,空链表看指针域是否为空
	//ListEmpty(L);
	//单链表的销毁
	//DestoryList_L(L);
	//清空链表，保留头指针和头结点
	//ClearList(L);
	//求链表的表长
	//int length = ListLength(L);
	//获取链表中第i个元素的值
	int e;
	//GetElem_L(L, 2, e);
	//查找数据所在的位置  地址/序号
	//地址
	//LocateElem(L, 3);//查找值为3的数据元素地址
	//查找3的返回序号
	//LocateElem_L(L, 3);//返回值为3的序号
	//在第i个结点前插入值为e的新结点
	//ListDelete_L(L, 3, e);
	//单链表的建立
	//头插法
	//printf("使用尾插法插入三个元素:");
	//CreateList_L(L, 3);
	
	

	return 0;
}