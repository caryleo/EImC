#include "stdafx.h"
#include"ModeExecute.h"
#include"ModeWhile.h"
#include"Expression.h"
#include"Stack.h"
extern Token ** esp, **ebp;	//����ջ��ջ����ջ��
extern Stack RunTime; //ʹ������ջ
ModeWhile::ModeWhile(int _s,int _t,int _x,int _y)
{
    top=_s;
    bottom=_t;
    conTop=_x;
    conBottom=_y;
}
bool ModeWhile::calcu()
{
    ExprIR *atom=new ExprIR;
    Token *tmp=atom->calculate_expr(conTop ,conBottom );
    if(tmp->tag==NUM)
    {
        if(((SoInt*)tmp)->val==0)
            return 0;
        else
            return 1;
    }
    else if(tmp->tag==RNUM)
    {
        if(((SoReal*)tmp)->val==0)
            return 0;
        else
            return 1;
    }
    else
        return 0;
}
void ModeWhile::runWhile()
{
    if(calcu())
    {
        PRTR *tmp=new PRTR(ebp);
        RunTime.push(tmp);
        RunTime.sync(ebp);
        RunTime.sync(esp);
        ModeExecute::commence(top,bottom);
    }
    while(calcu())
        ModeExecute::commence(top,bottom);
    RunTime.desync(ebp, esp);
}
