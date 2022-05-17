#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//对称矩阵
//若n阶矩阵中任意一个元素Aij都有Aij=Aji,则该矩阵为对称矩阵

//如何应对节省剩下的空间,,

#define MaxSize 6    //一维数组存储二维数组空间大小
typedef int ElemType;
//存储矩阵数据
typedef struct juzhen {
	ElemType data[(1+MaxSize)*MaxSize/2]; //使用一维数组存储二维数组的数据，利用性质，与空间存储的连续性
	int length;  //记录到哪里存储数据结束，使用对称矩阵进行数据存储
}juzhen, * Linkjuzhen;

void Push(Linkjuzhen& L) {//向矩阵中插入数据
	//对于对称矩阵直接按照行列的顺序进行插入//输出费工夫
	int b[30] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
	int n = (1 + MaxSize) * MaxSize / 2;   //除号保留了小数哈
	for (int i = 0; i < n; i++) {
		L->data[i] = b[i];   //输入对应的矩阵值，按照行列的形式不断进行输入
		L->length++;
	}
}
//使用矩阵的样式输出可视化对称矩阵
void Pop(Linkjuzhen L) {
	int a;//记录取值区间
	//三角矩阵从 第一个数据1个，依次累加到MaxSize
	for (int i = 0; i < MaxSize; i++)  //i的值记录的是下三角区存数据区的大小
	{
		for(int j = 0; j < MaxSize; j++) 
		{
			if (j <= i) 
			{
				//记录上三角前面数值所占的空间,继续进行累加计算
				printf("%5d", L->data[(1+i)*i/2+j]); 
			}
			else {//映射函数，将上三角函数的值映射到下三角函数
				//找到对应位置的数组，在一维数组的存储位置

				printf("%5d", L->data[(1 + j) * j / 2 +i]);
			}

		}
		printf("\n");//一行输入完毕，进行换行
	}
}
int main() {
	int n;
	juzhen* J;
	J = (juzhen*)malloc(sizeof(juzhen));
	J->length = 0;
	Push(J);
	Pop(J);
	return 0;
}
