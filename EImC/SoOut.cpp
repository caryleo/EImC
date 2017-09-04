#include"stdafx.h"
#include "EImC.h"
#include "SoOut.h"
#include "ModeTokenAnalysis.h"

extern vector<Token*>buffer;

bool SoOut::isValid(Token *top, Token *bottom)
{
	if (bottom - top <= 1 || bottom - top > 4 || bottom - top == 3)//out��;֮��û��������֮��Ķ�������
		return 0;
	for (Token *i = top+1; i < bottom; i++)
	{
		if (!(i->tag == COMMA || i->tag == STRING || i->tag == NUM || i->tag == RNUM || i->tag == IDT))//������ַǳ��������������߶��ŵ������Ϊ�д�
			return 0;
	}
	if (bottom - top == 2 && (top+1)->tag == COMMA)//���out��;֮��ֻ��һ������
		return 0;
	if (bottom - top == 4 && (top+2)->tag != COMMA || (top + 1)->tag == COMMA || (top + 3)->tag == COMMA)//ֻ���ڵڶ���λ���ǣ�
		return 0;
	else return 1;
}
void SoOut::judgeIdt(Token *m)
{
	Idt *p = (Idt*)m;
	/*��������
	Token qi(NUM,1,1);
	p->t=&qi;
	p->t->tag=NUM;*/
	if (p->t->tag == NUM)//����Ǹ�����
	{
		SoInt *q = (SoInt*)m;
		/*��������
		q->val=3;*/
		cout << q->val << endl;
	}
	else if (p->t->tag == RNUM)//����Ǹ�ʵ��
	{
		SoReal *q = (SoReal*)m;
		cout << q->val << endl;
	}
	else if (p->t->tag == STRING)//����Ǹ��ַ���
	{
		SoString *q = (SoString*)m;
		cout << q->str << endl;
	}
}

void SoOut::print(Token *top, Token *bottom)//top��buffer�����out��俪ʼ�ʵ�λ�ã�bottom��buffer�����out�������ʵ�λ��
{
	if (isValid(top, bottom) == 0)//����д�
		cout << "ERROR!!!" << endl;
	else
	{
		if ((top + 2)->tag != COMMA)//û��','�����
		{

			if ((top + 1)->tag == STRING)//ֻ����ַ��������
			{
				SoString *p = (SoString*)(top + 1);
				cout << p->str << endl;
			}
			else if ((top + 1)->tag == IDT)//ֻ�����ʶ����ֵ�����
			{
				judgeIdt(top + 1);
			}
		}
		else//��','�����
		{
			if ((top + 1)->tag == STRING)//��һ��������ַ��������
			{
				SoString *p = (SoString*)(top + 1);
				cout << p->str << endl;
				if ((top + 3)->tag == STRING)//�ڶ���������ַ��������
				{
					SoString *p = (SoString*)(top + 3);
					cout << p->str << endl;
				}
				else if ((top + 3)->tag == IDT)//�ڶ����������ʶ�������
				{
					judgeIdt(top + 3);
				}
			}
			else if ((top + 1)->tag == IDT)//��һ���������ʶ�������
			{
				Idt *p = (Idt*)(top + 1);
				/*��������
                Token qi(NUM,1,1);
                p->t=&qi;
                p->t->tag=NUM;*/
				if (p->t->tag == NUM)//����Ǹ�����
				{
					SoInt *s = (SoInt*)(top + 1);
					/*��������
                    s->val=3;*/
					for (int i = 0; i < s->val; i++)
					{
						if ((top + 3)->tag == STRING)//�ڶ���������ַ��������
						{
							SoString *m = (SoString*)(top + 3);
							cout << m->str << endl;
						}
						else if ((top + 3)->tag == IDT)//�ڶ����������ʶ����ֵ�����
						{
							judgeIdt(top + 3);
						}
					}
				}
				else cout << "ERROR!!!" << endl;//�����������Ҳ�����ַ����򱨴�
			}
			else if ((top + 1)->tag == NUM)//��һ����������������
			{
				SoInt *p = (SoInt*)(top + 1);
				for (int i = 0; i < p->val; i++)
				{
					if ((top + 3)->tag == STRING)//�ڶ���������ַ��������
					{
						SoString *m = (SoString*)(top + 3);
						cout << m->str << endl;
					}
					else if ((top + 3)->tag == IDT)//�ڶ����������ʶ����ֵ�����
					{
						judgeIdt(top + 3);
					}
				}
			}
		}
	}
}
