#ifndef STACK_H_
#define STACK_H_

#include "EImC.h"
#include "ModeTokenAnalysis.h"

const int STACK_INIT_SIZE = 100;	//初始大小
const int STACK_INCREMENT = 10;		//增量大小

class Stack {
public:
	int cnt;
	Stack();
	void push(Token * t);	//插入元素
	void pop();				//删除栈顶元素
	Token * front();		//取出栈顶元素
	bool empty();			//检查栈是否为空
	~Stack();				//销毁整个栈
private:
	Token ** base;		//栈底
	Token ** top;			//栈顶
	int stacksize;			//当前栈大小
};


#endif // !STACK_H_
#pragma once
