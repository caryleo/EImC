//////////////////////////////////
////    1.转型有点问题
////    2.5*((10-1)/3),到最后乘号不能处理
//////////////////////////////////
//
#include "stdafx.h"
#include "Expression.h"
//
//extern vector<Token*>buffer;
//
////查询类型IDT,NUM,ADD等
////IDT: FUNC,NUM,RNUM,STRING,ERR
//
//Tag ExprIR::getType(Token * t)
//{
//    if(isIDT(t)) return getAsstype(t);
//    else return t->tag;
//}
////查询IDT asstype
//Tag ExprIR::getAsstype(Token *t)
//{
//    Idt *idt;
//    idt=(Idt*)t;
//    return idt->assType;
//}
////判断是否为IDT
//bool ExprIR::isIDT(Token * t)
//{
//    if(t->tag==IDT) return 1;
//    else return 0;
//}
////查询是否被赋值
//bool ExprIR::isAssign(Token *token)
//{
//    Idt *idt;
//    idt=(Idt*) token;
//    if(idt->t==NULL) return 0;
//    else return 1;
//}
//
//
////查询SoString值
//string ExprIR::getStrVal(Token *token)
//{
//    if(token->tag==STRING)
//    {
//        SoString *so_string;
//        so_string= (SoString *) token;
//        return so_string->str;
//    }
//    else
//    {
//        Idt *idt;
//        idt=(Idt*) token;
//        SoString *so_string;
//        so_string= (SoString *)(idt->t);
//        return so_string->str;
//    }
//}
////查询SoInt值
//short ExprIR::getIntVal(Token *token)
//{
//    if(token->tag==NUM)
//    {
//        SoInt *so_int;
//        so_int= (SoInt *) token;
//        return so_int->val;
//    }
//    else
//    {
//        Idt *idt;
//        idt=(Idt*) token;
//        SoInt *so_int;
//        so_int= (SoInt *)(idt->t);
//        return so_int->val;
//    }
//}
////查询SoReal值
//float ExprIR::getRealVal(Token *token)
//{
//    if(token->tag==RNUM)
//    {
//        SoReal *so_real;
//        so_real= (SoReal *) token;
//        return so_real->val;
//    }
//    else
//    {
//        Idt *idt;
//        idt=(Idt*) token;
//        SoReal *so_real;
//        so_real= (SoReal *)(idt->t);
//        return so_real->val;
//    }
//}
////判断是否为操作数
//bool ExprIR::isOperand(Token * token)
//{
//    if(getType(token)==NUM||getType(token)==RNUM||getType(token)==STRING)
//        return 1;
//    else return 0;
//}
//
////运算符优先级
//int ExprIR::oper_priority(Token * token)
//{
//    switch(token->tag)
//    {
//        case LPAR: return 1;
//        case NOT: return 2;
//        case MUL:case DIV:case MOD: return 3;
//        case DOLLA:case HASH: return 4;
//        case GT: case GE: case LT: case LE: case EQU: case NEQU:
//            return 5;
//        case AND: return 6;
//        case OR: return 7;
//        case RPAR: return 8;
//    }
//}
//
////判断运算符优先级
//bool ExprIR::judge_priority(Token* op_1,Token* op_2)
//{
//    if(oper_priority(op_1)<oper_priority(op_2))
//        return 1;
//    else return 0;
//}
//
////加法
//Token * ExprIR::add_op(Token * a,Token * b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    Idt *idt;
//    idt = (Idt*) res;
//    if(getType(a)==STRING||getType(b)==STRING)
//    {
//        idt->assType=ERR;
//    }
//    else
//    {
//        if(isAssign(a)==0&&isAssign(b)==0)
//        {
//            idt->assType=ERR;
//            return res;
//        }
//        if(getType(a)==NUM&&getType(b)==NUM)
//        {
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=getIntVal(a)+getIntVal(b);
//        }
//        else if(getType(a)==RNUM&&getType(b)==NUM)
//        {
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)+getIntVal(b);
//        }
//        else if(getType(a)==NUM&&getType(b)==RNUM)
//        {
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getIntVal(a)+getRealVal(b);
//        }
//        else
//        {
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)+getRealVal(b);
//        }
//    }
//    return res;
//}
//
////减法
//Token * ExprIR::sub_op(Token * a,Token * b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(a)==STRING||getType(b)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        if(isAssign(a)==0&&isAssign(b)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        if(getType(a)==NUM&&getType(b)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=getIntVal(a)-getIntVal(b);
//        }
//        else if(getType(a)==RNUM&&getType(b)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)-getIntVal(b);
//        }
//        else if(getType(a)==NUM&&getType(b)==RNUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getIntVal(a)-getRealVal(b);
//        }
//        else
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)-getRealVal(b);
//        }
//    }
//    return res;
//}
//
////乘法
//Token * ExprIR::mul_op(Token * a,Token * b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(a)==STRING||getType(b)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        if(isAssign(a)==0&&isAssign(b)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        if(getType(a)==NUM&&getType(b)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=getIntVal(a)*getIntVal(b);
//        }
//        else if(getType(a)==RNUM&&getType(b)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)+getIntVal(b);
//        }
//        else if(getType(a)==NUM&&getType(b)==RNUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getIntVal(a)*getRealVal(b);
//        }
//        else
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)*getRealVal(b);
//        }
//    }
//    return res;
//}
//
////除法
//Token * ExprIR::div_op(Token * a,Token * b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(b)==NUM&&getIntVal(b)==0||getType(b)==RNUM&&getRealVal(b)==0.0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==STRING||getType(b)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        if(isAssign(a)==0&&isAssign(b)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        if(getType(a)==NUM&&getType(b)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=getIntVal(a)/getIntVal(b);
//        }
//        else if(getType(a)==RNUM&&getType(b)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)+getIntVal(b);
//        }
//        else if(getType(a)==NUM&&getType(b)==RNUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getIntVal(a)/getRealVal(b);
//        }
//        else
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a)/getRealVal(b);
//        }
//    }
//    return res;
//}
//
////余
//Token * ExprIR::mod_op(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(a)==NUM&&getType(b)==NUM&&getIntVal(b)!=0)
//    {
//        if(isAssign(a)==0&&isAssign(b)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=getIntVal(a)%getIntVal(b);
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
////正号
//Token * ExprIR::pos_op(Token * a)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(a)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        if(isAssign(a)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        if(getType(a)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=getIntVal(a);
//        }
//        else
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=getRealVal(a);
//        }
//    }
//    return res;
//}
//
////负号
//Token * ExprIR::neg_op(Token * a)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(a)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        if(isAssign(a)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        if(getType(a)==NUM)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=NUM;
//            SoInt *so_int;
//            so_int=(SoInt*) idt->t;
//            so_int->val=-getIntVal(a);
//        }
//        else
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=RNUM;
//            SoReal *so_real;
//            so_real=(SoReal*) idt->t;
//            so_real->val=-getRealVal(a);
//        }
//    }
//    return res;
//}
//
////字符串连接
//Token * ExprIR::connect_op(Token * s1,Token *s2)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(s1)==STRING&&getType(s2)==STRING)
//    {
//        if(isAssign(s1)==0&&isAssign(s2)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//        }
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=STRING;
//        SoString *so_string;
//        so_string=(SoString*) idt->t;
//        so_string->str=getStrVal(s1)+getStrVal(s2);
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////删除指定位置字符，对原字符串进行了更改
//Token * ExprIR::delete_spec(Token *s,Token *pos)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(s)==STRING&&getType(pos)==NUM)
//    {
//        if(isAssign(s)==0&&isAssign(pos)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        if(getIntVal(pos)>=getStrVal(s).size())
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=STRING;
//        SoString *so_string;
//        so_string=(SoString*) idt->t;
//        so_string->str=getStrVal(s).erase(getIntVal(pos),1);
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////删除最后一个字符
//Token * ExprIR::delete_tail(Token *s)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(s)==STRING)
//    {
//        if(isAssign(s)==0)
//        {
//            Idt *idt;
//            idt = (Idt*) res;
//            idt->assType=ERR;
//            return res;
//        }
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=STRING;
//        SoString *so_string;
//        so_string=(SoString*) idt->t;
//        so_string->str=getStrVal(s).erase(getStrVal(s).size()-1,1);
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////大于
//Token * ExprIR::is_greater(Token * a,Token * b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(isAssign(a)==0&&isAssign(b)==0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==STRING&&getType(b)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getStrVal(a)>getStrVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==NUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getIntVal(a)>getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==RNUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getRealVal(a)>getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==RNUM&&getType(b)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getRealVal(a)>getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==NUM&&getType(b)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getRealVal(a)>getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////大于等于
//Token * ExprIR::not_less(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(TransIDT(is_less(a,b))->assType==ERR)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        so_int->val=!getIntVal(is_less(a,b));
//    }
//    return res;
//}
//
////小于
//Token * ExprIR::is_less(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(isAssign(a)==0&&isAssign(b)==0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==STRING&&getType(b)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getStrVal(a)<getStrVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==NUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getIntVal(a)<getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==RNUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getRealVal(a)<getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==RNUM&&getType(b)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getRealVal(a)<getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else if(getType(a)==NUM&&getType(b)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getRealVal(a)<getIntVal(b))
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////小于等于
//Token * ExprIR::not_greater(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(TransIDT(is_greater(a,b))->assType==ERR)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        so_int->val=!getIntVal(is_greater(a,b));
//    }
//    return res;
//}
//
////等于
//Token * ExprIR::is_equal(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(isAssign(a)==0&&isAssign(b)==0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==STRING&&getType(b)==STRING)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getStrVal(a)==getStrVal(b))
//            so_int->val=1;
//        else
//            so_int->val=0;
//    }
//    else if(getType(a)==NUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getIntVal(a)==getIntVal(b))
//            so_int->val=1;
//        else
//            so_int->val=0;
//    }
//    else if(getType(a)==RNUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(fabs(getRealVal(a)-getIntVal(b))<1e-8)
//            so_int->val=1;
//        else
//            so_int->val=0;
//    }
//    else if(getType(a)==RNUM&&getType(b)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(fabs(getRealVal(a)-getRealVal(b))<1e-8)
//            so_int->val=1;
//        else
//            so_int->val=0;
//    }
//    else if(getType(a)==NUM&&getType(b)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(fabs(getIntVal(a)-getRealVal(b))<1e-8)
//            so_int->val=1;
//        else
//            so_int->val=0;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////不等
//Token * ExprIR::not_equal(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(getType(is_equal(a,b))==ERR)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        so_int->val=!getIntVal(is_equal(a,b));
//    }
//    return res;
//}
//
////与&& AND
//Token * ExprIR::and_lop(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(isAssign(a)==0&&isAssign(b)==0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==NUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getIntVal(a)==0||getIntVal(b)==0)
//        {
//            so_int->val=0;
//        }
//        else so_int->val=1;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////或||
//Token * ExprIR::or_lop(Token *a,Token *b)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(isAssign(a)==0&&isAssign(b)==0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==NUM&&getType(b)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getIntVal(a)==1||getIntVal(b)==1)
//        {
//            so_int->val=1;
//        }
//        else so_int->val=0;
//    }
//    else
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//    }
//    return res;
//}
//
////非，not
//Token * ExprIR::not_lop(Token *a)
//{
//    Token *res=new Token;
//    res->tag=IDT;
//    if(isAssign(a)==0)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=ERR;
//        return res;
//    }
//    if(getType(a)==NUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(getIntVal(a)!=0)
//            so_int->val=0;
//        else
//            so_int->val=1;
//    }
//    else if(getType(a)==RNUM)
//    {
//        Idt *idt;
//        idt = (Idt*) res;
//        idt->assType=NUM;
//        SoInt *so_int;
//        so_int=(SoInt*) idt->t;
//        if(fabs(getRealVal(a)-0.0)<1e-8)
//            so_int->val=1;
//        else
//            so_int->val=0;
//    }
//    return res;
//}
//
////计算表达式的值
////vector<Token*>buffer
Token * ExprIR::calculate_expr(int head,int tail)
{
//    pos=head;
//    start=head;
//    term=tail;
//    while(pos<=tail)
//    {
//        //操作数
//        Token *now=new Token;
//        now=buffer[pos];
//        if(isOperand(now))
//        {
//            operand_s.push(now);
//            if(getType(now)==NUM) cout<<getIntVal(now)<<endl;
//        }
//        //操作符
//        else
//        {
//            if(operator_s.size()==0) operator_s.push(now);
//            else
//            {
//                solve_op(now);
//            }
//        }
//        pos++;
//    }
//    Token *result=new Token;
//    result->tag=IDT;
//    if(operator_s.size()==0&&operand_s.size()==1)
//    {
//        if(getType(operand_s.front())!=ERR)
//        {
//            result=operand_s.front();
//        }
//        else TransIDT(result)->assType=ERR;
//    }
//    else TransIDT(result)->assType=ERR;
//    return result;
	return 0;
}
//
//void ExprIR::solve_op(Token * op)
//{
//    //如果是右括号，不入栈，对之前的操作符进行处理
//    //直到遇到左括号，将左括号出栈
//    if(getType(op)==LPAR)
//    {
//        operator_s.push(op);
//        return;
//    }
//    if(getType(op)==RPAR)
//    {
//        while(operator_s.size()>0)
//        {
//			Token * now_op= new Token;
//			now_op=operator_s.front();
//			cout<<getType(now_op)<<endl;
//			if(getType(now_op)==LPAR) break;
//            find_op(operator_s.front());
//            operator_s.pop();
//			delete now_op;
//        }
//        if(operator_s.size()>0) operator_s.pop();
//    }
//    else
//    {
//        //操作符栈中为空，直接入栈
//        //当前运算符优先级比栈顶运算符高，入栈
//        Token * ex_op =operator_s.front();
//        if(judge_priority(op,ex_op)||ex_op->tag==LPAR)
//            operator_s.push(op);
//        else
//        {
//            //对前面优先级不低于当前运算符的进行处理
//            while(operator_s.size()>0&&judge_priority(op,ex_op)==0)
//            {
//                //遇到左括号结束
//                if(getType(ex_op)==LPAR) break;
//                find_op(ex_op);
//                operator_s.pop();
//            }
//            operator_s.push(op);
//        }
//    }
//    return;
//}
//
////ADD,SUB,MUL,DIV,MOD
////GT, GE, LT, LE, EQU, NEQU
////AND, OR, NOT
////LPAR, RPAR,
//
//void ExprIR::find_op(Token *op)
//{
//    switch(getType(op))
//    {
//    case ADD://正号或者加号
//        {
//            //位于表达式首位或者位于（后边
//            if(pos==start||getType(operator_s.front())==LPAR)
//            {
//                Token * a=operand_s.front();  //取操作数栈顶元素
//                operand_s.pop();              //栈顶元素出栈
//                operand_s.push(pos_op(a));    //将得到的新数入栈
//            }
//            else
//            {
//                //当操作数大于二的时候
//                if(operand_s.size()>=2)
//                {
//                    Token *a=operand_s.front();
//                    operand_s.pop();
//                    Token *b=operand_s.front();
//                    operand_s.pop();
//                    operand_s.push(add_op(a,b));
//                }
//                else return;
//            }
//            break;
//        }
//    case SUB:
//        {
//            //负号同正号
//            if(pos==start||getType(operator_s.front())==LPAR)
//            {
//                Token * a=operand_s.front();
//                operand_s.pop();
//                operand_s.push(neg_op(a));
//            }
//            else
//            {
//                if(operand_s.size()>=2)
//                {
//                    Token *a=operand_s.front();
//                    operand_s.pop();
//                    Token *b=operand_s.front();
//                    operand_s.pop();
//                    operand_s.push(sub_op(a,b));
//                }
//                else return;
//            }
//            break;
//        }
//    case MUL:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(mul_op(a,b));
//            }
//            else return;
//            break;
//        }
//    case DIV:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(div_op(a,b));
//            }
//            else return;
//            break;
//        }
//    case MOD:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(mod_op(a,b));
//            }
//            else return;
//            break;
//        }
//    case GT:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(is_greater(a,b));
//            }
//            else return;
//            break;
//        }
//    case GE:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(not_less(a,b));
//            }
//            else return;
//            break;
//        }
//    case LT:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(is_less(a,b));
//            }
//            else return;
//            break;
//        }
//    case LE:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(not_greater(a,b));
//            }
//            else return;
//            break;
//        }
//    case EQU:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(is_equal(a,b));
//            }
//            else return;
//            break;
//        }
//    case NEQU:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(not_equal(a,b));
//            }
//            else return;
//            break;
//        }
//    case AND:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(and_lop(a,b));
//            }
//            else return;
//            break;
//        }
//    case OR:
//        {
//            if(operand_s.size()>=2)
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                Token *b=operand_s.front();
//                operand_s.pop();
//                operand_s.push(or_lop(a,b));
//            }
//            else return;
//            break;
//        }
//    //非！必须在操作数或者左括号前边
//    case NOT:
//        {
//            if(pos<term&&(getType(buffer[pos+1])==IDT||getType(buffer[pos
//
//+1])==LPAR))
//            {
//                Token *a=operand_s.front();
//                operand_s.pop();
//                operand_s.push(not_lop(a));
//            }
//            else return;
//            break;
//        }
//    }
//    return ;
//}
