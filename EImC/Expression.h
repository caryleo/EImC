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

    //单目算数运算符：正负号规定正负号要带括号例如（-a）
    Token * pos_op(Token *);
    Token * neg_op(Token *);

    //字符串处理DOLLA, HASH
    //定义$不改变原字符串的值，#删除字符对原字符串进行更改
    Token * connect_op(Token *,Token *);
    Token * delete_spec(Token *,Token *);
    Token * delete_tail(Token *);

    //关系运算:>,< ,>=,<=,==,<>
    //GT, GE, LT, LE, EQU, NEQU
    Token * is_greater(Token *,Token *);
    Token * not_less(Token *,Token *);
    Token * is_less(Token *,Token *);
    Token * not_greater(Token *,Token *);
    Token * is_equal(Token *,Token *);
    Token * not_equal(Token *,Token *);

    //逻辑运算：&&与 | ||或 | !非
    //AND, OR, NOT
    Token * and_lop(Token *,Token *);
    Token * or_lop(Token *,Token *);
    Token * not_lop(Token *);

    Token * calculate_expr(int ,int );
    void find_op(Token *);
    void solve_op(Token *);
};
