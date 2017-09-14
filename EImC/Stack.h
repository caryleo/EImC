#ifndef STACK_H_
#define STACK_H_

#include "EImC.h"
#include "ModeTokenAnalysis.h"
#include "ModeExecute.h"
#include <cstdlib>

const int STACK_INIT_SIZE = 100;	//��ʼ��С
const int STACK_INCREMENT = 50;		//������С

class Stack {
public:
	Stack();
	int push(Token * t);		//����Ԫ��
	void pop();					//ɾ��ջ��Ԫ��
	Token * front();			//ȡ��ջ��Ԫ��
	bool empty();				//���ջ�Ƿ�Ϊ��
	int size();					//��ʹ�õ�ջ�ռ�ĸ���
	Idt * query(string n);		//��ѯָ���ı�ʶ��
	void sync();				//ͬ��espָ��
	void syncb();				//ͬ��ebpָ��
	void desyncb();
	void desync();				//��������ջ
	void desync_func();			//���ú�������ջ
	void ret(Token * s);		//���Ʒ���ֵ�ĸ�ֵ
	Idt * query_alt(string n);	//��ѯ����ǰebp
	~Stack();					//��������ջ
private:
	Token ** base;				//ջ��
	Token ** top;				//ջ��
	int stacksize;				//��ǰջ��С
	int cnt;
};



#endif // !STACK_H_
#pragma once
