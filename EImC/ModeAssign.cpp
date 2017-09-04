#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
extern vector<Token*>buffer;

ModeAssign::ModeAssign(int a, int b)
{
	top = a;
	bottom = b;
}

void ModeAssign::Fuzhi()
{
	int temp = top;
	int idt;   //变量所在位置
	int expr_top;
	int expr_bottom;
	while (temp <= bottom)
	{
		if (buffer[temp]->tag==ASSIGN)
		{
			 idt = temp - 1; // 等号前面的变量
		}
		else
		{
			temp++;
			continue;
		}
		expr_top = temp + 1;
		while (buffer[temp]->tag!=SEMICO)
		{
			temp++;
		}
		expr_bottom = temp - 1;
	}
	// 算术表达式的开始和结束时 expr_top & expr_bottom
	// 将算术表达式的值赋值给等式右边的 buffer[idt]
	Token*head = buffer[expr_top];
	Token*tail = buffer[expr_bottom];
	ExprIR a;
	Idt result=a.exprEnter(head, tail);
	switch (result.assType)
	{
	case KEY_INT:
	{
		SoInt*num = (SoInt*)result.t;
		num->val = a.getIntVal(result);//要赋的数值
		Token* token = buffer[idt];
		Idt* idt = (Idt*)token; //被赋值的对象
		if (idt->tag==KEY_INT)
		{
			SoInt*hu = (SoInt*)token;
			hu->val = num->val;

		}
	}
	case KEY_REAL:
	{
		SoReal*num = (SoReal*)result.t;
		num->val = a.getRealVal;
		Token* token = buffer[idt];
		Idt* idt = (Idt*)token; //被赋值的对象
		if (idt->tag == KEY_REAL)
		{
			SoReal*hu = (SoReal*)token;
			hu->val = num->val;

		}
	}
	case KEY_STRING:
	{
		SoString*num = (SoString*)result.t;
		num->str = a.getStrVal;
		Token* token = buffer[idt];
		Idt* idt = (Idt*)token; //被赋值的对象
		if (idt->tag == KEY_STRING)
		{
			SoString*hu = (SoString*)token;
			hu->str = num->str;

		}
	}
	default:
		break;
	}


}