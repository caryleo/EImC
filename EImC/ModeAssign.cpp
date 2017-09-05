#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
#include"ModeExecute.h"
extern vector<Token*>buffer;
// 问题：表达式计算如何调用 ？？？
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
	while (temp<=bottom)
	{
		if (buffer[temp]->tag == ASSIGN)
		{
			expr_top = temp + 1;
		}
		temp++;
	}
	temp = expr_top;
	while (temp<=bottom&&buffer[temp]->tag!=SEMICO)
	{
		temp++;
	}
	expr_bottom = temp - 1;
	if ((expr_bottom-expr_top)<1)
	{
		cout << "Error!!!(no expression)" << endl;
	}
	if ((expr_top - top) < 2)
	{
		cout << "Error!!!(no var)" << endl;
	}
	else
	{
		// 调用算术表达式的值 ？？？？ 到底如何调用
		// 算术表达式的开始和结束时 expr_top & expr_bottom
		// 将算术表达式的值赋值给等式右边的 buffer[idt]
		// question： 表达式的返回值 以及 类型
		Token*head = buffer[expr_top];
		Token*tail = buffer[expr_bottom];
		ExprIR a;
		Idt result = a.exprEnter(head, tail);
		temp = expr_top;
		// 考虑连等的情况
		switch (result.assType)
		{
		case NUM:
		{
			int num = a.getIntVal(result);//通过表达式计算模块计算 要赋的数值
			temp = expr_top-1;
			while (temp>=top)
			{
				if (buffer[temp]->tag==IDT)
				{
					// a=b ,b->a
					Token* token = buffer[temp];
					Idt* idt = (Idt*)token; 
					if (idt->assType == NUM)
					{
						SoInt*hu = (SoInt*)idt->t;
						hu->val = num;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				temp--;
			}
		}
		case RNUM:
		{
			float num = a.getIntVal(result);//通过表达式计算模块计算 要赋的数值
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag == IDT)
				{
					Token* token = buffer[temp];
					Idt* idt = (Idt*)token;
					if (idt->assType == RNUM)
					{
						SoInt*hu = (SoInt*)idt->t;
						hu->val = num;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				temp--;
			}
		}
		case STRING:
		{
			string numm = a.getIntVal(result);//通过表达式计算模块计算 要赋的数值
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag == IDT)
				{
					Token* token = buffer[temp];
					Idt* idt = (Idt*)token;
					if (idt->assType == STRING)
					{
						SoString*hu = (SoString*)idt->t;
						hu->str = numm;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				temp--;
			}
		}

		default:
			break;
		}

	//// 调用算术表达式 ？？？？ 到底如何调用
	//// 算术表达式的开始和结束时 expr_top & expr_bottom
	//// 将算术表达式的值赋值给等式右边的 buffer[idt]
	//// question： 表达式的返回值 以及 类型

}