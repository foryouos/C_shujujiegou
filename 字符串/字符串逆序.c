#include<stdio.h>
void revers(char* s)
{
    char* p = s;
    char c[100] = { 0 };
    int i=0;
    while (*p) //记录的是指针,当输出所有值时跳出，p为空
    {
        c[i] = *p;
        p++;   //指针向前移动，p的值逐渐向后
        i++;  //记录一共有多少位
    }
    for(int j=0;j<i;j++) //记录的是指针,当输出所有值时跳出，p为空
    {
        *(s+j) = c[i-j-1];
          //指针向前移动，p的值逐渐向后。
    }
}
int main()
{
    char s[100];
    gets(s);
    revers(s);
    printf("\n");
    puts(s);
}
