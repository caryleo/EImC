#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "ModeExecute.h"
#include <vector>
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


