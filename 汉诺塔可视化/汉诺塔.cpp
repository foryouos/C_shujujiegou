/*
* project : 汉诺塔CMD可视化
* language：C
* time：2023年1月25日
* environment: VS2022
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
/*
*定义地图相关信息
* @sleepTime:等待时间
* @autoPlay:是否自动播放
* @wall：墙
* @pillar:柱子
* @hanoiLeft：汉诺塔圆盘左边显示
* @hanoiRight:汉诺塔圆盘右边显示
* @hanoiAir:汉诺塔圆盘中间镂空部分显示
*/
const int sleepTime = 5;  //每隔多长时间移动一下
const int autoPlay = 1;  //是否自动进行 0手动播放，
const char wall = '@';
const char pillar = '^';
const char hanoiLeft = '{';
const char hanoiRight = '}';
const char hanoiAir = '-';
const int up = 0, down = 1, left = 2, right = 3;
/*[控制移动]
*@next_go 下一次移动方向 //上0,下1左2右3
*/
int next_go[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
/*系统变量
*@abc_pillar[3][1000]  //当前柱子放置的圆盘数
* [高度，1长度，2长度，]
* [i][0]存放第i个柱子当前高度
* [i][j]表示第i个柱子第j层存放的圆盘大小
* @abc_x[3] abc柱子的坐标
*	数组可以直接通过ABC-'A'直接获取下标取值
*全局标量
* N：叠加的层数
* sum:记录移动次数 2^n -1;
*/
int N;
int sum; 
int abc_pillar[3][1000] = { {0},{0},{0} };
int abc_x[3] = { 0,0,0 };
int mapHeight, mapWidth;
int deep;

void gotoxy(int x, int y)//设置光标位置，从哪里开始输出
{
	COORD pos;//表示一个字符在控制台屏幕上的坐标，左上角（0，0）
	pos.X = x;
	pos.Y = y;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//GetStdhandle用于从一个特定的标准设备（标准输入、标准输出或标准错误）中取得一个句柄（用来标识不同设备的数值）。可以嵌套使用。

	SetConsoleCursorPosition(handle, pos);
}
/*
*清空x，y地方的绘制
* 并且绘制下一处长度为n的汉诺塔
*/
void drawHanoi(int& x, int& y, int n, int next) {
	// 清空原来的 
	char* replace = (char*)malloc(sizeof(char) * (2 * n + 1));

	for (int i = 0; i < 2 * n + 1; i++) {
		replace[i] = ' ';
		if (i == n && y != 1) {
			replace[i] = pillar;
		}
		if (i == 2 * n) {
			replace[i + 1] = '\0';
		}
	}
	gotoxy(x - n, y);
	printf("%s", replace);
	// 绘制新的 
	if (next != -1) {
		x += next_go[next][0];
		y += next_go[next][1];
	}
	for (int i = 0; i < 2 * n + 1; i++) {
		if (i == n && y != 1) {
			replace[i] = pillar;
		}
		else if (i == 0) {
			replace[i] = hanoiLeft;
		}
		else if (i == 2 * n) {
			replace[i] = hanoiRight;
		}
		else {
			replace[i] = hanoiAir;
		}
		if (i == 2 * n) {
			replace[i + 1] = '\0';
		}
	}
	gotoxy(x - n, y);
	printf("%s", replace);
	Sleep(sleepTime);
}


//定义隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;     //定义游标信息
	cursor.bVisible = FALSE;        //设置游标不可见
	cursor.dwSize = sizeof(cursor);  //设置游标不可见的数值
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);  //定义光标的位置
}
void move(char from, char to)
{
	gotoxy(0, mapHeight);
	printf("\n\t%c--->%c\n", from, to);
	sum++;
	printf("\n\t移动次数：%d", sum);
	//获取from的柱子有多少高定位从哪开始
	int fromHeight = abc_pillar[from - 'A'][0];  //获取from柱子放的圆盘数
	int n = abc_pillar[from - 'A'][fromHeight];//获取顶部圆盘大小
	int x = abc_x[from - 'A'];//获取当前柱子的x坐标
	int y = 2 + N - fromHeight; //获取当前y坐标
	abc_pillar[from - 'A'][0]--;//将出发的柱子相减
	//获取to的柱子高度，定位到那结束
	abc_pillar[to - 'A'][0]++; //将到达位置+1
	int toHeight = abc_pillar[to - 'A'][0]; //获取to柱子的圆盘数
	abc_pillar[to - 'A'][toHeight] = n;//将顶部的圆盘存进去
	int to_X = abc_x[to - 'A'];    //达到x的坐标
	int to_Y = 2 + N - toHeight;   //到达y的坐标
	//取出盘--->上升到顶部
	while (y > 1)
	{
		drawHanoi(x, y, n, up);  //移动绘画出来
	}
	//移动盘，移动到指定位置
	if (x < to_X)
	{
		while (x < to_X)
		{
			drawHanoi(x, y, n, right);
		}
	}
	else if (x > to_X)
	{
		while (x > to_X)
		{
			drawHanoi(x, y, n, left);
		}
	}
	//放置盘---->下降到上面
	while (y < to_Y)
	{
		drawHanoi(x, y, n, down);
	}
	//手动播放
	if (0 == autoPlay )
	{
		gotoxy(0, mapHeight + 2);
		printf("回车进行下一步");
		getchar();
	}

}
void init() {
	// 初始化柱子信息 
	abc_pillar[0][0] = N;
	for (int i = 1; i <= N; i++) {
		abc_pillar[0][i] = N + 1 - i;
	}
	//高度 = 上下墙(2) + deep(4) + 上空行(1) 
	//宽度 = 左右墙(2) + 3个区块[3*(deep*2+1)] + 两个中间空行(2)
	mapHeight = 2 + N + 1;
	mapWidth = 2 + 3 * (N * 2 + 1) + 2;

	//柱子0(a)水平坐标 = 左边墙(1) + deep(4) 
	//柱子1(b)水平坐标 = 柱子1 + 2*deep + 2 
	//柱子2(c)水平坐标 = 柱子2 + 2*deep + 2 
	abc_x[0] = 1 + N;
	abc_x[1] = abc_x[0] + 2 * N + 2;
	abc_x[2] = abc_x[1] + 2 * N + 2;

	// 绘制地图
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			//墙体绘制 
			if (i == 0 || i == mapHeight - 1 || j == 0 || j == mapWidth - 1) {
				gotoxy(j, i);
				printf("%c", wall);
			}
			//绘制柱子
			else if (i > 1 && i < mapHeight - 1) {
				if (j == abc_x[0] || j == abc_x[1] || j == abc_x[2]) {
					//初始化绘制圆盘
					int abc_x_index = 0;
					if (j == abc_x[0]) abc_x_index = 0;
					else if (j == abc_x[1]) abc_x_index = 1;
					else if (j == abc_x[2]) abc_x_index = 2;
					drawHanoi(j, i, abc_pillar[abc_x_index][N - i + 2], -1);
				}
			}
		}
	}
}
/*
* 汉诺塔递归算法
* from 开始地
* temp 中转地
* to   移动目的地
*/
void hanoi(int n, char from, char temp, char to)
{
	if (1 == n)
	{
		move(from, to);//递归截至条件
	}
	else
	{
		hanoi(n - 1, from, to, temp);
		move(from, to);
		hanoi(n - 1, temp, from, to);
	}
}

int main(void)
{
	HideCursor();
	printf("需要叠的层数:");
	scanf("%d", &N);
	init();
	getchar();//读取换行
	HideCursor();
	hanoi(N, 'A', 'B', 'C');

	getchar(); //让暂时不退出
	getchar();
	
	return 0;
}
