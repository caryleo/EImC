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
	content.insert(pair<int, string>(152, "���ָ�ʽ����ȷ"));
	content.insert(pair<int, string>(153, "�ַ���ת�����ʽ����ȷ"));
	content.insert(pair<int, string>(154, "�ַ�������������"));
	content.insert(pair<int, string>(250, "δ������ELSE����"));
	content.insert(pair<int, string>(251, "����ȷ�����")); 
	content.insert(pair<int, string>(201, "�����Ų�ƥ��"));
	content.insert(pair<int, string>(202, "δƥ�䵽�ֺ�"));
	content.insert(pair<int, string>(203, "return��䲻��Ϊ��"));
	content.insert(pair<int, string>(204, "�жϱ��ʽ����Ϊ��"));
	content.insert(pair<int, string>(205, "�������ʽ����Ϊ��"));
	content.insert(pair<int, string>(206, "��������Ϊ�Ƿ�"));
	content.insert(pair<int, string>(207, "�Ƿ����"));
	content.insert(pair<int, string>(208, "�Ƿ����ʽ"));
	content.insert(pair<int, string>(209, "�����б�Ϊ�Ƿ�"));
	content.insert(pair<int, string>(210, "�����ض���"));
	content.insert(pair<int, string>(300, "����û�г�ʼֵ"));
	content.insert(pair<int, string>(301, "�������Ͳ���ȷ��string+num��"));
	content.insert(pair<int, string>(302, "���㲻�Ϸ�������Ϊ0��������Ϊ0��"));
	content.insert(pair<int, string>(303, "�����ʹ�ò��Ϸ������磡��#��λ�ò���ȷ��"));
	content.insert(pair<int, string>(304, "���ʽ���㷢�����󣨷��ؽ��Ϊerr��"));
	content.insert(pair<int, string>(351, "�ظ�����ͬһ����"));
	content.insert(pair<int, string>(352, "����ʽ���Ϸ�"));
	content.insert(pair<int, string>(401, "��ֵ���ʽ���Ϸ�"));
	content.insert(pair<int, string>(402, "��ֵ���ʽ�����δ����"));
	content.insert(pair<int, string>(403, "��ֵ���ʽ�����δ����ֵ"));
	content.insert(pair<int, string>(451, "�����������Ϸ�"));

}

void ModeErrorReport::report()
{
}
