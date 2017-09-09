#include "stdafx.h"
#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "Stack.h"
using namespace std;

extern Token** esp, **ebp;

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
		*top = t;
		top++;
	}
	cnt++;
	return;
}

void Stack::pop() {/*ɾ��ջ��Ԫ�أ�ʵ�ʲ����ǿ���ָ��*/
	if (cnt) {
		top--;
		cnt--;
	}
	return;
}

Token * Stack::front() {/*ȡ��ջ��Ԫ��*/
	if (cnt == 0) {
		return nullptr;
	}
	else {
		top--;
		Token * t = *top;
		top++;
		return t;
	}
}

bool Stack::empty() {/*�ж�ջ�Ƿ�Ϊ��*/
	return cnt == 0 ? true : false;
}

int Stack::size()
{
	return cnt;
}

Idt * Stack::query(string n)
{
	Token ** p = top;
	while (p != base) {
		p--;
		if ((*p)->tag == IDT) {
			Idt * q = (Idt*)(*p);
			string name = q->name;
			if (n.compare(name) == 0) {
				return q;
			}
		}
	}
	return nullptr;
}

void Stack::sync()
{
	esp = top;
	return;
}

void Stack::syncb()
{
	ebp = top;
	return;
}

void Stack::desync()
{
	Token ** tmp = top;
	while (tmp != base) {
		tmp--;
		if ((*tmp)->tag == PRT) {
			PRTR * tt = (PRTR *)(*tmp);
			ebp = tt->prt;//����һ������ջ��ջ��ָ�븳��ebp
			break;
		}
	}
	while (esp != tmp) {
		this->pop();
		esp--;//��esp��������ebp��ַ��λ��
	}
}

void Stack::desync_func()
{
	Token ** tmp = top;
	while (tmp != base) {
		tmp--;
		if ((*tmp)->tag == PRT) {
			PRTR * tt = (PRTR *)(*tmp);
			ebp = tt->prt;//����һ������ջ��ջ��ָ�븳��ebp
			break;
		}
	}
	while (esp != tmp) {
		this->pop();
		esp--;//��esp��������ebp��ַ��λ��
	}
}

void Stack::ret(Token * s) {
	Token ** tmp = top - 1;
	while (((*tmp)->tag != NUM ) && ((*tmp)->tag != RNUM) && ((*tmp)->tag != STRING)) {
		tmp--;
	}
	*tmp = s;
}

Idt * Stack::query_alt(string n)
{
	Token ** p = top;
	while (p != ebp) {
		p--;
		if ((*p)->tag == IDT) {
			Idt * q = (Idt*)(*p);
			string name = q->name;
			if (n.compare(name) == 0) {
				return q;
			}
		}
	}
	return nullptr;
}

Stack::~Stack() {/*����*/
	free(base);
}