#include "stdafx.h"
#include "ModeErrorReport.h"
using namespace std;

ModeErrorReport::ModeErrorReport(int code, int l, int c)
{
	errorCode = code;
	line = l;
	col = c;
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(150, "����\"&\"δ��ȷƥ��"));
	content.insert(pair<int, string>(151, "����\"|\"δ��ȷƥ��"));
	content.insert(pair<int, string>(152, "���ָ�ʽ"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�")); 
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
	content.insert(pair<int, string>(100, "�Ҳ������ļ�"));
}

void ModeErrorReport::report()
{
}
