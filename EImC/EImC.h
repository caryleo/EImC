#ifndef EIMC_H_
#define EIMC_H_
#include<iostream>
#include<vector>
using namespace std;

enum Tag {
	ERR,									//错误、异常
	END,									//文件结束标记
	IDT,									//标识符
	TYPE,KEY_INT, KEY_REAL, KEY_STRING,		//数据类型关键字：int、real、string
	NUM, RNUM, STRING, CALL,				//数据常量
	AND, OR, NOT,							//逻辑运算符
	ADD, SUB, MUL, DIV, MOD,				//算数运算符
	GT, GE, LT, LE, EQU, NEQU,				//比较运算符
	LPAR, RPAR,								//小括号()
	LBRACK, RBRACK,							//中括号[]
	LBRACE, RBRACE,							//大括号{}
	COMMA, SEMICO, DOLLA, HASH,				//特殊符号：逗号，分号，美元号，井号
	ASSIGN,									//赋值符号
	KEY_IF, KEY_ELSE, KEY_WHILE,			//if，else，while
	KEY_BRK, KEY_RET, KEY_CON,				//break，return，continue
	KEY_IN, KEY_OUT,						//in ,out
	FUNC, WHILE, IF, ELSE,					//函数 循环 if-else
	EXPR, STATE, PRT						//表达式，语句，指针
};

class Token/*语素基类*/
{
public:
	Tag tag;                 //语素类型
	int line;                //行号
	int col;                 //列号
	Token();
	Token(Tag t, int l, int c);
};

#endif // !EIMC_H_


#pragma once