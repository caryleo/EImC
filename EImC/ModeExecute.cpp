#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "ModeExecute.h"
#include <vector>
using namespace std;

extern vector<Token*>buffer;
extern vector<Block*>CodeStore;

int ModeExecute::change(Token * t)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i] == t) {
			return i;
		}
	}
	return -1;
}

void ModeExecute::init(string name)
{
	for (int i = 0; i < CodeStore.size(); i++) {
		if (CodeStore[i]->tag == FUNC) {
			SoFunc * func = (SoFunc *)CodeStore[i];
			if(query(func))
		}
	}
}

Block * ModeExecute::query(SoFunc * corner, string name)
{

	return nullptr;
}
