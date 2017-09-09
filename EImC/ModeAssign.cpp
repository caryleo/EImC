#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"Expression.h"
#include"ModeExecute.h"
#include"Stack.h"
#include"FuncType.h"
#include"ModeErrorReport.h"
using namespace std;

extern Stack RunTime;
extern vector<Token*>buffer;
extern vector<Token*> ConstStore;

// ���⣺���ʽ������ε��� ������
ModeAssign::ModeAssign(int a, int b)
{
	top = a;
	bottom = b;
}

void ModeAssign::Fuzhi()
{
	int temp = top;
	int idt;   //��������λ��
	int expr_top;
	int expr_bottom;
	while (temp <= bottom)
	{
		if (buffer[temp]->tag == ASSIGN)
		{
			expr_top = temp + 1;
		}
		temp++;
	}
	temp = expr_top;
	// int a=b=c=d+e
	
	// int a=b+c,d;
	// b=1;
	//int a=b+c
	// ���ܵ�bug a=1+f(2,3);
	while (temp<=bottom)  // ���ʽ������Ϊֹ
	{
		if (buffer[temp]->tag == COMMA && temp == bottom)
		{
			break;
		}
		temp++;
	}
	expr_bottom = temp - 1;
	if ((expr_bottom - expr_top) < 0)
	{
		cout << "Error!!!" << endl;
		ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
		error.report();
		return;
	}
	if ((expr_top - top) < 2)
	{
		cout << "Error!!!" << endl;
		ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
		error.report();
		return;
	}
	else
	{
		temp = expr_top;
		Token *result; // ������ʽ����Ľ��
		// �ж��ǲ��Ǳ��ʽ����к������� 1+fun(2);
		int funcflag = 0;
		int exprflag = 0;
		int functop=0;
		int funcbottom=0;
		int mixuse = 0; // ����Ƿ�Ϊ����
		// �ж��ǲ��ǻ���
		while (temp<=expr_bottom)
		{
			if (buffer[temp]->tag == IDT &&buffer[temp + 1]->tag == LPAR)
			{
				funcflag = 1;
				functop = temp;
				while (temp <= bottom)
				{
					if (buffer[temp]->tag == RPAR)
					{
						funcbottom = temp;
						break;
					}
					temp++;
				}
			}
			temp++;
		}
		// �� ����
		temp = expr_top;
		if (funcflag == 1 && (funcbottom - functop) < (expr_bottom - expr_top))
		{
			int hu_start = buffer.size();

			mixuse = 1;
			int funcstart;
			int funcend;
			int expr_len=expr_bottom - expr_top;
			// ѹջһ�� 
			while (temp <= expr_bottom)
			{
				if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
				{
					funcstart = temp;
					while (temp<=bottom)
					{
						if (buffer[temp]->tag == RPAR)
						{
							funcend = temp;
							// 
							break;
						}
						temp++;
					}
					// ��������ֵ ѹ�� buffer 
					expr_len = expr_len - (funcend - funcstart);
					Token *restemp;
					FuncType a(funcstart, funcend);
					restemp = a.Func();
					buffer.push_back(restemp);
				}
				else   // �������� ֱ��ѹ��ջ
				{
					Token *token = buffer[temp];
					buffer.push_back(token);
				}
				temp++;
			}
			// ��ʼ���� �����ı��ʽ ����ĺ����Ѿ������� �õ��� ���
			int hu_end = hu_start + expr_len ; 
			// �����ı��ʽ�Ľ���
			// int hu_start = hu_end - expr_len;
			// ���� ���ʽ������
			// ���� ���ʽ
			ModeExecute::assign(hu_start, hu_end);
			ExprIR c;
			result = c.calculate_expr(hu_start, hu_end);

		}
		
		// �� ������
		else if ( mixuse == 0 && buffer[expr_top]->tag == IDT&&buffer[expr_top + 1]->tag == LPAR)  //�ж��Ǻ���
		{
			FuncType b(expr_top, expr_bottom);
			result = b.Func();
			//???
		}
		// �� ���ʽ
		else
		{
			
			temp = expr_top;
			while (temp <= expr_bottom)
			{
				//�����ʽ��ı�����ֵ ��ջ��ϵ��һ��  
				if (buffer[temp]->tag == IDT)
				{
					Idt* tem = (Idt*)buffer[temp];
					string q = tem->name;
					Idt *ret = RunTime.query(q);
					if (ret == NULL)
					{
						cout << "Error!" << endl;
						ModeErrorReport error(402, buffer[temp]->line, buffer[temp]->col);
						error.report();
						return;
					}
					if (ret->t == NULL)
					{
						cout << "Error!" << endl;
						ModeErrorReport error(403, buffer[temp]->line, buffer[temp]->col);
						error.report();
						return;
					}
					// int c=a+b; ��a �Ǳ� a ����Ҫ�ѱ��ʽ��� a ָ���assType �ĵ�
					// �ж�������� �½����� ��idt->t ��ϵ��һ��
					if (ret->assType == NUM)
					{
						tem->assType = NUM;
						SoInt*intt = (SoInt*)ret->t;
						SoInt *a = new SoInt(intt->val, 0, 0);
						tem->t = a;
					}
					if (ret->assType == RNUM)
					{
						tem->assType = RNUM;
						SoReal*intt = (SoReal*)ret->t;
						SoReal *a = new SoReal(intt->val, 0, 0);
						tem->t = a;
					}
					if (ret->assType == STRING)
					{
						tem->assType = STRING;
						SoString*strr = (SoString*)ret->t;
						SoString*b = new SoString(strr->str, 0, 0);
						tem->t = b;
					}
				}
				temp++;
			}
			
			// result Ϊ���ʽ����õ��ķ���ֵ ����Ϊtoken
			// ���ݷ���ֵ������ ���������
			ExprIR a;
			result = a.calculate_expr(expr_top, expr_bottom);
		}
		temp = expr_top;
		// �������ȵ����
		// ������δ����͸�ֵ����� ����Ĭ��Ϊ���� ����ֻ��num�������������
		switch (result->tag)
		{
		case NUM:
		{
			SoInt*number = (SoInt*)result;
			short num = number->val;
			temp = expr_top - 1;
			//a=b=c=d+1
			while (temp >= top)
			{
				if (buffer[temp]->tag != ASSIGN)
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				temp--;
				if (buffer[temp]->tag == IDT)
				{
					// a=b ,b->a
					Idt* idt = (Idt*)buffer[temp];
					//	�޸ı�����ֵ
					string q = idt->name;
					Idt *value = RunTime.query(q);// ����ȫ��ջ ���Ƿ������������
					if (value == NULL)  //�Ҳ������� ˵��δ�����ʹ��
					{
						//Idt *res = RunTime.query_alt(q);
						// �½�һ������ Ĭ��Ϊ���� ����ջ��
						// ����
						Token* token = buffer[temp];
						Idt* newidt = (Idt*)token;
						newidt->assType = NUM;  
						newidt->t = NULL;		//��ʱδ��ֵ �޸� t ָ�� ָ���
						RunTime.push(newidt);   // ����ջ��
						RunTime.sync();	 // �޸�ESP
						SoInt*intt = new SoInt(num, 0, 0);
						ConstStore.push_back(intt);
						Idt *newvalue = RunTime.query(q);
						/*if (newvalue == NULL)
							cout << "have" << endl;
						else
						{
							cout << "do not have" << endl;
						}*/
						newvalue->t = intt;
					}
					else if (value->assType == NUM)  //short
					{
						SoInt* intt = new SoInt(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else if (value->assType == RNUM)
					{
						float numtrans = num;
						SoReal* intt = new SoReal(numtrans, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else 
					{
						cout << "Error!!!" << endl;
						ModeErrorReport error(404, buffer[temp]->line, buffer[temp]->col);
						error.report();
						return;
					}
					temp--;
				}
				else
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				
			}
		}
		break;
		case RNUM:
		{
			SoReal *number = (SoReal*)result;
			float num = number->val;//ͨ�����ʽ����ģ����� Ҫ������ֵ
			temp = expr_top - 1;
			// a=b=c+d
			while (temp >= top)
			{
				if (buffer[temp]->tag != ASSIGN)
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				temp--;
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	�޸ı�����ֵ
					string q = idt->name;
					Idt *value = RunTime.query(q);
					if (value->assType == RNUM)
					{
						SoReal* intt = new SoReal(num, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;
					}
					else 
					{
						cout << "Error!!!" << endl;
						ModeErrorReport error(404, buffer[temp]->line, buffer[temp]->col);
						error.report();

						return; 
					}
				}
				else
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				temp--;
			}
		}
		break;
		case STRING:
		{
			SoString *strings = (SoString*)result;
			string numm = strings->str;//ͨ�����ʽ����ģ����� Ҫ������ֵ
			temp = expr_top - 1;
			while (temp >= top)
			{
				if (buffer[temp]->tag != ASSIGN)
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				temp--;
				if (buffer[temp]->tag == IDT)
				{
					Idt* idt = (Idt*)buffer[temp];
					//	�޸ı�����ֵ
					string q = idt->name;
					Idt *value = RunTime.query(q);
					if (value->assType == STRING)
					{

						SoString* intt = new SoString(numm, 0, 0);
						ConstStore.push_back(intt);
						value->t = intt;

					}
					else 
					{
						cout << "Error!!!" << endl;
						ModeErrorReport error(404, buffer[temp]->line, buffer[temp]->col);
						error.report();
					}
				}
				else
				{
					cout << "Error!!!" << endl;
					ModeErrorReport error(401, buffer[temp]->line, buffer[temp]->col);
					error.report();
					return;
				}
				temp--;
			}
		}
		break;
		default:
			break;
		}

	}
}