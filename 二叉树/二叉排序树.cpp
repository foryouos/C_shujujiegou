#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//二叉排序树--非常重要应用很广
typedef int KeyType;
typedef struct BSTNode {
	KeyType key;
	struct BSTNode* lchild, * rchild;
}BSTNode,*BiTree;
//将数据插入二叉树
int BST_Insert(BiTree&T,KeyType k) {
	if (NULL == T) {
		//为新节点申请空间
		T = (BiTree)malloc(sizeof(BSTNode));
		T->key = k;
		T->lchild = T->rchild = NULL;
		return 1;//代表插入成功
	}
	else if (k == T->key) {//二叉树不允许插入相同元素
		return 0;//发现相同元素，就不插入
	}
	else if (k < T->key) {
		return BST_Insert(T->lchild, k);
	}
	else {
		return BST_Insert(T->rchild, k);
	}
}


//创建二叉排序树
void Creat_BST(BiTree& T, KeyType str[], int n) {
	T = NULL;
	int i = 0;
	while (i<n)
	{
		BST_Insert(T, str[i]);//把某个节点放入二叉查找树
		i++;
	}
}
void visit(BiTree T) {//输出
	/*printf("\n");*/
	printf("%5d", T->key);
}
void InOrder(BiTree RootTree) {

	if (RootTree != NULL) {
		InOrder(RootTree->lchild);
		visit(RootTree);
		InOrder(RootTree->rchild);
	}


}
BSTNode* BST_Search(BiTree T, KeyType key, BiTree& p) {
	p = NULL; //存储要找到结点的父亲结点
	while (T!=NULL&&key!=T->key)
	{
		p = T;
		if (key < T->key) {
			T = T->lchild;//比当前结点小，就左边找
		}
		else {
			T = T->rchild;
		}
	}
	return T;
}
void DeleteNode(BiTree& root, KeyType x) {
	if (root == NULL) {
		return;
	}
	if (root->key > x) {
		DeleteNode(root->lchild, x);
	}
	else if(root->key<x){
		DeleteNode(root->rchild, x);
	}
	else {//找到了删除的节点
		if (root->lchild == NULL) {//左子树为空，右子树直接顶上去
			BiTree tempNode = root;//临时存储的目的是等会free
			root = root->rchild;
			free(tempNode);
		}
		else if (root->rchild == NULL) {//右子树为空，左子树直接顶上去
			BiTree tempNode = root;//临时存储的目的是等会free
			root = root->lchild;
			free(tempNode);
		}
		else {//左右指数都不为空
//一般的删除策略就是左子树的最大数据或者右子树的最小数据，代替要删除的节点
//这里采用左子树最大数据来替代
			BiTree tempNode = root->lchild;
			if (tempNode->rchild != NULL) {
				tempNode = tempNode->rchild;
			}
			root->key = tempNode->key;
			DeleteNode(root->lchild, tempNode->key);//下次不断递归，
		}
	}
}



int main() {
	BiTree T = NULL;//树根
	BiTree parent;//存储父亲节点的地址值
	BiTree search;
	KeyType str[] = { 54,20,66,40,28,79,58 };//将要存储的二叉树值
	Creat_BST(T, str, 7);
	//中序遍历
	InOrder(T);
	printf("\n");
	search = BST_Search(T, 40, parent);
	if (search) {
		printf("找到对应值=%d\n", search->key);
	}
	else {
		printf("未找到对应值\n"); //没有找到search返回null
	}
	//删除某个结点值
	DeleteNode(T, 66);
	InOrder(T);




	return 0;
}
