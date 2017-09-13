#ifndef DEBUGEXECUTE_H_
#define DEBUGEXECUTE_H_

using namespace std;

class DebugExecute {
public:
	static void commence(int top, int bottom);
	static void await(int i);
	static void print(int i);
	static void breakpoint(int i);
};

#endif // !DEBUGEXECUTE_H_
#pragma once
