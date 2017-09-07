#include"stdafx.h"
#include"VarType.h"
#include"EImC.h"
#include"ModeTokenAnalysis.h"
#include"ModeAssign.h"
#include"ModeExecute.h"
#include"Expression.h"
#include"Stack.h"
#include"FuncType.h"


// ���ڵ����� ��ֵ���õ�ʵ��(�ؼ���Ϊ���ں�)��û��д�� ���������� 50��  85 .118 ��
// ��ֵʽ��   ����﷨�Ƿ����﷨����  ��θ�ֵ�� ��Ҫ���õĹ��� 
extern vector<Token*>buffer;
extern Stack RunTime;				//����ջ
extern Token ** esp, **ebp;			//����ջ��ջ����ջ��
extern vector<Token*>ConstStore;

VarType::VarType(int a, int b)
{
	top = a;
	bottom = b;
}

void VarType::input()  //���ҵ��� int/real/string ��ͷ �Էֺ�Ϊ������һ�λ� 
{

	int temp;
	switch (buffer[top]->tag)  //��ȡ��һ������ �ж��� int real string ;
		// int a;  int a=1��b=1 ; int a,b; �����м������
		//a=2 ��ֵ 
		// real a;
		//string a;
	{
	case KEY_INT:
	{
		temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // �жϵ������ֺ� ���ֺ�Ϊ����
		{
			// �±��� ���±��� ������ջ��
			if (buffer[temp]->tag == IDT)  //idt �Ǳ�ʶ�� ���� a  Ҫ�����Ԫ�� a ��ȥ
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = NUM;  // ��idt�����asstype ��ע������� ���ڵ�����
				idt->t = NULL;		//��ʱδ��ֵ �޸� t ָ�� ָ���
				RunTime.push(idt);   // ����ջ��
				RunTime.sync();	 // �޸�ESP
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //��������
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //�������ں� ��������ֵ���ĵط� ���� int a=b+c;
			{
				int start = temp - 1;  //��ǰ��һ�� ��ʼ�ǵȺ���ߵı���
				temp++;


				// �����ֺ� ���� ����
				while (buffer[temp]->tag != COMMA&&temp <= bottom) //�������Ż�����������ʱ�� ˵����ֵ������
				{
					temp++;
				}
				int end = temp - 1;		// �����ֵ���Ľ���

				//���ø�ֵ��� ImpleAssign��start��end�� �ݶ����÷���
				ModeAssign test(start, end);
				test.Fuzhi();
			}
			if (buffer[temp]->tag == KEY_INT || buffer[temp]->tag == KEY_REAL || buffer[temp]->tag == KEY_STRING)
			{
				cout << "Error!!!" << endl;
				return;
			}
		}

		//�ڷ��ű����½�һ����Ϊtempָ������ֵ� �����ִ��ȥ ������֮ǰ���ֵ�int����������
		//����

	}
	break;
	case KEY_REAL:
	{
		temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // �жϵ������ֺ� ���ֺ�Ϊ����
		{
			if (buffer[temp]->tag == IDT)  //idt �Ǳ�ʶ�� ���� a   Ҫ�����Ԫ�� a ��ȥ
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = RNUM;  // ��idt�����asstype ��ע������� ���ڵ�����
				idt->t = NULL;
				RunTime.push(idt);   // ����ջ��
				RunTime.sync();	 // �޸�ESP
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //��������
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //�������ں� ��������ֵ���ĵط� ���� real a=b+c;
			{
				int start = temp - 1;  //��ǰ��һ�� ��ʼ�ǵȺ���ߵı���
				temp++;
				while (buffer[temp]->tag != COMMA && temp<=bottom) //����Ϊ�ֺŻ��߶��� ˵����ֵ������
				{
					temp++;
				}
				int end = temp - 1;		// �����ֵ���Ľ���
										//���ø�ֵ��� ��start��end�� �ݶ����÷���
				ModeAssign test(start, end);
				test.Fuzhi();
			}
			if (buffer[temp]->tag == KEY_INT || buffer[temp]->tag == KEY_REAL || buffer[temp]->tag == KEY_STRING)
			{
				cout << "Error!!!" << endl;
				return;
			}
		}


	}
	break;
	case KEY_STRING:
	{
		temp = top + 1;
		while (temp <= bottom&&buffer[temp]->tag != SEMICO) // �жϵ������ֺ� ���ֺ�Ϊ����
		{
			if (buffer[temp]->tag == IDT)  //idt �Ǳ�ʶ�� ���� a  Ҫ�����Ԫ�� a ��ȥ
			{
				Token* token = buffer[temp];
				Idt* idt = (Idt*)token;
				idt->assType = STRING;  // ��idt�����asstype ��ע������� ���ڵ�����
				idt->t = NULL;
				RunTime.push(idt);		// ����ջ��
				RunTime.sync();	 // �޸�ESP
				temp++;
				continue;
			}
			if (buffer[temp]->tag == COMMA)  //��������
			{
				temp++;
				continue;
			}
			if (buffer[temp]->tag == ASSIGN) //�������ں� ��������ֵ���ĵط� ���� srting a=
			{
				int start = temp - 1;  //��ǰ��һ�� ��ʼ�ǵȺ���ߵı���
				temp++;
				while (buffer[temp]->tag != COMMA && temp<=bottom) //����Ϊ�ֺŻ��߶��� ˵����ֵ������
				{
					temp++;
				}
				int end = temp - 1;		// �����ֵ���Ľ���
										//���ø�ֵ��� ��start��end�� �ݶ����÷���
				ModeAssign test(start, end);
				test.Fuzhi();
			}
			if (buffer[temp]->tag == KEY_INT || buffer[temp]->tag == KEY_REAL || buffer[temp]->tag == KEY_STRING)
			{
				cout << "Error!!!" << endl;
				return;
			}
		}

	}
	break;
	default:
		break;
	}

}
