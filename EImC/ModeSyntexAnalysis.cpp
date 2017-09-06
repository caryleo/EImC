//#include "stdafx.h"
#include "EImC.h"
#include "ModeSyntexAnalysis.h"
#include "ModeTokenAnalysis.h"
#include "ModeExecute.h"
extern std::vector<Token*>buffer;
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
    int ss=buffer.size()-1;
    if(h<0||t>=buffer.size())
    {
        cout<<"Error in Syntex Analysis!"<<endl;
        return 0;
    }
	subStart = h;
	subEnd = t;
	it=h;
	look=buffer[h];
	if(statement())
    {
        cout<<"Syntex Analysis sucess!"<<endl;
        ModeExecute::commence(ss,buffer.size()-1);
        return 1;
    }
    else
    {
        cout<<"Error in Syntex Analysis!"<<endl;
        return 0;
    }

}

bool ModeSyntexAnalysis::statement()
{
    while(it != subEnd+1)
    {
        switch(look->tag)
        {
            case KEY_WHILE:  //while����
                {
                    //cout<<"while"<<endl;
                    if(whileStat()) break;
                    else return 0;

                }
            case KEY_IF:    //if����
                {
                    //cout<<"if"<<endl;
                    if(ifStat()) break;
                    else return 0;
                }
            case KEY_ELSE:      //else����
                {
                    //cout<<"else"<<endl;
                    if(elseStat()) break;
                    else return 0;
                }
            case KEY_BRK:       //break����
                {
                    //cout<<"break"<<endl;
                    if(brkStat()) break;
                    else return 0;
                }
            case KEY_CON:       //continue����
                {
                    //cout<<"continue"<<endl;
                    if(conStat()) break;
                    else return 0;
                }
            case KEY_RET:       //return����
                {
                    //cout<<"return"<<endl;
                    if(retStat()) break;
                    else return 0;
                }
            case IDT:       //�������á����ʽ����
                {
                    //cout<<"idt"<<endl;
                    if(distinguish()) break;
                    else return 0;
                }
            default:    //�������������������������붨������
                {
                    //cout<<"altExpr"<<endl;
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
    if(look->tag==LPAR)     //��������,topΪ��������bottomΪ�����ŵ�ǰһ��λ��,tagΪCALL
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
        if(cnt!=0)
        {
            delete now;
            return 0;
        }
        if(!match(SEMICO))
        {
            delete now;
            return 0;
        }
        CodeStore.push_back(now);
        return 1;
    }
    else        //�������ʽ,topΪ��������bottomΪ�ֺ�ǰһ����λ��,tagΪEXPR
    {
        now->tag=STATE;
        now->top=it;
        sMove();
        while(it!=subEnd+1)
        {
            if(!match(SEMICO))
            {
                now->bottom=it;
                sMove();
            }
            else
            {
                CodeStore.push_back(now);
                return 1;
            }
        }
        delete now;
        return 0;

    }
    return 1;

}

bool ModeSyntexAnalysis::brkStat() //break���飬tagΪKEY_BRK
{
    AltExpr * now = new AltExpr(it, it);
    now->tag = KEY_BRK;
    match(KEY_BRK);
	if(!match(SEMICO))
    {
        delete now;
        return 0;
    }
	CodeStore.push_back(now);
	return 1;
}

bool ModeSyntexAnalysis::retStat()     //return���,bottom�Ƿֺ�ǰ�ĵ�һ��λ�ã�tagΪKEY_RET
{
	AltExpr * now = new AltExpr(it, -1);
	now->tag=KEY_RET;
	match(KEY_RET);
	while(it!=subEnd+1)
    {
        if(!match(SEMICO))
        {
            now->bottom=it;
            sMove();
        }
        else
        {
            if(now->bottom==-1)
                return 0;
            CodeStore.push_back(now);
            return 1;
        }

    }
    delete now;
    return 0;
}

bool ModeSyntexAnalysis::conStat() //continue��䣬bottomΪcontinue�ؼ��ֵ�λ��,tagΪKEY_CON
{
	AltExpr *now = new AltExpr(it,it);
	now->tag = KEY_CON;
	match(KEY_CON);
	if(!match(SEMICO))
    {
        delete now;
        return 0;
    }
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::inStat() //in��䣬bottomΪ�ֺ�ǰһ��λ�ã�tagΪKEY_IN
{
    AltExpr *now = new AltExpr(it,it);
    now->tag=KEY_IN;
    match(KEY_IN);
	while (it!=subEnd+1)
    {
        if(!match(SEMICO))
        {
            now->bottom=it;
            sMove();
        }
        else
        {
            CodeStore.push_back(now);
            return 1;
        }

    }
    delete now;
    return 0;
}
bool ModeSyntexAnalysis::outStat()//out��䣬bottomΪ�ֺ�ǰһ��λ�ã�tagΪKEY_OUT
{
	AltExpr *now = new AltExpr(it,it);
    now->tag=KEY_OUT;
    match(KEY_OUT);
	while (it!=subEnd+1)
    {
        if(!match(SEMICO))
        {
            now->bottom=it;
            sMove();
        }
        else
        {
            CodeStore.push_back(now);
            return 1;
        }
    }
    delete now;
    return 0;
}
void ModeSyntexAnalysis::sMove()
{
    if(it<=subEnd)
        it++;
    if(it<=subEnd)
        look = buffer[it];//������һ���ʷ��Ǻ�
}
bool ModeSyntexAnalysis::match(Tag need)
{
    if(it==subEnd+1)
        return 0;
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
	now->tag=WHILE;
	match(KEY_WHILE);
	now->conditionExprTop = it;
    now->conditionExprBottom = -1;
	while (it!=subEnd+1)
	{
	    if(!match(LBRACE))
        {
            now->conditionExprBottom = it;
            sMove();
        }
        else
        {
            if(now->conditionExprBottom==-1)
                return 0;
            now->top = it;
            int cnt = 1;
            while ((it != subEnd+1 )&& cnt != 0)
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
            if(cnt!=0)
            {
                delete now;
                return 0;
            }
            CodeStore.push_back(now);
            return 1;
        }

	}
	delete now;
	return 0;
}

bool ModeSyntexAnalysis::ifStat()//if���������޴�����
{
	SoIf * now = new SoIf(0, 0, 0, 0);
	now->tag=IF;
    match(KEY_IF);
	now->judgeExprTop = it;
	now->judgeExprBottom = -1;
	while (it!=subEnd+1)
	{
	    if(!match(LBRACE))
        {
            now->judgeExprBottom = it;
            sMove();
        }
        else
        {
            if(now->judgeExprBottom==-1)
                return 0;
            now->top = it;
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
            if (cnt!=0)
            {
                delete now;
                return 0;
            }
            CodeStore.push_back(now);
            return 1;
        }

	}
    delete now;
	return 0;

}

bool ModeSyntexAnalysis::elseStat()
{

	match(KEY_ELSE);
	if(!match(LBRACE)) return 0;
    SoElse * now = new SoElse(it, it);
    now->tag = ELSE;
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
	if ( cnt!=0 )
    {
        delete now;
        return 0;
    }
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
            //cout<<nowName<<endl;
            sMove();
            if(look->tag==LPAR)    //��������������
            {
                sMove();
                if(!funStat(nowTag,nowName)) return 0;
                else return 1;
            }
            else if(look->tag==ASSIGN)  //���������붨��
            {
                int st=it-2;
                sMove();
                int en=-1;
                while(it!=subEnd+1)
                {
                    if(!match(SEMICO))
                    {
                        en=it;
                        sMove();
                    }
                    else
                    {
                        AltExpr *now=new AltExpr(st,en);
                        now->tag=STATE;
                        CodeStore.push_back(now);
                        return 1;
                    }

                }

                return 0;
            }
            else
                return 0;

        }
        else
            return 0;
    }
    else return 0;
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
        else if(look->tag==RPAR)
        {
            sMove();
            break;
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
    if(cnt!=0)
    {
        delete now;
        return 0;
    }
    CodeStore.push_back(now);
    return 1;
}


