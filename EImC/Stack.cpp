#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "Stack.h"
using namespace std;

extern Stack RunTime;

Stack::Stack() {
	if (!(base = (Token **)malloc(STACK_INIT_SIZE * sizeof(Token *)))) {
		exit(1);
	}
	stacksize = STACK_INIT_SIZE;
	top = base;
	cnt = 0;
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
	cnt++;
	return;
}

void Stack::pop() {/*ɾ��ջ��Ԫ��*/
	if (top != base) {
		Token *tmp = *top--;
		delete tmp;
	}
	cnt--;
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

int Stack::size()
{
	return cnt;
}

Idt * Stack::query(string n)
{
	Token ** p = top;
	while (p != base) {
		if ((*p)->tag == IDT) {
			Idt * q = (Idt*)(*p);
			string name = q->name;
			if (n.compare(name) == 0) {
				return q;
			}
		}
		p--;
	}
	return nullptr;
}

void Stack::sync(Token **& esp)
{
	esp == top;
	return;
}

Stack::~Stack() {/*����*/
	free(base);
}