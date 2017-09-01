#include"ModeTokenAnalysis.h"
using namespace std;

Keywords::Keywords()/*关键字列表初始化*/
{
	keywords.insert(pair<string, Tag>("int", KEY_INT));
	keywords.insert(pair<string, Tag>("real", KEY_REAL));
	keywords.insert(pair<string, Tag>("string",KEY_STRING));
	keywords.insert(pair<string, Tag>("if",KEY_IF));
	keywords.insert(pair<string, Tag>("else", KEY_ELSE));
	keywords.insert(pair<string, Tag>("while", KEY_WHILE));
	keywords.insert(pair<string, Tag>("break", KEY_BRK));
	keywords.insert(pair<string, Tag>("continue", KEY_CON));
	keywords.insert(pair<string, Tag>("return", KEY_RET));
}

Tag Keywords::getTag(string name)/*查询关键字*/
{
	return keywords.find(name) != keywords.end() ? keywords[name] : IDT;
}