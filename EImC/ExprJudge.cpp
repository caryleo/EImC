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
	//�жϱ��ʽ�Ƿ�Ϸ�
	buffer[top]->tag;
}

