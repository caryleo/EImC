#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include "ModeTokenAnalysis.h"
#include"Stack.h"
#include "EImC.h"
#include<string>
#include<cmath>

class ExprIR
{
private:
	//��ǰɨ�赽���ʽ��λ��
	int pos;
	//���ʽͷָ���βָ��
	int start;
	int term;
	//������ջ
	Stack operator_s;
	//������ջ
	Stack operand_s;
public:
	//��ѯ����
	Tag getType(Token *);
	//��ѯIDT asstype
	Tag getAsstype(Token *);

	bool isAssign(Token *);
	//�ж��Ƿ�ΪIDT
	bool isIDT(Token *);

	//��ѯֵ
	string getStrVal(Token *);
	short getIntVal(Token *);
	float getRealVal(Token *);

	//�жϲ�����,�����ǲ��������ǲ�����
	bool isOperand(Token *);
	//��������ȼ�
	int oper_priority(Token *, Token *);
	int isp(Tag);
	int icp(Tag);

	//˫Ŀ�������㣺ADD,SUB,MUL,DIV,MOD
	Token * add_op(Token *, Token *);
	Token * sub_op(Token *, Token *);
	Token * mul_op(Token *, Token *);
	Token * div_op(Token *, Token *);
	Token * mod_op(Token *, Token *);


	//�ַ�������DOLLA, HASH
	//����$���ı�ԭ�ַ�����ֵ��#ɾ���ַ���ԭ�ַ������и���
	Token * connect_op(Token *, Token *);
	Token * delete_spec(Token *, Token *);
	Token * delete_tail(Token *);

	//��ϵ����:>,< ,>=,<=,==,<>
	//GT, GE, LT, LE, EQU, NEQU
	Token * is_greater(Token *, Token *);
	Token * not_less(Token *, Token *);
	Token * is_less(Token *, Token *);
	Token * not_greater(Token *, Token *);
	Token * is_equal(Token *, Token *);
	Token * not_equal(Token *, Token *);

	//�߼����㣺&&�� | ||�� | !��
	//AND, OR, NOT
	Token * and_lop(Token *, Token *);
	Token * or_lop(Token *, Token *);
	Token * not_lop(Token *);
	//vector<Token*>buffer
	//���ʽ�������
	Token * calculate_expr(int, int);
	//���Ҷ�Ӧ�����������ģ��
	int find_op(Token *);
	//��ɨ�赽�����ʱִ��
	int solve_op(Token *);
};

#endif // !EXPRESSION_H_
