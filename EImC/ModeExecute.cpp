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
using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;
vector <Token *> ConstStore;	//�����洢��
vector <SoFunc *> FuncStore;	//��������洢��
Stack RunTime;					//����ջ
Token ** esp, **ebp;			//����ջ��ջ����ջ��

void ModeExecute::init()
{
	for (int i = 0; i < CodeStore.size(); i++) {
		if (CodeStore[i]->tag == FUNC) {
			SoFunc * func = (SoFunc *)CodeStore[i];
			if (queryMain(func)) {
				ModeSyntexAnalysis mSA;
				mSA.getHeadAndTail(func->top, func->bottom);
			}
		}
	}
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
			case KEY_INT:
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
			case CALL: {

			}
			default:
				break;
			}
		}
		case CALL:
		case IF:
		case ELSE:
		case WHILE:
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
	ModeSyntexAnalysis mSA;
	return;
}


