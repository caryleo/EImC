#ifndef MODEEXECUTE_H_
#define MODEEXECUTE

#include"EImC.h"
#include "ModeSyntexAnalysis.h"

using namespace std;

class ModeExecute {
public:
	static void init(int top, int bottom);						//�������е�һ�εģ����򼶣����鼯�ϵ�ִ��
	static void commence(int top, int bottom);					//����ִ��ָ�������鼯��
	static Token * caller(Caller * func, vector <Token *> s, int line);		//�������к�������
	static void assign(int top, int bottom);					//�����Ա��ʽ���в�ѯ��ֵ
};

class PRTR : public Token {/*�������Token**����*/
public:
	Token ** prt;
	PRTR(Token ** s);
};
#endif // !MODEEXECUTE_H_
#pragma once
