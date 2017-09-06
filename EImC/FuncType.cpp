#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
#include"FuncType.h"
#include"Stack.h"

extern Stack RunTime;

using namespace std;
extern vector<Token*> buffer;
extern vector<Token*> ConstStore;
FuncType::FuncType(int a,int b){
	top = a;
	bottom = b;
}

void FuncType::Func()
{
	vector<Token*> paralist;  // 存放参数的值
	vector<Token*> paratype;	// 存放 参数的类型
	int temp = top;
	while (temp<=bottom) // 识别到 函数名 之后是个左括号 
	{
		if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
		{
			break;
		}
		temp++;
	}
	int funcname = temp; // 取函数名
	Idt *funame = (Idt*)buffer[funcname];
	string funcnamestring = funame->name;
	int para = temp + 2;
	while (para<=bottom)  // 参数列表 fun（a,b,5)
	{
		// 参数有四种情况 
		// IDT NUM RNUM STRING
		if (buffer[para]->tag == IDT) // 为标识符 将标识符对应的值 加入函数的参数列表中
		{
			Idt* id = (Idt*)buffer[para];
			string q = id->name;
			Idt*value=RunTime.query(q); // 查询 这个标识符 
			// value->assType 有三种情况
			// 三种情况 num rnum string
			if (value->assType==NUM)   
			{
				SoInt * p = (SoInt *)value->t;
				SoInt* intt = new SoInt(p->val,0,0);
				paralist.push_back(intt);
				Token *type = new Token(NUM, 0, 0);
				paratype.push_back(type);
			}
			if (value->assType == RNUM)
			{
				SoReal *p = (SoReal *)value->t;
				SoReal *innt = new SoReal(p->val, 0, 0);
				paralist.push_back(innt);
				Token *type = new Token(RNUM, 0, 0);
				paratype.push_back(type);
			}
			if (value->assType == STRING)
			{
				SoString *p = (SoString *)value->t;
				SoString *innt = new SoString(p->str, 0, 0);
				paralist.push_back(innt);
				Token *type = new Token(STRING, 0, 0);
				paratype.push_back(type);
			}
		}
		if (buffer[para]->tag == NUM)  // 以下三种为参数列表中为数字的情况 
		{
			paralist.push_back(buffer[para]); // 将参数的token 放入paralist 中
			Token *type = new Token(NUM, 0, 0); // 将参数的类型 放入 paratype 中
			paratype.push_back(type);
		}
		if (buffer[para]->tag == RNUM)
		{
			paralist.push_back(buffer[para]);
			Token *type = new Token(RNUM, 0, 0);
			paratype.push_back(type);
		}
		if (buffer[para]->tag == STRING)
		{
			paralist.push_back(buffer[para]);
			Token *type = new Token(STRING, 0, 0);
			paratype.push_back(type);
		}
		para++;
	}
	Caller ret(funcnamestring,paratype);  // 创建名为 ret 的 caller 类的 一个对象 两个参数 函数名 和 函数的参数类型构成的列表
	// 调用 ModeExecute 类
	ModeExecute::caller(&ret,paralist);				//  调用
	



}


