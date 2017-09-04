// EImC.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"EImC.h"
#include"ModeRead.h"
#include"ModeTokenAnalysis.h"
#include "ModeSyntexAnalysis.h"

std::vector<Token*>buffer;


int main()
{
	ModeRead mRead;
	mRead.readMode();
	ModeTokenAnalysis::read(mRead);
	int i = buffer.size();
	ModeSyntexAnalysis::getHeadAndTail(buffer[0], buffer[i - 1]);
    return 0;
}

