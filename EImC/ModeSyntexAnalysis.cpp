
//#include "stdafx.h"
#include "EImC.h"
#include "ModeSyntexAnalysis.h"
#include "ModeTokenAnalysis.h"
std::vector<Token*>buffer;
vector <Block*> CodeStore;//语句块存储区

Block::Block()
{
}

Block::Block(Tag t)
{
	tag = t;
}

SoWhile::SoWhile(int t, int b, int cETop, int cEBottom)
{
	tag = WHILE;
	top = t;
	bottom = b;
	conditionExprTop = cETop;
	conditionExprBottom = cEBottom;
}

SoIf::SoIf(int t, int b, int jETop, int jEBottom)
{
	tag = IF;
	top = t;
	bottom = b;
	judgeExprTop = jETop;
	judgeExprBottom = jEBottom;
}

SoElse::SoElse(int t, int b)
{
	tag = ELSE;
	top = t;
	bottom = b;
}

SoFunc::SoFunc(string n, Tag r)
{
	tag = FUNC;
	retType = r;
	name = n;
}
Caller :: Caller(string n, vector<Token *> t) {
    tag = CALL;
	string name=n;
	paralist=t;
};

AltExpr::AltExpr(int t, int b)
{
	tag = STATE;
	top = t;
	bottom = b;
}

Expr::Expr(int t, int b)
{
	tag = EXPR;
	top = t;
	bottom = b;
}

bool ModeSyntexAnalysis::getHeadAndTail(int h,int t)
{
	subStart = h;
	subEnd = t;
	it=h;
	return statement();
}

bool ModeSyntexAnalysis::statement()
{
    while(it != subEnd+1)
    {
        switch(look->tag)
        {
            case KEY_WHILE:  //while语句块
                {
                    if(whileStat()) break;
                    else return 0;
                }
            case KEY_IF:    //if语句块
                {
                    if(ifStat()) break;
                    else return 0;
                }
            case KEY_ELSE:      //else语句块
                {
                    if(elseStat()) break;
                    else return 0;
                }
            case KEY_BRK:       //break语句块
                {
                    if(brkStat()) break;
                    else return 0;
                }
            case KEY_CON:       //continue语句块
                {
                    if(conStat()) break;
                    else return 0;
                }
            case KEY_RET:       //return语句块
                {
                    if(retStat()) break;
                    else return 0;
                }
            case IDT:       //函数调用、表达式语句块
                {
                    if(distinguish()) break;
                    else return 0;
                }
            default:    //函数定义与声明、变量声明与定义语句块
                {
                    if(altExprStat()) break;
                    else return 0;
                }

        }
    }
    return 1;
}

bool ModeSyntexAnalysis::distinguish()//区分该表达式是函数调用还是变量表达式
{
    match(IDT);
    Block* now = new Block;
    if(look->tag==LPAR)     //函数调用,top为函数名，bottom为右括号的位置,tag为CALL
    {
        now->tag=CALL;
        now->top=it-1;
        match(LPAR);
        int cnt=1;
        while((it!=subEnd+1)&&(!match(RPAR)))
        {
            now->bottom=it;
            sMove();
        }
        if(it==subEnd+1)
            return 0;
        if(!match(SEMICO)) return 0;
        CodeStore.push_back(now);
    }
    else        //变量表达式,top为变量名，bottom为分号前一个的位置,tag为EXPR
    {
        now->tag=EXPR;
        now->top=it;
        sMove();
        while((it!=subEnd-1)&&(!match(SEMICO)))
        {
            now->bottom=it;
            sMove();
        }
        if(it==subEnd+1)
            return 0;
        CodeStore.push_back(now);
    }
    return 1;

}

bool ModeSyntexAnalysis::brkStat() //break语句块，tag为KEY_BRK
{
    match(KEY_BRK);
	AltExpr * now = new AltExpr(it-1, it);
	now->tag = KEY_BRK;
	if(!match(SEMICO))
        return 0;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::retStat()     //return语句,bottom是分号前的第一个位置，tag为KEY_RET
{
	AltExpr * now = new AltExpr(it, it);
	match(KEY_RET);
	while((it!=subEnd+1)&&!match(SEMICO))
    {
        now->bottom=it;
        sMove();
    }
	now->tag = KEY_RET;
	if(it==subEnd+1)
        return 0;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::conStat() //continue语句，bottom为continue关键字的位置,tag为KEY_CON
{
	AltExpr *now = new AltExpr(it,it);
	match(KEY_CON);
	if(!match(SEMICO)) return 0;
	now->tag = KEY_CON;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::inStat() //in语句，bottom为分号前一个位置，tag为KEY_IN
{
    AltExpr *now = new AltExpr(it,it);
    now->tag=KEY_IN;
    match(KEY_IN);
	while ((it!=subEnd+1)&&(!match(SEMICO)))
    {
        now->bottom=it;
        sMove();
    }
    if(it==subEnd+1) return 0;
    CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::outStat()//out语句，bottom为分号前一个位置，tag为KEY_OUT
{
	AltExpr *now = new AltExpr(it,it);
    now->tag=KEY_OUT;
    match(KEY_OUT);
	while ((it!=subEnd+1)&&(!match(SEMICO)))
    {
        now->bottom=it;
        sMove();
    }
    if(it==subEnd+1) return 0;
    CodeStore.push_back(now);
	return 1;
}
void ModeSyntexAnalysis::sMove()
{
	look = buffer[it++];//读入下一个词法记号
}
bool ModeSyntexAnalysis::match(Tag need)
{
    if(need==TYPE)
    {
        if(match(KEY_REAL))
            return 1;
        if(match(KEY_STRING))
            return 1;
        if(match(KEY_INT))
            return 1;
        return 0;
    }
	if (look->tag == need)
	{
		sMove();
		return 1;
	}
	else
		return 0;
}
bool ModeSyntexAnalysis::whileStat()//while语义分析,无大括号
{
	SoWhile * now = new SoWhile(0, 0, 0, 0);
	now->tag=KEY_WHILE;
	match(KEY_WHILE);
	now->conditionExprTop = it;
	while ((it!=subEnd+1)&&(!match(LBRACE)))
	{
		now->conditionExprBottom = it;
		sMove();
	}
	if(it==subEnd+1)   return 0;
	now->top = it;
	int cnt = 1;
	while (it != subEnd+1 && cnt != 0)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	(now->bottom)=(now->bottom)-1;
	if(it==subEnd+1) return 0;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::ifStat()//if语句分析，无大括号
{
	SoIf * now = new SoIf(0, 0, 0, 0);
	now->tag=KEY_IF;
    match(KEY_IF);
	now->judgeExprTop = it;
	while ((it!=subEnd+1)&&(!match(LBRACE)))
	{
		now->judgeExprBottom = it;
		sMove();
	}
	if(it==subEnd+1) return 0;
	now->top = it;
	int cnt = 1;
	while (it != subEnd+1&&cnt != 0)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	(now->bottom)=(now->bottom)-1;
	if (it==subEnd+1)
        return 0;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::elseStat()
{
	match(KEY_ELSE);
	if(!match(LBRACE)) return 0;
	SoElse * now = new SoElse(it, 0);
	now->tag = KEY_ELSE;
	int cnt = 1;
	while ((it != subEnd+1)&&cnt != 0)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	(now->bottom)=(now->bottom)-1;
	if ( it==subEnd+1) return 0;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::altExprStat() //区分函数定义与声明、变量声明与定义语句块
{
    string nowName;
    Tag nowTag;
    if(look->tag==KEY_INT||look->tag==KEY_STRING||look->tag==KEY_REAL)
    {
        nowTag=look->tag;
        sMove();
        if(look->tag==IDT)
        {
            nowName=((Idt*)look)->name;
            sMove();
            if(look->tag==LPAR)    //函数定义与声明
            {
                sMove();
                if(!funStat(nowTag,nowName)) return 0;
            }
            else if(look->tag==ASSIGN)  //变量声明与定义
            {
                int st=it-2;
                sMove();
                int en=-1;
                while(!match(SEMICO)&&(it!=subEnd+1))
                {
                    en=it;
                    sMove();
                }
                if(it==subEnd+1) return 0;
                AltExpr *now=new AltExpr(st,en);
                CodeStore.push_back(now);
                return 1;
            }
            else
                return 0;

        }
        else
            return 0;
    }
    else
        return 0;
}


bool ModeSyntexAnalysis::funStat(Tag retType,string name)   //函数定义与声明
{
    SoFunc *now =new SoFunc(name,retType);
    now->tag=FUNC;
    Idt *q;
    while(it!=(subEnd+1))
    {
        if(look->tag==KEY_INT||look->tag==KEY_REAL||look->tag==KEY_STRING)
        {
            q=new Idt;
            q->assType=look->tag;
            sMove();
            if(look->tag==IDT)
            {
                q->name=((Idt*)look)->name;
                now->paralist.push_back(q);
                now->bottom=it;
                sMove();
                if(look->tag==COMMA)
                {
                    sMove();
                    continue;
                }
                if(look->tag==RPAR)
                {
                    sMove();
                    break;
                }
                return 0;
            }
            else return 0;
        }
        else   return 0;
    }
    if(it==subEnd+1)   return 0;
    if(!match(LBRACE))  return 0;
    now->top=it;
    int cnt=1;
    while(cnt!=0&&(it!=subEnd+1))
    {
        now->bottom=it;
        if(match(LBRACE))
            cnt++;
        else if(match(RBRACE))
            cnt--;
        else
            sMove();
    }
    if(it!=subEnd+1) return 0;
    CodeStore.push_back(now);
    return 1;
}


