#include<iostream>
#include<vector>
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
using namespace std; 
// ʶ���� 
// ����fun(a,7)
// ʶ��� ������ �����б�

extern vector<Token*>partlist;

class FuncType
{
public:
	FuncType(int a,int b);
	Token* Func();
private:
	int top;
	int bottom;
};




