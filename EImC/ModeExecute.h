#ifndef MODEEXECUTE_H_
#define MODEEXECUTE

#include"EImC.h"
#include "ModeSyntexAnalysis.h"

using namespace std;

class ModeExecute {
public:
	static void init(int top, int bottom);						//用来进行第一次的（程序级）语句块集合的执行
	static void commence(int top, int bottom);					//用来执行指定的语句块集合
	static Token * caller(Caller * func, vector <Token *> s, int line);		//用来进行函数调用
	static void assign(int top, int bottom);					//用来对表达式进行查询赋值
};

class PRTR : public Token {/*用来存放Token**的类*/
public:
	Token ** prt;
	PRTR(Token ** s);
};
#endif // !MODEEXECUTE_H_
#pragma once
