#include "ModeTokenAnalysis.h"

class ExprIR
{
public:
    //获取变量值
    Tag getValType(Idt);
    string getStrVal(Idt);
    short getIntVal(Idt);
    double getRealVal(Idt);

    //运算符优先级
    int oper_priority(Idt);
    //判断运算符优先级
    int judge_priority(Idt,Idt);
    //算数运算： +加 | -减 | *乘 | /除 | %余
    Idt add_opr(Idt,Idt);
    Idt sub_opr(Idt,Idt);
    Idt mul_opr(Idt,Idt);
    Idt div_opr(Idt,Idt);
    Idt mod_opr(Idt,Idt);
    //单目运算：+正 | -负
    Idt pos_opr(Idt);
    Idt neg_opr(Idt);
    //括号运算：(左括号 | )右括号
    //串操作：$连接 | #删一个字符
    Idt connect_opr(Idt,Idt);
    Idt deltail_opr(Idt);
    //Idt delspecial_opr(Idt,Idt);
    //关系运算：>大于 | <小于 | >=大于等于 | <=小于等于 | ==恒等 | <>不等
    //int Greater(Idt,Idt);
    //int Greater_equal(Idt,Idt);
    //int Less(Idt,Idt);
    //int Less_equal(Idt,Idt);
    //int Equal(Idt,Idt);
    //int NEqual(Idt,Idt);
    //逻辑运算：&&与 | ||或 | !非
    //int And_opr(Idt,Idt);
    //int Or_opr(Idt,Idt);
    //int Not_opr(Idt);
};
