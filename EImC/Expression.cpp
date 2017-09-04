#include"stdafx.h"
#include "Expression.h"
//KEY_INT, KEY_REAL, KEY_STRING,
Tag ExprIR::getValType(Idt IDT){
    return IDT.assType;
};
//��ѯ�ַ�����ֵ
string ExprIR::getStrVal(Idt Str){
    SoString * strp= (SoString*) Str.t;
    return strp->str;
};
//��ѯsoint��ֵ
short ExprIR::getIntVal(Idt Int){
    SoInt * intp=(SoInt*) Int.t;
    return intp->val;
};
//��ѯsoreal��ֵ
double ExprIR::getRealVal(Idt Real){
    SoReal *realp=(SoReal*) Real.t;
    return realp->val;
};
//��������ȼ�
//AND, OR, NOT,//�߼������
//ADD, SUB, MUL, DIV, MOD,//���������
//GT, GE, LT, LE, EQU, NEQU,//�Ƚ������
//LPAR, RPAR,//С����()
//DOLLA, HASH,//�������:��Ԫ�ţ�����
int ExprIR::oper_priority(Idt Oprator){
    switch(Oprator.assType)
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
};
//�ж����ȼ�
int ExprIR::judge_priority(Idt a,Idt b){
    if(oper_priority(a)<oper_priority(b)) return 1;
    else return 0;
}
//�ӷ�
Idt ExprIR::add_opr(Idt a,Idt b){
    Idt c;
    if(getValType(a)==KEY_STRING||getValType(b)==KEY_STRING)
    {
        c.assType=ERR;
        return c;
    }
    else if(getValType(a)==KEY_INT&&getValType(b)==KEY_INT)
    {
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(getIntVal(a)+getIntVal(b),0,0);
        c.t=ip;
    }
    else if(getValType(a)==KEY_REAL||getValType(b)==KEY_REAL)
    {
        c.assType=KEY_REAL;
        if(getValType(a)==KEY_REAL&&getValType(b)==KEY_INT)
        {
            SoReal *ip=new SoReal(getRealVal(a)+getIntVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_REAL&&getValType(b)==KEY_REAL)
        {
            SoReal *ip=new SoReal(getRealVal(a)+getRealVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_INT&&getValType(b)==KEY_REAL)
        {
            SoReal *ip=new SoReal (getIntVal(a)+getRealVal(b),0,0);
            c.t=ip;
        }
    }
    return c;
}
//����
Idt ExprIR::sub_opr(Idt a,Idt b){
    Idt c;
    if(getValType(a)==KEY_STRING||getValType(b)==KEY_STRING)
    {
        c.assType=ERR;
        return c;
    }
    else if(getValType(a)==KEY_INT&&getValType(b)==KEY_INT)
    {
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(getIntVal(a)-getIntVal(b),0,0);
        c.t=ip;
    }
    else if(getValType(a)==KEY_REAL||getValType(b)==KEY_REAL)
    {
        c.assType=KEY_REAL;
        if(getValType(a)==KEY_REAL&&getValType(b)==KEY_INT)
        {
            SoReal *ip=new SoReal(getRealVal(a)-getIntVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_REAL&&getValType(b)==KEY_REAL)
        {
            SoReal *ip=new SoReal(getRealVal(a)-getRealVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_INT&&getValType(b)==KEY_REAL)
        {
            SoReal *ip=new SoReal (getIntVal(a)-getRealVal(b),0,0);
            c.t=ip;
        }
    }
    return c;
}
//�˷�
Idt ExprIR::mul_opr(Idt a,Idt b){
    Idt c;
    if(getValType(a)==KEY_STRING||getValType(b)==KEY_STRING)
    {
        c.assType=ERR;
        return c;
    }
    else if(getValType(a)==KEY_INT&&getValType(b)==KEY_INT)
    {
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(getIntVal(a)*getIntVal(b),0,0);
        c.t=ip;
    }
    else if(getValType(a)==KEY_REAL||getValType(b)==KEY_REAL)
    {
        c.assType=KEY_REAL;
        if(getValType(a)==KEY_REAL&&getValType(b)==KEY_INT)
        {
            SoReal *ip=new SoReal(getRealVal(a)*getIntVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_REAL&&getValType(b)==KEY_REAL)
        {
            SoReal *ip=new SoReal(getRealVal(a)*getRealVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_INT&&getValType(b)==KEY_REAL)
        {
            SoReal *ip=new SoReal (getIntVal(a)*getRealVal(b),0,0);
            c.t=ip;
        }
    }
    return c;
}
//����
Idt ExprIR::div_opr(Idt a,Idt b){
    Idt c;
    if(getValType(a)==KEY_STRING||getValType(b)==KEY_STRING)
    {
        c.assType=ERR;
        return c;
    }
    else if(getValType(a)==KEY_INT&&getValType(b)==KEY_INT)
    {
        if(getIntVal(b)==0)
        {
            c.assType=ERR;
            return c;
        }
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(getIntVal(a)/getIntVal(b),0,0);
        c.t=ip;
    }
    else if(getValType(a)==KEY_REAL||getValType(b)==KEY_REAL)
    {
        c.assType=KEY_REAL;
        if(getValType(a)==KEY_REAL&&getValType(b)==KEY_INT)
        {
            if(getIntVal(b)==0)
            {
                c.assType=ERR;
                return c;
            }
            SoReal *ip=new SoReal(getRealVal(a)/getIntVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_REAL&&getValType(b)==KEY_REAL)
        {
            if(getRealVal(b)==0)
            {
                c.assType=ERR;
                return c;
            }
            SoReal *ip=new SoReal(getRealVal(a)/getRealVal(b),0,0);
            c.t=ip;
        }
        else if(getValType(a)==KEY_INT&&getValType(b)==KEY_REAL)
        {
            if(getRealVal(b)==0)
            {
                c.assType=ERR;
                return c;
            }
            SoReal *ip=new SoReal (getIntVal(a)/getRealVal(b),0,0);
            c.t=ip;
        }
    }
    return c;
};
//��
Idt ExprIR::mod_opr(Idt a,Idt b){
    Idt c;
    if(getValType(a)==KEY_INT&&getValType(b)==KEY_INT&&getIntVal(b)!=0)
    {
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(getIntVal(a)%getIntVal(b),0,0);
        c.t=ip;
    }
    else
    {
        c.assType=ERR;
    }
    return c;
};
//����
Idt ExprIR::pos_opr(Idt a){
    Idt c;
    if(getValType(a)==KEY_INT)
    {
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(getIntVal(a),0,0);
        c.t=ip;
    }
    else if(getValType(a)==KEY_REAL)
    {
        c.assType=KEY_REAL;
        SoReal *ip=new SoReal(getRealVal(a),0,0);
        c.t=ip;
    }
    else
    {
        c.assType=ERR;
    }
    return c;
};
//����
Idt ExprIR::neg_opr(Idt a){
    Idt c;
    if(getValType(a)==KEY_INT)
    {
        c.assType=KEY_INT;
        SoInt *ip=new SoInt(0-getIntVal(a),0,0);
        c.t=ip;
    }
    else if(getValType(a)==KEY_REAL)
    {
        c.assType=KEY_REAL;
        SoReal *ip=new SoReal(0-getRealVal(a),0,0);
        c.t=ip;
    }
    else
    {
        c.assType=ERR;
    }
    return c;
};
////��������$����
Idt ExprIR::connect_opr(Idt s1,Idt s2){
    Idt s;
    if(getValType(s1)==KEY_STRING&&getValType(s2)==KEY_STRING)
    {
        s.assType=KEY_STRING;
        SoString *ip=new SoString(getStrVal(s1)+getStrVal(s2),0,0);
    }
    else
    {
        s.assType=ERR;
    }
    return s;
};
//#ɾ��β��
Idt ExprIR::deltail_opr(Idt s){

};
