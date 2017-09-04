#include"stdafx.h"
#include"SoIn.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"

extern vector<Token*>buffer;


void SoIn::judgeIdt(Token *m)
{
    int len= buffer.size();
	ModeRead in;
	in.readMode();
	ModeTokenAnalysis::read(in);
	int len2=buffer.size();
	for (int i = 0; i < buffer.size(); i++) {
		cout << buffer[i]->tag << endl;
	}
	if(len2-len!=1)//只支持输入一个
        cout << "ERROR!!!" << endl;
    else
    {
        Idt *p = (Idt*)(m);
        /*测试用例
        Token qi(NUM,1,1);//in a;中a的类型假如是整型
        p->t=&qi;
        p->t->tag=NUM;*/
        if (p->t->tag == NUM)//如果是个整型
        {
            if(buffer[len]->tag==NUM)
            {
                SoInt *q = (SoInt*)(m);
                SoInt *s = (SoInt*)buffer.at(len);
                q->val=s->val;
                cout<<q->val<<endl;
            }
            else cout << "ERROR!!!" << endl;
        }
        else if (p->t->tag == RNUM)//如果是个实型
        {
            if(buffer[len]->tag==RNUM)
            {
                SoReal *q = (SoReal*)(m);
                SoReal *s = (SoReal*)buffer.at(len);
                q->val=s->val;
                cout<<q->val<<endl;
            }
            else cout << "ERROR!!!" << endl;
        }
        else if (p->t->tag == STRING)//如果是个字符串
        {
            if(buffer[len]->tag==STRING)
            {
                SoString *q = (SoString*)(m);
                SoString *s = (SoString*)buffer.at(len);
                q->str=s->str;
                cout<<q->str<<endl;
            }
            else cout << "ERROR!!!" << endl;
        }
    }

}

void SoIn::input(Token *top, Token *bottom)
{
	vector<*Token>::iterator it1=top;
	vector<*Token>::iterator it2=bottom;
	int m =it2-it1;
	if (bottom - top == 2 && (top + 1)->tag == IDT)//只输入一个变量
	{
		judgeIdt(top + 1);
	}
	else if (bottom - top == 4 && (top + 1)->tag == STRING&&(top + 2)->tag == COMMA&&(top + 3)->tag == IDT)//输出一个字符串和输入一个变量
	{
		SoString *q = (SoString*)(top + 1);
		cout << q->str << endl;
		judgeIdt(top + 3);
	}
	else cout << "ERROR!!!" << endl;
}
