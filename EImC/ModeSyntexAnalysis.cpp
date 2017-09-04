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
<<<<<<< HEAD
void ModeSyntexAnalysis::getHeadAndTail(int h,int t)
=======
void ModeSyntexAnalysis::getHeadAndTail(Token *h, Token *t)
>>>>>>> dd3093159baf3c545940eb3e518ffd0513ed3f22
{
	subStart = h;
	subEnd = t;
}
void ModeSyntexAnalysis::statement()
{
<<<<<<< HEAD
    while(look != subEnd)
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
                 distinguish();
                 break;
            default:
                 altExprStat();
        }
    }
=======
	while (look != subEnd)
	{
		switch (look->tag)
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
>>>>>>> dd3093159baf3c545940eb3e518ffd0513ed3f22

}
void ModeSyntexAnalysis::distinguish()
{
    if()

    Idt *tmp=(*Idt)look;
    string tmpName=tmp1->name;




}
void ModeSyntexAnalysis::brkStat()
{
	AltExpr * now = new AltExpr(subStart, subEnd);
	now->tag = KEY_BRK;
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::retStat()
{
	AltExpr * now = new AltExpr(subStart, subEnd);
	now->tag = KEY_RET;
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::conStat()
{
	AltExpr *now = new AltExpr(subStart,subEnd);
	now->tag = KEY_CON;
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::inStat()
{
	match(KEY_IN);
	while (!match(SEMICO))
		sMove();
	return;
}
void ModeSyntexAnalysis::outStat()
{
	match(KEY_OUT);
	while (!match(SEMICO))
		sMove();
	return;
}
void ModeSyntexAnalysis::sMove()
{
<<<<<<< HEAD
	look = buffer[it++];//读入下一个词法记号
=======
	look = *it;//读入下一个词法记号
	it++;
>>>>>>> dd3093159baf3c545940eb3e518ffd0513ed3f22
}
bool ModeSyntexAnalysis::match(Tag need)
{
	if (look->tag == need)
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
	SoWhile * now = new SoWhile(NULL, NULL, NULL, NULL);
	now->conditionExprTop = *it;
	while (!match(LBRACE))
	{
		now->conditionExprBottom = *it;
		sMove();
	}
	now->top = *it;
	int cnt = 1;
	while (*it != subEnd || cnt != 0)
	{
		now->bottom = *it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	if (*it != subEnd || cnt != 0)
	{
		cout << "Error" << endl;
		return;
	}
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::ifStat()
{
	match(KEY_IF);
	SoIf * now = new SoIf(NULL, NULL, NULL, NULL);
	now->judgeExprTop = *it;
	while (!match(LBRACE))
	{
		now->judgeExprBottom = *it;
		sMove();
	}
	now->top = *it;
	int cnt = 1;
	while (*it != subEnd&&cnt != 0)
	{
		now->bottom = *it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	if (*it != subEnd || cnt != 0)
	{
		cout << "Error!!!" << endl;//报错模块
		return;
	}
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::elseStat()
{
	match(KEY_ELSE);
	SoElse * now = new SoElse(NULL, NULL);
	now->tag = KEY_ELSE;
	now->top = *it;
	match(LBRACE);
	int cnt = 1;
	while (*it != subEnd&&cnt != 0)
	{
		now->bottom = *it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	if (*it != subEnd || cnt != 0)
	{
		cout << "Error" << endl; //报错模块
		return;
	}
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::altExprStat()
{
<<<<<<< HEAD
    AltExpr now;
    now.tag=STATE;
    now.top=it;
    Tag tmp;
    if(!match(KEY_INT))
    {
        if(!match(KEY_REAL))
        {
            if(!match(KEY_STRING))
            {
                cout<<"Error"<<endl;
                return ;
            }

            else
                tmp=KEY_STRING;
        }
        else
            tmp=KEY_REAL;
    }
    else
        tmp=KEY_INT;
    if(look->tag==IDT)
    {
        Idt s1=(*Idt)look;
        s1->name=look->name;
        sMove();
        if(match(ASSIGN))
        {
            Expr now = new Expr;
            now->top=it-2;
            while(!match(SEMICO)&&it<=subEnd)
            {
                sMove();
                now->bottom=it;
            }
            if(it>subEnd)
            {
                cout<<"Error"<<endl;
                return ;
            }
            CodeStore.push_back(now);
            return ;
        }
        else if(match(LPAR))
        {
            SoFunc now=new Expr;
            now->retType=tmp;
            now->name=s1->name;
            while(!match(RPAR))
            {
                if(match(IDT))
                {

                }
                else
                {
                   Idt s=new Idt;

                }
            }
            now->

        }
        else
        {
            cout<<"Error"<<endl;
            return ;
        }

    }
    else
    {
        cout<<"Error"<<endl;
        return ;
    }



            {
                cout<<"Error"<<endl;
                return ;
            }
    else Tag=KEY_INT;
    while(!match(SEMICO)&&it!=subEnd)
    {
        now.bottom=it;
        sMove();
    }
    CodeStore.push_back(now);
    return ;
=======
	AltExpr * now = new AltExpr(NULL, NULL);
	now->tag = STATE;
	now->top = *it;
	if (!match(KEY_INT))
		if (!match(KEY_REAL))
			if (!match(KEY_STRING))
			{
				cout << "Error" << endl;
				return;
			}
	while (!match(SEMICO) && *it != subEnd)
	{
		now->bottom = *it;
		sMove();
	}
	CodeStore.push_back(now);
	return;
>>>>>>> dd3093159baf3c545940eb3e518ffd0513ed3f22
}
void ModeSyntexAnalysis::exprStat()
{
	match(IDT);
	Expr * now = new Expr(NULL, NULL);
	now->tag = EXPR;
	now->top = *it;
	while (!match(SEMICO) && *it != subEnd)
	{
		now->bottom = *it;
		sMove();
	}
	CodeStore.push_back(now);
	return;
}

