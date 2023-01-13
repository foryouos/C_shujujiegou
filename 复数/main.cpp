#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//复数结构体
typedef struct Complex
{
	float realpart;  //实部
	float imagpart;  //虚部
};
//输出结构体
void Print_Comples(struct Complex z)
{
	//如果实部为零
	//两种输出格式，虚部为负或为正
	if (z.realpart - 0.00000001 < 0.00000001&& z.realpart - 0.00000001 > 0.00000001)//当实部为零
	{
		printf("输入的复数为：%.1fi\n",z.imagpart);
	}
	else //实部不为零
	{
		if (z.imagpart > 0)
		{
			printf("输入的复数为：%.1f+%.1fi\n", z.realpart, z.imagpart);//输出输入的复数
		}
		else
		{
			printf("输入的复数为：%.1f%.1fi\n", z.realpart, z.imagpart);//输出输入的复数
		}
	}
}
bool Check_Complex(struct Complex z)//检查输入的复数是否合规
{
	if (z.imagpart - 0.00000001 < 0.0000001)
	{
		system("title error!!");
		system("color 4");
		printf("复数的虚部不能为零\n");
		return true; //若不合规，返回真
	}
	else
	{
		printf("输入检测完毕，符合！\n");
		return false;
	}
}
void Entry_Complex(struct Complex* z) //使用指针，要改变值
{
	printf("请输入复数的实部和虚部\n用\"a+bi\"的形式:");
	scanf("%f %fi", &z->realpart, &z->imagpart);
	//输入检测
	if (Check_Complex(*z))
	{
		abort();
	}
}
//复数的加法
//目标结构体，相加的两个结构体
void add(struct Complex* z, struct Complex z1, struct Complex z2)
{
	z->realpart = z1.realpart + z2.realpart;
	z->imagpart = z2.imagpart + z2.imagpart;
	printf("\n**********复数相加*********\t");
	Print_Comples(*z);

}
//复数相减
void minus(struct Complex* z, struct Complex z1, struct Complex z2)
{
	z->realpart = z1.realpart - z2.realpart;
	z->imagpart = z1.imagpart - z2.imagpart;
	printf("\n**********复数相减*********\t");
	Print_Comples(*z);

}
//复数相乘
void multiply(struct Complex* z, struct Complex z1, struct Complex z2)
{
	z->realpart = z1.realpart*z2.realpart - z1.imagpart*z2.imagpart;
	z->imagpart = z1.imagpart*z2.realpart + z1.realpart*z2.imagpart;
	printf("\n**********复数相乘*********\t");
	Print_Comples(*z);

}
//复数相除
void divide(struct Complex* z, struct Complex z1, struct Complex z2)
{
	float cd = z2.realpart * z2.realpart + z2.imagpart * z2.imagpart;
	z->realpart = (z1.realpart * z2.realpart + z1.imagpart * z2.imagpart)/cd;
	z->imagpart = (z1.imagpart * z1.realpart - z1.realpart * z2.imagpart)/cd;
	printf("\n**********复数相除*********\t");
	Print_Comples(*z);

}
int main(void)
{
	//首先实现两个复数的简单操作
	Complex z, z1, z2;
	Entry_Complex(&z1);
	Entry_Complex(&z2);
	//输出
	Print_Comples(z1);
	Print_Comples(z2);

	//复数的相加
	add(&z, z1, z2);
	//复数的减法
	minus(&z, z1, z2);
	//复数的乘法
	multiply(&z, z1, z2);
	//复数的除法
	divide(&z, z1, z2);

	return 0;
}
