#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
extern vector<Token*>buffer;

ModeAssign::ModeAssign(int a, int b)
{
	top = a;
	bottom = b;
}

void ModeAssign::Fuzhi()
{
	int temp = top;
	int idt;   //��������λ��
	int expr_top;
	int expr_bottom;
	while (temp <= bottom)
	{
		if (buffer[temp]->tag==ASSIGN)
		{
			 idt = temp - 1; // �Ⱥ�ǰ��ı���
		}
		else
		{
			temp++;
			continue;
		}
		expr_top = temp + 1;
		while (buffer[temp]->tag!=SEMICO)
		{
			temp++;
		}
		expr_bottom = temp - 1;
	}
	// �������ʽ�Ŀ�ʼ�ͽ���ʱ expr_top & expr_bottom
	// ���������ʽ��ֵ��ֵ����ʽ�ұߵ� buffer[idt]
	Token*head = buffer[expr_top];
	Token*tail = buffer[expr_bottom];
	ExprIR a;
	Idt result=a.exprEnter(head, tail);
	switch (result.assType)
	{
	case KEY_INT:
	{
		SoInt*num = (SoInt*)result.t;
		num->val = a.getIntVal(result);//Ҫ������ֵ
		Token* token = buffer[idt];
		Idt* idt = (Idt*)token; //����ֵ�Ķ���
		if (idt->tag==KEY_INT)
		{
			SoInt*hu = (SoInt*)token;
			hu->val = num->val;

		}
	}
	case KEY_REAL:
	{
		SoReal*num = (SoReal*)result.t;
		num->val = a.getRealVal;
		Token* token = buffer[idt];
		Idt* idt = (Idt*)token; //����ֵ�Ķ���
		if (idt->tag == KEY_REAL)
		{
			SoReal*hu = (SoReal*)token;
			hu->val = num->val;

		}
	}
	case KEY_STRING:
	{
		SoString*num = (SoString*)result.t;
		num->str = a.getStrVal;
		Token* token = buffer[idt];
		Idt* idt = (Idt*)token; //����ֵ�Ķ���
		if (idt->tag == KEY_STRING)
		{
			SoString*hu = (SoString*)token;
			hu->str = num->str;

		}
	}
	default:
		break;
	}


}