#include "stdafx.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
using namespace std;
extern vector<Token>buffer;

Keywords::Keywords()/*关键字列表初始化*/
{
	keywords.insert(pair<string, Tag>("int", KEY_INT));
	keywords.insert(pair<string, Tag>("real", KEY_REAL));
	keywords.insert(pair<string, Tag>("string",KEY_STRING));
	keywords.insert(pair<string, Tag>("if",KEY_IF));
	keywords.insert(pair<string, Tag>("else", KEY_ELSE));
	keywords.insert(pair<string, Tag>("while", KEY_WHILE));
	keywords.insert(pair<string, Tag>("break", KEY_BRK));
	keywords.insert(pair<string, Tag>("continue", KEY_CON));
	keywords.insert(pair<string, Tag>("return", KEY_RET));
}

Tag Keywords::getTag(string name)/*查询关键字*/
{
	return keywords.find(name) != keywords.end() ? keywords[name] : IDT;
}

Token::Token()
{
}

Token::Token(Tag t)
{
	tag = t;
}

string Token::tooString()
{
	return "This is a token ";
}

Idt::Idt()
{
}

Idt::Idt(string s)
{
	tag = IDT;
	name = s;
}

string Idt::toString() 
{
	return "This name is " + name;
}

SoInt::SoInt(short n)
{
	val = n;
}

string SoInt::toString()
{
	return "This value is " + val;
}

SoReal::SoReal(float f)
{
	tag = RNUM;
	val = f;
}

string SoReal::toString()
{
	cout << val;
	return " is the value.";
}

SoString::SoString(string s)
{
	tag = STRING;
	str = s;
}

string SoString::toString()
{
	return "This string is " + str;
}

void ModeTokenAnalysis::read()/*词义分析主控*/
{
	Token t(KEY_BRK);
	buffer.push_back(t);
}