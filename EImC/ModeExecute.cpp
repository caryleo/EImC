#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "ModeExecute.h"
#include <vector>
using namespace std;

extern vector<Token*>buffer;

int ModeExecute::change(Token * t)
{
	for (int i = 0; i < buffer.size(); i++) {
		if (buffer[i] == t) {
			return i;
		}
	}
	return -1;
}
