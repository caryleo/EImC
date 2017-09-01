#ifndef EIMC_H_
#define RIMC_H_
#include<iostream>
#include<vector>
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
	Token();
	Token(Tag t);
	string tooString();
};

#endif // !1
#pragma once