#ifndef SOOUT_H_
#define SOOUT_H_

#include"EImC.h"
using namespace std;

class SoOut {
public:
	static void print(Token *top, Token *bottom);//������
	static bool isValid(Token *top, Token *bottom);//�ж�out����Ƿ�Ϸ�
	static void judgeIdt(Token *m);//�ù�������Idt�����Ͳ����
};

#endif // !SOOUT_H_
