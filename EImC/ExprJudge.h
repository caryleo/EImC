//#ifndef ExprJudge_H_
//#define ExprJudge_H_

#include<iostream>
#include<vector>
#include"EImC.h"
#include<string>
#include<utility>
using namespace std;
// 判断算术表达式是否合法类：使用方法 
// ExprJudge a(top,bottom)
// a.ExprTest()   if return 1 right return 0 error
class ExprJudge
{
public:
	ExprJudge(int a, int b);
	bool input(int top, int bottom);
	void T();
	void F();
	int word_analysis(vector<pair<string, int>>& word, const string expr);
	void Next();
	void E();
	int ExprTest();

private:
	int top;
	int bottom;
	string expr;
	vector<pair<string, int>> word;
	int idx = 0;
	int sym;
	int err = 0; // 错误  

};


