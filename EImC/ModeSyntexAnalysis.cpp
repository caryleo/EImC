#include "stdafx.h"
#include "EImC.h"
#include "ModeSyntexAnalysis.h"

vector <Block*> CodeStore;

Block::Block()
{
}

Block::Block(Tag t)
{
	tag = t;
}

SoWhile::SoWhile(Token * t, Token * b, Token * cETop, Token * cEBottom)
{
	tag = WHILE;
	top = t;
	bottom = b;
	conditionExprTop = cETop;
	conditionExprBottom = cEBottom;
}

SoIf::SoIf(Token * t, Token * b, Token * jETop, Token * jEBottom)
{
	tag = IF;
	top = t;
	bottom = b;
	judgeExprTop = jETop;
	judgeExprBottom = jEBottom;
}

SoElse::SoElse(Token * t, Token * b)
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

AltExpr::AltExpr(Token * t, Token * b)
{
	tag = STATE;
	top = t;
	bottom = b;
}

Expr::Expr(Token * t, Token * b)
{
	tag = EXPR;
	top = t;
	bottom = b;
}
void ModeSyntexAnalysis::getHeadAndTail(Token *h,Token *t)
{
    subStart=h;
    subEnd=t+1;
}
void ModeSyntexAnalysis::statement()
{
    while(look!=(*subEnd))
    {
        switch(look->tag)
        {
            case KEY_WHILE:
                whileStat();
                break;
            case KEY_IF:
                 ifStat();
                 break;
            case KEY_ELSE:
                 elseStat();
                 break;
            case KEY_BRK:
                 brkStat();
                 break;
            case KEY_CON:
                 conStat();
            case KEY_RET:
                 retStat();
                 break;
            case IDT:
                 exprStat();
                 break;
            default:
                 altExprStat();
        }
    }

}
void ModeSyntexAnalysis::brkStat()
{
    AltExpr now(subStart,subEnd);
    now.tag=KEY_BRK;
    CodeStore.push_back(now);
    return ;
}
void ModeSyntexAnalysis::retStat()
{
    AltExpr now(subSart,subEnd);
    now.tag=KEY_RET;
    CodeStore.push_back(now);
    return ;
}

void ModeSyntexAnalysis::sMove()
{
    look=*it//读入下一个词法记号
    it++;
}
bool ModeSyntexAnalysis::match(Tag need)
{
    if(look->tag==need)
    {
        sMove();
        return 1;
    }
    else
        return 0;
}
void ModeSyntexAnalysis::whileStat()//while语义分析
{
    match(KEY_WHILE);
    SoWhile now;
    now.tag=KEY_WHILE;
    now.conditionExprTop=it;
    while(!match(LBRACE))
    {
        conditionExprBottom=it;
        Smove();
    }
    now.top=it;
    int cnt=1;
    while(it!=subEnd||cnt!=0)
    {
        now.bottom=it;
        if(match(LBRACE))
            cnt++;
        else if(match(RBRACE))
            cnt--;
        else
            sMove();
    }
    if(it!=subEnd||cnt!=0)
    {
        cout<<"Error"<<endl;
        return ;
    }
    CodeStore.push_back(now);
    return ;
}
void ModeSyntexAnalysis::ifStat()
{
    match(KEY_IF);
    soIf now;
    now.tag=KEY_IF;
    now.judgeExprTop=it;
    while(!match(LBRACE))
    {
        now.judgeExprBottom=it;
        sMove();
    }
    now.top=it;
    int cnt=1;
    while(it!=subEnd&&cnt!=0)
    {
        now.bottom=it;
        if(match(LBRACE))
            cnt++;
        else if(match(RBRACE))
            cnt--;
        else
            sMove();
    }
    if(it!=subEnd||cnt!=0)
    {
        cout<<"Error!!!"<<endl;//报错模块
        return ;
    }
    CodeStore.push_back(now);
    return ;
}
void ModeSyntexAnalysis::elseStat()
{
    match(KEY_ELSE);
    soElse now;
    now.tag=KEY_ELSE;
    now.top=it;
    while(it!=subEnd&&cnt!=0)
    {
        now.bottom=it;
        if(match(LBRACE))
            cnt++;
        else if(match(RBRACE))
            cnt--;
        else
            sMove();
    }
    if(it!=subEnd||cnt!=0)
    {
        cout<<"Error"<<endl; //报错模块
        return ;
    }
    CodeStore.push_back(now);
    return ;
}
void ModeSyntexAnalysis::altExprStat()
{
    AltExpr now;
    now.tag=STATE;
    now.top=it;
    if(!match(KEY_INT))
        if(!match(KEY_REAL))
            if(!match(KEY_STRING))
            {
                cout<<"Error"<<endl;
                return ;
            }
    while(!match(SEMICO)&&it!=subEnd)
    {
        now.bottom=it;
        sMove();
    }
    CodeStore.push_back(now);
    return ;
}
void ModeSyntexAnalysis::exprStat()
{
    match(IDT);
    Expr now;
    now.tag=EXPR;
    now.top=it;
    while(!match(SEMICO)&&it!=subEnd)
    {
        now.bottom=it;
        sMove();
    }
    CodeStore.push_back(now);
    return ;
}

