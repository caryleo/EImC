#include "ModeTokenAnalysis.h"

class ExprIR
{
public:
    //查询类型
    Tag getValType(Token *);
    //查询IDT asstype
    Tag getAsstype(Token *);
    //判断是否为IDT

    bool isIDT(Token *);
    //Token*向下转型为Idt*
    Idt* TransIDT(Token *);
    //Token*向下转型为SoString*
    SoString *TransStr(Token *);
    //Token*向下转型为SoInt*
    SoInt *TransInt(Token *);
    //Token*向下转型为SoReal*
    SoReal *TransReal(Token *);

    //查询值
    string getStrVal(Token *);
    short getIntVal(Token *);
    float getRealVal(Token *);

    //判断操作数,若不是操作数就是操作符
    bool isOperand(Token *);
    //运算符优先级
    int oper_priority(Token *);
    //判断运算符优先级
    bool judge_priority(Token * ,Token *);

    //算术运算：ADD,SUB,MUL,DIV,MOD
    Token * add_op(Token *,Token *);
    Token * sub_op(Token *,Token *);
    Token * mul_op(Token *,Token *);
    Token * div_op(Token *,Token *);
    Token * mod_op(Token *,Token *);
};
