
#include"Stack.h"
#include "Expression.h"

extern vector<Token*>buffer;

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
//��ѯ�Ƿ񱻸�ֵ
bool ExprIR::isAssign(Token *token)
{
    if(TransIDT(token)->t==NULL) return 0;
    else return 1;
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
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(a)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(a)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
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
        if(isAssign(s1)==0&&isAssign(s2)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
        TransIDT(res)->assType=STRING;
        TransStr(res)->str=getStrVal(s1)+getStrVal(s2);
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

//ɾ��ָ��λ���ַ�����ԭ�ַ��������˸���
Token * ExprIR::delete_spec(Token *s,Token *pos)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(s)==STRING&&getAsstype(pos)==NUM)
    {
        if(isAssign(s)==0&&isAssign(pos)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
        if(getIntVal(pos)>=getStrVal(s).size())
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
        TransIDT(res)->assType=STRING;
        TransStr(res)->str=getStrVal(s).erase(getIntVal(pos),1);
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

//ɾ�����һ���ַ�
Token * ExprIR::delete_tail(Token *s)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(s)==STRING)
    {
        if(isAssign(s)==0)
        {
            TransIDT(res)->assType=ERR;
            return res;
        }
        TransIDT(res)->assType=STRING;
        TransStr(res)->str=getStrVal(s).erase(getStrVal(s).size()-1,1);
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

//����
Token * ExprIR::is_greater(Token * a,Token * b)
{
    Token *res;
    res->tag=IDT;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==STRING&&getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=NUM;
        if(getStrVal(a)>getStrVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getIntVal(a)>getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getRealVal(a)>getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==RNUM&&getAsstype(b)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(getRealVal(a)>getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(getRealVal(a)>getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

//���ڵ���
Token * ExprIR::not_less(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(TransIDT(is_less(a,b))->assType==ERR)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        TransIDT(res)->assType=NUM;
        TransInt(res)->val=!getIntVal(is_less(a,b));
    }
    return res;
}

//С��
Token * ExprIR::is_less(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==STRING&&getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=NUM;
        if(getStrVal(a)<getStrVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getIntVal(a)<getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getRealVal(a)<getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==RNUM&&getAsstype(b)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(getRealVal(a)<getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(getRealVal(a)<getIntVal(b))
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

//С�ڵ���
Token * ExprIR::not_greater(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(TransIDT(is_greater(a,b))->assType==ERR)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        TransIDT(res)->assType=NUM;
        TransInt(res)->val=!getIntVal(is_greater(a,b));
    }
    return res;
}

//����
Token * ExprIR::is_equal(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==STRING&&getAsstype(b)==STRING)
    {
        TransIDT(res)->assType=NUM;
        if(getStrVal(a)==getStrVal(b))
            TransInt(res)->val=1;
        else
            TransInt(res)->val=0;
    }
    else if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getIntVal(a)==getIntVal(b))
            TransInt(res)->val=1;
        else
            TransInt(res)->val=0;
    }
    else if(getAsstype(a)==RNUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(fabs(getRealVal(a)-getIntVal(b))<1e-8)
            TransInt(res)->val=1;
        else
            TransInt(res)->val=0;
    }
    else if(getAsstype(a)==RNUM&&getAsstype(b)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(fabs(getRealVal(a)-getRealVal(b))<1e-8)
            TransInt(res)->val=1;
        else
            TransInt(res)->val=0;
    }
    else if(getAsstype(a)==NUM&&getAsstype(b)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(fabs(getIntVal(a)-getRealVal(b))<1e-8)
            TransInt(res)->val=1;
        else
            TransInt(res)->val=0;
    }
    else
    {
        TransIDT(res)->assType=ERR;
    }
    return res;
}

//����
Token * ExprIR::not_equal(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(getAsstype(is_equal(a,b))==ERR)
    {
        TransIDT(res)->assType=ERR;
    }
    else
    {
        TransIDT(res)->assType=NUM;
        TransInt(res)->val=!getIntVal(is_equal(a,b));
    }
    return res;
}

//��&& AND
Token * ExprIR::and_lop(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getIntVal(a)==0||getIntVal(b)==0)
        {
            TransInt(res)->val=0;
        }
        else TransInt(res)->val=1;
    }
    else
    {
       TransIDT(res)->assType=ERR;
    }
    return res;
}

//��||
Token * ExprIR::or_lop(Token *a,Token *b)
{
    Token *res;
    res->tag=IDT;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==NUM&&getAsstype(b)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getIntVal(a)==1||getIntVal(b)==1)
        {
            TransInt(res)->val=1;
        }
        else TransInt(res)->val=0;
    }
    else
    {
       TransIDT(res)->assType=ERR;
    }
    return res;
}

//�ǣ�not
Token * ExprIR::not_lop(Token *a)
{
    Token *res;
    res->tag=IDT;
    if(isAssign(a)==0)
    {
        TransIDT(res)->assType=ERR;
        return res;
    }
    if(getAsstype(a)==NUM)
    {
        TransIDT(res)->assType=NUM;
        if(getIntVal(a)!=0)
            TransInt(res)->val=0;
        else
            TransInt(res)->val=1;
    }
    else if(getAsstype(a)==RNUM)
    {
        TransIDT(res)->assType=NUM;
        if(fabs(getRealVal(a)-0.0)<1e-8)
            TransInt(res)->val=1;
        else
            TransInt(res)->val=0;
    }
    return res;
}

//������ʽ��ֵ
//vector<Token*>buffer
Token * ExprIR::calculate_expr(int head,int tail)
{
    pos=head;
    start=head;
    term=tail;
    while(pos<=tail)
    {
        //������
        if(isIDT(buffer[pos]))
        {
            operand_s.push(buffer[pos]);
        }
        else
        {
            if(pos==tail) operator_s.push(buffer[pos]);
            else
            {
                solve_op(buffer[pos]);
            }
        }
        pos++;
    }
    Token *result;
    result->tag=IDT;
    if(operator_s.size()==0&&operand_s.size()==1)
    {
        if(getAsstype(operand_s.front())!=ERR)
        {
            result=operand_s.front();
        }
        else TransIDT(result)->assType=ERR;
    }
    else TransIDT(result)->assType=ERR;
    return result;
}

void ExprIR::solve_op(Token * op)
{
    //����������ţ�����ջ����֮ǰ�Ĳ��������д���
    //ֱ�����������ţ��������ų�ջ
    if(getValType(op)==RPAR)
    {
        while(getValType(operator_s.front())!=LPAR&&operator_s.size()>0)
        {
            solve_op(operator_s.front());
            operator_s.pop();
        }
        if(operator_s.size()>0) operator_s.pop();
    }
    else
    {
        //������ջ��Ϊ�գ�ֱ����ջ
        //��ǰ��������ȼ���ջ��������ߣ���ջ
        if(judge_priority(op,operator_s.front()))
            operator_s.push(op);
        else
        {
            //��ǰ�����ȼ������ڵ�ǰ������Ľ��д���
            while(operator_s.size()>0&&judge_priority(op,operator_s.front())==0)
            {
                //���������Ž���
                if(getValType(operator_s.front())==LPAR) break;
                find_op(operator_s.front());
                operator_s.pop();
            }
            operator_s.push(op);
        }
    }
}

//ADD,SUB,MUL,DIV,MOD
//GT, GE, LT, LE, EQU, NEQU
//AND, OR, NOT
//LPAR, RPAR,

void ExprIR::find_op(Token *op)
{
    switch(getValType(op))
    {
    //���Ż��߼Ӻ�
    //λ�ڱ��ʽ��λ����λ�ڣ���߻���ֻʣ��һ��������Ϊ����
    case ADD:
        {
            if(pos==start||getValType(operator_s.front())==LPAR||operand_s.size()==1)
            {
                Token * a=operand_s.front();
                operand_s.pop();
                operand_s.push(pos_op(a));
            }
            else
            {
                if(operand_s.size()>=2)
                {
                    Token *a=operand_s.front();
                    operand_s.pop();
                    Token *b=operand_s.front();
                    operand_s.pop();
                    operand_s.push(add_op(a,b));
                }
                else return;
            }
            break;
        }
    case SUB:
        {
            if(pos==start||getValType(operator_s.front())==LPAR||operand_s.size()==1)
            {
                Token * a=operand_s.front();
                operand_s.pop();
                operand_s.push(neg_op(a));
            }
            else
            {
                if(operand_s.size()>=2)
                {
                    Token *a=operand_s.front();
                    operand_s.pop();
                    Token *b=operand_s.front();
                    operand_s.pop();
                    operand_s.push(sub_op(a,b));
                }
                else return;
            }
            break;
        }
    case MUL:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(mul_op(a,b));
            }
            else return;
            break;
        }
    case DIV:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(div_op(a,b));
            }
            else return;
            break;
        }
    case MOD:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(mod_op(a,b));
            }
            else return;
            break;
        }
    case GT:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(is_greater(a,b));
            }
            else return;
            break;
        }
    case GE:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(not_less(a,b));
            }
            else return;
            break;
        }
    case LT:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(is_less(a,b));
            }
            else return;
            break;
        }
    case LE:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(not_greater(a,b));
            }
            else return;
            break;
        }
    case EQU:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(is_equal(a,b));
            }
            else return;
            break;
        }
    case NEQU:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(not_equal(a,b));
            }
            else return;
            break;
        }
    case AND:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(and_lop(a,b));
            }
            else return;
            break;
        }
    case OR:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                operand_s.push(or_lop(a,b));
            }
            else return;
            break;
        }
    //�ǣ������ڲ���������������ǰ��
    case NOT:
        {
            if(pos<term&&getValType(buffer[pos+1])==IDT)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                operand_s.push(not_lop(a));
            }
            else return;
            break;
        }
    }
}
