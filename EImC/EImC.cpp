// EImC.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"EImC.h"
#include"ModeRead.h"
#include"ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"

std::vector<Token*>buffer;

int inp;//模式控制

int main()
{
	//cout << "please select process mode" << endl;
	//cout << "1.interpreter mode 2.debug mode" << endl;
	inp = 1;
	ModeRead mRead;
	mRead.readMode();
	ModeTokenAnalysis::read(mRead);
	ModeSyntexAnalysis mSA;
	mSA.getHeadAndTail(0, buffer.size() - 1);
    return 0;
}

