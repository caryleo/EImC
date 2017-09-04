#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "ModeExecute.h"
#include "VarType.h"
#include "SoIn.h"
#include "SoOut.h"
#include "ModeAssign.h"
using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;

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

bool ModeExecute::queryMain(SoFunc * corner)
{
	return corner->name == "main" && corner->paralist.size() == 0 ? true : false;
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
			case KEY_STRING: {
				VarType test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.input();
				break;
			}
			case IDT: {
				ModeAssign test(CodeStore[i]->top, CodeStore[i]->bottom);
				test.Fuzhi();
			}
			default:
				break;
			}
		}
		default:
			break;
		}
	}
}


