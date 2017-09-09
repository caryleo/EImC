#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
#include"ModeExecute.h"
#include"Stack.h"
#include"FuncType.h"
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
	while (temp <= bottom)
	{
		if (buffer[temp]->tag == ASSIGN)
		{
			expr_top = temp + 1;
		}
		temp++;
	}
	temp = expr_top;
	// int a=b=c=d+e
	
	// int a=b+c,d;
	// b=1;
	//int a=b+c
	while (buffer[temp]->tag != COMMA&&temp<=bottom)  // 表达式到逗号为止
	{
		temp++;
	}
	expr_bottom = temp - 1;
	if ((expr_bottom - expr_top) < 0)
	{
		cout << "Error!!!" << endl;
		return;
	}
	if ((expr_top - top) < 2)
	{
		cout << "Error!!!" << endl;
		return;
	}
	else
	{
		temp = expr_top;
		// 判断是不是函数
		Token *result;
		if (buffer[expr_top]->tag == IDT&&buffer[expr_top + 1]->tag == LPAR)  //判断是函数
		{
			FuncType b(expr_top, expr_bottom);
			result = b.Func();
			//???
		}
		else
		{
			// 判断是表达式
			while (temp <= expr_bottom)
			{
				//将表达式里的变量的值 和栈联系在一起  
				if (buffer[temp]->tag == IDT)
				{
					Idt* tem = (Idt*)buffer[temp];
					string q = tem->name;
					Idt *ret = RunTime.query(q);
					if (ret == NULL)
					{
						cout << "Error!" << endl;
						return;
					}
					if (ret->t == NULL)
					{
						cout << "Error!" << endl;
						return;
					}
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
			// a+b 
			// f(a)
			// result 为表达式计算得到的返回值 类型为token
			// 根据返回值的类型 有三种情况
			

			ExprIR a;
			result = a.calculate_expr(expr_top, expr_bottom);
		}
		temp = expr_top;
		// 考虑连等的情况
		// 可能有未定义就赋值的情况 但是默认为整型 所以只有num讨论了这种情况
		switch (result->tag)
		{
		case NUM:
		{
			SoInt*number = (SoInt*)result;
			short num = number->val;
			temp = expr_top - 1;
			//a=b=c=d+1
			while (temp >= top)
			{
				if (buffer[temp]->tag != ASSIGN)
				{
					cout << "Error!!!" << endl;
					return;
				}
				temp--;
				if (buffer[temp]->tag == IDT)
				{
					// a=b ,b->a
					Idt* idt = (Idt*)buffer[temp];
					//	修改变量的值
					string q = idt->name;
					Idt *value = RunTime.query(q);// 查找全部栈 看是否有这个变量名
					if (value == NULL)  //找不到该数 说明未定义就使用
					{
						//Idt *res = RunTime.query_alt(q);
						// 新建一个变量 默认为整型 放入栈中
						Token* token = buffer[temp];
						Idt* newidt = (Idt*)token;
						newidt->assType = NUM;  
						newidt->t = NULL;		//此时未赋值 修改 t 指针 指向空
						RunTime.push(idt);   // 放入栈中
						RunTime.sync();	 // 修改ESP
						SoInt*intt = new SoInt(num, 0, 0);
						ConstStore.push_back(intt);
						Idt *newvalue = RunTime.query(q);
						newvalue->t = intt;
					}
					if (value->assType == NUM)  //short
					{
						SoInt* intt = new SoInt(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else if (value->assType == RNUM)
					{
						float numtrans = num;
						SoReal* intt = new SoReal(numtrans, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else 
					{
						cout << "Error!!!(expression assignment matching error)" << endl;
						return;
					}
					temp--;
				}
				else
				{
					cout << "Error!!!" << endl;
					return;
				}
				
			}
		}
		break;
		case RNUM:
		{
			SoReal *number = (SoReal*)result;
			float num = number->val;//通过表达式计算模块计算 要赋的数值
			temp = expr_top - 1;
			// a=b=c+d
			while (temp >= top)
			{
				if (buffer[temp]->tag != ASSIGN)
				{
					cout << "Error!!!\n" << endl;
					return;
				}
				temp--;
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	修改变量的值
					string q = idt->name;
					Idt *value = RunTime.query(q);
					if (value->assType == RNUM)
					{
						SoReal* intt = new SoReal(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else 
					{
						cout << "Error!!!(expression assignment matching error)" << endl;
						return; 
					}
				}
				else
				{
					cout << "Error!!!\n" << endl;
					return;
				}
				temp--;
			}
		}
		break;
		case STRING:
		{
			SoString *strings = (SoString*)result;
			string numm = strings->str;//通过表达式计算模块计算 要赋的数值
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag != ASSIGN)
				{
					cout << "Error!!!\n" << endl;
					return;
				}
				temp--;
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	修改变量的值
					string q = idt->name;
					Idt *value = RunTime.query(q);
					if (value->assType == STRING)
					{

						SoString* intt = new SoString(numm, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;

					}
					else 
					{
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				else
				{
					cout << "Error!!!" << endl;
					return;
				}
				temp--;
			}
		}
		break;
		default:
			break;
		}

	}
}