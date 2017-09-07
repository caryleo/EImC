#include "stdafx.h"
#include "Expression.h"

extern vector<Token*>buffer;

//��ѯ����IDT,NUM,ADD��
//IDT: FUNC,NUM,RNUM,STRING,ERR

Tag ExprIR::getType(Token * t)
{
    if(isIDT(t)) return getAsstype(t);
    else return t->tag;
}
//��ѯIDT asstype
Tag ExprIR::getAsstype(Token *t)
{
    Idt *idt=(Idt*)t;
    return idt->assType;
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
    Idt *idt=(Idt*) token;
    if(idt->t==NULL) return 0;
    else return 1;
}


//��ѯSoStringֵ
string ExprIR::getStrVal(Token *token)
{
    if(token->tag==STRING)
    {
        SoString *so_string=new SoString;
        so_string=(SoString *) token;
        return so_string->str;
    }
    else
    {
        Idt *idt=new Idt;
        idt=(Idt*) token;
        SoString *so_string=new SoString;
        so_string= (SoString *)(idt->t);
        return so_string->str;
    }
}
//��ѯSoIntֵ
short ExprIR::getIntVal(Token *token)
{
    if(token->tag==NUM)
    {
        SoInt *so_int= new SoInt;
        so_int=(SoInt *) token;
        return so_int->val;
    }
    else
    {
        Idt *idt=new Idt;
        idt=(Idt*) token;
        SoInt *so_int=new SoInt;
        so_int= (SoInt *)(idt->t);
        return so_int->val;
    }
}
//��ѯSoRealֵ
float ExprIR::getRealVal(Token *token)
{
    if(token->tag==RNUM)
    {
        SoReal *so_real=new SoReal;
        so_real= (SoReal *) token;
        return so_real->val;
    }
    else
    {
        Idt *idt=new Idt;
        idt=(Idt*) token;
        SoReal *so_real=new SoReal;
        so_real= (SoReal *)(idt->t);
        return so_real->val;
    }
}
//�ж��Ƿ�Ϊ������
bool ExprIR::isOperand(Token * token)
{
    if(getType(token)==NUM||getType(token)==RNUM||getType(token)==STRING)
        return 1;
    else return 0;
}

//��������ȼ�
int ExprIR::oper_priority(Token * a, Token * b){
	int numa = icp(a->tag); //ջ��
	int numb = isp(b->tag);	//ջ��
	return numa > numb ? 1 :(numa == numb ? 0 : -1);
}

int ExprIR::isp(Tag tag){/*ջ��*/
	int ans = -1;
	switch(tag){
		case LPAR: ans = 1;break;
		case RPAR: ans = 16; break;
		case NOT: ans = 15; break;
		case MUL:
		case DIV:
		case MOD: ans = 13; break;
		case ADD:
		case SUB: ans = 11; break;
		case GT:
		case GE:
		case LT:
		case LE: ans = 9; break;
		case EQU:
		case NEQU: ans = 7; break;
		case AND: ans = 5; break;
		case OR: ans = 3; break;
		case END: ans = 0; break;
		default: ans = -1; break;
	}
	return ans;
}

int ExprIR::icp(Tag tag){/*ջ��*/
	int ans = -1;
	switch(tag){
		case LPAR: ans = 16;break;
		case RPAR: ans = 1; break;
		case NOT: ans = 14; break;
		case MUL:
		case DIV:
		case MOD: ans = 12; break;
		case ADD:
		case SUB: ans = 10; break;
		case GT:
		case GE:
		case LT:
		case LE: ans = 8; break;
		case EQU:
		case NEQU: ans = 6; break;
		case AND: ans = 4; break;
		case OR: ans = 2; break;
		case END: ans = 0; break;
		default: ans = -1; break;
	}
	return ans;
}



//�ӷ�
Token * ExprIR::add_op(Token * a,Token * b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(a)==STRING||getType(b)==STRING)
    {
        idt->assType=ERR;
    }
    else
    {
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            idt->assType=ERR;
            return res;
        }
        if(getType(a)==NUM&&getType(b)==NUM)
        {
            idt->assType=NUM;
            SoInt *so_int=new SoInt;
            idt->t=new SoInt;
            so_int=(SoInt*) idt->t;
            so_int->val=getIntVal(a)+getIntVal(b);
            //cout<<so_int->val<<endl;
        }
        else if(getType(a)==RNUM&&getType(b)==NUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)+getIntVal(b);
        }
        else if(getType(a)==NUM&&getType(b)==RNUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getIntVal(a)+getRealVal(b);
        }
        else
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)+getRealVal(b);
        }
    }
    return res;
}

//����
Token * ExprIR::sub_op(Token * a,Token * b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(a)==STRING||getType(b)==STRING)
    {
        idt->assType=ERR;
    }
    else
    {
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            idt->assType=ERR;
            return res;
        }
        if(getType(a)==NUM&&getType(b)==NUM)
        {
            idt->assType=NUM;
            SoInt *so_int=new SoInt;
            idt->t=new SoInt;
            so_int=(SoInt*) idt->t;
            so_int->val=getIntVal(a)-getIntVal(b);
            //cout<<so_int->val<<endl;
        }
        else if(getType(a)==RNUM&&getType(b)==NUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)-getIntVal(b);
        }
        else if(getType(a)==NUM&&getType(b)==RNUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getIntVal(a)-getRealVal(b);
        }
        else
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)-getRealVal(b);
        }
    }
    return res;
}

//�˷�
Token * ExprIR::mul_op(Token * a,Token * b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(a)==STRING||getType(b)==STRING)
    {
        idt->assType=ERR;
    }
    else
    {
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            idt->assType=ERR;
            return res;
        }
        if(getType(a)==NUM&&getType(b)==NUM)
        {
            idt->assType=NUM;
            SoInt *so_int=new SoInt;
            idt->t=new SoInt;
            so_int=(SoInt*) idt->t;
            so_int->val=getIntVal(a)*getIntVal(b);
            //cout<<so_int->val<<endl;
        }
        else if(getType(a)==RNUM&&getType(b)==NUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)*getIntVal(b);
        }
        else if(getType(a)==NUM&&getType(b)==RNUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getIntVal(a)*getRealVal(b);
        }
        else
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)*getRealVal(b);
        }
    }
    return res;
}

//����
Token * ExprIR::div_op(Token * a,Token * b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(b)==NUM&&getIntVal(b)==0||getType(b)==RNUM&&getRealVal(b)==0.0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==STRING||getType(b)==STRING)
    {
        idt->assType=ERR;
    }
    else
    {
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            idt->assType=ERR;
            return res;
        }
        if(getType(a)==NUM&&getType(b)==NUM)
        {
            idt->assType=NUM;
            SoInt *so_int=new SoInt;
            idt->t=new SoInt;
            so_int=(SoInt*) idt->t;
            so_int->val=getIntVal(a)/getIntVal(b);
            //cout<<so_int->val<<endl;
        }
        else if(getType(a)==RNUM&&getType(b)==NUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)/getIntVal(b);
        }
        else if(getType(a)==NUM&&getType(b)==RNUM)
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getIntVal(a)/getRealVal(b);
        }
        else
        {
            idt->assType=RNUM;
            SoReal *so_real=new SoReal;
            idt->t=new SoReal;
            so_real=(SoReal*) idt->t;
            so_real->val=getRealVal(a)/getRealVal(b);
        }
    }
    return res;
}

//��
Token * ExprIR::mod_op(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(a)==NUM&&getType(b)==NUM&&getIntVal(b)!=0)
    {
        if(isAssign(a)==0&&isAssign(b)==0)
        {
            idt->assType=ERR;
            return res;
        }
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        so_int->val=getIntVal(a)%getIntVal(b);
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}


//�ַ�������
Token * ExprIR::connect_op(Token * s1,Token *s2)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(s1)==STRING&&getType(s2)==STRING)
    {
        if(isAssign(s1)==0&&isAssign(s2)==0)
        {
            idt->assType=ERR;
        }
        idt->assType=STRING;
        SoString *so_string=new SoString;
        idt->t=new SoString;
        so_string=(SoString*) idt->t;
        so_string->str=getStrVal(s1)+getStrVal(s2);
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//ɾ��ָ��λ���ַ�����ԭ�ַ��������˸���
Token * ExprIR::delete_spec(Token *s,Token *pos)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(s)==STRING&&getType(pos)==NUM)
    {
        if(isAssign(s)==0&&isAssign(pos)==0)
        {
            idt->assType=ERR;
            return res;
        }
        if(getIntVal(pos)>=getStrVal(s).size())
        {
            idt->assType=ERR;
            return res;
        }
        idt->assType=STRING;
        SoString *so_string=new SoString;
        idt->t=new SoString;
        so_string=(SoString*) idt->t;
        so_string->str=getStrVal(s).erase(getIntVal(pos),1);
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//ɾ�����һ���ַ�
Token * ExprIR::delete_tail(Token *s)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(s)==STRING)
    {
        if(isAssign(s)==0)
        {
            idt->assType=ERR;
            return res;
        }
        idt->assType=STRING;
        SoString *so_string=new SoString;
        idt->t=new SoString;
        so_string=(SoString*) idt->t;
        so_string->str=getStrVal(s).erase(getStrVal(s).size()-1,1);
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//����
Token * ExprIR::is_greater(Token * a,Token * b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==STRING&&getType(b)==STRING)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getStrVal(a)>getStrVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==NUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getIntVal(a)>getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==RNUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getRealVal(a)>getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==RNUM&&getType(b)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getRealVal(a)>getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==NUM&&getType(b)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getRealVal(a)>getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//���ڵ���
Token * ExprIR::not_less(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(is_less(a,b))==ERR)
    {
        idt->assType=ERR;
    }
    else
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        so_int->val=!getIntVal(is_less(a,b));
    }
    return res;
}

//С��
Token * ExprIR::is_less(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==STRING&&getType(b)==STRING)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getStrVal(a)<getStrVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==NUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getIntVal(a)<getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==RNUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getRealVal(a)<getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==RNUM&&getType(b)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getRealVal(a)<getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else if(getType(a)==NUM&&getType(b)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getRealVal(a)<getIntVal(b))
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//С�ڵ���
Token * ExprIR::not_greater(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(is_greater(a,b))==ERR)
    {
        idt->assType=ERR;
    }
    else
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        so_int->val=!getIntVal(is_greater(a,b));
    }
    return res;
}

//����
Token * ExprIR::is_equal(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==STRING&&getType(b)==STRING)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getStrVal(a)==getStrVal(b))
            so_int->val=1;
        else
            so_int->val=0;
    }
    else if(getType(a)==NUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getIntVal(a)==getIntVal(b))
            so_int->val=1;
        else
            so_int->val=0;
    }
    else if(getType(a)==RNUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(fabs(getRealVal(a)-getIntVal(b))<1e-8)
            so_int->val=1;
        else
            so_int->val=0;
    }
    else if(getType(a)==RNUM&&getType(b)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(fabs(getRealVal(a)-getRealVal(b))<1e-8)
            so_int->val=1;
        else
            so_int->val=0;
    }
    else if(getType(a)==NUM&&getType(b)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(fabs(getIntVal(a)-getRealVal(b))<1e-8)
            so_int->val=1;
        else
            so_int->val=0;
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//����
Token * ExprIR::not_equal(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(getType(is_equal(a,b))==ERR)
    {
        idt->assType=ERR;
    }
    else
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        so_int->val=!getIntVal(is_equal(a,b));
    }
    return res;
}

//��&& AND
Token * ExprIR::and_lop(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==NUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getIntVal(a)==0||getIntVal(b)==0)
        {
            so_int->val=0;
        }
        else so_int->val=1;
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//��||
Token * ExprIR::or_lop(Token *a,Token *b)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(isAssign(a)==0&&isAssign(b)==0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==NUM&&getType(b)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getIntVal(a)==1||getIntVal(b)==1)
        {
            so_int->val=1;
        }
        else so_int->val=0;
    }
    else
    {
        idt->assType=ERR;
    }
    return res;
}

//�ǣ�not
Token * ExprIR::not_lop(Token *a)
{
    Token *res=new Token;
    res->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) res;
    if(isAssign(a)==0)
    {
        idt->assType=ERR;
        return res;
    }
    if(getType(a)==NUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(getIntVal(a)!=0)
            so_int->val=0;
        else
            so_int->val=1;
    }
    else if(getType(a)==RNUM)
    {
        idt->assType=NUM;
        SoInt *so_int=new SoInt;
        idt->t=new SoInt;
        so_int=(SoInt*) idt->t;
        if(fabs(getRealVal(a)-0.0)<1e-8)
            so_int->val=1;
        else
            so_int->val=0;
    }
    return res;
}

//������ʽ��ֵ
//vector<Token*>buffer
Token * ExprIR::calculate_expr(int head,int tail)
{
    Token *result=new Token;
    result->tag=IDT;
    Idt *idt=new Idt;
    idt = (Idt*) result;

    pos=head;
    start=head;
    term=tail;
    Token *st=new Token;
    st->tag=END;
    operator_s.push(st);
    while(pos<=tail+1)
    {
        Token *now=new Token;
        if(pos==(tail+1))
        {
            now->tag=END;
            while(operator_s.size()>0)
            {
                Token * ex_op= new Token;
                ex_op=operator_s.front();
                if(oper_priority(ex_op,now)==0)
                {
                    operator_s.pop();
                    break;
                }
                if(find_op(ex_op)==-1)
                {
                    idt->assType=ERR;
                    return result;
                }
                operator_s.pop();
            }
        }
        //������
        else
            {
            now=buffer[pos];
            if(isOperand(now))//������ֱ����ջ
            {
                operand_s.push(now);
                //cout<<operand_s.size()<<endl;
                //if(getType(now)==NUM) cout<<getIntVal(now)<<endl;
            }
            //������
            else
            {
                //�����Ŵ������
                if((getType(now)==ADD||getType(now)==SUB)&&(pos==head||getType(buffer[pos-1])==LPAR))
                {
                    Token *zero=new Token;
                    zero->tag=NUM;
                    SoInt *so_int=(SoInt*) zero;
                    so_int->val=0;
                    operand_s.push(zero);
                }
                if(getType(now)==NOT)
                {
                    if(pos<term&&(getType(buffer[pos+1])==NUM||getType(buffer[pos+1])==LPAR||getType(buffer[pos+1])==RNUM))
                    {
                        int i=1;
                    }
                    else
                    {
                        idt->assType=ERR;
                        return result;
                    }
                }
                //���ȼ��ߣ�ֱ����ջ
                if(oper_priority(now,operator_s.front())==1) operator_s.push(now);
                //�����ȴ���ǰ����Ǹ�
                else
                {
                    if(getType(now)==RPAR||getType(now)==END)
                    {
                        while(operator_s.size()>0)
                        {
                            Token * ex_op= new Token;
                            ex_op=operator_s.front();
                            if(oper_priority(ex_op,now)==0)
                            {
                                operator_s.pop();
                                break;
                            }
                            if(find_op(ex_op)==-1)
                            {
                                idt->assType=ERR;
                                return result;
                            }
                            operator_s.pop();
                        }
                    }
                    else
                    {
                        if(solve_op(operator_s.front())==-1)
                        {
                            idt->assType=ERR;
                            return result;
                        }
                        operator_s.push(now);
                    }
                }
            }
        }
        pos++;
    }

    if(operand_s.size()==1&&operator_s.size()==0)
    {
        if(getType(operand_s.front())!=ERR)
        {
            result=operand_s.front();
        }
        else idt->assType=ERR;
    }
    else idt->assType=ERR;
    return result;
}

int ExprIR::solve_op(Token * op)
{
    if(find_op(op)==-1) return -1;
    operator_s.pop();
    return 0;
}

//ADD,SUB,MUL,DIV,MOD
//GT, GE, LT, LE, EQU, NEQU
//AND, OR, NOT
//LPAR, RPAR,

int ExprIR::find_op(Token *op)
{
    Token *num=new Token;
    switch(getType(op))
    {
    case ADD://���Ż��߼Ӻ�
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                num=add_op(b,a);
                operand_s.push(num);
            }
            else return -1;
            break;
        }
    case SUB:
        {
            if(operand_s.size()>=2)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                Token *b=operand_s.front();
                operand_s.pop();
                num=sub_op(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=mul_op(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=div_op(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=mod_op(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=is_greater(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=not_less(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=is_less(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=not_greater(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=is_equal(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=not_equal(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=and_lop(b,a);
                operand_s.push(num);
            }
            else return -1;
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
                num=or_lop(b,a);
                operand_s.push(num);
            }
            else return -1;
            break;
        }
    //�ǣ������ڲ���������������ǰ��
    case NOT:
        {
            if(operand_s.size()>=1)
            {
                Token *a=operand_s.front();
                operand_s.pop();
                num=not_lop(a);
                operand_s.push(num);
            }
            else return -1;
            break;
        }
    }
    return 0;
}
