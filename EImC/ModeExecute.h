#ifndef MODEEXECUTE_H_
#define MODEEXECUTE

#include"EImC.h"

using namespace std;

class ModeExecute {
public:
	static int change(Token * t);
	static void init(string name);
	bool query(SoFunc * corner, string name);
};
#endif // !MODEEXECUTE_H_
#pragma once
