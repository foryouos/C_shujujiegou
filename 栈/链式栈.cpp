#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//链式栈的实现

typedef int Elemtype;
typedef struct LinkNode {
	Elemtype data;
	LinkNode *next; //指向下一个链表
}LinkNode, *LinkSNode;
bool InitLinkNode(LinkSNode& L) {//链表头结点也得初始化指针
	L = (LinkNode*)malloc(sizeof(LinkNode));
	printf("%d\n", L->data);//查看一下分配空间其值
	if (L == NULL)//带头结点的头指针
	{
		return false;
	}
	L->next = NULL;
	return true;
}
void Push(LinkSNode& L, Elemtype x) {
	LinkNode* S;
	S = (LinkNode*)malloc(sizeof(LinkNode));//申请地址
	S->data = x;
	S->next = L->next;
	L->next = S;
}
//输出链表
bool PrintLink(LinkNode* L) {
	L = L->next;
	if (L->next == NULL) {
		return false;
	}
	else {
		while (L) {
			printf("%d", L->data);
			L = L->next;
		}
		return true;
	}

}



int main() {
	LinkNode* L;
	//初始化链表指针
	InitLinkNode(L);
	//向聊表指针插入数据，使用头插法
	int x;
	scanf("%d", &x);
	while (x != 9999) {
		Push(L, x);
		scanf("%d", &x);
	}
	
	//输出数据,使用头部读取数据，先进出
	PrintLink(L);

	return 0;
}
