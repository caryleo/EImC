#include "stdafx.h"
#include "EImC.h"
#include "SoOut.h"
#include "ModeTokenAnalysis.h"

extern vector<Token*>buffer;

bool SoOut::isValid(int top, int bottom)
{
	if (bottom - top <= 1 || bottom - top > 4 || bottom - top == 3)//out��;֮��û��������֮��Ķ�������
		return 0;
	for (int i = top; i < bottom; i++)
	{
		if (buffer[i]->tag != COMMA || buffer[i]->tag != STRING || buffer[i]->tag != NUM || buffer[i]->tag != RNUM || buffer[i]->tag != IDT)//������ַǳ��������������߶��ŵ������Ϊ�д�
			return 0;
	}
	if (bottom - top == 2 && buffer[top + 1]->tag == COMMA)//���out��;֮��ֻ��һ������
		return 0;
	if (bottom - top == 4 && buffer[top + 2]->tag != COMMA || buffer[top + 1]->tag == COMMA || buffer[top + 3]->tag == COMMA)//ֻ���ڵڶ���λ���ǣ�
		return 0;
	else return 1;
}
void SoOut::judgeIdt(int m)
{
	Idt *p = (Idt*)buffer.at(m);
	if (p->t->tag == NUM)//����Ǹ�����
	{
		SoInt *q = (SoInt*)buffer.at(m);
		cout << q->val << endl;
	}
	else if (p->t->tag == RNUM)//����Ǹ�ʵ��
	{
		SoReal *q = (SoReal*)buffer.at(m);
		cout << q->val << endl;
	}
	else if (p->t->tag == STRING)//����Ǹ��ַ���
	{
		SoString *q = (SoString*)buffer.at(m);
		cout << q->str << endl;
	}
}

void SoOut::print(int top, int bottom)//top��buffer�����out��俪ʼ�ʵ�λ�ã�bottom��buffer�����out�������ʵ�λ��
{
	if (isValid(top, bottom) == 0)//����д�
		cout << "ERROR!!!" << endl;
	else
	{
		if (buffer[top + 2]->tag != COMMA)//û��','�����
		{

			if (buffer[top + 1]->tag == STRING)//ֻ����ַ��������
			{
				SoString *p = (SoString*)buffer.at(top + 1);
				cout << p->str << endl;
			}
			else if (buffer[top + 1]->tag == IDT)//ֻ�����ʶ����ֵ�����
			{
				judgeIdt(top + 1);
			}
		}
		else//��','�����
		{
			if (buffer[top + 1]->tag == STRING)//��һ��������ַ��������
			{
				SoString *p = (SoString*)buffer.at(top + 1);
				cout << p->str << endl;
				if (buffer[top + 3]->tag == STRING)//�ڶ���������ַ��������
				{
					SoString *p = (SoString*)buffer.at(top + 1);
					cout << p->str << endl;
				}
				else if (buffer[top + 3]->tag == IDT)//�ڶ����������ʶ�������
				{
					judgeIdt(top + 3);
				}
			}
			else if (buffer[top + 1]->tag == IDT)//��һ���������ʶ�������
			{
				Idt *p = (Idt*)buffer.at(top + 1);
				if (p->t->tag == NUM)//����Ǹ�����
				{
					SoInt *s = (SoInt*)buffer.at(top + 1);
					for (int i = 0; i < s->val; i++)
					{
						if (buffer[top + 3]->tag == STRING)//�ڶ���������ַ��������
						{
							SoString *m = (SoString*)buffer.at(top + 3);
							cout << m->str << endl;
						}
						else if (buffer[top + 3]->tag == IDT)//�ڶ����������ʶ����ֵ�����
						{
							judgeIdt(top + 3);
						}
					}
				}
				else cout << "ERROR!!!" << endl;//�����������Ҳ�����ַ����򱨴�
			}
			else if (buffer[top + 1]->tag == NUM)//��һ����������������
			{
				SoInt *p = (SoInt*)buffer.at(top + 1);
				for (int i = 0; i < p->val; i++)
				{
					if (buffer[top + 3]->tag == STRING)//�ڶ���������ַ��������
					{
						SoString *m = (SoString*)buffer.at(top + 3);
						cout << m->str << endl;
					}
					else if (buffer[top + 3]->tag == IDT)//�ڶ����������ʶ����ֵ�����
					{
						judgeIdt(top + 3);
					}
				}
			}
		}
	}
}