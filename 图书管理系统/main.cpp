#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 100  //图书表可以达到的最大长度
typedef char ElemType;		//定义顺序表的数据类型

//顺序表结构体
typedef struct Book //图书信息定义
{
	ElemType no[20];   //图书ISBN
	ElemType name[50];  //图书名称
	int price;		//图书价格
};

typedef struct LNode
{
	struct Book data;
	struct LNode* next;
}LNode,*LinkList;
//获取链表的长度
int ListLength(LNode* L)
{
	LinkList p;
	p = L->next;
	int length = 0;
	while (p)
	{
		length++;
		p = p->next;
	}
	return length;
}



//头插法插入数据
void CreateList_L(LinkList& L, int n)
{
	char ch='j';
	int i = 0;
	char m[20];
	L = (LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	for ( i = n; i > 0; i--)
	{
		LNode* p;
		p = (LNode*)malloc(sizeof(LNode));
		
		printf("请输入书籍名称:");
		//fgets(p->data.name, 50, stdin);
		scanf("%s", m);
		scanf("%c", &ch);
		strcpy(p->data.name, m);
		//strcpy(p->data.name, "foryouos");
		printf("请输入书籍编号:");
		//fgets(p->data.no, 20, stdin);
		scanf("%s", m);
		scanf("%c", &ch);
		strcpy(p->data.no, m);
		//strcpy(L[0]->data.no, "0000001");
		printf("请输出书本价格:");

		scanf("%d", &n);
		//printf("%d\n",n);
		p->data.price = n;
		//printf("%d\n", p->data.price);

		p->next = L->next;
		L->next = p;
		scanf("%c", &ch);//读取\n
		printf("\n");
	}
}


//保存到文件中，方便第二次打开读取
void File_Save(LinkList& L,int n, char location[10])
{
	LNode* p;
	p = L->next;
	FILE* fp;
	fp = fopen(location, "w+");//会覆盖掉之前的文件，谨慎使用
	for (int i = 0; i < n; i++)
	{
		//printf("保存的数据为：%s  %s  %d\n", p->data.name, p->data.no, p->data.price);
		fprintf(fp, "%s		%s		%d\n", p->data.name, p->data.no, p->data.price);
		p = p->next;
	}
	fclose(fp);
}
//刚开始的文件操作
void file_open(LinkList &L,char location[10])//第一个为链表，第二个为当前文件所对应的类型文件
{
	FILE* fp;
	//fp = fopen(location, "w");//如果没有文件，创建文件,但会覆盖之前文件
	//fclose(fp);

	fp = fopen(location, "r+");
	//判断文件是否为空
	int ch = fgetc(fp);  //读取了字符，改变了文件指针，必须修改指针，才能完整获得字符
	if (ch != EOF)  //判断文件是否为空
	{
		L = (LNode*)malloc(sizeof(LNode));
		L->next = NULL;
		printf("book文件有数据,正在将数据读入链表\n");
		while (ch != EOF)
		{
			LNode* p;
			p = (LNode*)malloc(sizeof(LNode));
			fseek(fp, -1, SEEK_CUR); //由于读取字符的缘故，指针向前偏移一个位置
			fscanf(fp, "%s		%s		%d\n", p->data.name, p->data.no, &p->data.price);
			printf("读取的数据为：%s  %s  %d\n", p->data.name, p->data.no, p->data.price);
			p->next = L->next;
			L->next = p;
			ch = fgetc(fp);
		}
		fclose(fp);

	}
	else
	{
		printf("book文件中没有数据，需要初始化数据并存入文件\n");
		fclose(fp);
		int n;
		printf("请输入你要存入的数据个数:");
		scanf("%d", &n);
		char ch;
		scanf("%c", &ch);
		CreateList_L(L, n);
		char m[10] = "book1.txt";
		File_Save(L, n,m);
	}
}
//返回
LNode* LocateElem(LinkList L, ElemType e[50])
{

	LNode* p;
	p = L->next;
	//通过strcmp函数来比较char*型字符串的比较
	while (p && strcmp((char*)p->data.name,e)) //当p不为空或者p->data.name != e时执行，直到达到条件
	{
		p = p->next;
	}
	return p;  //返回数据元素的地址
}

//尾插法
void CreateList_R(LinkList& L,int n1)
{
	LNode* r;
	LNode* q=L->next;
	char ch = 'j';
	int i = 0;
	char m[20];
	int n = 0;
	while(q->next)
	{
		q = q->next;
	}
	r = q;

	for (i = 0; i < n1; i++)
	{
		LNode* p;
		p = (LNode*)malloc(sizeof(LNode));
		printf("请输入书籍名称:");
		scanf("%s", m);
		scanf("%c", &ch);
		strcpy(p->data.name, m);
		printf("请输入书籍编号:");
		scanf("%s", m);
		scanf("%c", &ch);
		strcpy(p->data.no, m);
		
		printf("请输出书本价格:");
		
		scanf("%d", &n);
	
		p->data.price = n;
		
		p->next = NULL;
		r->next = p;
		r = p;
		scanf("%c", &ch);//读取\n


		printf("\n");
	}
}
void List_Delete(LinkList& L, ElemType e[50])
{
	LNode* p = L->next;;
	LNode* q=L->next;
	
	//通过strcmp函数来比较char*型字符串的比较
	while (p && strcmp((char*)p->data.name, e)) //当p不为空或者p->data.name != e时执行，直到达到条件
	{
		q = p;
		p = p->next;
	}

	q->next = p->next;
	free(p);
}
void Book_UI(LinkList &L)
{
	int t;//存放要进入的图书操作
	printf("\t\t\t******************图书管理系统******************\n\n");
	printf("\t\t\t********图书操作******||*******图书类别*********\n\n");
	printf("\t\t\t  ********1,查找******||*******出版*********\n\n");
	printf("\t\t\t  ********2,插入******||*******小说*********\n\n");
	printf("\t\t\t  ********3,删除******||*******青春*********\n\n");
	printf("\t\t\t  ********4,修改******||*******网文*********\n\n");
	printf("\t\t\t  ********5,排序******||*******历史*********\n\n");
	printf("\t\t\t  ********6,计数******||*******政治*********\n\n");
	printf("\t\t\t  ********0,主页******||*******经济*********\n\n");

	printf("请输入你要执行的操作(输入编号): ");
	scanf("%d", &t);
	switch (t)
	{
	case 1:
	{
		ElemType m[20];
		system("cls");
		printf("\t\t\t***********您已进入图书查找页面，根据书名查看相关编号和价格......\n\n\n"); 
		printf("\t\t\t***********请输入你要查询的书名:");
		scanf("%s", m);
		//printf("\n%s\n", m);
		LinkList p;
		//p = (LNode*)malloc(sizeof(LNode));
		p=LocateElem(L, m); //返回查询数据元素的地址
		printf("\t\t\t************书籍名称：%s\n", p->data.name);
		printf("\t\t\t************书籍名称：%s\n", p->data.no);
		printf("\t\t\t************书籍名称：%d\n", p->data.price);
		Book_UI(L);
		break;
	}
	case 2:
	{
		system("cls");
		printf("您已进入图书插入页面......\n");//插入新的图书
		//使用尾插法更新图书
		//并同时将更新内容到文件当中，使用fseek指针定位到末尾
		int n;
		printf("***********使用尾插法：请输入你要插入的个数:");
		scanf("%d", &n);

		CreateList_R(L,n);

		Book_UI(L);
		break;
	}
	case 3:
	{

		ElemType m[20];
		system("cls");
		printf("\n\t\t\t*****************您已进入图书删除页面......\n");
		printf("请输入你要删除的书籍名称:");
		scanf("%s", m);
		List_Delete(L, m); //返回书籍名称全面那个指针


		Book_UI(L);
		break;
	}
	case 4:
	{
		ElemType m[20];
		ElemType ch[20];
		system("cls");
		printf("您已进入图书修改页面......\n");
		printf("请输入你要删除的书籍名称:");
		scanf("%s", m);
		LNode* p;
		p = LocateElem(L,m);
		Loop:
			int i = 0;
			printf("请输入你要修改的编号:1,名称，2，编号，3，价格：");
			scanf("%d", &i);
			if (1 == i) 
			{
				printf("请输入书籍编号:");
				scanf("%s", m);
				scanf("%c", &ch);
				strcpy(p->data.name, m);
			}
			else if (2 == i)
			{
				printf("请输入书籍编号:");
				scanf("%s", m);
				scanf("%c", &ch);
				strcpy(p->data.no, m);
			}
			else if (3 == i)
			{
				int n;
				printf("请输出书本价格:");

				scanf("%d", &n);
				p->data.price = n;
				scanf("%c", &ch);//读取\n
			}
			else
			{
				printf("您输入错入，请重新出");
				goto Loop;
			}
		Book_UI(L);
		break;
	}
	case 5:
	{
		system("cls");
		printf("您已进入图书排序页面......\n");



		Book_UI(L);
		break;
	}
	case 6:
	{
		system("cls");
		printf("您已进入图书计数页面......\n");



		Book_UI(L);
		break;
	}
	case 0:
	{
		system("cls");
		printf("您已进入图书主页......\n");
		Book_UI(L);
		break;
	}
	default:
		printf("您输入编号错误！");
		break;
	}
}
int main(void)
{
	printf("数据库初始化........\n");
	LNode* L[10];	
	/*将图书管理数据存入文件当中，如果退出必须先存储数据
	启动时，读取文件系统数据，若为空为首次登陆需要填写数据*/
	//使用头插法存入数据
	char m[10] = "book1.txt";
	file_open(L[0],m);
	//初始化完成
	//printf("time : %ld\n", time(NULL));
	printf("初始化完成.....\n");
	system("cls");

	Book_UI(L[0]);
	int length = ListLength(L[0]);
	File_Save(L[0], length,m);

	printf("内容已经全部存入文件当中\n");
	printf("\n\nThank You\n\n");
	return 0;
}
