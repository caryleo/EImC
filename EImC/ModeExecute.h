#ifndef MODEEXECUTE_H_
#define MODEEXECUTE

#include"EImC.h"
#include "ModeSyntexAnalysis.h"

using namespace std;

class ModeExecute {
public:
	static void init(int top, int bottom);
	static void commence(int top, int bottom);
	static void caller(Caller * func, vector <Token *> s);
	static void assign(int top, int bottom);
};

class PRTR : public Token {/*用来存放Token**的类*/
public:
	Token ** prt;
	PRTR(Token ** s);
};
#endif // !MODEEXECUTE_H_
#pragma once
