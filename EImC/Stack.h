#ifndef STACK_H_
#define STACK_H_

#include "EImC.h"
#include "ModeTokenAnalysis.h"

const int STACK_INIT_SIZE = 100;	//初始大小
const int STACK_INCREMENT = 10;		//增量大小

class Stack {
public:
	Stack();
	void push(Token * t);		//插入元素
	void pop();					//删除栈顶元素
	Token * front();			//取出栈顶元素
	bool empty();				//检查栈是否为空
	int size();					//已使用的栈空间的个数
	Idt * query(string n);		//查询指定的标识符
	void sync(Token ** & esp);	//同步栈顶指针
	~Stack();					//销毁整个栈
private:
	Token ** base;				//栈底
	Token ** top;				//栈顶
	int stacksize;				//当前栈大小
	int cnt;
};



#endif // !STACK_H_
#pragma once
