#ifndef STACK_H_
#define STACK_H_

#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeExecute.h"
#include <cstdlib>

const int STACK_INIT_SIZE = 100;	//初始大小
const int STACK_INCREMENT = 50;		//增量大小

class Stack {
public:
	Stack();
	int push(Token * t);		//插入元素
	void pop();					//删除栈顶元素
	Token * front();			//取出栈顶元素
	bool empty();				//检查栈是否为空
	int size();					//已使用的栈空间的个数
	Idt * query(string n);		//查询指定的标识符
	void sync();				//同步esp指针
	void syncb();				//同步ebp指针
	void desyncb();
	void desync();				//重置运行栈
	void desync_func();			//重置函数运行栈
	void ret(Token * s);		//控制返回值的赋值
	Idt * query_alt(string n);	//查询到当前ebp
	~Stack();					//销毁整个栈
private:
	Token ** base;				//栈底
	Token ** top;				//栈顶
	int stacksize;				//当前栈大小
	int cnt;
};



#endif // !STACK_H_
#pragma once
