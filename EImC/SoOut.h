#include"EImC.h"
using namespace std;

class SoOut{
public:
    static void print(int top,int bottom);//输出语句
    static bool isValid(int top,int bottom);//判断out语句是否合法
    static void judgeIdt(int m);//用过来分析Idt的类型并输出
};

