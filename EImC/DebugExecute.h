#ifndef DEBUGEXECUTE_H_
#define DEBUGEXECUTE_H_
#include<set>
#include<iostream>
using namespace std;

class DebugExecute {
public:
	static int commence(int top, int bottom);
	static void stoprun(int i);
	//static void print(int i);
	static void watch(string name);
	static void add(string name);
	static void move(string name);
	static void print();

};
static set<string> iset;
#endif // !DEBUGEXECUTE_H_
#pragma once

