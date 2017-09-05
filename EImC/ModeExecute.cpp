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
vector <Token *> ConstStore;	//�����洢��
vector <SoFunc *> FuncStore;	//��������洢��
Stack RunTime;					//����ջ
Token ** esp, **ebp;			//����ջ��ջ����ջ��

void ModeExecute::init(int top, int bottom)		//�״ν���ִ�й���
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
			case KEY_INT:																//�������͹ؼ��֣�Ĭ���Ƕ���ʽ
			case KEY_REAL:
			case KEY_STRING: {//Ĭ���Ƕ���ʽ
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {//Ĭ���Ǹ�ֵʽ
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


void ModeExecute::caller(Caller * func, vector <Token *> s)/*Ѱ�Ҷ�Ӧ�ĺ���*/
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
	esp = ebp;
	ModeSyntexAnalysis mSA;						//����ִ��
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
