#ifndef VarType_H_
#define VarType_H_

#include<iostream>
#include<vector>
#include"EImC.h"
using namespace std;
//变量定义函数 使用方法
// VarType test(top,bottom);
// test.input();
// 即可处理
// 识别定义 int a; real b;
class VarType
{
public:
	VarType(int a, int b);
	void input(); //top is the start and bottom is the end
	//static bool match(int m,Tag a);//match buffer数组里应该比较的那个元素的标签和想要匹配的标签
private:
	int top;
	int bottom;
};


#endif // !SOIN_H_
// 这个部分是用作执行 int/real/string 开头 以分号为结束 的一行代码
//例如
// int a;  int a=1，b=1 ; int a,b; 大致有几种情况
//a=2 赋值 
// real a;
//string a;