#ifndef VarType_H_
#define VarType_H_

#include<iostream>
#include<vector>
#include"EImC.h"
using namespace std;
class VarType
{
public:
	VarType(int a, int b);
	static void input(int top, int bottom); //top is the start and bottom is the end
	static bool match(int m,Tag a);//match buffer������Ӧ�ñȽϵ��Ǹ�Ԫ�صı�ǩ����Ҫƥ��ı�ǩ
private:
	int top;
	int bottom;
};


#endif // !SOIN_H_
// �������������ִ�� int/real/string ��ͷ �Էֺ�Ϊ���� ��һ�д���
//����
// int a;  int a=1��b=1 ; int a,b; �����м������
//a=2 ��ֵ 
// real a;
//string a;