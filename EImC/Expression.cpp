#include "stdafx.h"
#include "Expression.h"

extern vector<Token*>buffer;

//查询类型IDT,NUM,ADD等
//IDT: FUNC,NUM,RNUM,STRING,ERR

Tag ExprIR::getType(Token * t)
{
	if (isIDT(t)) return getAsstype(t);
	else return t->tag;
}
//查询IDT asstype
Tag ExprIR::getAsstype(Token *t)
{
	Idt *idt = new Idt;
	idt = (Idt*)t;
	return idt->assType;
}
//判断是否为IDT
bool ExprIR::isIDT(Token * t)
{
	if (t->tag == IDT) return 1;
	else return 0;
}
//查询是否被赋值
bool ExprIR::isAssign(Token *token)
{
	if (isIDT(token))
	{
		Idt *idt = (Idt*)token;
		if ((idt->t == NULL)) return 0;
	}
	else return 1;
	return 1;
}


//查询SoString值
string ExprIR::getStrVal(Token *token)
{
	if (token->tag == STRING)
	{
		SoString *so_string = new SoString;
		so_string = (SoString *)token;
		return so_string->str;
	}
	else
	{
		Idt *idt = new Idt;
		idt = (Idt*)token;
		SoString *so_string = new SoString;
		so_string = (SoString *)(idt->t);
		return so_string->str;
	}
}
//查询SoInt值
short ExprIR::getIntVal(Token *token)
{
	if (token->tag == NUM)
	{
		SoInt *so_int = new SoInt;
		so_int = (SoInt *)token;
		return so_int->val;
	}
	else
	{
		Idt *idt = new Idt;
		idt = (Idt*)token;
		SoInt *so_int = new SoInt;
		so_int = (SoInt *)(idt->t);
		return so_int->val;
	}
}
//查询SoReal值
float ExprIR::getRealVal(Token *token)
{
	if (token->tag == RNUM)
	{
		SoReal *so_real = new SoReal;
		so_real = (SoReal *)token;
		return so_real->val;
	}
	else
	{
		Idt *idt = new Idt;
		idt = (Idt*)token;
		SoReal *so_real = new SoReal;
		so_real = (SoReal *)(idt->t);
		return so_real->val;
	}
}
//判断是否为操作数
bool ExprIR::isOperand(Token * token)
{
	if (getType(token) == NUM || getType(token) == RNUM || getType(token) == STRING)
		return 1;
	else return 0;
}

//运算符优先级
int ExprIR::oper_priority(Token * a, Token * b) {
	int numa = icp(a->tag); //栈外
	int numb = isp(b->tag);	//栈内
	return numa > numb ? 1 : (numa == numb ? 0 : -1);
}

int ExprIR::isp(Tag tag) {/*栈内*/
	int ans = -1;
	switch (tag) {
	case LPAR: ans = 1; break;
	case RPAR: ans = 18; break;
	case NOT: ans = 17; break;
	case POW: ans = 14; break;
	case MUL:
	case DIV:
	case MOD:
	case HASH: ans = 13; break;
	case ADD:
	case SUB:
	case DOLLA: ans = 11; break;
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

int ExprIR::icp(Tag tag) {/*栈外*/
	int ans = -1;
	switch (tag) {
	case LPAR: ans = 18; break;
	case RPAR: ans = 1; break;
	case NOT: ans = 16; break;
	case POW: ans = 15; break;
	case MUL:
	case DIV:
	case MOD:
	case HASH: ans = 12; break;
	case ADD:
	case SUB:
	case DOLLA: ans = 10; break;
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



//加法
Token * ExprIR::add_op(Token * a, Token * b)
{
	Token *res = new Token;
	if (getType(a) == STRING || getType(b) == STRING)
	{
		res->tag = ERR;
		ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
	}
	else
	{
		if (isAssign(a) == 0 || isAssign(b) == 0)
		{
		    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
			res->tag = ERR;
			return res;
		}
		if (getType(a) == NUM&&getType(b) == NUM)
		{
			res->tag = NUM;
			SoInt *so_int = new SoInt;
			so_int = (SoInt*)res;
			so_int->val = getIntVal(a) + getIntVal(b);
		}
		else if (getType(a) == RNUM&&getType(b) == NUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a) + getIntVal(b);
		}
		else if (getType(a) == NUM&&getType(b) == RNUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getIntVal(a) + getRealVal(b);
		}
		else
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a) + getRealVal(b);
		}
	}
	return res;
}

//减法
Token * ExprIR::sub_op(Token * a, Token * b)
{
	Token *res = new Token;
	if (getType(a) == STRING || getType(b) == STRING)
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	else
	{
		if (isAssign(a) == 0 || isAssign(b) == 0)
		{
		    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
			res->tag = ERR;
			return res;
		}
		if (getType(a) == NUM&&getType(b) == NUM)
		{
			res->tag = NUM;
			SoInt *so_int = new SoInt;
			so_int = (SoInt*)res;
			so_int->val = getIntVal(a) - getIntVal(b);
			//cout<<so_int->val<<endl;
		}
		else if (getType(a) == RNUM&&getType(b) == NUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a) - getIntVal(b);
		}
		else if (getType(a) == NUM&&getType(b) == RNUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getIntVal(a) - getRealVal(b);
		}
		else
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a) - getRealVal(b);
		}
	}
	return res;
}

//乘法
Token * ExprIR::mul_op(Token * a, Token * b)
{
	Token *res = new Token;
	if (getType(a) == STRING || getType(b) == STRING)
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	else
	{
		if (isAssign(a) == 0 || isAssign(b) == 0)
		{
		    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
			res->tag = ERR;
			return res;
		}
		if (getType(a) == NUM&&getType(b) == NUM)
		{
			res->tag = NUM;
			SoInt *so_int = new SoInt;
			so_int = (SoInt*)res;
			so_int->val = getIntVal(a)*getIntVal(b);
			//cout<<so_int->val<<endl;
		}
		else if (getType(a) == RNUM&&getType(b) == NUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a)*getIntVal(b);
		}
		else if (getType(a) == NUM&&getType(b) == RNUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getIntVal(a)*getRealVal(b);
		}
		else
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a)*getRealVal(b);
		}
	}
	return res;
}

//除法
Token * ExprIR::div_op(Token * a, Token * b)
{
	Token *res = new Token;
	if (getType(b) == NUM&&getIntVal(b) == 0 || getType(b) == RNUM&&getRealVal(b) == 0.0)
	{
	    ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == STRING || getType(b) == STRING)
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	else
	{
		if (isAssign(a) == 0 || isAssign(b) == 0)
		{
		    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
			res->tag = ERR;
			return res;
		}
		if (getType(a) == NUM&&getType(b) == NUM)
		{
			res->tag = NUM;
			SoInt *so_int = new SoInt;
			so_int = (SoInt*)res;
			so_int->val = getIntVal(a) / getIntVal(b);
			//cout<<so_int->val<<endl;
		}
		else if (getType(a) == RNUM&&getType(b) == NUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a) / getIntVal(b);
		}
		else if (getType(a) == NUM&&getType(b) == RNUM)
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getIntVal(a) / getRealVal(b);
		}
		else
		{
			res->tag = RNUM;
			SoReal *so_real = new SoReal;
			so_real = (SoReal*)res;
			so_real->val = getRealVal(a) / getRealVal(b);
		}
	}
	return res;
}

//余
Token * ExprIR::mod_op(Token *a, Token *b)
{
	Token *res = new Token;
	if (getType(a) == NUM&&getType(b) == NUM&&getIntVal(b) != 0)
	{
		if (isAssign(a) == 0 || isAssign(b) == 0)
		{
		    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
			res->tag = ERR;
			return res;
		}
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		so_int->val = getIntVal(a) % getIntVal(b);
	}
	else
	{
	    if(getType(b) == NUM&&getIntVal(b) == 0)
        {
            ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
            EXPR.report();
        }
        else
        {
            ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
            EXPR.report();
        }
		res->tag = ERR;
	}
	return res;
}

//乘方
Token * ExprIR::pow_op(Token *a,Token *b)
{
    Token *res = new Token;
    if(getType(a)==STRING&&getType(b)==STRING)
    {
        ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
        res->tag=ERR;
        return res;
    }
    else
    {
        if(isAssign(a)==0||isAssign(b)==0)
        {
            ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
            res->tag=ERR;
            return res;
        }
        if(getType(a)==NUM&&getType(b)==NUM)
        {
            if(getIntVal(a)==0&&getIntVal(b)==0)
            {
                ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
                EXPR.report();
                res->tag=ERR;
                return res;
            }
            else
            {
                res->tag=RNUM;
                SoReal *so_real=new SoReal;
                so_real=(SoReal*) res;
                so_real->val=(float) pow(getIntVal(a),getIntVal(b));
            }
        }
        else if(getType(a)==RNUM&&getType(b)==NUM)
        {
            if(getRealVal(a)==0&&getIntVal(b)==0)
            {
                ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
                EXPR.report();
                res->tag=ERR;
                return res;
            }
            else
            {
                res->tag=RNUM;
                SoReal *so_real=new SoReal;
                so_real=(SoReal*) res;
                so_real->val=(float) pow(getRealVal(a),getIntVal(b));
            }
        }
        else if(getType(a)==NUM&&getType(b)==RNUM)
        {
            if(getIntVal(a)==0&&getRealVal(b)==0)
            {
                ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
                EXPR.report();
                res->tag=ERR;
                return res;
            }
            else
            {
                res->tag=RNUM;
                SoReal *so_real=new SoReal;
                so_real=(SoReal*) res;
                so_real->val=(float) pow(getIntVal(a),getRealVal(b));
            }
        }
        else if(getType(a)==RNUM&&getType(b)==RNUM)
        {
            if(getRealVal(a)==0&&getIntVal(b)==0)
            {
                ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
                EXPR.report();
                res->tag=ERR;
                return res;
            }
            else
            {
                res->tag=RNUM;
                SoReal *so_real=new SoReal;
                so_real=(SoReal*) res;
                so_real->val=(float) pow(getRealVal(a),getRealVal(b));
            }
        }
    }
    return res;
}

//字符串连接
Token * ExprIR::connect_op(Token * s1, Token *s2)
{
	SoString *res = new SoString;
	if (getType(s1) == STRING&&getType(s2) == STRING)
	{
		if (isAssign(s1) == 0 || isAssign(s2) == 0)
		{
		    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
            EXPR.report();
			res->tag = ERR;
			return res;
		}
		res->tag = STRING;
		res->str = getStrVal(s1) + getStrVal(s2);
	}
	else
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	return res;
}

//删除指定位置字符，对原字符串进行了更改
Token * ExprIR::delete_spec(Token *s, Token *pos)
{
	SoString *res = new SoString;
	if (getType(s) == STRING&&getType(pos) == NUM)
	{
		if (isAssign(s) == 0 || isAssign(pos) == 0)
		{
			ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
			EXPR.report();
			res->tag = ERR;
			return res;
		}
		if (getIntVal(pos) >= getStrVal(s).size())
		{
			ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
			EXPR.report();
			res->tag = ERR;
			return res;
		}
		res->tag = STRING;
		res->str = getStrVal(s).erase(getIntVal(pos), 1);
	}
	else
	{
		ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
		EXPR.report();
		res->tag = ERR;
	}
	return res;

}

//大于
Token * ExprIR::is_greater(Token * a, Token * b)
{
	Token *res = new Token;
	if (isAssign(a) == 0 || isAssign(b) == 0)
	{
	    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == STRING&&getType(b) == STRING)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getStrVal(a) > getStrVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == NUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getIntVal(a) > getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == RNUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getRealVal(a) > getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == RNUM&&getType(b) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getRealVal(a) > getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == NUM&&getType(b) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getRealVal(a) > getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	return res;
}

//大于等于
Token * ExprIR::not_less(Token *a, Token *b)
{
	Token *res = new Token;
	if (getType(is_less(a, b)) == ERR)
	{
		res->tag = ERR;
	}
	else
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		so_int->val = !getIntVal(is_less(a, b));
	}
	return res;
}

//小于
Token * ExprIR::is_less(Token *a, Token *b)
{
	Token *res = new Token;
	if (isAssign(a) == 0 || isAssign(b) == 0)
	{
	    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == STRING&&getType(b) == STRING)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getStrVal(a) < getStrVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == NUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getIntVal(a) < getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == RNUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getRealVal(a) < getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == RNUM&&getType(b) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getRealVal(a) < getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else if (getType(a) == NUM&&getType(b) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getRealVal(a) < getIntVal(b))
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	return res;
}

//小于等于
Token * ExprIR::not_greater(Token *a, Token *b)
{
	Token *res = new Token;
	if (getType(is_greater(a, b)) == ERR)
	{
		res->tag = ERR;
	}
	else
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		so_int->val = !getIntVal(is_greater(a, b));
	}
	return res;
}

//等于
Token * ExprIR::is_equal(Token *a, Token *b)
{
	Token *res = new Token;
	if (isAssign(a) == 0 || isAssign(b) == 0)
	{
	    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == STRING&&getType(b) == STRING)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getStrVal(a) == getStrVal(b))
			so_int->val = 1;
		else
			so_int->val = 0;
	}
	else if (getType(a) == NUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getIntVal(a) == getIntVal(b))
			so_int->val = 1;
		else
			so_int->val = 0;
	}
	else if (getType(a) == RNUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (fabs(getRealVal(a) - getIntVal(b)) < 1e-8)
			so_int->val = 1;
		else
			so_int->val = 0;
	}
	else if (getType(a) == RNUM&&getType(b) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (fabs(getRealVal(a) - getRealVal(b)) < 1e-8)
			so_int->val = 1;
		else
			so_int->val = 0;
	}
	else if (getType(a) == NUM&&getType(b) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (fabs(getIntVal(a) - getRealVal(b)) < 1e-8)
			so_int->val = 1;
		else
			so_int->val = 0;
	}
	else
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	return res;
}

//不等
Token * ExprIR::not_equal(Token *a, Token *b)
{
	Token *res = new Token;
	if (getType(is_equal(a, b)) == ERR)
	{
		res->tag = ERR;
	}
	else
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		so_int->val = !getIntVal(is_equal(a, b));
	}
	return res;
}

//与&& AND
Token * ExprIR::and_lop(Token *a, Token *b)
{
	Token *res = new Token;
	if (isAssign(a) == 0 || isAssign(b) == 0)
	{
	    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == NUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getIntVal(a) == 0 || getIntVal(b) == 0)
		{
			so_int->val = 0;
		}
		else so_int->val = 1;
	}
	else
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	return res;
}

//或||
Token * ExprIR::or_lop(Token *a, Token *b)
{
	Token *res = new Token;
	if (isAssign(a) == 0 || isAssign(b) == 0)
	{
	    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == NUM&&getType(b) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getIntVal(a) == 1 || getIntVal(b) == 1)
		{
			so_int->val = 1;
		}
		else so_int->val = 0;
	}
	else
	{
	    ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
	}
	return res;
}

//非，not
Token * ExprIR::not_lop(Token *a)
{
	Token *res = new Token;
	if (isAssign(a) == 0)
	{
	    ModeErrorReport EXPR(300, buffer[term]->line, buffer[term]->col);
        EXPR.report();
		res->tag = ERR;
		return res;
	}
	if (getType(a) == NUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (getIntVal(a) != 0)
			so_int->val = 0;
		else
			so_int->val = 1;
	}
	else if (getType(a) == RNUM)
	{
		res->tag = NUM;
		SoInt *so_int = new SoInt;
		so_int = (SoInt*)res;
		if (fabs(getRealVal(a) - 0.0) < 1e-8)
			so_int->val = 1;
		else
			so_int->val = 0;
	}
	else
    {
        ModeErrorReport EXPR(301, buffer[term]->line, buffer[term]->col);
        EXPR.report();
    }
	return res;
}

//计算表达式的值
//vector<Token*>buffer
Token * ExprIR::calculate_expr(int head, int tail)
{
	Token *result = new Token;

	pos = head;
	start = head;
	term = tail;
	Token *st = new Token;
	st->tag = END;
	operator_s.push(st);
	while (pos <= tail + 1)
	{
		Token *now = new Token;
		if (pos == (tail + 1))
		{
			now->tag = END;
			while (operator_s.size() > 0)
			{
				Token * ex_op = new Token;
				ex_op = operator_s.front();
				if (oper_priority(ex_op, now) == 0)
				{
					operator_s.pop();
					break;
				}
				if (solve_op(ex_op) == -1)
				{
				    ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
                    EXPR.report();
					result->tag = ERR;
					return result;
				}
				//operator_s.pop();
			}
		}
		//操作数
		else
		{
			now = buffer[pos];
			if (isOperand(now))//操作数直接入栈
			{
				operand_s.push(now);
			}
			//操作符
			else
			{
				//正负号处理加零
				if ((getType(now) == ADD || getType(now) == SUB) && (pos == head || getType(buffer[pos - 1]) == LPAR||getType(buffer[pos - 1]) ==GE||getType(buffer[pos - 1]) ==GT||getType(buffer[pos - 1]) ==LE||getType(buffer[pos - 1]) ==LT||getType(buffer[pos - 1]) ==EQU||getType(buffer[pos - 1]) ==NEQU))
				{
					SoInt *zero = new SoInt;
					zero->tag = NUM;
					zero->val = 0;
					operand_s.push(zero);
				}
				if (getType(now) == NOT)
				{
					if (pos < term && (getType(buffer[pos + 1]) == NUM || getType(buffer[pos + 1]) == LPAR || getType(buffer[pos + 1]) == RNUM))
					{
						int i = 1;
					}
					else
					{
					    ModeErrorReport EXPR(303, buffer[term]->line, buffer[term]->col);
                        EXPR.report();
						result->tag = ERR;
						return result;
					}
				}
                Token *ex_op=new Token;
                while(operator_s.size()>0)
                {
                    ex_op=operator_s.front();
                    if(oper_priority(now, ex_op) == 1)
                    {
                        operator_s.push(now);
                        if (getType(now) == HASH)
                        {
                            if (pos > start && (getType(buffer[pos - 1]) == STRING || getType(buffer[pos - 1]) == RPAR || getType(buffer[pos - 1]) == HASH))
                            {
                                if(pos<tail&&getType(buffer[pos+1])==NUM)
                                {
                                    int i=1;
                                }
                                else
                                {
                                    SoInt *last = new SoInt;
                                    last->tag = NUM;
                                    Token *temp=operand_s.front();
                                    if(getType(temp)==STRING)
                                    {
                                        last->val=getStrVal(temp).size()-1;
                                    }
                                    operand_s.push(last);
                                }
                            }
                        }
                        break;
                    }
                    else if(oper_priority(now, ex_op) == 0)
                    {
                        operator_s.pop();
                        break;
                    }
                    else if(oper_priority(now,ex_op)==-1)
                    {
                        if(solve_op(ex_op)==-1)
                        {
                            ModeErrorReport EXPR(302, buffer[term]->line, buffer[term]->col);
                            EXPR.report();
                            result->tag = ERR;
                        }
                    }
                }
            }
        }
		pos++;
	}

	if (operand_s.size() == 1 && operator_s.size() == 0)
	{
		if (getType(operand_s.front()) != ERR)
		{
			Token * bababa = operand_s.front();
			if (isIDT(bababa))
			{
				if (getType(operand_s.front()) == NUM)
				{
					Idt *idt = new Idt;
					idt = (Idt*)bababa;
					SoInt *temp = new SoInt;
					result->tag = NUM;
					temp = (SoInt*)result;
					temp->val = getIntVal(bababa);
				}
				else if (getType(operand_s.front()) == RNUM)
				{
					Idt *idt = new Idt;
					idt = (Idt*)bababa;
					SoReal *temp = new SoReal;
					result->tag = RNUM;
					temp = (SoReal*)result;
					temp->val = getRealVal(bababa);
				}
				else if (getType(operand_s.front()) == STRING)
				{
					SoString *temp = new SoString;
					temp->tag = STRING;
					temp->str = getStrVal(bababa);
					return temp;
				}
			}
			else result = operand_s.front();
		}
		else
        {
            ModeErrorReport EXPR(304, buffer[term]->line, buffer[term]->col);
            EXPR.report();
            result->tag = ERR;
        }
	}
	else
    {
        ModeErrorReport EXPR(304, buffer[term]->line, buffer[term]->col);
        EXPR.report();
        result->tag = ERR;
    }
	return result;
}

int ExprIR::solve_op(Token * op)
{
	if (find_op(op) == -1) return -1;
	operator_s.pop();
	return 0;
}

//ADD,SUB,MUL,DIV,MOD
//GT, GE, LT, LE, EQU, NEQU
//AND, OR, NOT
//LPAR, RPAR,

int ExprIR::find_op(Token *op)
{
	Token *num = new Token;
	switch (getType(op))
	{
	case ADD://正号或者加号
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = add_op(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case SUB:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = sub_op(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case MUL:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = mul_op(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case DIV:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = div_op(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case MOD:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = mod_op(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case GT:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = is_greater(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case GE:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = not_less(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case LT:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = is_less(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case LE:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = not_greater(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case EQU:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = is_equal(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case NEQU:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = not_equal(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case AND:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = and_lop(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case OR:
	{
		if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = or_lop(b, a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	//非！必须在操作数或者左括号前边
	case NOT:
	{
		if (operand_s.size() >= 1)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			num = not_lop(a);
			operand_s.push(num);
		}
		else return -1;
		break;
	}
	case DOLLA:
    {
        if (operand_s.size() >= 2)
		{
			Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num = connect_op(b,a);
			operand_s.push(num);
		}
		else return -1;
		break;
    }
    case HASH:
    {
        if(operand_s.size()>=2)
        {
            Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num= delete_spec(b,a);
			operand_s.push(num);
        }
        else return -1;
		break;
    }
    case POW:
    {
        if(operand_s.size()>=2)
        {
            Token *a = operand_s.front();
			operand_s.pop();
			Token *b = operand_s.front();
			operand_s.pop();
			num= pow_op(b,a);
			operand_s.push(num);
        }
        else return -1;
		break;
    }
	}
	return 0;
}
