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

typedef struct SqQueue
{
	ElemType* base;//初始化动态分配存储空间
	int front;  //头指针
	int rear;   //尾指针
}SqQueue;
Status InitQueue(SqQueue* &Q)
{
	Q->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	if (!Q->base)
		exit(OVERFLOW);
	Q->front = Q->rear = 0;  //头指针，尾指针置为空，队列为空
	return OK;
}
//求队列的长度
int QueueLength(SqQueue* Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;  //循环队列
}
//循环队列的入队
Status EnQueue(SqQueue*& Q, ElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		return ERROR;//堆满
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}
//出队
Status DeQueue(SqQueue*& Q, ElemType& e)
{
	if (Q->front == Q->rear)
		return ERROR;//队空
	e = Q->base[Q->front];		//保存队头元素
	Q->front = (Q->front + 1) % MAXSIZE;  //队头指针+1
	return OK;
}
ElemType GetHead(SqQueue* Q)
{
	if (Q->front != Q->rear)   //队列不为空
		return Q->base[Q->front];  //返回队头指针元素的值，队头指针不变
}


int main(void)
{
	SqQueue* S;

	return 0;
}

