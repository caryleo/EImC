#include "stdafx.h"
#include"SoIn.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"Stack.h"
#include "ModeErrorReport.h"
extern Stack RunTime;
extern vector<Token*>buffer;
extern vector<Token*>ConstStore;

void SoIn::judgeIdt(int m)
{
	int len = buffer.size();
	ModeRead in;
	in.readMode();
	ModeTokenAnalysis::read(in);
	int len2 = buffer.size();
	/*for (int i = 0; i < buffer.size(); i++) {
		cout << buffer[i]->tag << endl;
	}*/
	if (len2 - len != 1) {//ֻ֧������һ��
		ModeErrorReport mER(750, buffer[m]->line, buffer[m]->col);
		mER.report();
	}
	else
	{
		Idt *a = (Idt*)buffer.at(m);
		Idt *p=RunTime.query(a->name);
		if (p == NULL)//�������֮ǰδ������
		{
			a->assType = NUM;
			a->t = NULL;
			RunTime.push(a);
			p = a;
			if (buffer[len]->tag == NUM)
			{
				SoInt *s = (SoInt*)buffer.at(len);
				ConstStore.push_back(s);
				p->t = s;
				//cout << p->val << endl;
			}
			else
			{
				ModeErrorReport mER(751, buffer[m]->line, buffer[m]->col);
				mER.report();
			}
		}
		if (p->assType== NUM)//����Ǹ�����
		{
			if (buffer[len]->tag == NUM)
			{
				SoInt *s = (SoInt*)buffer.at(len);
				ConstStore.push_back(s);
				p->t = s;
				//cout << p->val << endl;
			}
			else {
				ModeErrorReport mER(751, buffer[m]->line, buffer[m]->col);
				mER.report();
			}
		}
		else if (p->assType == RNUM)//����Ǹ�ʵ��
		{
			if (buffer[len]->tag == RNUM)
			{
				SoReal *s = (SoReal*)buffer.at(len);
				ConstStore.push_back(s);
				p->t = s;
				//cout << q->val << endl;
			}
			else if (buffer[len]->tag == NUM)
			{
				SoInt *s = (SoInt*)buffer.at(len);
				float tmp = s->val;
				SoReal * tmpr = new SoReal(tmp, 0, 0);
				ConstStore.push_back(tmpr);
				p->t = tmpr;
				//cout << q->val << endl;
			}
			else {
				ModeErrorReport mER(751, buffer[m]->line, buffer[m]->col);
				mER.report();
			}
		}
		else if (p->assType == STRING)//����Ǹ��ַ���
		{
			if (buffer[len]->tag == STRING)
			{
				SoString *s = (SoString*)buffer.at(len);
				ConstStore.push_back(s);
				p->t = s;
			}
			else {
				ModeErrorReport mER(751, buffer[m]->line, buffer[m]->col);
				mER.report();
			}
		}
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
	else {
		ModeErrorReport mER(752, buffer[bottom]->line, buffer[bottom]->col);
		mER.report();
	}
}
