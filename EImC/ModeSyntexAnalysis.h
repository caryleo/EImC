#ifndef MODESYNTEXANALYSIS_H_
#define MODESYNTEXANALYSIS_H_

#include"EImC.h"
#include"ModeTokenAnalysis.h"

class Block {/*�������*/
public:
	Tag tag;
	int top;            //�����������ŵ����鿪ʼλ��
	int bottom;         //�����������ŵ��������λ��
	Block();
	Block(Tag t);
};

class AltExpr : public Block {/*�������*/
public:
	AltExpr(int t, int b);
};

class Expr :public Block {/*���ʽ*/
public:
	Expr(int t, int b);
};

class SoWhile : public Block {/*while������*/
public:
	int conditionExprTop;       //�������ʽ��ʼλ��
	int conditionExprBottom;	//�������ʽ����λ��
	SoWhile(int top, int bottom, int cETop, int cEBottom);
};

class SoIf : public Block {/*if������*/
public:
	int judgeExprTop;			//�жϱ��ʽ��ʼλ��
	int judgeExprBottom;		//�жϱ��ʽ����λ��
	SoIf(int t, int b, int jETop, int jEBottom);
};

class SoElse : public Block {/*else������*/
public:
	SoElse(int t, int b);
};

class SoFunc : public Block {/*����������*/
public:
	string name;
	Tag retType;				//����ֵ����
	bool isImple;
	vector <Token*> paralist;	//�����б�
	SoFunc(string n, Tag r);
};

class Caller : public Block {
public:
	string name;
	vector <Token *> paralist;
	Caller(string n, vector<Token *> t);
};

class DoUntil : public Block {/*do untilѭ��������*/
public:
	int conditionExprTop;       //�������ʽ��ʼλ��
	int conditionExprBottom;	//�������ʽ����λ��
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
	bool getHeadAndTail(int h, int t);
	int subEnd, subStart, it;
	bool findSame(string name, SoFunc * func);
	void getError(int _l,int _r,int _code)
	{
	    l=_l;
	    r=_r;
	    code=_code;
	}
	bool hasRet();
	Token *look;
private:
    int l,r,code;
    bool ret;
};

#endif // !MODESYNTEXANALYSIS_H_
#pragma once

