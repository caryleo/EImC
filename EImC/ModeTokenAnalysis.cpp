#include "stdafx.h"
#include"ModeTokenAnalysis.h"
using namespace std;

extern vector<Token*>buffer;

Keywords::Keywords()/*�ؼ����б��ʼ��*/ {
	keywords.insert(pair<string, Tag>("int", KEY_INT));
	keywords.insert(pair<string, Tag>("real", KEY_REAL));
	keywords.insert(pair<string, Tag>("string", KEY_STRING));
	keywords.insert(pair<string, Tag>("if", KEY_IF));
	keywords.insert(pair<string, Tag>("else", KEY_ELSE));
	keywords.insert(pair<string, Tag>("while", KEY_WHILE));
	keywords.insert(pair<string, Tag>("break", KEY_BRK));
	keywords.insert(pair<string, Tag>("continue", KEY_CON));
	keywords.insert(pair<string, Tag>("return", KEY_RET));
}

Tag Keywords::getTag(string name)/*��ѯ�ؼ���*/ {
	return keywords.find(name) != keywords.end() ? keywords[name] : IDT;
}

Token::Token() {}

Token::Token(Tag t) {
	tag = t;
}

string Token::tooString() {
	return "This is a token ";
}

Idt::Idt() {}

Idt::Idt(string s) {
	tag = IDT;
	name = s;
}

string Idt::toString() {
	return "This name is " + name;
}

SoInt::SoInt(short n) {
	val = n;
}

string SoInt::toString() {
	return "This value is " + val;
}

SoReal::SoReal(float f) {
	tag = RNUM;
	val = f;
}

string SoReal::toString() {
	cout << val;
	return " is the value.";
}

SoString::SoString(string s) {
	tag = STRING;
	str = s;
}

string SoString::toString() {
	return "This string is " + str;
}

void ModeTokenAnalysis::read(ModeRead& mRead)/*�����������*/ {
	Token* t;
	while (t = ModeTokenAnalysis::getToken(mRead), t != NULL)
	{
		buffer.push_back(t);
	}
	cout << "Token Analysis Completed." << endl;
}
Token* ModeTokenAnalysis::getToken(ModeRead& mRead) {/*ʶ�����ؿ���ģ��*/
	char ch;
	while ((ch = mRead.scan()) != -1) {
		if (ch = ' ' || ch == '\n' || ch == '\t') {/*������ʽ��*/
			continue;
		}
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {/*��ʶ��*/
			string name = "";
			do {
				name += ch;
				ch = mRead.scan();
			} while (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9');
			Keywords kw;
			Tag tag = kw.getTag(name);
			if (tag == IDT) {
				return new Idt(name);
			}
			else {
				return new Token(tag);
			}
		}
		if (ch >= '0' && ch <= '9') {/*���ֳ���*/
			short val1 = 0;
			float val2 = 0.0;
			do {
				val1 *= 10;
				val1 += ch - '0';
				ch = mRead.scan();
			} while (ch >= '0'&&ch <= '9');
			if (ch == '.') {
				ch = mRead.scan();
				string tmp = "";
				while (ch >= '0' && ch <= '9') {
					tmp += ch;
					ch = mRead.scan();
				}
				for (int i = tmp.size() - 1; i >= 0; i--) {
					val2 += (tmp.at(i) - '0')*0.1;
				}
				val2 += val1;
				return new SoReal(val2);
			}
			else {
				return new SoInt(val1);
			}
		}
		if (ch == '"') {/*�ַ�������*/
			string str = "";
			while (ch = mRead.scan(), ch != '"') {
				if (ch == '\\') {
					ch = mRead.scan();
					switch (ch)
					{
					case 'n': str.push_back('\n'); break;
					case '\\':str.push_back('\\'); break;
					case 't':str.push_back('\t'); break;
					case '"':str.push_back('\"'); break;
					case '0':str.push_back('\0'); break;
					case '\'':str.push_back('\''); break;
					case 'r':str.push_back('\r'); break;
					case '\n':
					case -1:
						cout << "ERROR!!!" << endl;
						return NULL;
						break;
					default:str.push_back(ch);
					}
				}
				else if (ch == '\n' || ch == -1) {
					cout << "ERROR!!!" << endl;
					return NULL;
				}
				else {
					str.push_back(ch);
				}
			}
			return new SoString(str);
		}
		if (ch == '+')/*�Ӻ�*/ {
			return new Token(ADD);
		}
		if (ch == '-')/*����*/ {
			return new Token(SUB);
		}
		if (ch == '*')/*�˺�*/ {
			return new Token(MUL);
		}
		if (ch == '/')/*����*/ {
			return new Token(DIV);
		}
		if (ch == '%')/*ȡ��*/ {
			return new Token(MOD);
		}
		if (ch == '&')/*�߼���*/ {
			if (ch = mRead.scan(), ch == '&') {
				return new Token(AND);
			}
			else {
				cout << "ERROR!!!" << endl;
				return NULL;
			}
		}
		if (ch == '|')/*�߼���*/ {
			if (ch = mRead.scan(), ch == '|') {
				return new Token(OR);
			}
			else {
				cout << "ERROR!!!" << endl;
				return NULL;
			}
		}
		if()
	}
}