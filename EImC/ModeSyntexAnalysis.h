#ifndef MODESYNTEXANALYSIS_H_
#define MODESYNTEXANALYSIS_H_

#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include<vector>

class Block {/*语句块基类*/
public:
	Tag tag;
	Token * top;            //不包括大括号的语句块开始位置
	Token * bottom;         //不包括大括号的语句块结束位置
	Block();
	Block(Tag t);
};

class AltExpr : public Block {/*单行语句*/
public:
	AltExpr(Token * t, Token * b);
};

class Expr :public Block {/*表达式*/
public:
	Expr(Token * t, Token * b);
};

class SoWhile : public Block {/*while语句块类*/
public:
	Token * conditionExprTop;       //条件表达式开始位置
	Token * conditionExprBottom;	//条件表达式结束位置
	SoWhile(Token * top, Token * bottom, Token * cETop, Token * cEBottom);
};

class SoIf : public Block {/*if语句块类*/
public:
	Token * judgeExprTop;			//判断表达式开始位置
	Token * judgeExprBottom;		//判断表达式结束位置
	SoIf(Token * t, Token * b, Token * jETop, Token * jEBottom);
};

class SoElse : public Block {/*else语句块类*/
public:
	SoElse(Token * t, Token * b);
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
    void getHeadAndTail(Token *h,Token *t);
    vector<Token*>::iterator it=subStart;
    Token *look,*subEnd,*subStart;
};

#endif // !MODESYNTEXANALYSIS_H_
#pragma once
