#ifndef STACK_H_
#define STACK_H_

#include "EImC.h"
#include "ModeTokenAnalysis.h"

const int STACK_INIT_SIZE = 100;	//��ʼ��С
const int STACK_INCREMENT = 10;		//������С

class Stack {
public:
	Stack();
	void push(Token * t);			//����Ԫ��
	void pop();						//ɾ��ջ��Ԫ��
	Token * front();				//ȡ��ջ��Ԫ��
	bool empty();					//���ջ�Ƿ�Ϊ��
	Token * query(string name);		//�ñ�������ѯIDT
	~Stack();						//��������ջ
private:
	(Token*) * base;				//ջ��
	(Token*) * top;					//ջ��
	int stacksize;					//��ǰջ��С
};


#endif // !STACK_H_
#pragma once