#include"EImC.h"
using namespace std;
extern vector<Token*>buffer;

class SoOut{
public:
    static void print(int top,int bottom);//������
    static bool isValid(int top,int bottom);//�ж�out����Ƿ�Ϸ�
    static void judgeIdt(int m);//�ù�������Idt�����Ͳ����
    static void judgeString(int m);//�������string
};

