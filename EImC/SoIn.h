#ifndef SOIN_H_
#define SOIN_H_

#include<iostream>
#include"EImC.h"
#include<vector>
using namespace std;
class SoIn
{
public:
	static void input(Token *top, Token *bottom);
	static void judgeIdt(Token *m);//用过来分析Idt的类型并输出
};


#endif // !SOIN_H_
