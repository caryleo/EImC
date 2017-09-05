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
private:
	int top;
	int bottom;
};


#endif // !SOIN_H_
