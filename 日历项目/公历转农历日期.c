#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int Isprime(int year)  //判断闰年或者平年
{
    char flag;
    if (year % 4 == 0)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    return flag;
}
int Days(int year, int mouth) //返回开学之前已经过去的天数
{
    int days = 0;
    int isprime;
    isprime = Isprime(year);
    switch (mouth)
    {
    case 12:days += 31;
    case 11:days += 30;
    case 10:days += 31;
    case 9:days += 30;
    case 8:days += 31;
    case 7:days += 31;
    case 6:days += 30;
    case 5:days += 31;
    case 4:days += 30;
    case 3:days += 31;
    case 2:if (isprime == 1) days += 29;
          else days += 28;
    case 1:days += 31;
    }
    return days;
}
int Sum_day(int year, int mouth, int day)  //返回某年某月某天在这一年中已经过去多少天
{
	int days;
	days = Days(year, mouth - 1);  //返回这一年开学之前已经过去的天数
	days += day;
	return days;
}


int main() {
	int year = 2022;
    int month = 5;
    int day = 17;
	int Q = (year - 1977) / 4;
	int R = (year - 1977) % 4;
	printf("%d\n", Q);
	printf("%d\n", R);
	float n = 14 * Q + 10.6 * (R + 1)+Sum_day(year,month,day); //年内基数就是这一年过了多少天
	printf("%.1f\n", n);


	float m = n / 29.5;
	int mn = int(n*10) % int(29.5*10);
	
	printf("农历日期为%d\n", mn/10);

}
