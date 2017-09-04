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

void Stack::push(Token * t) {/*将元素压入栈中*/
	if (top - base >= stacksize) {/*栈已满建立新栈*/
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

void Stack::pop() {/*删除栈顶元素*/
	if (top != base) {
		Token *tmp = *top--;
		delete tmp;
	}
	return;
}

Token * Stack::front() {/*取出栈顶元素*/
	if (top == base) {
		return NULL;
	}
	else {
		Token * t = *top--;
		return t;
	}
}

bool Stack::empty() {/*判断栈是否为空*/
	return top == base ? true : false;
}

Stack::~Stack() {/*销毁*/
	free(base);
}

Token * Stack::query(string name) {/*查询指定的IDT*/
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