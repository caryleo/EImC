#ifndef MODESYNTEXANALYSIS_H_
#define MODESYNTEXANALYSIS_H_

#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include<vector>

class Block {/*语句块基类*/
public:
	Tag tag;
	int top;            //不包括大括号的语句块开始位置
	int bottom;         //不包括大括号的语句块结束位置
	Block();
	Block(Tag tag);
};

class SoWhile: public Block {/*while语句块类*/
public:
	int conditionExprTop;       //条件表达式开始位置
	int conditionExprBottom;	//条件表达式结束位置
	SoWhile(int top, int bottom, int cETop, int cEBottom);
};

class SoIf: public Block {/*if语句块类*/
public:
	int judgeExprTop;			//判断表达式开始位置
	int judgeExprBottom;		//判断表达式结束位置
	SoIf(int top, int bottom, int jETop, int jEBottom);
};

class SoElse: public Block {/*else语句块类*/
public:
	SoElse(int top, int bottom);
};

class SoFunc : public Block {/*函数语句块类*/
public:
	string name;
	Tag retType;
	vector <Token*> paralist;
	SoFunc(int top, int bottom, )
};


#endif // !MODESYNTEXANALYSIS_H_
#pragma once
