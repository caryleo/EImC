#include "stdafx.h"
#include "EImC.h"
#include "ReturnType.h"
#include "Expression.h"
#include "FuncType.h"

extern vector<Token*>buffer;

ReturnType::ReturnType(int t, int b){
	top = t;
	bottom = b;
}


void ReturnType::startReturn() {
	if (buffer[top + 1]->tag == IDT) {
		if (buffer[top + 2]->tag = LPAR) {
			FuncType fType(top + 1, bottom);
			Token * tmp = fType.Func();

		}
	}
	else {
		ExprIR eIR;

		eIR.calculate_expr(top + 1, bottom);
	}
}