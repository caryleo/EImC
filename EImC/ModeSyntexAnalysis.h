#ifndef MODESYNTEXANALYSIS_H_
#define MODESYNTEXANALYSIS_H_

#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include<vector>

class Block {/*�������*/
public:
	Tag tag;
	int top;            //�����������ŵ����鿪ʼλ��
	int bottom;         //�����������ŵ��������λ��
	Block();
	Block(Tag t);
};

class AltExpr: public Block	{/*�������*/
public:
	AltExpr(int t, int b);
};

class Expr :public Block {/*���ʽ*/
public:
	Expr(int t, int b);
};

class SoWhile: public Block {/*while������*/
public:
	int conditionExprTop;       //�������ʽ��ʼλ��
	int conditionExprBottom;	//�������ʽ����λ��
	SoWhile(int top, int bottom, int cETop, int cEBottom);
};

class SoIf: public Block {/*if������*/
public:
	int judgeExprTop;			//�жϱ��ʽ��ʼλ��
	int judgeExprBottom;		//�жϱ��ʽ����λ��
	SoIf(int t, int b, int jETop, int jEBottom);
};

class SoElse: public Block {/*else������*/
public:
	SoElse(int t, int b);
};

class SoFunc : public Block {/*����������*/
public:
	string name;
	Tag retType;				//����ֵ����
	vector <Token*> paralist;	//�����б�
	SoFunc(string n, Tag r);
};


#endif // !MODESYNTEXANALYSIS_H_
#pragma once
