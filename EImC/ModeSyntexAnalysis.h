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
	Block(Tag tag);
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
	SoIf(int top, int bottom, int jETop, int jEBottom);
};

class SoElse: public Block {/*else������*/
public:
	SoElse(int top, int bottom);
};

class SoFunc : public Block {/*����������*/
public:
	string name;
	Tag retType;
	vector <Token*> paralist;
	SoFunc(int top, int bottom, )
};


#endif // !MODESYNTEXANALYSIS_H_
#pragma once
