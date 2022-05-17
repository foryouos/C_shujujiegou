#include<iostream> 

using namespace std;
bool isleap(int year)
{
    if ((year % 4 == 0 && year % 4 != 0) || (year % 400 == 0))
    {
        return 1;
    }
    return 0;
}//判断是否闰年
/*
太阳公转周期，一年时间约365.2425天。
公历为了对齐公转周期，4年一闰，100年一停闰，400年加一闰。 400年共97闰， （365×400+97）/400 = 365.2425
农历，一个月相周期为一月，月相周期大约为29.53,   有大小月之分，大月30天，小月29天。
农历为了对齐公转周期，每19年加7个闰月，
因为，农历的推算比较复杂， 大多使用查表法进行计算.
*/

/*
使用比特位记录每年的情况
数据说明
0~4 共5bit 春节日份
5~6 共2bit 春节月份
7~19 共13bit 13个月的大小月情况(如果无闰月，最后位无效)，大月为1（30天）,小月为0（29天）
20~23 共4bit 记录闰月的月份，如果没有闰月为0
*/
int lunarYear[199] = {
    0x04AE53, 0x0A5748, 0x5526BD, 0x0D2650, 0x0D9544, 0x46AAB9, 0x056A4D, 0x09AD42, 0x24AEB6, 0x04AE4A, /*1901-1910*/
    0x6A4DBE, 0x0A4D52, 0x0D2546, 0x5D52BA, 0x0B544E, 0x0D6A43, 0x296D37, 0x095B4B, 0x749BC1, 0x049754, /*1911-1920*/
    0x0A4B48, 0x5B25BC, 0x06A550, 0x06D445, 0x4ADAB8, 0x02B64D, 0x095742, 0x2497B7, 0x04974A, 0x664B3E, /*1921-1930*/
    0x0D4A51, 0x0EA546, 0x56D4BA, 0x05AD4E, 0x02B644, 0x393738, 0x092E4B, 0x7C96BF, 0x0C9553, 0x0D4A48, /*1931-1940*/
    0x6DA53B, 0x0B554F, 0x056A45, 0x4AADB9, 0x025D4D, 0x092D42, 0x2C95B6, 0x0A954A, 0x7B4ABD, 0x06CA51, /*1941-1950*/
    0x0B5546, 0x555ABB, 0x04DA4E, 0x0A5B43, 0x352BB8, 0x052B4C, 0x8A953F, 0x0E9552, 0x06AA48, 0x6AD53C, /*1951-1960*/
    0x0AB54F, 0x04B645, 0x4A5739, 0x0A574D, 0x052642, 0x3E9335, 0x0D9549, 0x75AABE, 0x056A51, 0x096D46, /*1961-1970*/
    0x54AEBB, 0x04AD4F, 0x0A4D43, 0x4D26B7, 0x0D254B, 0x8D52BF, 0x0B5452, 0x0B6A47, 0x696D3C, 0x095B50, /*1971-1980*/
    0x049B45, 0x4A4BB9, 0x0A4B4D, 0xAB25C2, 0x06A554, 0x06D449, 0x6ADA3D, 0x0AB651, 0x093746, 0x5497BB, /*1981-1990*/
    0x04974F, 0x064B44, 0x36A537, 0x0EA54A, 0x86B2BF, 0x05AC53, 0x0AB647, 0x5936BC, 0x092E50, 0x0C9645, /*1991-2000*/
    0x4D4AB8, 0x0D4A4C, 0x0DA541, 0x25AAB6, 0x056A49, 0x7AADBD, 0x025D52, 0x092D47, 0x5C95BA, 0x0A954E, /*2001-2010*/
    0x0B4A43, 0x4B5537, 0x0AD54A, 0x955ABF, 0x04BA53, 0x0A5B48, 0x652BBC, 0x052B50, 0x0A9345, 0x474AB9, /*2011-2020*/
    0x06AA4C, 0x0AD541, 0x24DAB6, 0x04B64A, 0x69573D, 0x0A4E51, 0x0D2646, 0x5E933A, 0x0D534D, 0x05AA43, /*2021-2030*/
    0x36B537, 0x096D4B, 0xB4AEBF, 0x04AD53, 0x0A4D48, 0x6D25BC, 0x0D254F, 0x0D5244, 0x5DAA38, 0x0B5A4C, /*2031-2040*/
    0x056D41, 0x24ADB6, 0x049B4A, 0x7A4BBE, 0x0A4B51, 0x0AA546, 0x5B52BA, 0x06D24E, 0x0ADA42, 0x355B37, /*2041-2050*/
    0x09374B, 0x8497C1, 0x049753, 0x064B48, 0x66A53C, 0x0EA54F, 0x06B244, 0x4AB638, 0x0AAE4C, 0x092E42, /*2051-2060*/
    0x3C9735, 0x0C9649, 0x7D4ABD, 0x0D4A51, 0x0DA545, 0x55AABA, 0x056A4E, 0x0A6D43, 0x452EB7, 0x052D4B, /*2061-2070*/
    0x8A95BF, 0x0A9553, 0x0B4A47, 0x6B553B, 0x0AD54F, 0x055A45, 0x4A5D38, 0x0A5B4C, 0x052B42, 0x3A93B6, /*2071-2080*/
    0x069349, 0x7729BD, 0x06AA51, 0x0AD546, 0x54DABA, 0x04B64E, 0x0A5743, 0x452738, 0x0D264A, 0x8E933E, /*2081-2090*/
    0x0D5252, 0x0DAA47, 0x66B53B, 0x056D4F, 0x04AE45, 0x4A4EB9, 0x0A4D4C, 0x0D1541, 0x2D92B5            /*2091-2099*/
}; //阴历数据表
const int beginYear = 1901; //计算阴历的开始年份

const int days[2][12] = {
    {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335},
    {1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336} };

struct lunar
{
    int year, month, day; // 年月日
    bool isLeap; //是否为闰月，即阴历一年中多月的那一个月
    lunar() {}
    lunar(int y, int m, int d, bool isL) : year(y),
        month(m), day(d), isLeap(isL) {};
};

int Days(int year, int mouth) //返回开学之前已经过去的天数
{
    int days = 0;
    int isprime;
    isprime = isleap(year);
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


lunar getLunar(int y, int m, int d)
{
    lunar nowlunar(y, 0, 0, false); //默认初始化
    int index = y - beginYear;                        //年份下标
    int springMonth = (lunarYear[index] & 0x60) >> 5; //春节的月份
    int springDay = lunarYear[index] & 0x1f;          // 春节的日历
    int todaySolar = days[isleap(y)][m - 1] + d - 1;  //公历第几天
    int springLunar = days[isleap(y)][springMonth - 1] + springDay - 1;
    // 春节是公历年的第几天
    int gap = todaySolar - springLunar + 1; //计算公历这天与春节在公历的日期的间隔
    if (gap < 0) //今天在春节的前面 重新计算
    {
        index--;
        nowlunar.year--;
        if (index < 0)
            return nowlunar;                          //少于1901，不在计算范围内
        springMonth = (lunarYear[index] & 0x60) >> 5; //春节的月份
        springDay = lunarYear[index] & 0x1f;          // 春节的日历
        springLunar = days[isleap(y)][springMonth - 1] + springDay - 1;
        int yearToday = days[isleap(y - 1)][11] + 30;
        gap = todaySolar + yearToday - springLunar + 1;
    }
    int lunarMonth = 1;
    for (; lunarMonth <= 13; ++lunarMonth)
    {
        int monthDay = 29;
        if ((lunarYear[index] >> (6 + lunarMonth)) & 0x1)
            monthDay = 30;
        if (gap <= monthDay)
            break;
        gap -= monthDay;
    }
    nowlunar.day = gap;
    int leapMonth = (lunarYear[index] >> 20) & 0xf;
    if (leapMonth > 0 && leapMonth < lunarMonth)
    {
        lunarMonth--; //如果当前月为闰月，设置闰月标志
        if (lunarMonth == leapMonth)
            nowlunar.isLeap = true;
    }
    nowlunar.month = lunarMonth;
    int Q = (y - 1977) / 4;
    int R = (y - 1977) % 4;
    float n = 14 * Q + 10.6 * (R + 1) + Sum_day(y, m, d); //年内基数就是这一年过了多少天
    float ms = n / 29.5;
    int mn = int(n * 10) % int(29.5 * 10);
    nowlunar.day = mn/10;
    return nowlunar;
}

int main() {
    int y, m, d;
    while (cin >> y >> m >> d) {
        
        lunar nowlunar = getLunar(y, m, d);
        printf("%d-%d-%d ", nowlunar.year, nowlunar.month,nowlunar.day);
    }
}

