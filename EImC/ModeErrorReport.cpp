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
	content.insert(pair<int, string>(152, "数字格式不正确"));
	content.insert(pair<int, string>(153, "字符串转义符格式不正确"));
	content.insert(pair<int, string>(154, "字符串非正常结束"));
	content.insert(pair<int, string>(250, "未关联的ELSE语句块"));
	content.insert(pair<int, string>(251, "不正确的语句")); 
	content.insert(pair<int, string>(201, "大括号不匹配"));
	content.insert(pair<int, string>(202, "未匹配到分号"));
	content.insert(pair<int, string>(203, "return语句不能为空"));
	content.insert(pair<int, string>(204, "判断表达式不能为空"));
	content.insert(pair<int, string>(205, "条件表达式不能为空"));
	content.insert(pair<int, string>(206, "变量定义为非法"));
	content.insert(pair<int, string>(207, "非法语句"));
	content.insert(pair<int, string>(208, "非法表达式"));
	content.insert(pair<int, string>(209, "参数列表为非法"));
	content.insert(pair<int, string>(210, "函数重定义"));
	content.insert(pair<int, string>(300, "变量没有初始值"));
	content.insert(pair<int, string>(301, "变量类型不正确（string+num）"));
	content.insert(pair<int, string>(302, "运算不合法（除数为0或者余数为0）"));
	content.insert(pair<int, string>(303, "运算符使用不合法（比如！和#的位置不正确）"));
	content.insert(pair<int, string>(304, "表达式运算发生错误（返回结果为err）"));
	content.insert(pair<int, string>(351, "重复定义同一变量"));
	content.insert(pair<int, string>(352, "定义式不合法"));
	content.insert(pair<int, string>(401, "赋值表达式不合法"));
	content.insert(pair<int, string>(402, "赋值表达式里参数未定义"));
	content.insert(pair<int, string>(403, "赋值表达式里参数未赋初值"));
	content.insert(pair<int, string>(451, "函数参数不合法"));

}

void ModeErrorReport::report()
{
}
