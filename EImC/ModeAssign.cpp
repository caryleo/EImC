#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
#include"ModeExecute.h"
#include"Stack.h"
using namespace std;

extern Stack RunTime;
extern vector<Token*>buffer;
extern vector<Token*> ConstStore;

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
		temp = expr_top;
		while (temp<=expr_bottom)
		{
			if (buffer[temp]->tag == IDT)
			{
				Idt* tem = (Idt*)buffer[temp]; //将表达式里的变量的值 和栈联系在一起  
				string q = tem->name;
				Idt *ret = RunTime.query(q);
				// int c=a+b; 此a 非彼 a 而且要把表达式里的 a 指向的assType 改掉
				// 判断三种情况 新建对象 和idt->t 联系在一起
				if (ret->assType == NUM)   
				{
					tem->assType = NUM;
					SoInt*intt = (SoInt*)ret->t;
					SoInt *a = new SoInt(intt->val, 0, 0);
					tem->t = a;
				}
				if (ret->assType == RNUM)
				{
					tem->assType = RNUM;
					SoReal*intt = (SoReal*)ret->t;
					SoReal *a = new SoReal(intt->val, 0, 0);
					tem->t = a;
				}
				if (ret->assType == STRING)
				{
					tem->assType = STRING;
					SoString*strr = (SoString*)ret->t;
					SoString*b = new SoString(strr->str, 0, 0);
					tem->t = b;
				}
			}
			temp++;
		}
		// 调用算术表达式的值 ？？？？ 到底如何调用
		// 算术表达式的开始和结束时 expr_top & expr_bottom
		// 将算术表达式的值赋值给等式右边的 buffer[idt]

		// result 为表达式计算得到的返回值 类型为token
		// 根据返回值的类型 有三种情况


		ExprIR a;
		Token*result=a.calculate_expr(expr_top, expr_bottom);
		temp = expr_top;
		// 考虑连等的情况
		switch (result->tag)
		{
		case NUM:
		{
			SoInt*number = (SoInt*)result;
			int num = number->val;
			temp = expr_top-1;
			while (temp>=top)
			{
				if (buffer[temp]->tag==IDT)
				{
					// a=b ,b->a
					Idt* idt = (Idt*)buffer[temp];
					//	修改变量的值
					string q = idt->name;
					Idt *value = RunTime.query(q);

					if (value->assType == NUM)
					{
						SoInt * p = (SoInt *)value->t;
						SoInt* intt = new SoInt(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else if (value->assType==RNUM)
					{
						SoReal * p = (SoReal *)value->t;
						SoReal* intt = new SoReal(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
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
			SoReal*number = (SoReal*)result;

			float num = number->val;//通过表达式计算模块计算 要赋的数值
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	修改变量的值
					string q = idt->name;
					Idt *value = RunTime.query(q);

					if (value->assType == RNUM)
					{
						SoReal * p = (SoReal *)value->t;
						SoReal* intt = new SoReal(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
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
			SoString*strings = (SoString*)result;
			string numm = strings->str;//通过表达式计算模块计算 要赋的数值
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	修改变量的值
					string q = idt->name;
					Idt *value = RunTime.query(q);
					if (value->assType == STRING)
					{
						SoString * p = (SoString *)value->t;
						SoString* intt = new SoString(numm, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;

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