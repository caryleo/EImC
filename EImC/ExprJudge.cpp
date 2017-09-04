#include"stdafx.h"
#include"EImC.h"
#include"ExprJudge.h"
#include"ModeTokenAnalysis.h"
extern vector<Token*>buffer;


ExprJudge::ExprJudge(int a, int b)
{
	top = a;
	bottom = b;
}

bool ExprJudge::input(int top, int bottom)  // top ~bottom ֮��Ĵ�ת���� string expr
{
	//�жϱ��ʽ�Ƿ�Ϸ�  ���ʽ���� idt ����� ����
	int temp=top;
	/*string expr;*///���ʽ����string
	while (temp<=bottom)
	{
		if (buffer[temp]->tag==NUM)  // ������ת��Ϊstring �浽expr��
		{
			Token* token = buffer[temp];
			SoInt *intp = (SoInt*)token;
			int hu = intp->val;
			char value[100];
			sprintf(value, "%d", hu);
			string tem = value;
			expr += tem;
		}
		if (buffer[temp]->tag == RNUM)  // ��r����ת��Ϊstring �浽expr��
		{
			Token* token = buffer[temp];
			SoReal *intp = (SoReal*)token;
			float hu = intp->val;
			char value[100];
			sprintf(value, "%f", hu);
			string tem = value;
			expr += tem;
		}

		if (buffer[temp]->tag == IDT)  //������һ����ʶ�� ��������ֵ����string expr ��
		{
			Token* token = buffer[temp];
			Idt* idt = (Idt*)token;
			switch (idt->assType)
			{
			case NUM:
			{
				SoInt*intp = (SoInt*)idt->t;
				int hu = intp->val;
				char value[100];
				sprintf(value, "%d", hu);
				string tem = value;
				expr += tem;
			}
			case RNUM:
			{
				SoReal*intp = (SoReal*)idt->t;
				float hu = intp->val;
				char value[100];
				sprintf(value, "%f", hu);
				string tem = value;
				expr += tem;
			}
			default:
				break;
			}
			
		}
		if (buffer[temp]->tag == ADD)
		{
			expr += "+";
		}
		if (buffer[temp]->tag == SUB)
		{
			expr += "-";
		}
		if (buffer[temp]->tag == MUL)
		{
			expr += "*";
		}
		if (buffer[temp]->tag == DIV)
		{
			expr += "/";
		}
		if (buffer[temp]->tag == MOD)
		{
			expr += "%";
		}
		if (buffer[temp]->tag == LPAR)
		{
			expr += "(";
		}
		if (buffer[temp]->tag == RPAR)
		{
			expr += ")";
		}
		temp++;
	}

}

int ExprJudge::word_analysis(vector<pair<string, int>>& word, const string expr)
{
	for (int i = 0; i<expr.length(); ++i)
	{
		// ����� + - * / ( )  
		if (expr[i] == '(' || expr[i] == ')' || expr[i] == '+'
			|| expr[i] == '-' || expr[i] == '*' || expr[i] == '/')
		{
			string tmp;
			tmp.push_back(expr[i]);
			switch (expr[i])
			{
			case '+':
				word.push_back(make_pair(tmp, 1));
				break;
			case '-':
				word.push_back(make_pair(tmp, 2));
				break;
			case '*':
				word.push_back(make_pair(tmp, 3));
				break;
			case '/':
				word.push_back(make_pair(tmp, 4));
				break;
			case '(':
				word.push_back(make_pair(tmp, 6));
				break;
			case ')':
				word.push_back(make_pair(tmp, 7));
				break;
			}
		}
		// ��������ֿ�ͷ  
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			string tmp;
			while (expr[i] >= '0' && expr[i] <= '9')
			{
				tmp.push_back(expr[i]);
				++i;
			}
			if (expr[i] == '.')
			{
				++i;
				if (expr[i] >= '0' && expr[i] <= '9')
				{
					tmp.push_back('.');
					while (expr[i] >= '0' && expr[i] <= '9')
					{
						tmp.push_back(expr[i]);
						++i;
					}
				}
				else
				{
					return -1;  // .���治�����֣��ʷ�����  
				}
			}
			word.push_back(make_pair(tmp, 5));
			--i;
		}
		// �����.��ͷ  
		else
		{
			return -1;  // ��.��ͷ���ʷ�����  
		}
	}
	return 0;
}

void ExprJudge::Next()
{
	if (idx < word.size())
		sym = word[idx++].second;
	else
		sym = 0;
}

void ExprJudge::E()
{
	T();
	while (sym == 1 || sym == 2)
	{
		Next();
		T();
	}
}

void ExprJudge::T()
{
	F();
	while (sym == 3 || sym == 4)
	{
		Next();
		F();
	}
}

void ExprJudge::F()
{
	if (sym == 5)
	{
		Next();
	}
	else if (sym == 6)
	{
		Next();
		E();
		if (sym == 7)
		{
			Next();
		}
		else
		{
			err = -1;
		}
	}
	else
	{
		err = -1;
	}
}

int ExprJudge::ExprTest()  //return 0 ������ʽ����  return 1 ���� ���ʽ��ȷ
{
	input(top, bottom);
	int err_num = word_analysis(word, expr);
	/*cout << expr << endl << "Word Analysis:" << endl;*/
	if (-1 == err_num)
	{
		return 0;
		/*cout << "Word Error!" << endl;*/
	}
	else
	{
		// �������  
		vector<pair<string, int>>::iterator beg = word.begin();
		/*for (; beg != word.end(); ++beg)
		cout << "   (" << beg->first << ", " << beg->second << ")" << endl;*/

		// �ʷ���ȷ�������﷨����  
		Next();
		E();
		if (sym == 0 && err == 0)  // ע��Ҫ�ж���������  
		{
			/*cout << "Right Expression." << endl;*/
			return 1;
		}

		else
		{
			/*cout << "Wrong Expression." << endl;*/
			return 0;
		}

	}
	return 0;
}

