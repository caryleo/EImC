#include"EImC.h"
using namespace std;
extern vector<Token*>buffer;



class SoOut{
public:
    SoOut(int top,int bottom);
    bool isValid(int top,int bottom);
};
bool SoInt::isValid(int top,int bottom)
{
    if(bottom-top<=1||bottom-top>4||bottom-top==3)//out与;之间没东西或者之间的东西多了
        return 0;
    for(int i=top;i<bottom;i++)
    {
        if(buffer[i].tag!=COMMA||buffer[i].tag!=STRING||buffer[i].tag!=NUM||buffer[i].tag!=RNUM||buffer[i].tag!=IDT)//如果出现非常量、变量名或者逗号的情况视为有错
            return 0;

    }
    if(bottom-top==2&&buffer[top+1].tag==COMMA)//如果out与;之间只有一个逗号
        return 0;
    if(bottom-top==4&&buffer[top+2].tag!=COMMA||buffer[top+1].tag==COMMA||buffer[top+3].tag==COMMA)//只能在第二个位置是，
        return 0;
    else return 1;
}
SoOut::SoOut(int top,int bottom)//top是buffer数组的out语句开始词的位置，bottom是buffer数组的out语句结束词的位置
{
    if(isValid(top,bottom)==0)//如果有错
        cout << "ERROR!!!" << endl;
    else
    {
        if(buffer[top+2].tag!=COMMA)//没有','的情况
        {

            if(buffer[top+1].tag==STRING)//只输出字符串的情况
            {
                SoString *p=(SoString*)buffer.at(top+1);
                cout<<p->str<<endl;
            }
            else if(buffer[top+1].tag==IDT)//只输出标识符的值的情况
            {
                Idt *p=(Idt*)buffer.at(top+1);
                if(p->t==NUM)//如果是个整型
                {
                    SoInt *q=(SoInt*)buffer.at(top+1);
                    cout<<q->val<<endl;
                }
                else if(p->t==RNUM)//如果是个实型
                {
                    SoReal *q=(SoReal*)buffer.at(top+1);
                    cout<<q->val<<endl;
                }
                else if(p->t==STRING)//如果是个字符串
                {
                    SoString *q=(SoString*)buffer.at(top+1);
                    cout<<q->str<<endl;
                }
            }
        }
        else//有','的情况
        {
            if(buffer[top+1].tag==STRING)//第一部分输出字符串的情况
            {
                SoString *p=(SoString*)buffer.at(top+1);
                cout<<p->str<<endl;
                if(buffer[top+3].tag==STRING)//第二部分输出字符串的情况
                    cout<<buffer[top+3];
                else if(buffer[top+3].tag==IDT)//第二部分输出标识符的情况
                {
                    Idt *m=(Idt*)buffer.at(top+3);
                    if(m->t==NUM)//如果是个整型
                    {
                        SoInt *q=(SoInt*)buffer.at(top+3);
                        cout<<q->val<<endl;
                    }
                    else if(m->t==RNUM)//如果是个实型
                    {
                        SoReal *q=(SoReal*)buffer.at(top+3);
                        cout<<q->val<<endl;
                    }
                    else if(m->t==STRING)//如果是个字符串
                    {
                        SoString *q=(SoString*)buffer.at(top+3);
                        cout<<q->str<<endl;
                    }
                }
            }
            else if(buffer[top+1].tag==IDT)//第一部分输出标识符的情况
            {
                Idt *p=(Idt*)buffer.at(top+1);
                if(p->t==NUM)//如果是个整型
                {
                    SoInt *s=(SoInt*)buffer.at(top+1);
                    for(int i=0;i<s->val;i++)
                    {
                        if(buffer[top+3].tag==STRING)//第二部分输出字符串的情况
                        {
                            SoString *m=(SoString*)buffer.at(top+1);
                            cout<<m->str<<endl;
                        }
                        else if(buffer[top+3].tag==IDT)//第二部分输出标识符的值的情况
                        {
                            Idt *m=(Idt*)buffer.at(top+3);
                            if(m->t==NUM)//如果是个整型
                            {
                                SoInt *q=(SoInt*)buffer.at(top+3);
                                cout<<q->val<<endl;
                            }
                            else if(m->t==RNUM)//如果是个实型
                            {
                                SoReal *q=(SoReal*)buffer.at(top+3);
                                cout<<q->val<<endl;
                            }
                            else if(m->t==STRING)//如果是个字符串
                            {
                                SoString *q=(SoString*)buffer.at(top+3);
                                cout<<q->str<<endl;
                            }
                        }
                    }
                }
                else cout << "ERROR!!!" << endl;//如果不是整数也不是字符串则报错
            }
            else if(buffer[top+1].tag==NUM)//第一部分输出整数的情况
            {
                SoInt *p=(SoInt*)buffer.at(top+1);
                for(int i=0;i<p->val;i++)
                {
                    if(buffer[top+3].tag==STRING)//第二部分输出字符串的情况
                    {
                        SoString *m=(SoString*)buffer.at(top+1);
                        cout<<m->str<<endl;
                    }
                    else if(buffer[top+3].tag==IDT)//第二部分输出标识符的值的情况
                    {
                        Idt *m=(Idt*)buffer.at(top+3);
                        if(m->t==NUM)//如果是个整型
                        {
                            SoInt *q=(SoInt*)buffer.at(top+3);
                            cout<<q->val<<endl;
                        }
                        else if(m->t==RNUM)//如果是个实型
                        {
                            SoReal *q=(SoReal*)buffer.at(top+3);
                            cout<<q->val<<endl;
                        }
                        else if(m->t==STRING)//如果是个字符串
                        {
                            SoString *q=(SoString*)buffer.at(top+3);
                            cout<<q->str<<endl;
                        }
                    }
                }
            }
        }
    }
}
