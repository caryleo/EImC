
#include "stdafx.h"
#include "EImC.h"
#include "ModeSyntexAnalysis.h"
#include "ModeTokenAnalysis.h"
std::vector<Token*>buffer;
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
void ModeSyntexAnalysis::getHeadAndTail(int h,int t)
{
	subStart = h;
	subEnd = t;
	it=h;
}
void ModeSyntexAnalysis::statement()
{
    while(it != subEnd+1)
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
}

void ModeSyntexAnalysis::distinguish()//区分该表达式是函数调用还是变量表达式
{
    /*
    string nowName=((*Idt)look)->name;
    if(match(LPAR))
    {
        SoFunc now=new
        while(!match(RPAR))
        {
            if(look->tag==NUM||look->tag==IDT)

        }
    }
    else
    {
        cout<<"Error"<<endl;
        return ;
    }
    if()

    Idt *tmp=(*Idt)look;
    string tmpName=tmp1->name;


*/

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
void ModeSyntexAnalysis::whileStat()//while语义分析
{
	match(KEY_WHILE);
	SoWhile * now = new SoWhile(NULL, NULL, NULL, NULL);
	now->conditionExprTop = it;
	while (!match(LBRACE))
	{
		now->conditionExprBottom = it;
		sMove();
	}
	now->top = it;
	int cnt = 1;
	while (it != subEnd || cnt != 0)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	if (cnt != 0)
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
	now->judgeExprTop = it;
	while (!match(LBRACE))
	{
		now->judgeExprBottom = it;
		sMove();
	}
	now->top = it;
	int cnt = 1;
	while (it != subEnd&&cnt != 0)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	if ( cnt != 0)
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
	now->top = it;
	match(LBRACE);
	int cnt = 1;
	while (it != subEnd&&cnt != 0)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
	}
	if ( cnt != 0)
	{
		cout << "Error" << endl; //报错模块
		return;
	}
	CodeStore.push_back(now);
	return;
}
void ModeSyntexAnalysis::altExprStat()
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
            if(look->tag==LPAR)
            {
                sMove();
                funStat(nowTag,nowName);
            }
            else if(look->tag==ASSIGN)
            {
                int st=it-2;
                sMove();
                int en=-1;
                while(!match(SEMICO)&&(it!=subEnd+1))
                {
                    en=it;
                    sMove();
                }
                if(it==subEnd+1)
                {
                    cout<<"Error"<<endl;
                    return ;
                }
                AltExpr *now=new AltExpr(st,en);
                CodeStore.push_back(now);
            }

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
}


void ModeSyntexAnalysis::funStat(Tag retType,string name)
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
                    break;
                cout<<"Error"<<endl;
                return ;
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
    }
    if(it==subEnd+1)
    {
        cout<<"Error"<<endl;
        return;
    }
    match(RPAR);
    if(!match(LBRACE))
    {
        cout<<"Error"<<endl;
        return ;
    }
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
    if(cnt)
    {
        cout<<"Error"<<endl;
        return ;
    }
    CodeStore.push_back(now);
}

void ModeSyntexAnalysis::exprStat()
{
	match(IDT);
	Expr * now = new Expr(NULL, NULL);
	now->tag = EXPR;
	now->top = it;
	while (!match(SEMICO) && it != subEnd)
	{
		now->bottom = it;
		sMove();
	}
	CodeStore.push_back(now);
	return;
}

Caller::Caller(string n, vector<Token*> t)
{
	name = n;

}
