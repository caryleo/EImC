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
	ModeExecute::assign(conTop, conBottom);
    Token *tmp=atom->calculate_expr(conTop ,conBottom );
    int now=atom->getIntVal(tmp);
    if(now==0)
        return 0;
    else
        return 1;

}
int ModeWhile::runWhile()
{
	ModeSyntexAnalysis mSA;
	while (calcu()) {
		PRTR *tmp = new PRTR(ebp);
		RunTime.push(tmp);
		RunTime.syncb();
		RunTime.sync();
		int ans = mSA.getHeadAndTail(top, bottom);
		if (ans == 0) {
			RunTime.desync();
			continue;
		}
		else if (ans == 1) {
			return 1;
		}
		else if (ans == 2) {
			RunTime.desync();
			continue;
		}
		else if (ans == 3) {
			RunTime.desync();
			break;
		}
	}
	return 0;
}

ModeDo::ModeDo(int _s, int _t, int _x, int _y) {
	top = _s;
	bottom = _t;
	conTop = _x;
	conBottom = _y;
}

bool ModeDo::calcu() {
	ExprIR *atom = new ExprIR;
	ModeExecute::assign(conTop, conBottom);
	Token *tmp = atom->calculate_expr(conTop, conBottom);
	int now = atom->getIntVal(tmp);
	if (now == 0)
		return 0;
	else
		return 1;
}

int ModeDo::runDo() {
	ModeSyntexAnalysis mSA;
	PRTR *tmp = new PRTR(ebp);
	RunTime.push(tmp);
	RunTime.syncb();
	RunTime.sync();
	int ans = mSA.getHeadAndTail(top, bottom);
	if (ans == 0) {
		RunTime.desync();
	}
	else if (ans == 1) {
		return 1;
	}
	else if (ans == 2) {
		RunTime.desync();
	}
	else if (ans == 3) {
		RunTime.desync();
		return 0;
	}
	while (!calcu()) {
		PRTR *tmp = new PRTR(ebp);
		RunTime.push(tmp);
		RunTime.syncb();
		RunTime.sync();
		int ans = mSA.getHeadAndTail(top, bottom);
		if (ans == 0) {
			RunTime.desync();
		}
		else if (ans == 1) {
			return 1;
		}
		else if (ans == 2) {
			RunTime.desync();
			continue;
		}
		else if (ans == 3) {
			RunTime.desync();
			break;
		}
	}
	return 0;
}
