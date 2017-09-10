#include "stdafx.h"
#include "EImC.h"
#include "SoOut.h"
#include "ModeTokenAnalysis.h"
#include "ModeErrorReport.h"

extern vector<Token*>buffer;

bool SoOut::isValid(int top, int bottom)
{
	for (int i = top; i < bottom; i++)//����м��б���δ������
	{
		Idt *p = (Idt*)buffer.at(i);
		if (p==NULL||p->t == NULL)//�������֮ǰδ������
			return 0;
	}
	if (bottom - top <= 1 || bottom - top > 4 || bottom - top == 3)//out��;֮��û��������֮��Ķ�������
		return 0;
	for (int i = top + 1; i < bottom; i++)
	{
		if (!(buffer[i]->tag == COMMA || buffer[i]->tag == STRING || buffer[i]->tag == NUM || buffer[i]->tag == RNUM || buffer[i]->tag == IDT))//������ַǳ��������������߶��ŵ������Ϊ�д�
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
		SoInt *q = (SoInt*)p->t;
		cout << q->val;
	}
	else if (p->t->tag == RNUM)//����Ǹ�ʵ��
	{
		SoReal *q = (SoReal*)p->t;
		cout << q->val;
	}
	else if (p->t->tag == STRING)//����Ǹ��ַ���
	{
		SoString *q = (SoString*)p->t;
		cout << q->str;
	}
	else {
		ModeErrorReport mER(756, buffer[m]->line, buffer[m]->col);
		mER.report();
	}
}

void SoOut::print(int top, int bottom)//top��buffer�����out��俪ʼ�ʵ�λ�ã�bottom��buffer�����out�������ʵ�λ��
{
	if (isValid(top, bottom) == 0)//����д�
	{
		ModeErrorReport mER(753, buffer[bottom]->line, buffer[bottom]->col);
		mER.report();
	}
	else
	{
		if (buffer[top + 2]->tag != COMMA)//û��','�����
		{

			if (buffer[top + 1]->tag == STRING)//ֻ����ַ��������
			{
				SoString *p = (SoString*)buffer.at(top + 1);
				cout << p->str;
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
				cout << p->str;
				if (buffer[top + 3]->tag == STRING)//�ڶ���������ַ��������
				{
					SoString *p = (SoString*)buffer.at(top + 3);
					cout << p->str;
				}
				else if (buffer[top + 3]->tag == IDT)//�ڶ����������ʶ�������
				{
					judgeIdt(top + 3);
				}
			}
			else if (buffer[top + 1]->tag == IDT)//��һ���������ʶ�������
			{
				Idt *p = (Idt*)buffer.at(top + 1);
				if (p == NULL||p->t==NULL)//�˱���֮ǰδ������
				{
					ModeErrorReport mER(756, buffer[bottom]->line, buffer[bottom]->col);
					mER.report();
				}
				else 
				{					
					if (p->t->tag == NUM)//����Ǹ�����
					{
						SoInt *s = (SoInt*)p->t;						
						if (s->val > 0)
						{
							for (int i = 0; i < s->val; i++)
							{
								if (buffer[top + 3]->tag == STRING)//�ڶ���������ַ��������
								{
									SoString *m = (SoString*)buffer.at(top + 3);
									cout << m->str;
								}
								else if (buffer[top + 3]->tag == IDT)//�ڶ����������ʶ����ֵ�����
								{
									judgeIdt(top + 3);
								}
							}
						}
						else //��������������򱨴�
						{
							ModeErrorReport mER(754, buffer[bottom]->line, buffer[bottom]->col);
							mER.report();
						}
					}
					else //��������������򱨴�
					{
						ModeErrorReport mER(754, buffer[bottom]->line, buffer[bottom]->col);
						mER.report();
					}
				}
				
			}
			else if (buffer[top + 1]->tag == NUM)//��һ����������������
			{
				SoInt *p = (SoInt*)buffer.at(top + 1);
				if (p->val > 0)
				{
					for (int i = 0; i < p->val; i++)
					{
						if (buffer[top + 3]->tag == STRING)//�ڶ���������ַ��������
						{
							SoString *m = (SoString*)buffer.at(top + 3);
							cout << m->str;
						}
						else if (buffer[top + 3]->tag == IDT)//�ڶ����������ʶ����ֵ�����
						{
							judgeIdt(top + 3);
						}
					}
				}
				else {
					ModeErrorReport mER(754, buffer[bottom]->line, buffer[bottom]->col);
					mER.report();
				}
			}
			else {
				ModeErrorReport mER(755, buffer[bottom]->line, buffer[bottom]->col);
				mER.report();
			}
		}
	}
}
