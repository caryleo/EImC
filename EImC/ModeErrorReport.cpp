#include "stdafx.h"
#include "EImC.h"
#include "ModeErrorReport.h"
using namespace std;

ModeErrorReport::ModeErrorReport(int code, int l, int c)
{
	errorCode = code;
	line = l;
	col = c;
	content.insert(pair<int, string>(100, "couldn't find the file"));
	content.insert(pair<int, string>(150, "mismatch of mark \"&\""));
	content.insert(pair<int, string>(151, "mismatch of mark \"|\""));
	content.insert(pair<int, string>(152, "incorrect numeric formation"));
	content.insert(pair<int, string>(153, "incorrect formation of escape character"));
	content.insert(pair<int, string>(154, "irregular end of string"));
	content.insert(pair<int, string>(155, "illegal charactor"));
	content.insert(pair<int, string>(250, "mismatch of Else statements block"));
	content.insert(pair<int, string>(251, "incorrect statement")); 
	content.insert(pair<int, string>(201, "mismatch of brace"));
	content.insert(pair<int, string>(202, "mismatch of semicolon"));
	content.insert(pair<int, string>(203, "empty return value"));
	content.insert(pair<int, string>(204, "empty judge expression"));
	content.insert(pair<int, string>(205, "empty condition expression"));
	content.insert(pair<int, string>(206, "illegal defintion of variable"));
	content.insert(pair<int, string>(207, "illegal statement"));
	content.insert(pair<int, string>(208, "illegal expression"));
	content.insert(pair<int, string>(209, "illegal paralist"));
	content.insert(pair<int, string>(210, "redefinition of function"));
	content.insert(pair<int, string>(300, "uninitialized variable"));
	content.insert(pair<int, string>(301, "incorrect type of variables£¨string+num£©"));
	content.insert(pair<int, string>(302, "illegal operation"));
	content.insert(pair<int, string>(303, "illegal expression"));
	content.insert(pair<int, string>(304, "error operation"));
	content.insert(pair<int, string>(351, "redefinition of variable"));
	content.insert(pair<int, string>(352, "illegal definition"));
	content.insert(pair<int, string>(401, "illegal assignment"));
	content.insert(pair<int, string>(402, "undefined variable in assignment"));
	content.insert(pair<int, string>(403, "uninitialized variable in assignment"));
	content.insert(pair<int, string>(404, "mismatch of parameter type"));
	content.insert(pair<int, string>(451, "illegal parameter"));
	content.insert(pair<int, string>(501, "mismatch of function signature"));
	content.insert(pair<int, string>(750, "more than one input"));
	content.insert(pair<int, string>(751, "mismatch of input type"));
	content.insert(pair<int, string>(752, "incorrect input statement"));
	content.insert(pair<int, string>(753, "incorrect output formation"));
	content.insert(pair<int, string>(754, "minus number of output"));
	content.insert(pair<int, string>(755, "illegal output type"));
	content.insert(pair<int, string>(756, "undefined output variable"));
}

void ModeErrorReport::report()
{
	string ans = content[errorCode];
	cout << "Error Detected" << endl;
	cout << "Line£º" << line << endl;
	cout << "Cause£º" << ans << endl;
	exit(0);
}
