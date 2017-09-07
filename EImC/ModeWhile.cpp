#include "stdafx.h"
#include"ModeExecute.h"
#include"ModeWhile.h"
#include"Expression.h"
#include"Stack.h"
#include "Expression.h"
extern Token ** esp, **ebp;	//运行栈的栈顶和栈底
extern Stack RunTime; //使用运行栈
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
    int now=expr.getIntVal(tmp);
    if(now==0)
        return 0;
    else
        return 1;

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
