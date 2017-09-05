#ifndef EIMC_H_
#define EIMC_H_
#include<iostream>
#include<vector>
using namespace std;

enum Tag {
	ERR,									//�����쳣
	END,									//�ļ��������
	IDT,									//��ʶ��
	TYPE,KEY_INT, KEY_REAL, KEY_STRING,		//�������͹ؼ��֣�int��real��string
	NUM, RNUM, STRING, CALL,				//���ݳ���
	AND, OR, NOT,							//�߼������
	ADD, SUB, MUL, DIV, MOD,				//���������
	GT, GE, LT, LE, EQU, NEQU,				//�Ƚ������
	LPAR, RPAR,								//С����()
	LBRACK, RBRACK,							//������[]
	LBRACE, RBRACE,							//������{}
	COMMA, SEMICO, DOLLA, HASH,				//������ţ����ţ��ֺţ���Ԫ�ţ�����
	ASSIGN,									//��ֵ����
	KEY_IF, KEY_ELSE, KEY_WHILE,			//if��else��while
	KEY_BRK, KEY_RET, KEY_CON,				//break��return��continue
	KEY_IN, KEY_OUT,						//in ,out
	FUNC, WHILE, IF, ELSE,					//���� ѭ�� if-else
	EXPR, STATE, PRT						//���ʽ����䣬ָ��
};

class Token/*���ػ���*/
{
public:
	Tag tag;                 //��������
	int line;                //�к�
	int col;                 //�к�
	Token();
	Token(Tag t, int l, int c);
};

#endif // !EIMC_H_


#pragma once