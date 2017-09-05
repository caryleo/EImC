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
		// 调用算术表达式 ？？？？ 到底如何调用
		// 算术表达式的开始和结束时 expr_top & expr_bottom
		// 将算术表达式的值赋值给等式右边的 buffer[idt]
		// question： 表达式的返回值 以及 类型
		Token*head = buffer[expr_top];
		Token*tail = buffer[expr_bottom];
		ExprIR a;
		Idt result = a.exprEnter(head, tail);
		temp = expr_top;
		while (temp>=top)
		{
			if (buffer[temp]->tag == IDT)
			{
				switch (result.assType)
				{
				case KEY_INT:
				{
					// 等式左右类型不一样怎么处理 如何报错
					int num = a.getIntVal(result);//通过表达式计算模块计算 要赋的数值
					Token* token = buffer[idt];
					Idt* idt = (Idt*)token; //被赋值的对象
					if (idt->assType == KEY_INT)
					{
						SoInt*hu = (SoInt*)idt->t;
						hu->val = num;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				case KEY_REAL:
				{
					float num = a.getRealVal(result);
					Token* token = buffer[idt];
					Idt* idt = (Idt*)token; //被赋值的对象
					if (idt->assType == KEY_REAL)
					{
						SoReal*hu = (SoReal*)idt->t;
						hu->val = num;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				case KEY_STRING:
				{

					string strs = a.getStrVal(result);
					Token* token = buffer[idt];
					Idt* idt = (Idt*)token; //被赋值的对象
					if (idt->tag == KEY_STRING)
					{
						SoString*hu = (SoString*)idt->t;
						hu->str = strs;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				default:
					break;
				}
			}
			temp--;
		}
	}
	//// 调用算术表达式 ？？？？ 到底如何调用
	//// 算术表达式的开始和结束时 expr_top & expr_bottom
	//// 将算术表达式的值赋值给等式右边的 buffer[idt]
	//// question： 表达式的返回值 以及 类型
	//Token*head = buffer[expr_top];
	//Token*tail = buffer[expr_bottom];
	//ExprIR a;
	//Idt result=a.exprEnter(head, tail);
	//switch (result.assType)
	//{
	//case KEY_INT:
	//{
	//	// 等式左右类型不一样怎么处理 如何报错
	//	int num = a.getIntVal(result);//通过表达式计算模块计算 要赋的数值
	//	Token* token = buffer[idt];
	//	Idt* idt = (Idt*)token; //被赋值的对象
	//	if (idt->assType==KEY_INT)
	//	{
	//		SoInt*hu = (SoInt*)idt->t;
	//		hu->val = num;

	//	}
	//}
	//case KEY_REAL:
	//{
	//	float num = a.getRealVal(result);
	//	Token* token = buffer[idt];
	//	Idt* idt = (Idt*)token; //被赋值的对象
	//	if (idt->assType == KEY_REAL)
	//	{
	//		SoReal*hu = (SoReal*)idt->t;
	//		hu->val = num;

	//	}
	//}
	//case KEY_STRING:
	//{

	//	string strs= a.getStrVal(result);
	//	Token* token = buffer[idt];
	//	Idt* idt = (Idt*)token; //被赋值的对象
	//	if (idt->tag == KEY_STRING)
	//	{
	//		SoString*hu = (SoString*)idt->t;
	//		hu->str = strs;

	//	}
	//}
	//default:
	//	break;
	//}


}