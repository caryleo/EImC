#ifndef MODEREAD_H_
#define MODEREAD_H_

#include <iostream>
#include<cstdio>
#include<cstring>
#include <vector>
#include <fstream>
#include <string>
#define BUFLEN 80       //��������С
using namespace std;
class ModeRead
{
private:
	int readType;           //���뷽ʽ���ļ���ֱ������
	int lineLen = 0;          //�������ڵ����ݳ���
	int readPos = -1;         //��ȡλ��
	char line[BUFLEN];      //������
	int lineNum = -1;         //�к�
	int colNum = 0;           //�к�
	char lastch;         //��һ���ַ�
	FILE *file;         //�ļ�ָ��
	vector <char> in_content;//ֱ����������
	char filePathName[1024];//�ļ�·��
public:
	ModeRead();
	void readMode();//����ģ�����
	char scan();//��ȡ�ַ�
				//void output();
};

#endif // !MODEREAD_H_
#pragma once
