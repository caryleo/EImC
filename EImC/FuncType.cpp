#include"stdafx.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
#include"FuncType.h"
#include"Stack.h"
#include"ModeErrorReport.h"
#include"Expression.h"

extern Stack RunTime;

using namespace std;
extern vector<Token*> buffer;
extern vector<Token*> ConstStore;
FuncType::FuncType(int a, int b) {
	top = a;
	bottom = b;
}

Token* FuncType::Func()
{
	vector<Token*> paralist;	// ��Ų�����ֵ
	vector<Token*> paratype;	// ��� ����������
	int temp = top;
	while (temp <= bottom)		// ʶ�� ������ ֮���Ǹ������� 
	{
		if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
		{
			break;
		}
		temp++;
	}
	int funcname = temp; // ȡ������
	Idt *funame = (Idt*)buffer[funcname];
	string funcnamestring = funame->name;
	int para = temp + 2;
	/*if ((bottom - para) < 1)
	{
		cout << "Error!!!" << endl;
		ModeErrorReport error(451, buffer[temp]->line, buffer[temp]->col);
		error.report();
		return 0;
	}*/
	// para �����Ŀ�ʼ
	while (para <= bottom)  // �����б� fun��a+2,b,5)
	{
		// ������������� 
		// IDT NUM RNUM STRING 
		if (buffer[para]->tag != COMMA  && buffer[para + 1]->tag != COMMA ) // ������Ĳ��Ƕ��� ˵����һ�����ʽ
		{
			int exprstart = para;
			para++;
			while (buffer[para]->tag != COMMA&&para<bottom)  // f(1+2);
			{
				para++;
			}
			int exprend = para - 1;
			// �����������б��ʽ ��ȡ���
			ExprIR a;
			Token *ress=a.calculate_expr(exprstart, exprend);
			// ���ص� token 
			if (ress->tag == NUM)  // ��������Ϊ�����б���Ϊ���ֵ���� 
			{
				paralist.push_back(ress); // ��������token ����paralist ��
				Token *type = new Token(NUM, 0, 0); // ������������ ���� paratype ��
				paratype.push_back(type);
			}
			if (ress->tag == RNUM)
			{
				paralist.push_back(ress);
				Token *type = new Token(RNUM, 0, 0);
				paratype.push_back(type);
			}
			if (ress->tag == STRING)
			{
				paralist.push_back(ress);
				Token *type = new Token(STRING, 0, 0);
				paratype.push_back(type);
			}

		}
		if (buffer[para]->tag == IDT) // Ϊ��ʶ�� ����ʶ����Ӧ��ֵ ���뺯���Ĳ����б���
		{
			
			
			Idt* id = (Idt*)buffer[para];
			string q = id->name;
			Idt*value = RunTime.query(q); // ��ѯ �����ʶ�� 
			// value->assType ���������
			// ������� num rnum string
			// 451490053
			if (value->assType == NUM)
			{
				SoInt * p = (SoInt *)value->t;
				SoInt* intt = new SoInt(p->val, 0, 0);
				paralist.push_back(intt);
				Token *type = new Token(NUM, 0, 0);
				paratype.push_back(type);
			}
			if (value->assType == RNUM)
			{
				SoReal *p = (SoReal *)value->t;
				SoReal *innt = new SoReal(p->val, 0, 0);
				paralist.push_back(innt);
				Token *type = new Token(RNUM, 0, 0);
				paratype.push_back(type);
			}
			if (value->assType == STRING)
			{
				SoString *p = (SoString *)value->t;
				SoString *innt = new SoString(p->str, 0, 0);
				paralist.push_back(innt);
				Token *type = new Token(STRING, 0, 0);
				paratype.push_back(type);
			}
		}
		if (buffer[para]->tag == NUM)  // ��������Ϊ�����б���Ϊ���ֵ���� 
		{
			paralist.push_back(buffer[para]); // ��������token ����paralist ��
			Token *type = new Token(NUM, 0, 0); // ������������ ���� paratype ��
			paratype.push_back(type);
		}
		if (buffer[para]->tag == RNUM)
		{
			paralist.push_back(buffer[para]);
			Token *type = new Token(RNUM, 0, 0);
			paratype.push_back(type);
		}
		if (buffer[para]->tag == STRING)
		{
			paralist.push_back(buffer[para]);
			Token *type = new Token(STRING, 0, 0);
			paratype.push_back(type);
		}
		para++;
	}
	Caller ret(funcnamestring, paratype);  // ������Ϊ ret �� caller ��� һ������ �������� ������ �� �����Ĳ������͹��ɵ��б�
	// ���� ModeExecute ��
	Token* res = ModeExecute::caller(&ret, paralist);				//  ����
	return res;
}


