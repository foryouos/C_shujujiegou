#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//矩阵数据，考虑的是空间复杂度
#define MaxSize_x 2    //行
#define MaxSize_y 4    //列

typedef int ElemType;
//存储矩阵数据
typedef struct juzhen {
	ElemType data[MaxSize_x][MaxSize_y];
	int length;  //存储矩阵个数  //用处未知
}juzhen,*Linkjuzhen;
void Push(Linkjuzhen& L) {//向矩阵中插入数据
	//使用for循环插入数据
	for (int i = 0; i < MaxSize_x; i++) {
		for (int j = 0; j < MaxSize_y; j++) {
			L->data[i][j] = 5;   //输入对应的矩阵值，按照行列的形式不断进行输入
		}
	}
}
//使用矩阵的样式输出可视化矩阵
void Pop(Linkjuzhen L) {
	for (int i = 0; i < MaxSize_x; i++) {
		for (int j = 0; j < MaxSize_y; j++) {
			printf("%d  ", L->data[i][j]);
		}
		printf("\n");//换行
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
