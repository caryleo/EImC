#include<string>
#include"Stack.h"
#include "Expression.h"

//��ѯ����IDT,NUM,ADD��
//IDT: FUNC,NUM,RNUM,STRING,ERR

Tag ExprIR::getValType(Token * t)
{
    return t->tag;
}
//��ѯIDT asstype
Tag ExprIR::getAsstype(Token *t)
{
    return TransIDT(t)->assType;
}
//�ж��Ƿ�ΪIDT
bool ExprIR::isIDT(Token * t)
{
    if(t->tag==IDT) return 1;
    else return 0;
}
//��Tokenת��ΪIdt
Idt* ExprIR::TransIDT(Token * t)
{
    Idt *IDT;
    IDT= (Idt*)t;
    return IDT;
}
//Token*->SoString*
SoString* ExprIR::TransStr(Token *t)
{
    SoString *SoStr;
    SoStr=(SoString*) t;
    return SoStr;
}

//Token*->SoInt*
SoInt* ExprIR::TransInt(Token *t)
{
    SoInt *SoI;
    SoI=(SoInt*) t;
    return SoI;
}

//Token*->SoReal*
SoReal* ExprIR::TransReal(Token *t)
{
    SoReal *SoR;
    SoR=(SoReal*) t;
    return SoR;
}

//��ѯSoStringֵ
string ExprIR::getStrVal(Token *token)
{
    return TransStr(TransIDT(token)->t)->str;
}
//��ѯSoIntֵ
short ExprIR::getIntVal(Token *token)
{
    return TransInt(TransIDT(token)->t)->val;
}
//��ѯSoRealֵ
float ExprIR::getRealVal(Token *token)
{
    return TransReal(TransIDT(token)->t)->val;
}
//�ж��Ƿ�Ϊ������
bool ExprIR::isOperand(Token * token)
{
    if(token->tag==IDT)
        return 1;
    else return 0;
}

//��������ȼ�
int ExprIR::oper_priority(Token * token)
{
    switch(token->tag)
    {
        case LPAR: return 1;
        case NOT: return 2;
        case MUL:case DIV:case MOD: return 3;
        case DOLLA:case HASH: return 4;
        case GT: case GE: case LT: case LE: case EQU: case NEQU:
            return 5;
        case AND: return 6;
        case OR: return 7;
        case RPAR: return 8;
    }
}

//�ж���������ȼ�
bool ExprIR::judge_priority(Token* op_1,Token* op_2)
{
    if(oper_priority(op_1)<oper_priority(op_2))
        return 1;
    else return 0;
}

//�ӷ�
Token * ExprIR::add_op(Token * a,Token * b)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(a)==STRING||getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=NUM;
            TransInt(res)->val=getIntVal(a)+getIntVal(b);
        }
        else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)+getIntVal(b);
        }
        else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getIntVal(a)+getRealVal(b);
        }
        else
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)+getRealVal(b);
        }
    }
    return res;
}

//����
Token * ExprIR::sub_op(Token * a,Token * b)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(a)==STRING||getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=NUM;
            TransInt(res)->val=getIntVal(a)-getIntVal(b);
        }
        else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)-getIntVal(b);
        }
        else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getIntVal(a)-getRealVal(b);
        }
        else
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)-getRealVal(b);
        }
    }
    return res;
}

//�˷�
Token * ExprIR::mul_op(Token * a,Token * b)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(a)==STRING||getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=NUM;
            TransInt(res)->val=getIntVal(a)*getIntVal(b);
        }
        else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)*getIntVal(b);
        }
        else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getIntVal(a)*getRealVal(b);
        }
        else
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)*getRealVal(b);
        }
    }
    return res;
}

//����
Token * ExprIR::div_op(Token * a,Token * b)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(b)==NUM&&getIntVal(b)==0||getAsstype(b)==RNUM&&getRealVal(b)==0.0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==STRING||getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=NUM;
            TransInt(res)->val=getIntVal(a)/getIntVal(b);
        }
        else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)/getIntVal(b);
        }
        else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getIntVal(a)/getRealVal(b);
        }
        else
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a)/getRealVal(b);
        }
    }
    return res;
}

//��
Token * ExprIR::mod_op(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(a)==NUM&&getAsstype(b)==NUM&&getIntVal(b)!=0)
    {
        TransIDT(res)->assType=NUM;
        TransInt(res)->val=getIntVal(a)%getIntVal(b);
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}
//����
Token * ExprIR::pos_op(Token * a)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(a)==STRING)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        if(getAsstype(a)==NUM)
        {
            TransIDT(res)->assType=NUM;
            TransInt(res)->val=getIntVal(a);
        }
        else
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=getRealVal(a);
        }
    }
    return res;
}

//����
Token * ExprIR::neg_op(Token * a)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(a)==STRING)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        if(getAsstype(a)==NUM)
        {
            TransIDT(res)->assType=NUM;
            TransInt(res)->val=0-getIntVal(a);
        }
        else
        {
            TransIDT(res)->assType=RNUM;
            TransReal(res)->val=0-getRealVal(a);
        }
    }
    return res;
}

//�ַ�������
Token * ExprIR::connect_op(Token * s1,Token *s2)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(s1)==STRING&&getAsstype(s2)==STRING)
    {
        TransIDT(res)->assType=STRING;
        TransStr(res)->str=getStrVal(s1)+getStrVal(s2);
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

Token * delete_spec(Token *s,Token *pos)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(s)==STRING&&getAsstype(pos)==NUM)
    {
        TransIDT(res)->assType=STRING;
    }
}
