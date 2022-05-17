#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>


int Weekdayofyear(int year)   //判断开学那年第一天星期

{
    int days = 0, week;
    int a;
    for (a = 0; a < year - 1900; a++)
    {
        if (a % 4 == 0) days += 366;
        else days += 365;
    }
    week = days % 7;
    if (week == 0) week = 7;
    return week;
}
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
int Weekday(int year, int mouth, int day)  //返回来学那天星期数
{
    int days;
    int weekday;
    days = Days(year, mouth - 1);  //返回这一年开学之前已经过去的天数
    days += day;  //加上开学月份的天数，记录这一年一共过去多少天
    weekday = days % 7;  //判断今天星期几
    weekday = weekday + Weekdayofyear(year) - 1;   //判断这一年第一天星期数
    if (weekday > 7) weekday -= 7;
    return weekday;  //得出开学第一天是星期几
}
int Max(int year, int mouth)  //返回某年某月的具体天数
{
    int days;
    int isprime;
    isprime = Isprime(year);
    switch (mouth)
    {
    case 12:days = 31; break;
    case 11:days = 30; break;
    case 10:days = 31; break;
    case 9:days = 30; break;
    case 8:days = 31; break;
    case 7:days = 31; break;
    case 6:days = 30; break;
    case 5:days = 31; break;
    case 4:days = 30; break;
    case 3:days = 31; break;
    case 2:if (isprime == 1) days = 29;
          else days = 28; break;
    case 1:days = 31; break;
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


int main()
{
    char title1[] = "\t\txxxxxx大学教学日历\t\t";
    char title2[] = "0000-0000学年第0学期";
    char tab[60] = "周      一      二      三      四      五      六      日";
    char term3;
    char calender[100][8];
    int tempday, tempmouth, flag = 1, b, c, d, e, f, g, h, i, j, cnt = 1, week, term1, term2, year, mouth, day;

    printf("学期(写2017-2018_2的形式)(最后的2代表第二学期):");
    //scanf("%d-%d_%c", &term1, &term2, &term3);  //记录学期年份
    term1 = 2021;
    term2 = 2022;
    term3 = 2;
    printf("开学时间(写成2018/3/5的形式(星期一)：");
    //scanf("%d/%d/%d", &year, &mouth, &day);  //记录开学时间
    year = 2022;
    mouth = 2;
    day = 21;
    int month_begin = mouth;

    printf("总周数:");
    //scanf("%d", &week);  //记录总周数
    week = 50;
    tempday = day;
    tempmouth = mouth;
    //修改学期年份
    for (b = 3; b >= 0; b--)
    {
        title2[b] = term1 % 10 + 48;  //求处于10的余数为末尾数+48是数字与对应的字符串差距(ASCII表)

        term1 /= 10;
    }
    for (c = 8; c >= 5; c--)
    {
        title2[c] = term2 % 10 + 48;
        term2 /= 10;
    }
    title2[15] = term3;
    for (d = 0; d < week; d++)
    {
        calender[d][0] = d + 1;
    }

    //增加阳历节气，直接在下面for函数里面即可




    int g1 = Weekday(year, mouth, day);  //返回开学那一天是星期几

    for (e = 0; e < week; e++)//周数循环
    {
        for (f = 1; f < 8; f++) //星期循环
        {
            if (e == 0) //开学那一周
            {
                
                for (g = 1; g <g1; g++)
                {
                    calender[e][g] = 0;  //让开学前这星期为0
                }
                for (h =g1; h < 8; h++)
                {
                    calender[e][h] = day++;
                }
                break;
            }
            
            if (day > Max(year, mouth))  //day记录日期，如果日期超过本月最大天数
            {
                mouth += 1;
                if (mouth > 12)
                {
                    mouth = 1;
                }
                calender[e][f] = -mouth; //月份第一天给负数
                day = 2;
                //增加五一假期
                if (mouth == 5 && day == 2) {
                    calender[e][f] = 51;
                }
                //增加国庆假期
                if (mouth == 9 && day == 2) {
                    calender[e][f] = 52;
                }
            }
            //添加农历假期，首先要先将农历假期转换为公历
            
            
            else  //否则进行记录
            {
                calender[e][f] = day++;
            }

        }
    }
    puts(title1);
    printf("\t\t");
    puts(title2);
    puts(tab);


    //根据上述更新遍历周数
    for (i = 0; i < week; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (calender[i][j] == 0) //如果等于0就是缩进即空
            {
                printf("  \t");
                continue;
            }
            //五一判断
            if (calender[i][j] == 51)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("劳动节\t");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | 0 | 0 | 0);
            }
            else if (calender[i][j] == 52)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("国庆节\t");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | 0 | 0 | 0);
            }
            else if (calender[i][j] < 0) //月份第一天使用月份输出，使用特殊颜色
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                printf("%d月\t", -calender[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | 0 | 0 | 0);
            }
          
            
           
            //周六周日特别输出
            else if (j==6||j==7)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
                printf("%2d\t", calender[i][j]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | 0 | 0 | 0);
            }

            else //直接输出
            {
                printf("%2d\t", calender[i][j]);
            }
        }
        printf("\n\n");
    }
}
