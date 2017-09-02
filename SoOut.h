#include"EImC.h"
using namespace std;
extern vector<Token*>buffer;

class SoOut{
public:
    static void print(int top,int bottom);//输出语句
    static bool isValid(int top,int bottom);//判断out语句是否合法
    static void judgeIdt(int m);//用过来分析Idt的类型并输出
    static void judgeString(int m);//用来输出string
};

