#ifndef MODEERRORREPORT_H_
#define MODEERRORREPORT_H_
#include <map>
#include <string>
class ModeErrorReport {
private:
	int errorCode;
	int line;
	int col;
	static std::map <int, std::string> content;
public:
	ModeErrorReport(int code, int l, int c);
	void report();
};

#endif // !MODEERRORREPORT_H_
#pragma once
