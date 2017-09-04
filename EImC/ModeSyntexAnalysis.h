#ifndef MODESYNTEXANALYSIS_H_
#define MODESYNTEXANALYSIS_H_

#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include<vector>

class Block {/*�������*/
public:
	Tag tag;
	Token * top;            //�����������ŵ����鿪ʼλ��
	Token * bottom;         //�����������ŵ��������λ��
	Block();
	Block(Tag t);
};

class AltExpr : public Block {/*�������*/
public:
	AltExpr(Token * t, Token * b);
};

class Expr :public Block {/*���ʽ*/
public:
	Expr(Token * t, Token * b);
};

class SoWhile : public Block {/*while������*/
public:
	Token * conditionExprTop;       //�������ʽ��ʼλ��
	Token * conditionExprBottom;	//�������ʽ����λ��
	SoWhile(Token * top, Token * bottom, Token * cETop, Token * cEBottom);
};

class SoIf : public Block {/*if������*/
public:
	Token * judgeExprTop;			//�жϱ��ʽ��ʼλ��
	Token * judgeExprBottom;		//�жϱ��ʽ����λ��
	SoIf(Token * t, Token * b, Token * jETop, Token * jEBottom);
};

class SoElse : public Block {/*else������*/
public:
	SoElse(Token * t, Token * b);
};

class SoFunc : public Block {/*����������*/
public:
	string name;
	Tag retType;				//����ֵ����
	vector <Token*> paralist;	//�����б�
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
