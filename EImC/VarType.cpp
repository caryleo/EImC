#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"ModeExecute.h"
#include"Expression.h"
#include"Stack.h"
#include"FuncType.h"
#include"ModeErrorReport.h"

// 存在的问题 赋值调用的实现(关键字为等于号)还没有写好 还空在那里 50，  85 .118 行
// 赋值式子   监测语法是否有语法错误  如何赋值是 需要调用的功能 
extern vector<Token*>buffer;
extern Stack RunTime;				//运行栈
extern Token ** esp, **ebp;			//运行栈的栈顶和栈底
extern vector<Token*>ConstStore;

VarType::VarType(int a, int b)
{
	top = a;
	bottom = b;
}

void VarType::input()  //给我的是 int/real/string 开头 以分号为结束的一段话 
{

	int temp;
	switch (buffer[top]->tag)  //读取第一个单词 判断是 int real string ;
		// int a;  int a=1，b=1 ; int a,b; 大致有几种情况
		//a=2 赋值 
		// real a;
		//string a;
	{
	case KEY_INT:
	{
		temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // 判断到不到分号 到分号为结束
		{
			// 新变量 将新变量 放入新栈中
			if (buffer[temp]->tag == IDT)  //idt 是标识符 比如 a  要添加新元素 a 进去
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				// 判断是否已经在当前栈出现 不能重复定义
				Idt *ressu = RunTime.query_alt(idt->name);
				if (ressu!=NULL)
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(351, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				idt->assType = NUM;  // 在idt类里的asstype 标注这个变量 属于的类型
				idt->t = NULL;		//此时未赋值 修改 t 指针 指向空
				RunTime.push(idt);   // 放入栈中
				RunTime.sync();	 // 修改ESP
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //读到逗号
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //读到等于号 跳到处理赋值语句的地方 例如 int a=b+c;
			{
				int start = temp - 1;  //向前读一个 开始是等号左边的变量
				temp++;
				int flag=0;

				// 读到分号 或者 结束
				while (buffer[temp]->tag != COMMA&&temp <= bottom) //读到逗号或者语句结束的时候 说明赋值语句结束
				{
					if (buffer[temp]->tag == IDT&&buffer[temp+1]->tag == LPAR)
					{
						flag = 1;
						temp++;
						while (buffer[temp]->tag!=RPAR)
						{
							flag = 0;
							temp++;
						}
					}
					temp++;
				}
				
				int end = temp - 1;		// 这个赋值语句的结束
				/*if (flag == 1)
				{
					temp = start;
					while (temp <= bottom)
					{
						if (buffer[temp]->tag == RPAR)
							break;
						temp++;
					}
					end = temp;
				}*/
				//调用赋值语句 ImpleAssign（start，end） 暂定调用方法
				//有三
				ModeExecute::assign(start, end);
				ModeAssign test(start, end);
				test.Fuzhi();
				temp = end + 1;
			
			}
			if (buffer[temp]->tag == KEY_INT || buffer[temp]->tag == KEY_REAL || buffer[temp]->tag == KEY_STRING)
			{
				cout << "Error!!!" << endl;
				ModeErrorReport error(352, buffer[temp]->line, buffer[temp]->col);
				error.report();
				return;
			}
		}

		//在符号表中新建一个名为temp指向的名字的 把名字存进去 类型是之前出现的int，或着其他
		//继续

	}
	break;
	case KEY_REAL:
	{
		temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // 判断到不到分号 到分号为结束
		{
			if (buffer[temp]->tag == IDT)  //idt 是标识符 比如 a   要添加新元素 a 进去
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				// 判断是否已经在当前栈出现 不能重复定义
				Idt *ressu = RunTime.query_alt(idt->name);
				if (ressu != NULL)
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(351, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				idt->assType = RNUM;  // 在idt类里的asstype 标注这个变量 属于的类型
				idt->t = NULL;
				RunTime.push(idt);   // 放入栈中
				RunTime.sync();	 // 修改ESP
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //读到逗号
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //读到等于号 跳到处理赋值语句的地方 例如 real a=b+c;
			{
				int start = temp - 1;  //向前读一个 开始是等号左边的变量
				temp++;
				int flag = 0;

				// 读到分号 或者 结束
				while (buffer[temp]->tag != COMMA&&temp <= bottom) //读到逗号或者语句结束的时候 说明赋值语句结束
				{
					if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
					{
						flag = 1;
						temp++;
						while (buffer[temp]->tag != RPAR)
						{
							flag = 0;
							temp++;
						}
					}
					temp++;
				}

				int end = temp - 1;		// 这个赋值语句的结束
				
				//调用赋值语句 ImpleAssign（start，end） 暂定调用方法
				//有三
				ModeExecute::assign(start, end);
				ModeAssign test(start, end);
				test.Fuzhi();
				temp = end + 1;	
			}
			if (buffer[temp]->tag == KEY_INT || buffer[temp]->tag == KEY_REAL || buffer[temp]->tag == KEY_STRING)
			{
				cout << "Error!!!" << endl;
				ModeErrorReport error(352, buffer[temp]->line, buffer[temp]->col);
				error.report();
				return;
			}
		}


	}
	break;
	case KEY_STRING:
	{
		temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // 判断到不到分号 到分号为结束
		{
			if (buffer[temp]->tag == IDT)  //idt 是标识符 比如 a  要添加新元素 a 进去
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				// 判断是否已经在当前栈出现 不能重复定义
				Idt *ressu = RunTime.query_alt(idt->name);
				if (ressu != NULL)
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(351, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				idt->assType = STRING;  // 在idt类里的asstype 标注这个变量 属于的类型
				idt->t = NULL;
				RunTime.push(idt);		// 放入栈中
				RunTime.sync();	 // 修改ESP
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //读到逗号
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //读到等于号 跳到处理赋值语句的地方 例如 srting a=
			{
				int start = temp - 1;  //向前读一个 开始是等号左边的变量
				temp++;
				int flag = 0;

				// 读到分号 或者 结束
				while (buffer[temp]->tag != COMMA&&temp <= bottom) //读到逗号或者语句结束的时候 说明赋值语句结束
				{
					if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
					{
						flag = 1;
						temp++;
						while (buffer[temp]->tag != RPAR)
						{
							flag = 0;
							temp++;
						}
					}
					temp++;
				}
				int end = temp - 1;		// 这个赋值语句的结束
				
				//调用赋值语句 ImpleAssign（start，end） 暂定调用方法
				//有三
				ModeExecute::assign(start, end);
				ModeAssign test(start, end);
				test.Fuzhi();
				temp = end + 1;
			}
			if (buffer[temp]->tag == KEY_INT || buffer[temp]->tag == KEY_REAL || buffer[temp]->tag == KEY_STRING)
			{
				cout << "Error!!!" << endl;
				ModeErrorReport error(352, buffer[temp]->line, buffer[temp]->col);
				error.report();
				return;
			}
		}

	}
	break;
	default:
		break;
	}

}
