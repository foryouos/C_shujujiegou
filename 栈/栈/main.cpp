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

typedef struct 
{
	ElemType* base;
	ElemType* top;
	int stacksize;  //栈可用最大容量
}SqStack;
Status InitStack(SqStack* &S)
{
	S->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	if (!S->base)
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = MAXSIZE;
}
Status StackEmpty(SqStack* S)
{
	if (S->top == S->base)
		return TRUE;
	else
		return FALSE;
}
int StackLength(SqStack* S)
{
	return S->top - S->base;
}
//销毁顺序栈
Status DestoryStack(SqStack*& S)
{
	if (S->base)
	{
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return OK;
}
//入栈
Status Push(SqStack* &S, ElemType e)
{
	if (S->top - S->base == S->stacksize)
		return ERROR;
	*S->top++ = e;
	/*相当于
	*S->top=e;
	S->top++*/
	return OK;
}
//出栈
Status Pop(SqStack*& S, ElemType& e)
{
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
	if (S->top == S->base)
		return ERROR;
	e = *--S->top;
	//相当于
	//--S->top;
	//e=*S->top;

	return OK;
}
void Print_Stack(SqStack* S)
{
	while (S->base != S->top)
	{
		S->top--;
		printf("%d\n", *S->top);
		
	}
		

}
int main(void)
{
	SqStack* S;
	int e;
	int n;
	char ch;
	S = (SqStack*)malloc(sizeof(SqStack));
	InitStack(S);
	//StackEmpty(S);
	//DestoryStack(S);
	printf("入栈操作：请输入你要入栈的个数：");
	scanf("%d", &n);
	for (int j = 0; j < n; j++)
	{
		printf("请输入%d个栈", j + 1);
		scanf("%d", &e);
		Push(S, e);
		scanf("%c", &ch);
	}
	Print_Stack(S);
	printf("栈输出完毕！\n");
	return 0;
}
