#ifndef SOOUT_H_
#define SOOUT_H_

#include"EImC.h"
using namespace std;

class SoOut {
public:
	static void print(Token *top, Token *bottom);//输出语句
	static bool isValid(Token *top, Token *bottom);//判断out语句是否合法
	static void judgeIdt(Token *m);//用过来分析Idt的类型并输出
};

#endif // !SOOUT_H_
