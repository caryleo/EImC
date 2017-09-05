#ifndef MODEEXECUTE_H_
#define MODEEXECUTE

#include"EImC.h"
#include "ModeSyntexAnalysis.h"

using namespace std;

class ModeExecute {
public:
	static void init();
	static bool queryMain(SoFunc * corner);
	static void commence(int top, int bottom);
	static void caller(Caller * func);
};
#endif // !MODEEXECUTE_H_
#pragma once
