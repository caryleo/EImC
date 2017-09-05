#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "ModeExecute.h"
#include "VarType.h"
#include "SoIn.h"
#include "SoOut.h"
#include "ModeAssign.h"
#include "Stack.h"
#include "FuncType.h"
using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;
vector <Token *> ConstStore;	//常量存储区
vector <SoFunc *> FuncStore;	//函数语句块存储区
Stack RunTime;					//运行栈
Token ** esp, **ebp;			//运行栈的栈顶和栈底

void ModeExecute::init(int top, int bottom)		//首次进行执行管理
{
}

void ModeExecute::commence(int top, int bottom)
{
	for (int i = top; i <= bottom; i++) {
		switch (CodeStore[i]->tag)
		{
		case STATE: {
			int st = CodeStore[i]->top;
			int ed = CodeStore[i]->bottom;
			switch (buffer[st]->tag)
			{
			case KEY_IN: SoIn::input(CodeStore[i]->top, CodeStore[i]->bottom); break;
			case KEY_OUT: SoOut::print(CodeStore[i]->top, CodeStore[i]->bottom); break;
			case KEY_INT:																//三种类型关键字，默认是定义式
			case KEY_REAL:
			case KEY_STRING: {//默认是定义式
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {//默认是赋值式
				ModeAssign test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.Fuzhi();
			}
			default:
				break;
			}
		}
		case CALL: {//函数调用式
			FuncType fType(CodeStore[i]->top, CodeStore[i]->bottom);
			fType.Func();
			break;
		}
		case IF: {//If式
			Mode
		}
		case ELSE:
		case WHILE:
		case KEY_BRK:
		case KEY_CON:
		case KEY_RET:
		default:
			break;
		}
	}
}


void ModeExecute::caller(Caller * func, vector <Token *> s)/*寻找对应的函数*/
{
	string name = func->name;
	int cnt = func->paralist.size();
	int ans = 0;
	for (int i = 0; i < FuncStore.size(); i++) {
		if ((FuncStore[i]->paralist.size() == cnt) && (name.compare(FuncStore[i]->name) == 0))
		{
			bool flag = true;
			for (int j = 0; j < func->paralist.size(); j++) {
				Idt * a = (Idt *)FuncStore[i]->paralist[j];
				if (a->assType != func->paralist[j]->tag) {
					flag = false;
					break;
				}
			}
			if (flag) {
				ans = i;
				break;
			}
		}
	}
	SoFunc * a = FuncStore[ans];				//调用函数
	vector<Token *> tmp = a->paralist;
	for (int i = 0; i < tmp.size(); i++) {
		Idt * idt = (Idt *)tmp[i];
		idt->t = s[i];
		RunTime.push(idt);
		RunTime.sync(esp);						//同步运行栈栈顶
	}
	switch (a->retType)							//将函数返回值入栈
	{
	case NUM: RunTime.push(new SoInt(0, 0, 0)); RunTime.sync(esp); break;
	case RNUM: RunTime.push(new SoReal(0, 0, 0)); RunTime.sync(esp); break;
	case STRING:
	default: RunTime.push(new SoString(0, 0, 0)); RunTime.sync(esp);
		break;
	}
	PRTR * prt = new PRTR(ebp);					//将当前层运行栈指针保存
	RunTime.push(prt);
	RunTime.sync(ebp);
	esp = ebp;
	ModeSyntexAnalysis mSA;						//分析执行
	mSA.getHeadAndTail(a->top, a->bottom);
	return;
}

PRTR::PRTR(Token ** s)
{
	tag = PRT;
	prt = s;
	line = 0;
	col = 0;
}
