#ifndef SOOUT_H_
#define SOOUT_H_

#include"EImC.h"
using namespace std;

class SoOut {
public:
	static void print(int top, int bottom);//������
	static bool isValid(int top, int bottom);//�ж�out����Ƿ�Ϸ�
	static void judgeIdt(int m);//�ù�������Idt�����Ͳ����
};

#endif // !SOOUT_H_
