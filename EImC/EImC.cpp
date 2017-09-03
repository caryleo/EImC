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
	cout << "Start token analyzing..." << endl;
	ModeTokenAnalysis::read(mRead);
	for (int i = 0; i < buffer.size(); i++) {
		cout << buffer[i]->tag << endl;
		if (buffer[i]->tag == NUM) {
			Token * t = buffer[i];
			SoInt * i = (SoInt*)t;
			cout << "NUM: " << i->val << endl;
		}
		if (buffer[i]->tag == RNUM) {
			Token * t = buffer[i];
			SoReal * i = (SoReal*)t;
			cout << "RNUM: " << i->val << endl;
		}
		if (buffer[i]->tag == STRING) {
			Token * t = buffer[i];
			SoString * i = (SoString*)t;
			cout << "STRING: " << i->str << endl;
		}
	}
	return 0;
}

