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
#include "Expression.h"
#include "ModeWhile.h"
#include "ReturnType.h"
using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;
vector <Token *> ConstStore;	//常量存储区
vector <SoFunc *> FuncStore;	//函数语句块存储区
Stack RunTime;					//运行栈
Token ** esp, **ebp;			//运行栈的栈顶和栈底

void ModeExecute::init(int top, int bottom)		//首次进行执行管理
{
	for (int i = top; i <= bottom; i++) {
		switch (CodeStore[i]->tag)
		{
		case STATE: {
			int st = CodeStore[i]->top;
			int ed = CodeStore[i]->bottom;
			switch (buffer[st]->tag)
			{
			case KEY_IN: {//输入式
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				SoIn::input(CodeStore[i]->top, CodeStore[i]->bottom);
				break;
			}

			case KEY_OUT: {
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				SoOut::print(CodeStore[i]->top, CodeStore[i]->bottom);
				break;
			}
			case KEY_INT:																//三种类型关键字，默认是定义式
			case KEY_REAL:
			case KEY_STRING: {//默认是定义式
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {//默认是赋值式
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				ModeAssign test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.Fuzhi();
			}
			default:
				break;
			}
		}
		case CALL:
		case IF:
		case ELSE:
		case WHILE:
		case KEY_RET: {//return语句
			cout << "ERROR!!!" << endl;
			break;
		}
		default:
			break;
		}
	}
	vector <Token *> tmp;
	tmp.clear();
	Caller * main = new Caller("main", tmp);
	ModeExecute::caller(main, tmp);
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
			case KEY_IN: {//输入式
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				SoIn::input(CodeStore[i]->top, CodeStore[i]->bottom);
				break;
			}

			case KEY_OUT: {
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				SoOut::print(CodeStore[i]->top, CodeStore[i]->bottom);
				break;
			}
			case KEY_INT:																//三种类型关键字，默认是定义式
			case KEY_REAL:
			case KEY_STRING: {//默认是定义式
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {//默认是赋值式
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
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
			Block * tmp = CodeStore[i];
			SoIf * baba = (SoIf *)tmp;
			ExprIR eIR;
			ModeExecute::assign(baba->judgeExprTop, baba->judgeExprBottom);//为表达式寻找值
			Token * ans = eIR.calculate_expr(baba->judgeExprTop, baba->judgeExprBottom); //获得条件表达式的结果
			switch (ans->tag)
			{
			case NUM:
			{
				if (((SoInt *)ans)->val == 0) {//if不可执行，或跳过，或无条件执行紧邻的else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
						i++;//执行else块 并跳至else块的下一个位置
						RunTime.desync(ebp, esp);
					}
					else {
					}
				}
				else {//if可执行，执行，并无条件跳过紧邻的else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						i++;
						RunTime.desync(ebp, esp);
					}
					else {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						RunTime.desync(ebp, esp);
					}
				}
				break;
			}
			case RNUM: {
				if (((SoReal *)ans)->val == 0.0) {//if不可执行，或跳过，或无条件执行紧邻的else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
						i++;//执行else块 并跳至else块的下一个位置
						RunTime.desync(ebp, esp);
					}
					else {
					}
				}
				else {//if可执行，执行，并无条件跳过紧邻的else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						i++;
						RunTime.desync(ebp, esp);
					}
					else {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						RunTime.desync(ebp, esp);
					}
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case ELSE: {//没有关联if的else式
			cout << "ERROR!!!" << endl;
			break;
		}
		case WHILE: {//While式
			Block * tmp = CodeStore[i];
			SoWhile * baba = (SoWhile *)tmp;
			ModeExecute::assign(baba->conditionExprTop, baba->conditionExprBottom);
			ModeWhile mWhile(CodeStore[i]->top, CodeStore[i]->bottom, baba->conditionExprTop, baba->conditionExprBottom);
			mWhile.runWhile();
			break;
		}
		case KEY_RET: {//return语句
			ReturnType rType(CodeStore[i]->top, CodeStore[i]->bottom);
			rType.startReturn();
			break;
		}
		default:
			break;
		}
	}
}


Token * ModeExecute::caller(Caller * func, vector <Token *> s)/*寻找对应的函数*/
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
	RunTime.sync(esp);
	esp = ebp;
	ModeSyntexAnalysis mSA;						//分析执行
	mSA.getHeadAndTail(a->top, a->bottom);
	Token * ret = RunTime.front();				// 拿到函数返回值
	RunTime.sync(esp);
	return;
}

void ModeExecute::assign(int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		if (buffer[i]->tag == IDT) {//为表达式赋初值
			Idt * tmp = (Idt *)buffer[i];
			Idt * ret = RunTime.query(tmp->name);
			if (ret != NULL) {
				tmp->assType = ret->assType;
				switch (tmp->assType)
				{
				case NUM: {
					SoInt * comecome = (SoInt *)(ret->t);
					SoInt * gogo = new SoInt(comecome->val, 0, 0);
					ConstStore.push_back(gogo);
					tmp->t = gogo;
					break;
				}
				case RNUM: {
					SoReal * comecome = (SoReal *)(ret->t);
					SoReal * gogo = new SoReal(comecome->val, 0, 0);
					ConstStore.push_back(gogo);
					tmp->t = gogo;
					break;
				}
				case STRING: {
					SoString * comecome = (SoString *)(ret->t);
					SoString * gogo = new SoString(comecome->str, 0, 0);
					ConstStore.push_back(gogo);
					tmp->t = gogo;
					break;
				}
				default:
					tmp->t = NULL;
					break;
				}
			}
			else {
				tmp->assType = ERR;
				tmp->t = NULL;
			}
		}
	}
}

PRTR::PRTR(Token ** s)
{
	tag = PRT;
	prt = s;
	line = 0;
	col = 0;
}
