#ifndef MODETOKENANALYSIS_H_
#define MODETOKENANALYSIS_H_
#include<string>
#include<cstring>
#include<map>
#include<hash_map>
using namespace std;
enum Tag {
	ERR,                                                            //错误、异常
	END,                                                           //文件结束标记
	IDT,                                                             //标识符
	KEY_INT, KEY_REAL, KEY_STRING,               //数据类型关键字：int、real、string
	NUM, RNUM, STRING,                               //数据常量
	AND, OR, NOT,                                           //逻辑运算符
	ADD, SUB, MUL, DIV, MOD,                       //算数运算符
	GT, GE, LT, LE, EQU, NEQU,                         //比较运算符
	LPAR, RPAR,                                                //小括号()
	LBRACK, RBRACK,                                       //中括号[]
	LBRACE, RBRACE,                                        //大括号{}
	COMMA, SEMICO, DOLLA, HASH,              //特殊符号：逗号，分号，美元号，井号
	ASSIGN,                                                      //赋值符号
	KEY_IF, KEY_ELSE, KEY_WHILE,                     //if，else，while
	KEY_BRK, KEY_RET, KEY_CON                       //break，return，continue
};

class Token/*语素基类*/
{
public:
	Tag tag;
	Token(Tag t);
	virtual string toString();
	virtual ~Token();
};

class Idt :public Token/*标识符类*/
{
public:
	string name;
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
	map<string, Tag> keywords;
	Keywords();
	Tag getTag(string name);
};

class ModeTokenAnalysis
{
	static string getToken(ModeRead file);
};

#endif // !MODETOKENANALYSIS_H_
#pragma once
