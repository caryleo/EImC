// EImC.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"EImC.h"
#include"ModeRead.h"
#include"ModeTokenAnalysis.h"

std::vector<Token*>buffer;


int main()
{
	ModeRead mRead;
	mRead.readMode();
	ModeTokenAnalysis::read(mRead);
	return 0;
}

