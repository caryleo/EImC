#ifndef MODETOKENANALYSIS_H_
#define MODETOKENANALYSIS_H_
#include<string>
#include<map>
#include<vector>
#include"EImC.h"
#include"ModeRead.h"
using namespace std;

class Idt :public Token/*��ʶ����*/
{
public:
	string name;
	Tag assType;
	Idt();
	Idt(string n, int l, int c);
	Token* t;
};

class SoInt :public Token/*int�ͳ�����*/
{
public:
	short val;
	SoInt();
	SoInt(short n, int l, int c);
};

class SoReal :public Token/*real�ͳ�����*/
{
public:
	float val;
	SoReal();
	SoReal(float n, int l, int c);
};

class SoString :public Token/*string�ͳ�����*/
{
public:
	string str;
	SoString();
	SoString(string s, int l, int c);
};

class Keywords/*�ؼ��ֹ�����*/
{
public:
	map<string, Tag> keywords;
	Keywords();
	Tag getTag(string name);
};

class ModeTokenAnalysis/*�������ģ�������*/
{
public:
	static void read(ModeRead& mRead);
	static Token * getToken(ModeRead & mRead, char & ch);
	static Token * getIdt(ModeRead & mRead, char & ch);
	static Token * getNum(ModeRead & mRead, char & ch);
	static Token * getString(ModeRead & mRead, char & ch);
};

class babababana{
public:
    void add(int pos);
    babababana();
    int cnt;
    int num[105];
};
babababana retPos,conPos,brkPos;

#endif // !MODETOKENANALYSIS_H_
#pragma once
