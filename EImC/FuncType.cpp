#include<iostream>
#include<vector>
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
#include"FuncType.h"
using namespace std;

FuncType::FuncType(int a,int b){
	top = a;
	bottom = b;
}