#ifndef MODEREAD_H_
#define MODEREAD_H_

#include <iostream>
#include<cstdio>
#include<cstring>
#include <vector>
#include <fstream>
#include <string>
#define BUFLEN 80       //缓冲区大小
using namespace std;
class ModeRead
{
private:
	int readType;           //输入方式：文件或直接输入
	int lineLen = 0;          //缓冲区内的数据长度
	int readPos = -1;         //读取位置
	char line[BUFLEN];      //缓冲区
	int lineNum = -1;         //行号
	int colNum = 0;           //列号
	char lastch;         //上一个字符
	FILE *file;         //文件指针
	vector <char> in_content;//直接输入内容
	char filePathName[1024];//文件路径
public:
	ModeRead();
	void readMode();//运行模块入口
	char scan();//读取字符
				//void output();
};

#endif // !MODEREAD_H_
#pragma once
