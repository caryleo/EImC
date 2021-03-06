#ifndef MODESYNTEXANALYSIS_H_
#define MODESYNTEXANALYSIS_H_

#include"EImC.h"
#include"ModeTokenAnalysis.h"

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
	bool isImple;
	vector <Token*> paralist;	//参数列表
	SoFunc(string n, Tag r);
};

class Caller : public Block {
public:
	string name;
	vector <Token *> paralist;
	Caller(string n, vector<Token *> t);
};

class DoUntil : public Block {/*do until循环语句块类*/
public:
	int conditionExprTop;       //条件表达式开始位置
	int conditionExprBottom;	//条件表达式结束位置
	DoUntil(int top, int bottom, int cETop, int cEBottom);
};

//fun(a, 6);

class ModeSyntexAnalysis {
public:
	void sMove();
	bool match(Tag need);
	bool statement();
	bool whileStat();
	bool ifStat();
	bool elseStat();
	bool altExprStat();
	bool exp();
	bool doStat();
	bool brkStat();
	bool conStat();
	bool retStat();
	bool inStat();
	bool outStat();
	bool distinguish();
	bool funStat(Tag retType,string name);
	int getHeadAndTail(int h, int t);
	int subEnd, subStart, it;
	bool findSame(string name, SoFunc * func);
	void getError(int _l,int _r,int _code)
	{
	    l=_l;
	    r=_r;
	    code=_code;
	}
	//bool hasRet();
	Token *look;
private:
    int l,r,code;
    //bool ret;
};

#endif // !MODESYNTEXANALYSIS_H_
#pragma once

