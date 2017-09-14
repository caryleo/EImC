// EImC.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "EImC.h"
#include "ModeRead.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "Stack.h"
#include <time.h>
using namespace std;

vector<Token*>buffer;
extern Stack RunTime;
extern vector<Token*>buffer;
extern vector<Token*> ConstStore;
extern vector<Block*>CodeStore;
extern vector <SoFunc *> FuncStore;
extern Token ** esp, **ebp;
int sizen;

int inp;//模式控制

int main()
{
	//最终版1.5
	cout << "please select process mode" << endl;
	cout << "1.interpreter mode 2.debug mode" << endl;
	cin >> inp;
	ModeRead mRead;
	mRead.readMode();
	clock_t start, finish;
	double totaltime;
	start = clock();
	ModeTokenAnalysis::read(mRead);
	sizen = buffer.size();
	RunTime.sync();
	RunTime.syncb();
	ModeSyntexAnalysis mSA;
	mSA.getHeadAndTail(0, buffer.size() - 1);
	buffer.clear();
	ConstStore.clear();
	CodeStore.clear();
	FuncStore.clear();
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << endl << "processing time: " << totaltime << "s" << endl;
    return 0;
}

