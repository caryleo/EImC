#include "stdafx.h"
#include "ModeErrorReport.h"
using namespace std;

ModeErrorReport::ModeErrorReport(int code, int l, int c)
{
	errorCode = code;
	line = l;
	col = c;
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(150, "符号\"&\"未正确匹配"));
	content.insert(pair<int, string>(151, "符号\"|\"未正确匹配"));
	content.insert(pair<int, string>(152, "数字格式"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件")); 
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
	content.insert(pair<int, string>(100, "找不到该文件"));
}

void ModeErrorReport::report()
{
}
