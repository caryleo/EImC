//#ifndef ExprJudge_H_
//#define ExprJudge_H_

#include<iostream>
#include<vector>
#include"EImC.h"
using namespace std;

class ExprJudge
{
public:
	ExprJudge(int a, int b);
	void input(int top, int bottom);

private:
	int top;
	int bottom;
};


