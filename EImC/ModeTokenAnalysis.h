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
	Idt();
	Idt(string n);
	virtual string toString();
};

class SoInt :public Token/*int型常量类*/
{
public:
	short val;
	SoInt(short n);
	virtual string toString();
};

class SoReal :public Token/*real型常量类*/
{
public:
	float val;
	SoReal(float n);
	virtual string toString();
};

class SoString :public Token/*string型常量类*/
{
public:
	string str;
	SoString(string s);
	virtual string toString();
};

class Keywords/*关键字管理类*/
{
public:
	map<string, Tag> keywords;
	Keywords();
	Tag getTag(string name);
};

class ModeTokenAnalysis
{
public:
	static Token* getToken(ModeRead mRead);
	static void read(ModeRead mRead);
};

#endif // !MODETOKENANALYSIS_H_
#pragma once
