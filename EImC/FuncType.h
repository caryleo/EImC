#include<iostream>
#include<vector>
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
using namespace std; 
// 识别函数 
// 例如fun(a,7)
// 识别出 函数名 参数列表

extern vector<Token*>partlist;

class FuncType
{
public:
	FuncType(int a,int b);
	void Func();
	vector <Token*>paralist;
private:
	int top;
	int bottom;
};




