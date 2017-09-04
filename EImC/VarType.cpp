#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
// ���ڵ����� ��ֵ���õ�ʵ��(�ؼ���Ϊ���ں�)��û��д�� ���������� 50��  85 .118 ��
// ��ֵʽ�� ����﷨�Ƿ����﷨����  ��θ�ֵ�� ��Ҫ���õĹ��� 
extern vector<Token*>buffer;

VarType::VarType(int a, int b)
{
	top = a;
	bottom = b;
}

void VarType::input(int top,int bottom)  //���ҵ��� int/real/string ��ͷ �Էֺ�Ϊ������һ�λ� 
{
	
	switch (buffer[top]->tag)  //��ȡ��һ������ �ж��� int real string ;
		// int a;  int a=1��b=1 ; int a,b; �����м������
		//a=2 ��ֵ 
		// real a;
		//string a;
	{
	case KEY_INT:
	{
		int temp = top + 1;
		while (temp<=bottom&&buffer[temp]->tag!=SEMICO) // �жϵ������ֺ� ���ֺ�Ϊ����
		{
			if (buffer[temp]->tag == IDT)  //idt �Ǳ�ʶ�� ���� a
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = NUM;  // ��idt�����asstype ��ע������� ���ڵ�����
				temp++;
				continue;
			}
			if (buffer[temp]->tag== COMMA)  //��������
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //�������ں� ��������ֵ���ĵط� ���� int a=b+c;
			{
				int start = temp - 1;  //��ǰ��һ�� ��ʼ�ǵȺ���ߵı���
				temp++;
				while (buffer[temp]->tag != COMMA || buffer[temp]->tag != SEMICO) //����Ϊ�ֺŻ��߶��� ˵����ֵ������
				{
					temp++;
				}
				int end = temp-1;		// �����ֵ���Ľ���
				//���ø�ֵ��� ImpleAssign��start��end�� �ݶ����÷���
			}
		}

		//�ڷ��ű����½�һ����Ϊtempָ������ֵ� �����ִ��ȥ ������֮ǰ���ֵ�int����������
		//����

	}
	case KEY_REAL:
	{
		int temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // �жϵ������ֺ� ���ֺ�Ϊ����
		{
			if (buffer[temp]->tag == IDT)  //idt �Ǳ�ʶ�� ���� a
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = RNUM;  // ��idt�����asstype ��ע������� ���ڵ�����
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //��������
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //�������ں� ��������ֵ���ĵط� ���� real a=b+c;
			{
				int start = temp - 1;  //��ǰ��һ�� ��ʼ�ǵȺ���ߵı���
				temp++;
				while (buffer[temp]->tag != COMMA || buffer[temp]->tag != SEMICO) //����Ϊ�ֺŻ��߶��� ˵����ֵ������
				{
					temp++;
				}
				int end = temp - 1;		// �����ֵ���Ľ���
										//���ø�ֵ��� ��start��end�� �ݶ����÷���
			}
		}

		
	}
	case KEY_STRING:
	{
		int temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // �жϵ������ֺ� ���ֺ�Ϊ����
		{
			if (buffer[temp]->tag == IDT)  //idt �Ǳ�ʶ�� ���� a
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = STRING;  // ��idt�����asstype ��ע������� ���ڵ�����
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //��������
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //�������ں� ��������ֵ���ĵط� ���� srting a=
			{
				int start = temp - 1;  //��ǰ��һ�� ��ʼ�ǵȺ���ߵı���
				temp++;
				while (buffer[temp]->tag != COMMA || buffer[temp]->tag != SEMICO) //����Ϊ�ֺŻ��߶��� ˵����ֵ������
				{
					temp++;
				}
				int end = temp - 1;		// �����ֵ���Ľ���
										//���ø�ֵ��� ��start��end�� �ݶ����÷���
			}
		}

	}
	default:
		break;
	}
	
}
// bool VarType::match(int m, Tag a)
//{
//	Idt *p = (Idt*)buffer.at(m);
//	if (p->t->tag == a)
//		return true;
//	else
//		return false;
//}


