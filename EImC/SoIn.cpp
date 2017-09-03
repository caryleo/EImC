#include"SoIn.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"

extern vector<Token*>buffer;


void SoIn::judgeIdt(int m)
{
	Idt *p = (Idt*)buffer.at(m);
	/*��������*/
	Token qi(NUM,1,1);
	p->t=&qi;
	p->t->tag=NUM;
	if (p->t->tag == NUM)//����Ǹ�����
	{
		SoInt *q = (SoInt*)buffer.at(m);
		cin >> q->val;
	}
	else if (p->t->tag == RNUM)//����Ǹ�ʵ��
	{
		SoReal *q = (SoReal*)buffer.at(m);
		cin >> q->val;
	}
	else if (p->t->tag == STRING)//����Ǹ��ַ���
	{
		SoString *q = (SoString*)buffer.at(m);
		cin >> q->str;
	}
}

void SoIn::input(int top, int bottom)
{
	if (bottom - top == 2 && buffer[top + 1]->tag == IDT)//ֻ����һ������
	{
		judgeIdt(top + 1);
	}
	else if (bottom - top == 4 && buffer[top + 1]->tag == STRING&&buffer[top + 2]->tag == COMMA&&buffer[top + 3]->tag == IDT)//���һ���ַ���������һ������
	{
		SoString *q = (SoString*)buffer.at(top + 1);
		cout << q->str << endl;
		judgeIdt(top + 3);
	}
	else cout << "ERROR!!!" << endl;
}
