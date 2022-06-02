#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int ElemType;
//定义树
typedef struct BiTree {
	ElemType data;
	struct BiTree* lchild;
	struct BiTree* rchild;
}BiTree, * P_BiTree;
//定义辅助队列
typedef struct Queue {
	P_BiTree tree;  //使用指针模式可以直接根据队列来间接修改数，
	struct Queue* P_next;  //队列记录入队顺序，以便判断在哪里加入队列
}Queue, * P_Queue;
//创建二叉树函数

//创建层次遍历链式队列，队列（数据，下一个指着），头结点，尾结点
typedef struct LinkNode {
	P_BiTree data;
	struct LinkNode* next;
}LinkNode;
typedef struct {
	LinkNode* front, * rear;
}LinkQueue;

void BuildTree(P_BiTree* RootTree, P_Queue* Head, P_Queue* Tail, ElemType T)
{
	//对二叉树和队列初始化
	BiTree* NewTree = (BiTree*)malloc(sizeof(BiTree));  //新二叉树记录新的数据
	NewTree->lchild = NULL;
	NewTree->rchild = NULL;
	P_Queue NewQueue = (P_Queue)malloc(sizeof(Queue));
	P_Queue QueueLin = *Head;
	//定义临时队列，和新树
	NewTree->data = T;
	NewQueue->tree = NewTree;
	if (NULL == *RootTree) {
		*RootTree = NewTree;
		*Head = NewQueue;
		*Tail = NewQueue;
	}
	else {
		(*Tail)->P_next = NewQueue;
		*Tail = NewQueue;//尾指针指向最后的新队列
		if (NULL == QueueLin->tree->lchild) {
			QueueLin->tree->lchild = NewTree;
		}
		else {
			QueueLin->tree->rchild = NewTree;
			//然后向队列向前
			*Head = QueueLin->P_next;
			//删除临时队列，并释放空间
			free(QueueLin);
			QueueLin = NULL;
		}
	}
}
//二叉树遍历
void visit(P_BiTree RootTree)
{
	printf("%d", RootTree->data);//直接输出二叉树值
}



//先序遍历
void PreOrder(P_BiTree RootTree) {

	if (RootTree != NULL) {
		visit(RootTree);
		PreOrder(RootTree->lchild);
		PreOrder(RootTree->rchild);
	}

}
//中序遍历
void InOrder(P_BiTree RootTree) {

	if (RootTree != NULL) {
		InOrder(RootTree->lchild);
		visit(RootTree);
		InOrder(RootTree->rchild);
	}


}
//后序遍历
void PostOrder(P_BiTree RootTree) {

	if (RootTree != NULL) {
		PostOrder(RootTree->lchild);
		visit(RootTree);
		PostOrder(RootTree->rchild);
	}

}
void InitNode(LinkNode*& Q, LinkQueue*& N) {
	Q = (LinkNode*)malloc(sizeof(LinkNode));//初始化空间
	Q->next = N->front;//不带头结点
	N->front = N->rear = Q;
}
//入队----尾结点入
void EnQueue(P_BiTree &T, LinkQueue*& N) {
	LinkNode* P = (LinkNode*)malloc(sizeof(LinkNode));
	P->data = T; //将节点的值给临时队列
	P->next = NULL;
	N->rear->next = P;//带头节点的队列  尾插法
	N->rear = P;
}

//出队----从头结点出来
bool DeQueue(LinkQueue*& N, P_BiTree& x) {
	
	if (N->front == N->rear) {
		return false;
	}
	LinkNode* p = N->front->next;
	p = N->front->next;
	x = p->data;
	N->front->next = p->next;
	if (N->rear == p) {
		N->rear = N->front;
	}
	
}
//判空
bool IsEmpty(LinkQueue*& N) {
	if (N->rear == N->front) {
		return true;
	}
	else {
		return false;
	}
}
//层次遍历
void LevelOrder(P_BiTree T) {//后序遍历
	//使用一个临时队列，依次进入并输出
	LinkNode* Q; //初始化指针队列
	LinkQueue* N = (LinkQueue*)malloc(sizeof(LinkQueue)); //初始化队列指针
	InitNode(Q, N);   //队列数据初始化，初始化指针指向位置
	P_BiTree P; //定义二叉树
	EnQueue(T, N);   //将头节点放入队列
	while (!IsEmpty(N)) {//当非空的时候执行如下语句
		DeQueue(N,P);
		visit(P);  //队列输出那个，然后判断那个，并将其子集放入队列
		if (P->lchild != NULL) {
			EnQueue(P->lchild,N);
		}
		if (P->rchild != NULL) {
			EnQueue(P->rchild,N);
		}

		
	}
}



//主函数
int main() {
	//定义根节点
	P_BiTree RootTree = NULL;
	//定义头队列
	//记录队列的头指针，尾指针，头指针二叉树进入左或右指针
	//尾指针用于向队列后添加数据
	P_Queue Head = NULL;
	//定义尾队列
	P_Queue Tail = NULL;
	//定义输入值
	ElemType T[10] = { 1,2,3,4,5,6,7,8 };
	/*ElemType T;
	while (scanf("%d", &T) != EOF)
	{
		if (T=='\n') {
			break;
		}
		BuildTree(&RootTree, &Head, &Tail, T);
	}*/
	for (int i = 0; T[i]; i++) {
		if (T[i] == 0) {
			break;
		}
		BuildTree(&RootTree, &Head, &Tail, T[i]);
	}


	//先序遍历
	printf("\n先序遍历");
	PreOrder(RootTree);
	//中序遍历
	printf("\n中序遍历");
	InOrder(RootTree);
	//后序遍历
	printf("\n后序遍历");
	PostOrder(RootTree);
	//层次遍历
	//传入辅助队列复制值
	printf("\n层次遍历");
	LevelOrder(RootTree); 



	return 0;
}
