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
vector <Token *> ConstStore;	//�����洢��
vector <SoFunc *> FuncStore;	//��������洢��
Stack RunTime;					//����ջ
Token ** esp, **ebp;			//����ջ��ջ����ջ��

void ModeExecute::init(int top, int bottom)		//�״ν���ִ�й���
{
	for (int i = top; i <= bottom; i++) {
		switch (CodeStore[i]->tag)
		{
		case STATE: {
			int st = CodeStore[i]->top;
			int ed = CodeStore[i]->bottom;
			switch (buffer[st]->tag)
			{
			case KEY_IN: {//����ʽ
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				SoIn::input(CodeStore[i]->top, CodeStore[i]->bottom);
				break;
			}

			case KEY_OUT: {
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				SoOut::print(CodeStore[i]->top, CodeStore[i]->bottom);
				break;
			}
			case KEY_INT:																//�������͹ؼ��֣�Ĭ���Ƕ���ʽ
			case KEY_REAL:
			case KEY_STRING: {//Ĭ���Ƕ���ʽ
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {//Ĭ���Ǹ�ֵʽ
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
		case KEY_RET: {//return���
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
}

void ModeExecute::commence(int top, int bottom)
{
	for (int i = top; i <= bottom; i++) {
		Token * tmpn = buffer[CodeStore[i]->top];
		ModeErrorReport mEP(250, tmpn->line, tmpn->col);
		switch (CodeStore[i]->tag)
		{
		case KEY_IN: {//����ʽ
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
			case KEY_INT:																//�������͹ؼ��֣�Ĭ���Ƕ���ʽ
			case KEY_REAL:
			case KEY_STRING: {//Ĭ���Ƕ���ʽ
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {//Ĭ���Ǹ�ֵʽ
				ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
				ModeAssign test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.Fuzhi();
			}
			default:
				break;
			}
			break;
		}
		case CALL: {//��������ʽ
			FuncType fType(CodeStore[i]->top, CodeStore[i]->bottom);
			fType.Func();
			break;
		}
		case IF: {//Ifʽ
			Block * tmp = CodeStore[i];
			SoIf * baba = (SoIf *)tmp;
			ExprIR eIR;
			ModeExecute::assign(baba->judgeExprTop, baba->judgeExprBottom);//Ϊ���ʽѰ��ֵ
			Token * ans = eIR.calculate_expr(baba->judgeExprTop, baba->judgeExprBottom); //����������ʽ�Ľ��
			switch (ans->tag)
			{
			case NUM:
			{
				if (((SoInt *)ans)->val == 0) {//if����ִ�У�����������������ִ�н��ڵ�else
					if (i < CodeStore.size() - 1) {
						if (CodeStore[i + 1]->tag == ELSE) {
							PRTR * build = new PRTR(ebp);
							RunTime.push(build);
							RunTime.syncb();
							RunTime.sync();
							ModeSyntexAnalysis mSA;
							mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
							i++;//ִ��else�� ������else�����һ��λ��
							if (!mSA.hasRet()) {
								RunTime.desync();
							}
						}
						else {

						}
					}
				}
				else {//if��ִ�У�ִ�У����������������ڵ�else
					if (i < CodeStore.size() - 1) {
						if (CodeStore[i + 1]->tag == ELSE) {
							PRTR * build = new PRTR(ebp);
							RunTime.push(build);
							RunTime.syncb();
							RunTime.sync();
							ModeSyntexAnalysis mSA;
							mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
							i++;
							if (!mSA.hasRet()) {
								RunTime.desync();
							}
						}
						else {
							PRTR * build = new PRTR(ebp);
							RunTime.push(build);
							RunTime.syncb();
							RunTime.sync();
							ModeSyntexAnalysis mSA;
							mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
							if (!mSA.hasRet()) {
								RunTime.desync();
							}
						}
					}
					else {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						if (!mSA.hasRet()) {
							RunTime.desync();
						}
					}
				}
				break;
			}
			case RNUM: {
				if (((SoReal *)ans)->val == 0.0) {//if����ִ�У�����������������ִ�н��ڵ�else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
						i++;//ִ��else�� ������else�����һ��λ��
						if (!mSA.hasRet()) {
							RunTime.desync();
						}
					}
					else {
					}
				}
				else {//if��ִ�У�ִ�У����������������ڵ�else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						i++;
						if (!mSA.hasRet()) {
							RunTime.desync();
						}
					}
					else {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.syncb();
						RunTime.sync();
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i]->top, CodeStore[i]->bottom);
						if (!mSA.hasRet()) {
							RunTime.desync();
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
		case ELSE: {//û�й���if��elseʽ
			mEP.report();
			break;
		}
		case WHILE: {//Whileʽ
			Block * tmp = CodeStore[i];
			SoWhile * baba = (SoWhile *)tmp;
			ModeWhile mWhile(CodeStore[i]->top, CodeStore[i]->bottom, baba->conditionExprTop, baba->conditionExprBottom);
			mWhile.runWhile();
			break;
		}
		case DOUNTIL: {//do-untilʽ
			Block *tmp = CodeStore[i];
			DoUntil * baba = (DoUntil *)tmp;
			ModeDo mDo(CodeStore[i]->top, CodeStore[i]->bottom, baba->conditionExprTop, baba->conditionExprBottom);
			mDo.runDo();
		}
		case KEY_RET: {//return���
			ModeExecute::assign(CodeStore[i]->top, CodeStore[i]->bottom);
			ReturnType rType(CodeStore[i]->top, CodeStore[i]->bottom);
			rType.startReturn();
			break;
		}
		default:
			break;
		}
	}
}


Token * ModeExecute::caller(Caller * func, vector <Token *> s, int line)/*Ѱ�Ҷ�Ӧ�ĺ���*/
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
	SoFunc * a = FuncStore[ans];				//���ú���
	Token *t = new Token;
	switch (a->retType)							//����������ֵ��ջ
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
	PRTR * prt = new PRTR(ebp);					//����ǰ������ջָ�뱣��
	RunTime.push(prt);
	RunTime.syncb();
	RunTime.sync();
	for (int i = 0; i < a->paralist.size(); i++) {
		Idt * idt = (Idt *)(a->paralist)[i];
		idt->t = s[i];
		idt->tag = IDT;
		RunTime.push(idt);
		RunTime.sync();						//ͬ������ջջ��
	}
	ModeSyntexAnalysis mSA;						//����ִ��
	mSA.getHeadAndTail(a->top, a->bottom);
	Token * ret = RunTime.front();	// �õ���������ֵ����ʱ�����Ѿ���ջ������ֵ�����ڲ�
	RunTime.pop();					//pop������ֵ
	RunTime.sync();
	return ret;
}

void ModeExecute::assign(int top, int bottom)
{
	for (int i = top; i <= bottom; i++)
	{
		if (buffer[i]->tag == IDT) {//Ϊ���ʽ����ֵ
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
			else {//����δ���� ֱ�Ӷ����int����
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
