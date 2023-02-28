#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define List_INIT_SIZE 10  //顺序表的大小
typedef int Status;
typedef int ElemType;
typedef struct SqList
{
	ElemType* elem;
	int length;
};
Status InitList_Sq(struct SqList& L)
{
	L.elem = (ElemType*)malloc(sizeof(ElemType) * List_INIT_SIZE);
	if (!L.elem)
		exit(OVERFLOW); //退出程序函数，为1异常退出，0正常退出
	L.length = 0;
	return OK;
}
//返回线性表的长度
int GetLength(struct SqList L)
{
	return L.length;
}
Status List_voluation(struct SqList& L, ElemType e)
{
	L.elem[L.length] = e;
	L.length++;			//表长+1
	return OK;
}
void MergeList_sq(SqList LA, SqList LB, SqList& LC)
{
	ElemType* pa = LA.elem;
	ElemType* pb = LB.elem;
	LC.length = LA.length + LB.length;
	LC.elem = (ElemType*)malloc(sizeof(ElemType) * LC.length);
	ElemType* pc = LC.elem;
	ElemType* pa_last = LA.elem + LA.length - 1;
	ElemType* pb_last = LB.elem + LB.length - 1;
	while (pa <= pa_last && pb <= pb_last)
	{
		if (*pa <= *pb)
			*pc++ = *pa++;
		else
			*pc++ = *pb++;
	}
	while (pa <= pa_last)
		*pc++ = *pa++;
	while (pb <= pb_last)
	{
		*pc++ = *pb++;
	}

}



int main(void)
{
	int n;		//存储用户输入的值
	int i;
	SqList LA;  //合并表1
	SqList LB;	//合并表2
	InitList_Sq(LA);
	InitList_Sq(LB);
	printf("请问顺序表LA赋值：");
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &n);
		List_voluation(LA, n);
	}
	printf("\n");
	printf("请问顺序表LB赋值：");
	for (i = 0; i < 3; i++)
	{
		scanf("%d", &n);
		List_voluation(LB, n);
	}
	printf("\n");
	SqList LC; //合并空间
	MergeList_sq(LA, LB, LC);
	int j;
	for (j = 0; j < LC.length; j++)
	{
		printf("%d ", LC.elem[j]);
	}
	printf("\n");
	return 0;
}