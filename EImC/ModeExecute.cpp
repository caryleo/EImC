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
#include "ModeErrorReport.h"
using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;
vector <Token *> ConstStore;	//常量存储区
vector <SoFunc *> FuncStore;	//函数语句块存储区
Stack RunTime;					//运行栈
Token ** esp, **ebp;			//运行栈的栈顶和栈底

int ModeExecute::init(int top, int bottom)		//首次进行执行管理
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
			break;
		}
		case CALL:
		case IF:
		case ELSE:
		case WHILE:
		case DOUNTIL:
		case KEY_RET: {//return语句
			ModeErrorReport mER(251, buffer[CodeStore[i]->bottom]->line, buffer[CodeStore[i]->bottom]->col);
			mER.report();
			break;
		}
		default:
			break;
		}
	}
	vector <Token *> tmp;
	tmp.clear();
	Caller * main = new Caller("main", tmp);
	ModeExecute::caller(main, tmp, 0);
	return 0;
}

int ModeExecute::commence(int top, int bottom)
{
	for (int i = top; i <= bottom; i++) {
		Token * tmpn = buffer[CodeStore[i]->top];
		ModeErrorReport mEP(250, tmpn->line, tmpn->col);
		switch (CodeStore[i]->tag)
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
		case STATE: {
			int st = CodeStore[i]->top;
			int ed = CodeStore[i]->bottom;
			switch (buffer[st]->tag)
			{
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
			break;
		}
		case CALL: {//函数调用式
			FuncType fType(CodeStore[i]->top, CodeStore[i]->bottom);
			fType.Func();
			break;
		}
		case KEY_BRK: {
			return 3;
			break;
		}
		case KEY_CON: {
			return 2;
			break;
		}
		case IF: {//If式
			Block * tmp = CodeStore[i];
			SoIf * baba = (SoIf *)tmp;
			ExprIR eIR;
			ModeExecute::assign(baba->judgeExprTop, baba->judgeExprBottom);//为表达式寻找值
			Token * ans;
			if (buffer[baba->judgeExprTop]->tag == IDT && buffer[baba->judgeExprTop + 1]->tag == LPAR) {
				FuncType test(baba->judgeExprTop, baba->judgeExprBottom);
				ans = test.Func();
			}
			else
			{
				ans = eIR.calculate_expr(baba->judgeExprTop, baba->judgeExprBottom); //获得条件表达式的结果
			}
			switch (ans->tag)
			{
			case NUM:
			{
				if (((SoInt *)ans)->val == 0) {//if不可执行，或跳过，或无条件执行紧邻的else
					if (i < CodeStore.size() - 1) {
						if (CodeStore[i + 1]->tag == ELSE) {
							PRTR * build = new PRTR(ebp);
							RunTime.push(build);
							RunTime.syncb();
							RunTime.sync();
							ModeSyntexAnalysis mSA;
							int ans = mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
							switch (ans)
							{
							case 0: {
								i++;
								RunTime.desync();
								break;
							}
							case 1: {//return
								return 1;
								break;
							}
							case 2: {//continue
								RunTime.desync();
								return 2;
								break;
							}
							case 3: {//break;
								RunTime.desync();
								return 3;
								break;
							}
							default:
								break;
							}
						}
						else {

						}
					}
				}
				else {//if可执行，执行，并无条件跳过紧邻的else
					if (i < CodeStore.size() - 1) {
						if (CodeStore[i + 1]->tag == ELSE) {
							PRTR * build = new PRTR(ebp);
							RunTime.push(build);
							RunTime.syncb();
							RunTime.sync();
							ModeSyntexAnalysis mSA;
							int ans = mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
							switch (ans)
							{
							case 0: {
								i++;
								RunTime.desync();
								break;
							}
							case 1: {//return
								return 1;
								break;
							}
							case 2: {//continue
								RunTime.desync();
								return 2;
								break;
							}
							case 3: {//break;
								RunTime.desync();
								return 3;
								break;
							}
							default:
								break;
							}
						}
						else {
							PRTR * build = new PRTR(ebp);
							RunTime.push(build);
							RunTime.syncb();
							RunTime.sync();
							ModeSyntexAnalysis mSA;
							int ans = mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
							switch (ans)
							{
							case 0: {
								RunTime.desync();
								break;
							}
							case 1: {//return
								return 1;
								break;
							}
							case 2: {//continue
								RunTime.desync();
								return 2;
								break;
							}
							case 3: {//break;
								RunTime.desync();
								return 3;
								break;
							}
							default:
								break;
							}
						}
					}
					else {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						int ans = mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						switch (ans)
						{
						case 0: {
							RunTime.desync();
							break;
						}
						case 1: {//return
							return 1;
							break;
						}
						case 2: {//continue
							RunTime.desync();
							return 2;
							break;
						}
						case 3: {//break;
							RunTime.desync();
							return 3;
							break;
						}
						default:
							break;
						}
					}
				}
				break;
			}
			case RNUM: {
				if (((SoReal *)ans)->val == 0.0) {//if不可执行，或跳过，或无条件执行紧邻的else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						int ans = mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
						switch (ans)
						{
						case 0: {
							i++;
							RunTime.desync();
							break;
						}
						case 1: {//return
							return 1;
							break;
						}
						case 2: {//continue
							RunTime.desync();
							return 2;
							break;
						}
						case 3: {//break;
							RunTime.desync();
							return 3;
							break;
						}
						default:
							break;
						}
					}
					else {
					}
				}
				else {//if可执行，执行，并无条件跳过紧邻的else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						int ans = mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						switch (ans)
						{
						case 0: {
							i++;
							RunTime.desync();
							break;
						}
						case 1: {//return
							return 1;
							break;
						}
						case 2: {//continue
							RunTime.desync();
							return 2;
							break;
						}
						case 3: {//break;
							RunTime.desync();
							return 3;
							break;
						}
						default:
							break;
						}
					}
					else {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						int ans = mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						switch (ans)
						{
						case 0: {
							RunTime.desync();
							break;
						}
						case 1: {//return
							return 1;
							break;
						}
						case 2: {//continue
							RunTime.desync();
							return 2;
							break;
						}
						case 3: {//break;
							RunTime.desync();
							return 3;
							break;
						}
						default:
							break;
						}
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
			mEP.report();
			break;
		}
		case WHILE: {//While式
			Block * tmp = CodeStore[i];
			SoWhile * baba = (SoWhile *)tmp;
			ModeWhile mWhile(CodeStore[i]->top, CodeStore[i]->bottom, baba->conditionExprTop, baba->conditionExprBottom);
			int ans = mWhile.runWhile();
			if (ans == 0) {

			}
			else if (ans == 1) {
				return 1;
			}
			break;
		}
		case DOUNTIL: {//do-until式
			Block *tmp = CodeStore[i];
			DoUntil * baba = (DoUntil *)tmp;
			ModeDo mDo(CodeStore[i]->top, CodeStore[i]->bottom, baba->conditionExprTop, baba->conditionExprBottom);
			int ans = mDo.runDo();
			if (ans == 0) {

			}
			else if (ans == 1) {
				return 1;
			}
			break;
		}
		case KEY_RET: {//return语句
			ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
			ReturnType rType(CodeStore[i]->top, CodeStore[i]->bottom);
			rType.startReturn();
			return 1;
			break;
		}
		default:
			break;
		}
	}
	return 0;
}


Token * ModeExecute::caller(Caller * func, vector <Token *> s, int line)/*寻找对应的函数*/
{
	string name = func->name;
	int cnt = func->paralist.size();
	int ans = -1;
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
	if (ans == -1) {
		ModeErrorReport mER(501, line, 0);
		mER.report();
	}
	SoFunc * a = FuncStore[ans];				//调用函数
	Token *t = new Token;
	switch (a->retType)							//将函数返回值入栈
	{
	case KEY_INT: 
		t = new SoInt(0, 0, 0);
		RunTime.push(t);
		RunTime.sync();
		break;
	case KEY_REAL: 
		t = new SoReal(0.0, 0, 0);
		RunTime.push(t);
		RunTime.sync();
		break;
	case KEY_STRING:
		t = new SoString("", 0, 0);
		RunTime.push(t);
		RunTime.sync();
		break;
	default: 
		break;
	}
	PRTR * prt = new PRTR(ebp);					//将当前层运行栈指针保存
	RunTime.push(prt);
	RunTime.syncb();
	RunTime.sync();
	for (int i = 0; i < a->paralist.size(); i++) {
		Idt * idt = (Idt *)(a->paralist)[i];
		idt->t = s[i];
		idt->tag = IDT;
		RunTime.push(idt);
		RunTime.sync();						//同步运行栈栈顶
	}
	ModeSyntexAnalysis mSA;						//分析执行
	mSA.getHeadAndTail(a->top, a->bottom);
	Token * ret = RunTime.front();	// 拿到函数返回值，此时函数已经退栈，返回值在最内部
	RunTime.pop();					//pop掉返回值
	RunTime.sync();
	return ret;
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
					SoInt * gogo;
					if (comecome != nullptr) {
						gogo = new SoInt(comecome->val, 0, 0);
						ConstStore.push_back(gogo);
					}
					else {
						gogo = nullptr;
					}
					tmp->t = gogo;
					break;
				}
				case RNUM: {
					SoReal * comecome = (SoReal *)(ret->t);
					SoReal * gogo;
					if (comecome != nullptr) {
						gogo = new SoReal(comecome->val, 0, 0);
						ConstStore.push_back(gogo);
					}
					else {
						gogo = nullptr;
					}
					tmp->t = gogo;
					break;
				}
				case STRING: {
					SoString * comecome = (SoString *)(ret->t);
					SoString * gogo;
					if (comecome != nullptr) {
						gogo = new SoString(comecome->str, 0, 0);
						ConstStore.push_back(gogo);
					}
					else {
						gogo = nullptr;
					}
					tmp->t = gogo;
					break;
				}
				default:
					tmp->t = NULL;
					break;
				}
			}
			else {//变量未定义 直接定义成int型量
				tmp->assType = NUM;
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
