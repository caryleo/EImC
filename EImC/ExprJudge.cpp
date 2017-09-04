#include"stdafx.h"
#include"EImC.h"
#include"ExprJudge.h"
#include"ModeTokenAnalysis.h"
extern vector<Token*>buffer;


ExprJudge::ExprJudge(int a, int b)
{
	top = a;
	bottom = b;
}

void ExprJudge::input(int top, int bottom)
{
	//判断表达式是否合法
	buffer[top]->tag;
}

