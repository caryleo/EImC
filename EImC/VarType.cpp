#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
// 存在的问题 赋值调用的实现(关键字为等于号)还没有写好 还空在那里 50，  85 .118 行
// 赋值式子 监测语法是否有语法错误  如何赋值是 需要调用的功能 
extern vector<Token*>buffer;

VarType::VarType(int a, int b)
{
	top = a;
	bottom = b;
}

void VarType::input(int top,int bottom)  //给我的是 int/real/string 开头 以分号为结束的一段话 
{
	
	switch (buffer[top]->tag)  //读取第一个单词 判断是 int real string ;
		// int a;  int a=1，b=1 ; int a,b; 大致有几种情况
		//a=2 赋值 
		// real a;
		//string a;
	{
	case KEY_INT:
	{
		int temp = top + 1;
		while (temp<=bottom&&buffer[temp]->tag!=SEMICO) // 判断到不到分号 到分号为结束
		{
			if (buffer[temp]->tag == IDT)  //idt 是标识符 比如 a
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = NUM;  // 在idt类里的asstype 标注这个变量 属于的类型
				temp++;
				continue;
			}
			if (buffer[temp]->tag== COMMA)  //读到逗号
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //读到等于号 跳到处理赋值语句的地方 例如 int a=b+c;
			{
				int start = temp - 1;  //向前读一个 开始是等号左边的变量
				temp++;
				while (buffer[temp]->tag != COMMA || buffer[temp]->tag != SEMICO) //读到为分号或者逗号 说明赋值语句结束
				{
					temp++;
				}
				int end = temp-1;		// 这个赋值语句的结束
				//调用赋值语句 ImpleAssign（start，end） 暂定调用方法
			}
		}

		//在符号表中新建一个名为temp指向的名字的 把名字存进去 类型是之前出现的int，或着其他
		//继续

	}
	case KEY_REAL:
	{
		int temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // 判断到不到分号 到分号为结束
		{
			if (buffer[temp]->tag == IDT)  //idt 是标识符 比如 a
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = RNUM;  // 在idt类里的asstype 标注这个变量 属于的类型
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
				while (buffer[temp]->tag != COMMA || buffer[temp]->tag != SEMICO) //读到为分号或者逗号 说明赋值语句结束
				{
					temp++;
				}
				int end = temp - 1;		// 这个赋值语句的结束
										//调用赋值语句 （start，end） 暂定调用方法
			}
		}

		
	}
	case KEY_STRING:
	{
		int temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // 判断到不到分号 到分号为结束
		{
			if (buffer[temp]->tag == IDT)  //idt 是标识符 比如 a
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = STRING;  // 在idt类里的asstype 标注这个变量 属于的类型
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
				while (buffer[temp]->tag != COMMA || buffer[temp]->tag != SEMICO) //读到为分号或者逗号 说明赋值语句结束
				{
					temp++;
				}
				int end = temp - 1;		// 这个赋值语句的结束
										//调用赋值语句 （start，end） 暂定调用方法
			}
		}

	}
	default:
		break;
	}
	
}
// bool VarType::match(int m, Tag a)
//{
//	Idt *p = (Idt*)buffer.at(m);
//	if (p->t->tag == a)
//		return true;
//	else
//		return false;
//}


