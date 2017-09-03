#include"SoIn.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"

extern vector<Token*>buffer;


void SoIn::judgeIdt(int m)
{
	Idt *p = (Idt*)buffer.at(m);
	/*测试用例*/
	Token qi(NUM,1,1);
	p->t=&qi;
	p->t->tag=NUM;
	if (p->t->tag == NUM)//如果是个整型
	{
		SoInt *q = (SoInt*)buffer.at(m);
		cin >> q->val;
	}
	else if (p->t->tag == RNUM)//如果是个实型
	{
		SoReal *q = (SoReal*)buffer.at(m);
		cin >> q->val;
	}
	else if (p->t->tag == STRING)//如果是个字符串
	{
		SoString *q = (SoString*)buffer.at(m);
		cin >> q->str;
	}
}

void SoIn::input(int top, int bottom)
{
	if (bottom - top == 2 && buffer[top + 1]->tag == IDT)//只输入一个变量
	{
		judgeIdt(top + 1);
	}
	else if (bottom - top == 4 && buffer[top + 1]->tag == STRING&&buffer[top + 2]->tag == COMMA&&buffer[top + 3]->tag == IDT)//输出一个字符串和输入一个变量
	{
		SoString *q = (SoString*)buffer.at(top + 1);
		cout << q->str << endl;
		judgeIdt(top + 3);
	}
	else cout << "ERROR!!!" << endl;
}
