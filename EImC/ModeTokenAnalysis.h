#ifndef MODETOKENANALYSIS_H_
#define MODETOKENANALYSIS_H_
#include<string>
#include<map>
#include<vector>
#include"EImC.h"
#include"ModeRead.h"
using namespace std;

class Idt :public Token/*标识符类*/
{
public:
	string name;
	Tag assType;
	Idt();
	Idt(string n, int l, int c);
	Token* t;
};

class SoInt :public Token/*int型常量类*/
{
public:
	short val;
	SoInt();
	SoInt(short n, int l, int c);
};

class SoReal :public Token/*real型常量类*/
{
public:
	float val;
	SoReal();
	SoReal(float n, int l, int c);
};

class SoString :public Token/*string型常量类*/
{
public:
	string str;
	SoString();
	SoString(string s, int l, int c);
};

class Keywords/*关键字管理类*/
{
public:
	map<string, Tag> keywords;
	Keywords();
	Tag getTag(string name);
};

class ModeTokenAnalysis/*词义分析模块控制类*/
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
