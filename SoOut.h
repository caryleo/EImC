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
    if(bottom-top<=1||bottom-top>4||bottom-top==3)//out��;֮��û��������֮��Ķ�������
        return 0;
    for(int i=top;i<bottom;i++)
    {
        if(buffer[i].tag!=COMMA||buffer[i].tag!=STRING||buffer[i].tag!=NUM||buffer[i].tag!=RNUM||buffer[i].tag!=IDT)//������ַǳ��������������߶��ŵ������Ϊ�д�
            return 0;

    }
    if(bottom-top==2&&buffer[top+1].tag==COMMA)//���out��;֮��ֻ��һ������
        return 0;
    if(bottom-top==4&&buffer[top+2].tag!=COMMA||buffer[top+1].tag==COMMA||buffer[top+3].tag==COMMA)//ֻ���ڵڶ���λ���ǣ�
        return 0;
    else return 1;
}
SoOut::SoOut(int top,int bottom)//top��buffer�����out��俪ʼ�ʵ�λ�ã�bottom��buffer�����out�������ʵ�λ��
{
    if(isValid(top,bottom)==0)//����д�
        cout << "ERROR!!!" << endl;
    else
    {
        if(buffer[top+2].tag!=COMMA)//û��','�����
        {

            if(buffer[top+1].tag==STRING)//ֻ����ַ��������
            {
                SoString *p=(SoString*)buffer.at(top+1);
                cout<<p->str<<endl;
            }
            else if(buffer[top+1].tag==IDT)//ֻ�����ʶ����ֵ�����
            {
                Idt *p=(Idt*)buffer.at(top+1);
                if(p->t==NUM)//����Ǹ�����
                {
                    SoInt *q=(SoInt*)buffer.at(top+1);
                    cout<<q->val<<endl;
                }
                else if(p->t==RNUM)//����Ǹ�ʵ��
                {
                    SoReal *q=(SoReal*)buffer.at(top+1);
                    cout<<q->val<<endl;
                }
                else if(p->t==STRING)//����Ǹ��ַ���
                {
                    SoString *q=(SoString*)buffer.at(top+1);
                    cout<<q->str<<endl;
                }
            }
        }
        else//��','�����
        {
            if(buffer[top+1].tag==STRING)//��һ��������ַ��������
            {
                SoString *p=(SoString*)buffer.at(top+1);
                cout<<p->str<<endl;
                if(buffer[top+3].tag==STRING)//�ڶ���������ַ��������
                    cout<<buffer[top+3];
                else if(buffer[top+3].tag==IDT)//�ڶ����������ʶ�������
                {
                    Idt *m=(Idt*)buffer.at(top+3);
                    if(m->t==NUM)//����Ǹ�����
                    {
                        SoInt *q=(SoInt*)buffer.at(top+3);
                        cout<<q->val<<endl;
                    }
                    else if(m->t==RNUM)//����Ǹ�ʵ��
                    {
                        SoReal *q=(SoReal*)buffer.at(top+3);
                        cout<<q->val<<endl;
                    }
                    else if(m->t==STRING)//����Ǹ��ַ���
                    {
                        SoString *q=(SoString*)buffer.at(top+3);
                        cout<<q->str<<endl;
                    }
                }
            }
            else if(buffer[top+1].tag==IDT)//��һ���������ʶ�������
            {
                Idt *p=(Idt*)buffer.at(top+1);
                if(p->t==NUM)//����Ǹ�����
                {
                    SoInt *s=(SoInt*)buffer.at(top+1);
                    for(int i=0;i<s->val;i++)
                    {
                        if(buffer[top+3].tag==STRING)//�ڶ���������ַ��������
                        {
                            SoString *m=(SoString*)buffer.at(top+1);
                            cout<<m->str<<endl;
                        }
                        else if(buffer[top+3].tag==IDT)//�ڶ����������ʶ����ֵ�����
                        {
                            Idt *m=(Idt*)buffer.at(top+3);
                            if(m->t==NUM)//����Ǹ�����
                            {
                                SoInt *q=(SoInt*)buffer.at(top+3);
                                cout<<q->val<<endl;
                            }
                            else if(m->t==RNUM)//����Ǹ�ʵ��
                            {
                                SoReal *q=(SoReal*)buffer.at(top+3);
                                cout<<q->val<<endl;
                            }
                            else if(m->t==STRING)//����Ǹ��ַ���
                            {
                                SoString *q=(SoString*)buffer.at(top+3);
                                cout<<q->str<<endl;
                            }
                        }
                    }
                }
                else cout << "ERROR!!!" << endl;//�����������Ҳ�����ַ����򱨴�
            }
            else if(buffer[top+1].tag==NUM)//��һ����������������
            {
                SoInt *p=(SoInt*)buffer.at(top+1);
                for(int i=0;i<p->val;i++)
                {
                    if(buffer[top+3].tag==STRING)//�ڶ���������ַ��������
                    {
                        SoString *m=(SoString*)buffer.at(top+1);
                        cout<<m->str<<endl;
                    }
                    else if(buffer[top+3].tag==IDT)//�ڶ����������ʶ����ֵ�����
                    {
                        Idt *m=(Idt*)buffer.at(top+3);
                        if(m->t==NUM)//����Ǹ�����
                        {
                            SoInt *q=(SoInt*)buffer.at(top+3);
                            cout<<q->val<<endl;
                        }
                        else if(m->t==RNUM)//����Ǹ�ʵ��
                        {
                            SoReal *q=(SoReal*)buffer.at(top+3);
                            cout<<q->val<<endl;
                        }
                        else if(m->t==STRING)//����Ǹ��ַ���
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
