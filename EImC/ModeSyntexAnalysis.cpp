
//#include "stdafx.h"
#include "EImC.h"
#include "ModeSyntexAnalysis.h"
#include "ModeTokenAnalysis.h"
std::vector<Token*>buffer;
vector <Block*> CodeStore;//����洢��

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
            case KEY_WHILE:  //while����
                {
                    if(whileStat()) break;
                    else return 0;
                }
            case KEY_IF:    //if����
                {
                    if(ifStat()) break;
                    else return 0;
                }
            case KEY_ELSE:      //else����
                {
                    if(elseStat()) break;
                    else return 0;
                }
            case KEY_BRK:       //break����
                {
                    if(brkStat()) break;
                    else return 0;
                }
            case KEY_CON:       //continue����
                {
                    if(conStat()) break;
                    else return 0;
                }
            case KEY_RET:       //return����
                {
                    if(retStat()) break;
                    else return 0;
                }
            case IDT:       //�������á����ʽ����
                {
                    if(distinguish()) break;
                    else return 0;
                }
            default:    //�������������������������붨������
                {
                    if(altExprStat()) break;
                    else return 0;
                }

        }
    }
    return 1;
}

bool ModeSyntexAnalysis::distinguish()//���ָñ��ʽ�Ǻ������û��Ǳ������ʽ
{
    match(IDT);
    Block* now = new Block;
    if(look->tag==LPAR)     //��������,topΪ��������bottomΪ�����ŵ�λ��,tagΪCALL
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
    else        //�������ʽ,topΪ��������bottomΪ�ֺ�ǰһ����λ��,tagΪEXPR
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

bool ModeSyntexAnalysis::brkStat() //break���飬tagΪKEY_BRK
{
    match(KEY_BRK);
	AltExpr * now = new AltExpr(it-1, it);
	now->tag = KEY_BRK;
	if(!match(SEMICO))
        return 0;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::retStat()     //return���,bottom�Ƿֺ�ǰ�ĵ�һ��λ�ã�tagΪKEY_RET
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
bool ModeSyntexAnalysis::conStat() //continue��䣬bottomΪcontinue�ؼ��ֵ�λ��,tagΪKEY_CON
{
	AltExpr *now = new AltExpr(it,it);
	match(KEY_CON);
	if(!match(SEMICO)) return 0;
	now->tag = KEY_CON;
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::inStat() //in��䣬bottomΪ�ֺ�ǰһ��λ�ã�tagΪKEY_IN
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
bool ModeSyntexAnalysis::outStat()//out��䣬bottomΪ�ֺ�ǰһ��λ�ã�tagΪKEY_OUT
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
	look = buffer[it++];//������һ���ʷ��Ǻ�
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
bool ModeSyntexAnalysis::whileStat()//while�������,�޴�����
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
bool ModeSyntexAnalysis::ifStat()//if���������޴�����
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
bool ModeSyntexAnalysis::altExprStat() //���ֺ������������������������붨������
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
            if(look->tag==LPAR)    //��������������
            {
                sMove();
                if(!funStat(nowTag,nowName)) return 0;
            }
            else if(look->tag==ASSIGN)  //���������붨��
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


bool ModeSyntexAnalysis::funStat(Tag retType,string name)   //��������������
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


