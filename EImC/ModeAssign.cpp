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
		// �����������ʽ �������� ������ε���
		// �������ʽ�Ŀ�ʼ�ͽ���ʱ expr_top & expr_bottom
		// ���������ʽ��ֵ��ֵ����ʽ�ұߵ� buffer[idt]
		// question�� ���ʽ�ķ���ֵ �Լ� ����
		Token*head = buffer[expr_top];
		Token*tail = buffer[expr_bottom];
		ExprIR a;
		Idt result = a.exprEnter(head, tail);
		temp = expr_top;
		while (temp>=top)
		{
			if (buffer[temp]->tag == IDT)
			{
				switch (result.assType)
				{
				case KEY_INT:
				{
					// ��ʽ�������Ͳ�һ����ô���� ��α���
					int num = a.getIntVal(result);//ͨ�����ʽ����ģ����� Ҫ������ֵ
					Token* token = buffer[idt];
					Idt* idt = (Idt*)token; //����ֵ�Ķ���
					if (idt->assType == KEY_INT)
					{
						SoInt*hu = (SoInt*)idt->t;
						hu->val = num;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				case KEY_REAL:
				{
					float num = a.getRealVal(result);
					Token* token = buffer[idt];
					Idt* idt = (Idt*)token; //����ֵ�Ķ���
					if (idt->assType == KEY_REAL)
					{
						SoReal*hu = (SoReal*)idt->t;
						hu->val = num;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				case KEY_STRING:
				{

					string strs = a.getStrVal(result);
					Token* token = buffer[idt];
					Idt* idt = (Idt*)token; //����ֵ�Ķ���
					if (idt->tag == KEY_STRING)
					{
						SoString*hu = (SoString*)idt->t;
						hu->str = strs;

					}
					else {
						cout << "Error!!!(expression assignment matching error)" << endl;
					}
				}
				default:
					break;
				}
			}
			temp--;
		}
	}
	//// �����������ʽ �������� ������ε���
	//// �������ʽ�Ŀ�ʼ�ͽ���ʱ expr_top & expr_bottom
	//// ���������ʽ��ֵ��ֵ����ʽ�ұߵ� buffer[idt]
	//// question�� ���ʽ�ķ���ֵ �Լ� ����
	//Token*head = buffer[expr_top];
	//Token*tail = buffer[expr_bottom];
	//ExprIR a;
	//Idt result=a.exprEnter(head, tail);
	//switch (result.assType)
	//{
	//case KEY_INT:
	//{
	//	// ��ʽ�������Ͳ�һ����ô���� ��α���
	//	int num = a.getIntVal(result);//ͨ�����ʽ����ģ����� Ҫ������ֵ
	//	Token* token = buffer[idt];
	//	Idt* idt = (Idt*)token; //����ֵ�Ķ���
	//	if (idt->assType==KEY_INT)
	//	{
	//		SoInt*hu = (SoInt*)idt->t;
	//		hu->val = num;

	//	}
	//}
	//case KEY_REAL:
	//{
	//	float num = a.getRealVal(result);
	//	Token* token = buffer[idt];
	//	Idt* idt = (Idt*)token; //����ֵ�Ķ���
	//	if (idt->assType == KEY_REAL)
	//	{
	//		SoReal*hu = (SoReal*)idt->t;
	//		hu->val = num;

	//	}
	//}
	//case KEY_STRING:
	//{

	//	string strs= a.getStrVal(result);
	//	Token* token = buffer[idt];
	//	Idt* idt = (Idt*)token; //����ֵ�Ķ���
	//	if (idt->tag == KEY_STRING)
	//	{
	//		SoString*hu = (SoString*)idt->t;
	//		hu->str = strs;

	//	}
	//}
	//default:
	//	break;
	//}


}