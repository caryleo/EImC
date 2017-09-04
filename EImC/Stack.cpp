#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "Stack.h"
#include <cstdlib>
using namespace std;

Stack::Stack() {
	if (!(base = (Token **)malloc(STACK_INIT_SIZE * sizeof(Token *)))) {
		exit(1);
	}
	stacksize = STACK_INIT_SIZE;
	top = base;
}

void Stack::push(Token * t) {/*��Ԫ��ѹ��ջ��*/
	if (top - base >= stacksize) {/*ջ����������ջ*/
		if (!(base = (Token **)realloc(base, (STACK_INIT_SIZE + STACK_INCREMENT) * sizeof(Token *)))) {
			top = base + stacksize;
			stacksize += STACK_INCREMENT;
		}
	}
	else {
		*top++ = t;
	}
	return;
}

void Stack::pop() {/*ɾ��ջ��Ԫ��*/
	if (top != base) {
		Token *tmp = *top--;
		delete tmp;
	}
	return;
}

Token * Stack::front() {/*ȡ��ջ��Ԫ��*/
	if (top == base) {
		return NULL;
	}
	else {
		Token * t = *top--;
		return t;
	}
}

bool Stack::empty() {/*�ж�ջ�Ƿ�Ϊ��*/
	return top == base ? true : false;
}

Stack::~Stack() {/*����*/
	free(base);
}

Token * Stack::query(string name) {/*��ѯָ����IDT*/
	Token ** ans;
	ans = top;
	while (ans-- != base) {
		if ((*ans)->tag == IDT) {
			Idt * i = (Idt *)(*ans);
			if (name.compare(i->name) == 0) {
				return i->t;
			}
		}
	}
	return NULL;
}