#include"stdafx.h"
#include "EImC.h"
#include "SoOut.h"
#include "ModeTokenAnalysis.h"

extern vector<Token*>buffer;

bool SoOut::isValid(Token *top, Token *bottom)
{
	if (bottom - top <= 1 || bottom - top > 4 || bottom - top == 3)//out与;之间没东西或者之间的东西多了
		return 0;
	for (Token *i = top+1; i < bottom; i++)
	{
		if (!(i->tag == COMMA || i->tag == STRING || i->tag == NUM || i->tag == RNUM || i->tag == IDT))//如果出现非常量、变量名或者逗号的情况视为有错
			return 0;
	}
	if (bottom - top == 2 && (top+1)->tag == COMMA)//如果out与;之间只有一个逗号
		return 0;
	if (bottom - top == 4 && (top+2)->tag != COMMA || (top + 1)->tag == COMMA || (top + 3)->tag == COMMA)//只能在第二个位置是，
		return 0;
	else return 1;
}
void SoOut::judgeIdt(Token *m)
{
	Idt *p = (Idt*)m;
	/*测试用例
	Token qi(NUM,1,1);
	p->t=&qi;
	p->t->tag=NUM;*/
	if (p->t->tag == NUM)//如果是个整型
	{
		SoInt *q = (SoInt*)m;
		/*测试用例
		q->val=3;*/
		cout << q->val << endl;
	}
	else if (p->t->tag == RNUM)//如果是个实型
	{
		SoReal *q = (SoReal*)m;
		cout << q->val << endl;
	}
	else if (p->t->tag == STRING)//如果是个字符串
	{
		SoString *q = (SoString*)m;
		cout << q->str << endl;
	}
}

void SoOut::print(Token *top, Token *bottom)//top是buffer数组的out语句开始词的位置，bottom是buffer数组的out语句结束词的位置
{
	if (isValid(top, bottom) == 0)//如果有错
		cout << "ERROR!!!" << endl;
	else
	{
		if ((top + 2)->tag != COMMA)//没有','的情况
		{

			if ((top + 1)->tag == STRING)//只输出字符串的情况
			{
				SoString *p = (SoString*)(top + 1);
				cout << p->str << endl;
			}
			else if ((top + 1)->tag == IDT)//只输出标识符的值的情况
			{
				judgeIdt(top + 1);
			}
		}
		else//有','的情况
		{
			if ((top + 1)->tag == STRING)//第一部分输出字符串的情况
			{
				SoString *p = (SoString*)(top + 1);
				cout << p->str << endl;
				if ((top + 3)->tag == STRING)//第二部分输出字符串的情况
				{
					SoString *p = (SoString*)(top + 3);
					cout << p->str << endl;
				}
				else if ((top + 3)->tag == IDT)//第二部分输出标识符的情况
				{
					judgeIdt(top + 3);
				}
			}
			else if ((top + 1)->tag == IDT)//第一部分输出标识符的情况
			{
				Idt *p = (Idt*)(top + 1);
				/*测试用例
                Token qi(NUM,1,1);
                p->t=&qi;
                p->t->tag=NUM;*/
				if (p->t->tag == NUM)//如果是个整型
				{
					SoInt *s = (SoInt*)(top + 1);
					/*测试用例
                    s->val=3;*/
					for (int i = 0; i < s->val; i++)
					{
						if ((top + 3)->tag == STRING)//第二部分输出字符串的情况
						{
							SoString *m = (SoString*)(top + 3);
							cout << m->str << endl;
						}
						else if ((top + 3)->tag == IDT)//第二部分输出标识符的值的情况
						{
							judgeIdt(top + 3);
						}
					}
				}
				else cout << "ERROR!!!" << endl;//如果不是整数也不是字符串则报错
			}
			else if ((top + 1)->tag == NUM)//第一部分输出整数的情况
			{
				SoInt *p = (SoInt*)(top + 1);
				for (int i = 0; i < p->val; i++)
				{
					if ((top + 3)->tag == STRING)//第二部分输出字符串的情况
					{
						SoString *m = (SoString*)(top + 3);
						cout << m->str << endl;
					}
					else if ((top + 3)->tag == IDT)//第二部分输出标识符的值的情况
					{
						judgeIdt(top + 3);
					}
				}
			}
		}
	}
}
