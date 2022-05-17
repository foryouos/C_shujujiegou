#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//三对角矩阵，又称带状矩阵

#define MaxSize 7    //一维数组存储二维数组空间大小
typedef int ElemType;
//三对角矩阵
typedef struct juzhen {
	ElemType data[3*MaxSize-2];   //数据存储所需要的空间大小
	int length;  
}juzhen, * Linkjuzhen;
void Push(Linkjuzhen& L) {//向矩阵中插入数据
	//对于对称矩阵直接按照行列的顺序进行插入//输出费工夫
	int b[30] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 };
	int n = 3 * MaxSize - 2;   //除号保留了小数哈
	for (int i = 0; i < n; i++) {
		L->data[i] = b[i];   //输入对应的矩阵值，按照行列的形式不断进行输入
		L->length++;
	}
}
//输出三对角矩阵
void Pop(Linkjuzhen L) {
	//三角矩阵从 第一个数据1个，依次累加到MaxSize
	for (int i = 1; i <= MaxSize; i++)  //i的值记录的是下三角区存数据区的大小
	{
		for (int j = 1; j <= MaxSize; j++)
		{
			if ((i==1&&j <= 2) || (i == MaxSize && j>MaxSize-2))
			{
				printf("%5d", L->data[2 * i + j - 2 - 1]);
			}
			else if (i>1 && i<MaxSize) {  //此处不能有循环
				if (j-1>=0&&j-1 < i - 2) {
					printf("%5d", 0);
				}
				if (j-1>=i-2&&j <= 3+i-2) {
					printf("%5d", L->data[2 * i + j - 2-1]);
				}
				if (j> 3 + i - 2 &&j <= MaxSize) {
					printf("%5d", 0);
				}
				
			}
			else {
				//其它区间全部输出为零
				printf("%5d",0);
			}

		}
		printf("\n");//一行输入完毕，进行换行
	}
}
int main() {
	juzhen* J;
	J = (juzhen*)malloc(sizeof(juzhen));
	J->length = 0;
	Push(J);
	Pop(J);
	return 0;

}
