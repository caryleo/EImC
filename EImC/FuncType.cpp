#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeExecute.h"
#include"ModeSyntexAnalysis.h"
#include"FuncType.h"
#include"Stack.h"

extern Stack RunTime;

using namespace std;
extern vector<Token*> buffer;
extern vector<Token*> ConstStore;
FuncType::FuncType(int a,int b){
	top = a;
	bottom = b;
}

void FuncType::Func()
{
	vector<Token*> paralist;  // ��Ų�����ֵ
	vector<Token*> paratype;	// ��� ����������
	int temp = top;
	while (temp<=bottom) // ʶ�� ������ ֮���Ǹ������� 
	{
		if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
		{
			break;
		}
		temp++;
	}
	int funcname = temp; // ȡ������
	Idt *funame = (Idt*)buffer[funcname];
	string funcnamestring = funame->name;
	int para = temp + 2;
	while (para<=bottom)  // �����б� fun��a,b,5)
	{
		// ������������� 
		// IDT NUM RNUM STRING
		if (buffer[para]->tag == IDT) // Ϊ��ʶ�� ����ʶ����Ӧ��ֵ ���뺯���Ĳ����б���
		{
			Idt* id = (Idt*)buffer[para];
			string q = id->name;
			Idt*value=RunTime.query(q); // ��ѯ �����ʶ�� 
			// value->assType ���������
			// ������� num rnum string
			if (value->assType==NUM)   
			{
				SoInt * p = (SoInt *)value->t;
				SoInt* intt = new SoInt(p->val,0,0);
				paralist.push_back(intt);
				Token *type = new Token(NUM, 0, 0);
				paratype.push_back(type);
			}
			if (value->assType == RNUM)
			{
				SoReal *p = (SoReal *)value->t;
				SoReal *innt = new SoReal(p->val, 0, 0);
				paralist.push_back(innt);
				Token *type = new Token(RNUM, 0, 0);
				paratype.push_back(type);
			}
			if (value->assType == STRING)
			{
				SoString *p = (SoString *)value->t;
				SoString *innt = new SoString(p->str, 0, 0);
				paralist.push_back(innt);
				Token *type = new Token(STRING, 0, 0);
				paratype.push_back(type);
			}
		}
		if (buffer[para]->tag == NUM)  // ��������Ϊ�����б���Ϊ���ֵ���� 
		{
			paralist.push_back(buffer[para]); // ��������token ����paralist ��
			Token *type = new Token(NUM, 0, 0); // ������������ ���� paratype ��
			paratype.push_back(type);
		}
		if (buffer[para]->tag == RNUM)
		{
			paralist.push_back(buffer[para]);
			Token *type = new Token(RNUM, 0, 0);
			paratype.push_back(type);
		}
		if (buffer[para]->tag == STRING)
		{
			paralist.push_back(buffer[para]);
			Token *type = new Token(STRING, 0, 0);
			paratype.push_back(type);
		}
		para++;
	}
	Caller ret(funcnamestring,paratype);  // ������Ϊ ret �� caller ��� һ������ �������� ������ �� �����Ĳ������͹��ɵ��б�
	// ���� ModeExecute ��
	ModeExecute::caller(&ret,paralist);				//  ����
	



}


