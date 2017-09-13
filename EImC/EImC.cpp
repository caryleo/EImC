// EImC.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "EImC.h"
#include "ModeRead.h"
#include "ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"
#include "Stack.h"
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
	cout << "please select process mode" << endl;
	cout << "1.interpreter mode 2.debug mode" << endl;
	cin >> inp;
	ModeRead mRead;
	mRead.readMode();
	ModeTokenAnalysis::read(mRead);
	sizen = buffer.size();
	ModeSyntexAnalysis mSA;
	mSA.getHeadAndTail(0, buffer.size() - 1);
	buffer.clear();
	ConstStore.clear();
	CodeStore.clear();
	FuncStore.clear();
	delete esp;
	delete ebp;
    return 0;
}

