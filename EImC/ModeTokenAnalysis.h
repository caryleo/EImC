#ifndef MODETOKENANALYSIS_H_
#define MODETOKENANALYSIS_H_
#include<string>
#include<cstring>
#include<map>
#include<hash_map>
using namespace std;
enum Tag {
	ERR,                                                            //�����쳣
	END,                                                           //�ļ��������
	IDT,                                                             //��ʶ��
	KEY_INT, KEY_REAL, KEY_STRING,               //�������͹ؼ��֣�int��real��string
	NUM, RNUM, STRING,                               //���ݳ���
	AND, OR, NOT,                                           //�߼������
	ADD, SUB, MUL, DIV, MOD,                       //���������
	GT, GE, LT, LE, EQU, NEQU,                         //�Ƚ������
	LPAR, RPAR,                                                //С����()
	LBRACK, RBRACK,                                       //������[]
	LBRACE, RBRACE,                                        //������{}
	COMMA, SEMICO, DOLLA, HASH,              //������ţ����ţ��ֺţ���Ԫ�ţ�����
	ASSIGN,                                                      //��ֵ����
	KEY_IF, KEY_ELSE, KEY_WHILE,                     //if��else��while
	KEY_BRK, KEY_RET, KEY_CON                       //break��return��continue
};

class Token/*���ػ���*/
{
public:
	Tag tag;
	Token(Tag t);
	virtual string toString();
	virtual ~Token();
};

class Idt :public Token/*��ʶ����*/
{
public:
	string name;
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
	static string getToken(ModeRead file);
};

#endif // !MODETOKENANALYSIS_H_
#pragma once
