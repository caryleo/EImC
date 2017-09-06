#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
#include"ModeExecute.h"
#include"Stack.h"
using namespace std;

extern Stack RunTime;
extern vector<Token*>buffer;
extern vector<Token*> ConstStore;

// ���⣺���ʽ������ε��� ������
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
	while (temp<=bottom)
	{
		if (buffer[temp]->tag == ASSIGN)
		{
			expr_top = temp + 1;
		}
		temp++;
	}
	temp = expr_top;
	while (temp<=bottom&&buffer[temp]->tag!=SEMICO)
	{
		temp++;
	}
	expr_bottom = temp - 1;
	if ((expr_bottom-expr_top)<1)
	{
		cout << "Error!!!(no expression)" << endl;
	}
	if ((expr_top - top) < 2)
	{
		cout << "Error!!!(no var)" << endl;
	}
	else
	{
		temp = expr_top;
		while (temp<=expr_bottom)
		{
			if (buffer[temp]->tag == IDT)
			{
				Idt* tem = (Idt*)buffer[temp]; //�����ʽ��ı�����ֵ ��ջ��ϵ��һ��  
				string q = tem->name;
				Idt *ret = RunTime.query(q);
				// int c=a+b; ��a �Ǳ� a ����Ҫ�ѱ��ʽ��� a ָ���assType �ĵ�
				// �ж�������� �½����� ��idt->t ��ϵ��һ��
				if (ret->assType == NUM)   
				{
					tem->assType = NUM;
					SoInt*intt = (SoInt*)ret->t;
					SoInt *a = new SoInt(intt->val, 0, 0);
					tem->t = a;
				}
				if (ret->assType == RNUM)
				{
					tem->assType = RNUM;
					SoReal*intt = (SoReal*)ret->t;
					SoReal *a = new SoReal(intt->val, 0, 0);
					tem->t = a;
				}
				if (ret->assType == STRING)
				{
					tem->assType = STRING;
					SoString*strr = (SoString*)ret->t;
					SoString*b = new SoString(strr->str, 0, 0);
					tem->t = b;
				}
			}
			temp++;
		}
		// �����������ʽ��ֵ �������� ������ε���
		// �������ʽ�Ŀ�ʼ�ͽ���ʱ expr_top & expr_bottom
		// ���������ʽ��ֵ��ֵ����ʽ�ұߵ� buffer[idt]

		// result Ϊ���ʽ����õ��ķ���ֵ ����Ϊtoken
		// ���ݷ���ֵ������ ���������


		ExprIR a;
		Token*result=a.calculate_expr(expr_top, expr_bottom);
		temp = expr_top;
		// �������ȵ����
		switch (result->tag)
		{
		case NUM:
		{
			SoInt*number = (SoInt*)result;
			int num = number->val;
			temp = expr_top-1;
			while (temp>=top)
			{
				if (buffer[temp]->tag==IDT)
				{
					// a=b ,b->a
					Idt* idt = (Idt*)buffer[temp];
					//	�޸ı�����ֵ
					string q = idt->name;
					Idt *value = RunTime.query(q);

					if (value->assType == NUM)
					{
						SoInt * p = (SoInt *)value->t;
						SoInt* intt = new SoInt(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else if (value->assType==RNUM)
					{
						SoReal * p = (SoReal *)value->t;
						SoReal* intt = new SoReal(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				temp--;
			}
		}
		case RNUM:
		{
			SoReal*number = (SoReal*)result;

			float num = number->val;//ͨ�����ʽ����ģ����� Ҫ������ֵ
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	�޸ı�����ֵ
					string q = idt->name;
					Idt *value = RunTime.query(q);

					if (value->assType == RNUM)
					{
						SoReal * p = (SoReal *)value->t;
						SoReal* intt = new SoReal(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				temp--;
			}
		}
		case STRING:
		{
			SoString*strings = (SoString*)result;
			string numm = strings->str;//ͨ�����ʽ����ģ����� Ҫ������ֵ
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	�޸ı�����ֵ
					string q = idt->name;
					Idt *value = RunTime.query(q);
					if (value->assType == STRING)
					{
						SoString * p = (SoString *)value->t;
						SoString* intt = new SoString(numm, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				temp--;
			}
		}

		default:
			break;
		}

	//// �����������ʽ �������� ������ε���
	//// �������ʽ�Ŀ�ʼ�ͽ���ʱ expr_top & expr_bottom
	//// ���������ʽ��ֵ��ֵ����ʽ�ұߵ� buffer[idt]
	//// question�� ���ʽ�ķ���ֵ �Լ� ����

}