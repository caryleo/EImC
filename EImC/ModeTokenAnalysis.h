#ifndef MODETOKENANALYSIS_H_
#define MODETOKENANALYSIS_H_
#include<string>
#include<map>
#include<vector>
#include"ModeRead.h"
using namespace std;

class Idt :public Token/*��ʶ����*/
{
public:
	string name;
	Idt();
	Idt(string n);
	virtual string toString();
};

class SoInt :public Token/*int�ͳ�����*/
{
public:
	short val;
	SoInt(short n);
	virtual string toString();
};

class SoReal :public Token/*real�ͳ�����*/
{
public:
	float val;
	SoReal(float n);
	virtual string toString();
};

class SoString :public Token/*string�ͳ�����*/
{
public:
	string str;
	SoString(string s);
	virtual string toString();
};

class Keywords/*�ؼ��ֹ�����*/
{
	map<string, Tag> keywords;
	Keywords();
	Tag getTag(string name);
};

class ModeTokenAnalysis
{
public:
	static string getToken(ModeRead file);
	static void read();
};

#endif // !MODETOKENANALYSIS_H_
#pragma once