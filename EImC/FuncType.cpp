#include<iostream>
#include<vector>
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
#include"FuncType.h"
using namespace std;
extern vector<Token*> buffer;

FuncType::FuncType(int a,int b){
	top = a;
	bottom = b;
}

void FuncType::Func()
{
	int temp = top;
	while (temp<=bottom) // 识别到 函数名 之后是个左括号 
	{
		if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
		{
			break;
		}
		temp++;
	}
	int funcname = temp;
}