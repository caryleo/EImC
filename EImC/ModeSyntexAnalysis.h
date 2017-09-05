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
	Block(Tag t);
};

class AltExpr : public Block {/*单行语句*/
public:
	AltExpr(int t, int b);
};

class Expr :public Block {/*表达式*/
public:
	Expr(int t, int b);
};

class SoWhile : public Block {/*while语句块类*/
public:
	int conditionExprTop;       //条件表达式开始位置
	int conditionExprBottom;	//条件表达式结束位置
	SoWhile(int top, int bottom, int cETop, int cEBottom);
};

class SoIf : public Block {/*if语句块类*/
public:
	int judgeExprTop;			//判断表达式开始位置
	int judgeExprBottom;		//判断表达式结束位置
	SoIf(int t, int b, int jETop, int jEBottom);
};

class SoElse : public Block {/*else语句块类*/
public:
	SoElse(int t, int b);
};

class SoFunc : public Block {/*函数语句块类*/
public:
	string name;
	Tag retType;				//返回值类型
	vector <Token*> paralist;	//参数列表
	SoFunc(string n, Tag r);
};
class ModeSyntexAnalysis {
public:
	void sMove();
	bool match(Tag need);
	void statement();
	void whileStat();
	void ifStat();
	void elseStat();
	void exprStat();
	void altExprStat();
	void brkStat();
	void conStat();
	void retStat();
	void inStat();
	void outStat();
	void distinguish();
	void funStat(Tag retType,string name);
	void getHeadAndTail(int h, int t);
	int subEnd, subStart, it;
	Token *look;
};

#endif // !MODESYNTEXANALYSIS_H_
#pragma once

