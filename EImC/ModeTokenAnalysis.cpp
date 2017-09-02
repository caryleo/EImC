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
	keywords.insert(pair<string, Tag>("in", KEY_IN));
	keywords.insert(pair<string, Tag>("out", KEY_OUT));
}

Tag Keywords::getTag(string name)/*��ѯ�ؼ���*/ {
	return keywords.find(name) != keywords.end() ? keywords[name] : IDT;
}

Token::Token() {}

Token::Token(Tag t, int l, int c) {
	tag = t;
	line = l;
	col = c;
}

Idt::Idt() {}

Idt::Idt(string s, int l, int c) {
	tag = IDT;
	name = s;
	line = l;
	col = c;
}

SoInt::SoInt(short n, int l, int c) {
	tag = NUM;
	val = n;
	line = l;
	col = c;
}

SoReal::SoReal(float f, int l, int c) {
	tag = RNUM;
	val = f;
	line = l;
	col = c;
}

SoString::SoString(string s, int l, int c) {
	tag = STRING;
	str = s;
	line = l;
	col = c;
}

void ModeTokenAnalysis::read(ModeRead& mRead)/*�����������*/ {
	Token* t;
	char ch = ' ';
	t = ModeTokenAnalysis::getToken(mRead, ch);
	while (t != NULL)
	{
		buffer.push_back(t);
		t = ModeTokenAnalysis::getToken(mRead, ch);
	}
	cout << "Token Analysis Completed." << endl;
}
Token* ModeTokenAnalysis::getToken(ModeRead& mRead, char & ch) {/*ʶ�����ؿ���ģ��*/
	while (ch != -1) {
		if (ch == ' ' || ch == '\n' || ch == '\t') {/*������ʽ��*/
			ch = mRead.scan();
			continue;
		}
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {/*��ʶ��*/
			return ModeTokenAnalysis::getIdt(mRead, ch);
		}
		if (ch >= '0' && ch <= '9') {/*���ֳ���*/
			return ModeTokenAnalysis::getNum(mRead, ch);
		}
		if (ch == '"') {/*�ַ�������*/
			return ModeTokenAnalysis::getString(mRead, ch);
		}
		if (ch == '+')/*�Ӻ�*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(ADD, l, c);
		}
		if (ch == '-')/*����*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(SUB, l, c);
		}
		if (ch == '*')/*�˺�*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(MUL, l, c);
		}
		if (ch == '/')/*���Ż�ע��*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			if (ch == '/') {
				do {
					ch = mRead.scan();
				} while (ch != '\n');
				return ModeTokenAnalysis::getToken(mRead, ch);
			}
			return new Token(DIV, l, c);
		}
		if (ch == '%')/*ȡ��*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(MOD, l, c);
		}
		if (ch == '&')/*�߼���*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			if (ch == '&') {
				ch = mRead.scan();
				return new Token(AND, l, c);
			}
			else {
				cout << "ERROR!!!" << endl;
				return NULL;
			}
		}
		if (ch == '|')/*�߼���*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			if (ch == '|') {
				ch = mRead.scan();
				return new Token(OR, l, c);
			}
			else {
				cout << "ERROR!!!" << endl;
				return NULL;
			}
		}
		if (ch == '!')/*�߼���*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(NOT, l, c);
		}
		if (ch == '>')/*���ڻ���ڵ���*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			if (ch == '=') {
				ch = mRead.scan();
				return new Token(GE, l, c);
			}
			else {
				return new Token(GT, l, c);
			}
		}
		if (ch == '<')/*С�ڡ�С�ڵ��ڻ򲻵���*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			if (ch == '=') {
				ch = mRead.scan();
				return new Token(LE, l, c);
			}
			else if (ch == '>') {
				ch = mRead.scan();
				return new Token(NEQU, l, c);
			}
			else {
				return new Token(LT, l, c);
			}
		}
		if (ch == '=')/*��ֵ�����*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			if (ch == '=') {
				ch = mRead.scan();
				return new Token(EQU, l, c);
			}
			else {
				return new Token(ASSIGN, l, c);
			}
		}
		if (ch == '(')/*��С����*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(LPAR, l, c);
		}
		if (ch == ')')/*��С����*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(RPAR, l, c);
		}
		if (ch == ']')/*��������*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(LBRACK, l, c);
		}
		if (ch == ']')/*��������*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(RBRACK, l, c);
		}
		if (ch == '{')/*�������*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(LBRACE, l, c);
		}
		if (ch == '}')/*�Ҵ�����*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(RBRACE, l, c);
		}
		if (ch == ',')/*����*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(COMMA, l, c);
		}
		if (ch == ';')/*�ֺ�*/ {
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(SEMICO, l, c);
		}
		if (ch == '$') /*��Ԫ��*/{
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(DOLLA, l, c);
		}
		if (ch == '#') /*����*/{
			int l = mRead.getLine();
			int c = mRead.getCol();
			ch = mRead.scan();
			return new Token(HASH, l, c);
		}
	}
	return NULL;
}

Token * ModeTokenAnalysis::getIdt(ModeRead & mRead, char & ch) {
	int l = mRead.getLine();
	int c = mRead.getCol();
	string name = "";
	do {
		name += ch;
		ch = mRead.scan();
	} while (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9');
	Keywords kw;
	Tag tag = kw.getTag(name);
	if (tag == IDT) {
		return new Idt(name, l, c);
	}
	else {
		return new Token(tag, l, c);
	}
}

Token * ModeTokenAnalysis::getNum(ModeRead & mRead, char & ch) {
	int l = mRead.getLine();
	int c = mRead.getCol();
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
		return new SoReal(val2, l, c);
	}
	else {
		return new SoInt(val1, l, c);
	}
}

Token * ModeTokenAnalysis::getString(ModeRead & mRead, char & ch) {
	int l = mRead.getLine();
	int c = mRead.getCol();
	string str = "";
	ch = mRead.scan();
	while (ch != '"') {
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
		ch = mRead.scan();
	}
	ch = mRead.scan();
	return new SoString(str, l, c);
}