#ifndef STACK_H_
#define STACK_H_

#include "EImC.h"
#include "ModeTokenAnalysis.h"

const int STACK_INIT_SIZE = 100;	//��ʼ��С
const int STACK_INCREMENT = 10;		//������С

class Stack {
public:
	Stack();
	void push(Token * t);		//����Ԫ��
	void pop();					//ɾ��ջ��Ԫ��
	Token * front();			//ȡ��ջ��Ԫ��
	bool empty();				//���ջ�Ƿ�Ϊ��
	int size();					//��ʹ�õ�ջ�ռ�ĸ���
	Idt * query(string n);		//��ѯָ���ı�ʶ��
	void sync(Token ** & esp);	//ͬ��ջ��ָ��
	~Stack();					//��������ջ
private:
	Token ** base;				//ջ��
	Token ** top;				//ջ��
	int stacksize;				//��ǰջ��С
	int cnt;
};



#endif // !STACK_H_
#pragma once
