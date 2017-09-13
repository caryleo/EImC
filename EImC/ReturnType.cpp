#include "stdafx.h"
#include "EImC.h"
#include "ReturnType.h"
#include "Expression.h"
#include "FuncType.h"
#include "Stack.h"

extern vector<Token*>buffer;
extern Token ** esp, ** ebp;
extern Stack RunTime;

ReturnType::ReturnType(int t, int b){
	top = t;
	bottom = b;
}


void ReturnType::startReturn() {
	int expr_top = top + 1;
	int expr_bottom = bottom;
	int temp = expr_top;
	Token *result; // ������ʽ����Ľ��
				   // �ж��ǲ��Ǳ��ʽ����к������� 1+fun(2);
	int funcflag = 0;
	int exprflag = 0;
	int functop = 0;
	int funcbottom = 0;
	int mixuse = 0; // ����Ƿ�Ϊ����
					// �ж��ǲ��ǻ���
	while (temp <= expr_bottom)
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
		int expr_len = expr_bottom - expr_top;
		// ѹջһ�� 
		while (temp <= expr_bottom)
		{
			if (buffer[temp]->tag == IDT&&buffer[temp + 1]->tag == LPAR)
			{
				funcstart = temp;
				while (temp <= bottom)
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
				if ((funcend - funcstart) < (expr_bottom - expr_top))
				{
					int len = buffer.size();
					FuncType a(funcstart, funcend);
					buffer.push_back(buffer[temp-1]);//�޸�
					restemp = a.Func(len);
				}
				else
				{
					FuncType a(funcstart, funcend);
                    restemp = a.Func();
					buffer.push_back(restemp);
				}
				
				
				
			}
			else   // �������� ֱ��ѹ��ջ
			{
				
				//Token *token = buffer[temp];
				//buffer.push_back(token);
				// 9.12 �޸�
				if (buffer[temp]->tag == IDT)
				{
					Idt *id = (Idt*)buffer[temp];
					if (id->assType == NUM)
					{
						Idt* numm=RunTime.query(id->name);
					    
						SoInt *number = (SoInt*)(numm->t);
						short num = number->val;
						SoInt *newint = new SoInt(num, 1, 1);
						buffer.push_back(newint);
						//cout << num << endl;
					}
				}
				//9.12 �޸�
				else
				{
					Token *token = buffer[temp];
					buffer.push_back(token);
				}
			}
			temp++;
		}
		// ��ʼ���� �����ı��ʽ ����ĺ����Ѿ������� �õ��� ���
		int hu_end = hu_start+expr_len; 
		// �����ı��ʽ�Ľ���
		// int hu_start = hu_end - expr_len;
		// ���� ���ʽ������
		// ���� ���ʽ
		ModeExecute::assign(hu_start, hu_end);
		ExprIR c;
		result = c.calculate_expr(hu_start, hu_end);
		RunTime.ret(result);
		RunTime.desync_func();

	}
	
	else  if (buffer[top + 1]->tag == IDT) 
	{
		if (buffer[top + 2]->tag == LPAR) {//����ֵ��һ���������õĽ��
			FuncType fType(top + 1, bottom);
			Token * tmp = fType.Func();
			RunTime.ret(tmp);
			RunTime.desync_func();
		}
		else//����ֵ�Ǳ��ʽ���
		{
			ExprIR eIR;
			Token * tmp = eIR.calculate_expr(top + 1, bottom);
			RunTime.ret(tmp);
			RunTime.desync_func();
		}
	}
	else {//����ֵ�Ǳ��ʽ���
		ExprIR eIR;
		Token * tmp = eIR.calculate_expr(top + 1, bottom);
		RunTime.ret(tmp);
		RunTime.desync_func();
	}
}