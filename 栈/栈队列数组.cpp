#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//顺序栈的实现

typedef int Elemtype;
#define MaxSize 50
typedef struct SqStack {
	Elemtype data[MaxSize];
	int top;
}SqStack,*linkSqStack;
//初始化栈。栈顶指针指向-1
void InitStack(SqStack &S) {
	S.top= -1;
}
//为栈添加数据
bool Push(SqStack &S, Elemtype x) {
	if (S.top == MaxSize - 1) {
		return false;
	}
	else {
		S.data[++S.top] = x;
		return true;
	}
}
//判断栈是否为空
bool stackEmpty(SqStack S) {
	if (S.top == -1) {
		return true;
	}
	else {
		return false;
	}
}
//判断栈是否满
bool stackFull(SqStack& S) {
	if (S.top == MaxSize-1) {
		return true;
	}
	else {
		return false;
	}
}
//输出栈,栈采用后进先出的政策.逻辑上给予
void PrintStack(SqStack S) {
	while (S.top != -1) {
		printf("%d", S.data[S.top--]);//s.top指向顶部指针
	}
}
//读取栈顶元素
bool GetTop(SqStack S,Elemtype &a) {
	if (S.top == -1) {
		return false;
	}
	else {
		printf("栈顶元素为%d\n", S.data[S.top]);
		a = S.data[S.top];
		return true;
	}
	
}

//删除栈数据，删除最后一个的话，就是逻辑上调整top指针向下，
bool DeleteTopStalk(SqStack &S, Elemtype& b) {
	if (S.top == -1) {
		printf("flase");
		return false;
	}
	else {
		S.top--; //删除栈顶元素，仅逻辑上将栈顶指针向下
		return true;
	}
}

//改变某个栈的数据，要经历一系列出栈和入栈

//查找某个栈的数据->通过序号和查找值两种方式

int main() {
	//定义栈
	SqStack S;
	InitStack(S);
	//对栈输入内容
	int x;//定义要加入的内容
	//设置特定的值，进行入栈处理
	scanf("%d", &x);
	while(x != 9999) {
		Push(S, x);
		scanf("%d", &x);
	}
	if (stackEmpty) {
		PrintStack(S);//输出栈
	}
	else {
		printf("栈为空");
	}
	int a;
	//读取栈顶元素
	if (GetTop(S,a)) {
		printf("读取栈顶元素成功,栈顶元素为%d\n",a);
	}
	else {
		printf("读取栈顶元素失败");
	}
	int b;//记录删除的栈顶元素
	if (DeleteTopStalk(S, b)) {
		PrintStack(S);
	}
	
	
	return 0;
}
