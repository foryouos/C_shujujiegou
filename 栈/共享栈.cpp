#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//共享栈的实现

typedef int Elemtype;
#define MaxSize 6

//实际上是一个栈，通过两个top来进行共享，分别进行输出
typedef struct ShStack {
	Elemtype data[MaxSize];
	Elemtype top0;//1号栈
	Elemtype top1;//2号栈
}ShStack, * linkShStack;
//初始化共享栈
void InitShStack(ShStack& S) {
	S.top0 = -1;//栈为空
	S.top1 = MaxSize;//栈为最大值
}
//判断栈满
bool FullShStack(ShStack &S) {
	if (S.top0 + 1 == S.top1) {
		return true;
	}
	else {
		return false;
	}
}
//判断栈空
bool EmptyShStack(ShStack& S) {
	if (S.top0 == -1 && S.top1 == MaxSize) {
		return true;
	}
	else {
		return false;
	}
}


//向栈中添加数据,共享栈，虽然为一个栈，但是共享栈被查分成两个栈
bool Insert1ShStack(ShStack& S,Elemtype x) {
	if (FullShStack(S)) {
		return false;
	}
	else {//插入,
		S.data[++S.top0] = x;
		return true;
	}
}

bool Insert2ShStack(ShStack& S, Elemtype x) {
	if (FullShStack(S)) {
		return false;
	}
	else {//从高往下插入数据
		S.data[--S.top1] = x;
		return true;
	}
}
void PrintShtack(ShStack S) {
	while (S.top0 != -1) {
		printf("%d", S.data[S.top0--]);
	}
	while (S.top1 != MaxSize) {
		printf("%d", S.data[S.top1++]);
	}
}



int main() {
	ShStack S;
	InitShStack(S);
	Elemtype x;
	scanf("%d", &x);
	//插入第一个栈
	while (x != 9999) {
		Insert1ShStack(S, x);
		scanf("%d", &x);
	}
	scanf("%d", &x);
	//插入第二个栈
	while (x != 9999) {
		Insert2ShStack(S, x);
		scanf("%d", &x);
	}
	
	//输出栈
	PrintShtack(S);


}
