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
	if (buffer[top + 1]->tag == IDT) {
		if (buffer[top + 2]->tag = LPAR) {//����ֵ��һ���������õĽ��
			FuncType fType(top + 1, bottom);
			Token * tmp = fType.Func();
			RunTime.ret(tmp, ebp);
			RunTime.desync(ebp, esp);
		}
		else//����ֵ�Ǳ��ʽ���
		{
			ExprIR eIR;
			Token * tmp = eIR.calculate_expr(top + 1, bottom);
			RunTime.ret(tmp, ebp);
			RunTime.desync(ebp, esp);
		}
	}
	else {//����ֵ�Ǳ��ʽ���
		ExprIR eIR;
		Token * tmp = eIR.calculate_expr(top + 1, bottom);
		RunTime.ret(tmp, ebp);
		RunTime.desync(ebp, esp);
	}
}