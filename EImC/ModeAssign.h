#include<iostream>
#include<vector>
#include"EImC.h"
#include"VarType.h"
using namespace std; 
// 赋值表达式处理 
// 赋值语句实现 使用方法
// ModeAssign test(top,bottom);
// sent.Fuzhi();
// 即可处理赋值语句
class ModeAssign
{
public:
	ModeAssign(int a,int b);
	void Fuzhi();

private:
	int top;
	int bottom;
};



