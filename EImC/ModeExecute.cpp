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
		}
		case CALL:
		case IF:
		case ELSE:
		case WHILE:
		case KEY_RET: {//return���
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
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
						i++;//ִ��else�� ������else�����һ��λ��
						RunTime.desync(ebp, esp);
					}
					else {
					}
				}
				else {//if��ִ�У�ִ�У����������������ڵ�else
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
				if (((SoReal *)ans)->val == 0.0) {//if����ִ�У�����������������ִ�н��ڵ�else
					if (CodeStore[i + 1]->tag == ELSE) {
						PRTR * build = new PRTR(ebp);
						RunTime.push(build);
						RunTime.sync(ebp);
						RunTime.sync(esp);
						ModeSyntexAnalysis mSA;
						mSA.getHeadAndTail(CodeStore[i + 1]->top, CodeStore[i + 1]->bottom);
						i++;//ִ��else�� ������else�����һ��λ��
						RunTime.desync(ebp, esp);
					}
					else {
					}
				}
				else {//if��ִ�У�ִ�У����������������ڵ�else
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
		case ELSE: {//û�й���if��elseʽ
			cout << "ERROR!!!" << endl;
			break;
		}
		case WHILE: {//Whileʽ
			Block * tmp = CodeStore[i];
			SoWhile * baba = (SoWhile *)tmp;
			ModeExecute::assign(baba->conditionExprTop, baba->conditionExprBottom);
			ModeWhile mWhile(CodeStore[i]->top, CodeStore[i]->bottom, baba->conditionExprTop, baba->conditionExprBottom);
			mWhile.runWhile();
			break;
		}
		case KEY_RET: {//return���
			ReturnType rType(CodeStore[i]->top, CodeStore[i]->bottom);
			rType.startReturn();
			break;
		}
		default:
			break;
		}
	}
}


Token * ModeExecute::caller(Caller * func, vector <Token *> s)/*Ѱ�Ҷ�Ӧ�ĺ���*/
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
	SoFunc * a = FuncStore[ans];				//���ú���
	vector<Token *> tmp = a->paralist;
	for (int i = 0; i < tmp.size(); i++) {
		Idt * idt = (Idt *)tmp[i];
		idt->t = s[i];
		RunTime.push(idt);
		RunTime.sync(esp);						//ͬ������ջջ��
	}
	switch (a->retType)							//����������ֵ��ջ
	{
	case NUM: RunTime.push(new SoInt(0, 0, 0)); RunTime.sync(esp); break;
	case RNUM: RunTime.push(new SoReal(0, 0, 0)); RunTime.sync(esp); break;
	case STRING:
	default: RunTime.push(new SoString(0, 0, 0)); RunTime.sync(esp);
		break;
	}
	PRTR * prt = new PRTR(ebp);					//����ǰ������ջָ�뱣��
	RunTime.push(prt);
	RunTime.sync(ebp);
	RunTime.sync(esp);
	esp = ebp;
	ModeSyntexAnalysis mSA;						//����ִ��
	mSA.getHeadAndTail(a->top, a->bottom);
	Token * ret = RunTime.front();				// �õ���������ֵ
	RunTime.sync(esp);
	return;
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
