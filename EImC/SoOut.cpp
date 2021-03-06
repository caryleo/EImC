#include "stdafx.h"
#include "EImC.h"
#include "SoOut.h"
#include "ModeTokenAnalysis.h"
#include "ModeErrorReport.h"

extern vector<Token*>buffer;

bool SoOut::isValid(int top, int bottom)
{
    if (bottom - top <= 1 || bottom - top > 5 || bottom - top == 3)//out与;之间没东西或者之间的东西多了
		return 0;
	for (int i = top + 1; i < bottom; i++)//如果中间有变量未声明过
	{
	    Token *now=buffer[i];
	    if(now->tag==IDT)   //如果变量之前未声明过
        {
            if(((Idt*)now)->t==NULL)
                return 0;
        }
	}

	for (int i = top + 1; i < bottom; i++)
	{
		if (!(buffer[i]->tag == COMMA || buffer[i]->tag == STRING || buffer[i]->tag == NUM || buffer[i]->tag == RNUM || buffer[i]->tag == IDT|| buffer[i]->tag == ADD))//如果出现非常量、变量名、加号或者逗号的情况视为有错
			return 0;
	}
	if (bottom - top == 2 )//out a; out "string";
    {
        if(buffer[top + 1]->tag != STRING &&buffer[top + 1]->tag != IDT)
            return 0;
    }
	if (bottom - top == 4 )//out 5,5.5; out a,5.5; out a,a; out "string",a;
    {
        if(buffer[top + 1]->tag == COMMA||buffer[top+1]->tag==ADD||buffer[top+1]->tag==RNUM)
            return 0;
        if(buffer[top + 2]->tag != COMMA )
            return 0;
        if(buffer[top+3]->tag==COMMA||buffer[top+3]->tag==ADD)
            return 0;
    }
	if (bottom - top == 5 )
    {
        if(buffer[top+1]->tag!=ADD)
            return 0;
        if(buffer[top+2]->tag!=NUM)
            return 0;
        if(buffer[top+3]->tag!=COMMA)
            return 0;
        Token *tmp=buffer[top+4];
        if(tmp->tag==COMMA||tmp->tag==ADD)
            return 0;
    }
	return 1;
}
void SoOut::judgeIdt(int m)
{
	Idt *p = (Idt*)buffer.at(m);
	if (p->t->tag == NUM)//如果是个整型
	{
		SoInt *q = (SoInt*)p->t;
		cout << q->val;
	}
	else if (p->t->tag == RNUM)//如果是个实型
	{
		SoReal *q = (SoReal*)p->t;
		cout << q->val;
	}
	else if (p->t->tag == STRING)//如果是个字符串
	{
		SoString *q = (SoString*)p->t;
		cout << q->str;
	}
	else {
		ModeErrorReport mER(756, buffer[m]->line, buffer[m]->col);
		mER.report();
	}
}

void SoOut::print(int top, int bottom)//top是buffer数组的out语句开始词的位置，bottom是buffer数组的out语句结束词的位置
{
	if (isValid(top, bottom) == 0)//如果有错
	{
		ModeErrorReport mER(753, buffer[bottom]->line, buffer[bottom]->col);
		mER.report();
	}
	else if (bottom - top == 5)//有可能出现+5
	{
		SoInt *p = (SoInt*)buffer.at(top + 2);
		for (int i = 0; i < p->val; i++)
		{
			if (buffer[top + 4]->tag == STRING)//第二部分输出字符串的情况
			{
				SoString *m = (SoString*)buffer.at(top + 4);
				cout << m->str;
			}
			else if (buffer[top + 4]->tag == IDT)//第二部分输出标识符的值的情况
			{
				judgeIdt(top + 4);
			}
		}
	}
	else
	{
		if (buffer[top + 2]->tag != COMMA)//没有','的情况
		{

			if (buffer[top + 1]->tag == STRING)//只输出字符串的情况
			{
				SoString *p = (SoString*)buffer.at(top + 1);
				cout << p->str;
			}
			else if (buffer[top + 1]->tag == IDT)//只输出标识符的值的情况
			{
				judgeIdt(top + 1);
			}
		}
		else//有','的情况
		{
			if (buffer[top + 1]->tag == STRING)//第一部分输出字符串的情况
			{
				SoString *p = (SoString*)buffer.at(top + 1);
				cout << p->str;
				if (buffer[top + 3]->tag == STRING)//第二部分输出字符串的情况
				{
					SoString *p = (SoString*)buffer.at(top + 3);
					cout << p->str;
				}
				else if (buffer[top + 3]->tag == IDT)//第二部分输出标识符的情况
				{
					judgeIdt(top + 3);
				}
			}
			else if (buffer[top + 1]->tag == IDT)//第一部分输出标识符的情况
			{
				Idt *p = (Idt*)buffer.at(top + 1);
				if (p == NULL||p->t==NULL)//此变量之前未声明过
				{
					ModeErrorReport mER(756, buffer[bottom]->line, buffer[bottom]->col);
					mER.report();
				}
				else
				{
					if (p->t->tag == NUM)//如果是个整型
					{
						SoInt *s = (SoInt*)p->t;
						if (s->val > 0)
						{
							for (int i = 0; i < s->val; i++)
							{
								if (buffer[top + 3]->tag == STRING)//第二部分输出字符串的情况
								{
									SoString *m = (SoString*)buffer.at(top + 3);
									cout << m->str;
								}
								else if (buffer[top + 3]->tag == IDT)//第二部分输出标识符的值的情况
								{
									judgeIdt(top + 3);
								}
							}
						}
						else //如果不是正整数则报错
						{
							ModeErrorReport mER(754, buffer[bottom]->line, buffer[bottom]->col);
							mER.report();
						}
					}
					else //如果不是正整数则报错
					{
						ModeErrorReport mER(754, buffer[bottom]->line, buffer[bottom]->col);
						mER.report();
					}
				}

			}
			else if (buffer[top + 1]->tag == NUM)//第一部分输出整数的情况
			{
				SoInt *p = (SoInt*)buffer.at(top + 1);
				if (p->val > 0)
				{
					for (int i = 0; i < p->val; i++)
					{
						if (buffer[top + 3]->tag == STRING)//第二部分输出字符串的情况
						{
							SoString *m = (SoString*)buffer.at(top + 3);
							cout << m->str;
						}
						else if (buffer[top + 3]->tag == IDT)//第二部分输出标识符的值的情况
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
