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
#include "DebugExecute.h"

using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;
extern vector <Token *> ConstStore;	//常量存储区
extern vector <SoFunc *> FuncStore;	//函数语句块存储区
extern Stack RunTime;					//运行栈
extern Token ** esp, **ebp;			//运行栈的栈顶和栈底

int DebugExecute::commence(int top, int bottom) {
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

void DebugExecute::stoprun(int i) {
	string inp;
	cin >> inp;
	if (inp.compare("next")) {
		return;
	}
	else if (inp.compare("watch")) {
		Idt * ans = RunTime.query(inp);
		
	}
}

void DebugExecute::print(int i) {
	cout << "current statement: ";
	for (int j = CodeStore[i]->top; j <= CodeStore[i]->bottom; j++) {
		switch (buffer[j]->tag)
		{
		case IDT: {
			Idt * tmp = (Idt *)buffer[i];
			cout << tmp->name << " ";
			break;
		}
		case NUM: {
			SoInt * tmp = (SoInt *)buffer[i];
			cout << tmp->val << " ";
			break;
		}
		case RNUM: {
			SoReal * tmp = (SoReal *)buffer[i];
			cout << tmp->val << " ";
			break;
		}
		default:
			break;
		}
	}
}