#include "stdafx.h"
#include "EImC.h"
#include "ModeSyntexAnalysis.h"
#include "ModeTokenAnalysis.h"
#include "ModeErrorReport.h"
#include "ModeExecute.h"
extern std::vector<Token*>buffer;
vector <Block*> CodeStore;//语句块存储区
extern vector<SoFunc *>FuncStore;
extern babababana retPos;
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
Caller::Caller(string n, vector<Token *> t) {
	tag = CALL;
	name = n;
	paralist = t;
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

DoUntil::DoUntil(int t, int b, int cETop, int cEBottom)
{
	tag = DOUNTIL;
	top = t;
	bottom = b;
	conditionExprTop = cETop;
	conditionExprBottom = cEBottom;
}


bool ModeSyntexAnalysis::getHeadAndTail(int h, int t)
{
	int ss = CodeStore.size();
	if (h < 0 || t >= buffer.size())
	{
		cout << "Error in Syntex Analysis!" << endl;
		return 0;
	}
	subStart = h;
	subEnd = t;
	it = h;
	look = buffer[h];
	if (statement())
	{
		cout << "Syntex Analysis sucess!" << endl;
		if (subStart == 0 && subEnd == buffer.size() - 1) {
			ModeExecute::init(ss, CodeStore.size() - 1);
		}
		else {
			ModeExecute::commence(ss, CodeStore.size() - 1);
		}

		return 1;
	}
	else
	{
		cout << "Error in Syntex Analysis!" << endl;
		code += 200;
		ModeErrorReport MER(code, l, r);
		MER.report();
		return 0;
	}

}
bool ModeSyntexAnalysis::hasRet()
{
	for (int i = 0; i < retPos.cnt; i++)
	{
		if (retPos.num[i] >= subStart&&retPos.num[i] <= subEnd)
			return 1;
	}
	return 0;
}
bool ModeSyntexAnalysis::statement()
{
	while (it != subEnd + 1)
	{
		switch (look->tag)
		{
		case KEY_WHILE:  //while语句块
		{
			//cout<<"while"<<endl;
			if (whileStat()) break;
			else return 0;

		}
		case KEY_DO: //do until语句
		{
			if (doStat()) break;
			else return 0;
		}
		case KEY_IF:    //if语句块
		{
			//cout<<"if"<<endl;
			if (ifStat()) break;
			else return 0;
		}
		case KEY_ELSE:      //else语句块
		{
			//cout<<"else"<<endl;
			if (elseStat()) break;
			else return 0;
		}
		case KEY_BRK:       //break语句块
		{
			//cout<<"break"<<endl;
			if (brkStat()) break;
			else return 0;
		}
		case KEY_CON:       //continue语句块
		{
			//cout<<"continue"<<endl;
			if (conStat()) break;
			else return 0;
		}
		case KEY_RET:       //return语句块
		{
			//cout<<"return"<<endl;
			if (retStat()) break;
			else return 0;
		}
		case IDT:       //函数调用、表达式语句块
		{
			//cout<<"idt"<<endl;
			if (distinguish()) break;
			else return 0;
		}
		case KEY_IN:    //in语句的语法
		{
			if (inStat()) break;
			else return 0;
		}
		case KEY_OUT:
		{
			if (outStat()) break;
			else return 0;
		}
		default:    //函数定义与声明、变量声明与定义语句块
		{
			//cout<<"altExpr"<<endl;
			if (altExprStat()) break;
			else return 0;
		}

		}
	}
	return 1;
}
bool ModeSyntexAnalysis::doStat() //do...until语句块
{
	match(KEY_DO);
	if (!match(LBRACE))
	{
		getError(look->line, look->col, 1);
		return 0;
	}
	DoUntil *now = new DoUntil(it, it, -1, -1);
	now->tag = DOUNTIL;
	int cnt = 1;
	while (it != subEnd + 1)
	{
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
		if (cnt == 0)
			break;
	}
	if (it == subEnd + 1)
	{
		delete now;
		getError(look->line, look->col, 1);
		return 0;
	}
	now->bottom = it - 2;
	if (match(KEY_UNTIL))
	{
		now->conditionExprTop = it;
		while (it != subEnd + 1)
		{
			if (look->tag != SEMICO) sMove();
			else
			{
				now->conditionExprBottom = it - 1;
				if ((now->conditionExprTop) > (now->conditionExprBottom))
				{
					getError(look->line, look->col, 5);
					delete now;
					return 0;
				}
				match(SEMICO);
				CodeStore.push_back(now);
				return 1;
			}
		}
		getError(look->line, look->col, 2);
		delete now;
		return 0;
	}
	else
	{
		delete now;
		getError(look->line, look->col, 11);
		return 0;
	}
}
bool ModeSyntexAnalysis::distinguish()//区分该表达式是函数调用还是变量表达式
{
	match(IDT);
	Block* now = new Block;
	if (look->tag == LPAR)     //函数调用,top为函数名，bottom为右括号的前一个位置,tag为CALL
	{
		now->tag = CALL;
		now->top = it - 1;
		match(LPAR);
		while ((it != subEnd + 1) && (!match(RPAR)))
		{
			now->bottom = it;
			sMove();
		}
		if (it == subEnd + 1)
		{
			delete now;
			getError(look->line, look->col, 1);
			return 0;
		}
		if (!match(SEMICO))
		{
			delete now;
			getError(look->line, look->col, 2);
			return 0;
		}
		CodeStore.push_back(now);
		return 1;
	}
	else        //变量表达式,top为变量名，bottom为分号前一个的位置,tag为EXPR
	{
		now->tag = STATE;
		now->top = it - 1;
		sMove();
		while (it != subEnd + 1)
		{
			if (!match(SEMICO))
			{
				now->bottom = it;
				sMove();
			}
			else
			{
				CodeStore.push_back(now);
				return 1;
			}
		}
		getError(look->line, look->col, 2);
		delete now;
		return 0;

	}
	return 1;

}

bool ModeSyntexAnalysis::brkStat() //break语句块，tag为KEY_BRK
{
	AltExpr * now = new AltExpr(it, it);
	now->tag = KEY_BRK;
	match(KEY_BRK);
	if (!match(SEMICO))
	{
		getError(look->line, look->col, 2);
		delete now;
		return 0;
	}
	CodeStore.push_back(now);
	return 1;
}

bool ModeSyntexAnalysis::retStat()     //return语句,bottom是分号前的第一个位置，tag为KEY_RET
{
	AltExpr * now = new AltExpr(it, -1);
	now->tag = KEY_RET;
	match(KEY_RET);
	while (it != subEnd + 1)
	{
		if (!match(SEMICO))
		{
			now->bottom = it;
			sMove();
		}
		else
		{
			if (now->bottom == -1)
			{
				getError(look->line, look->col, 3);
				return 0;
			}
			CodeStore.push_back(now);
			return 1;
		}

	}
	getError(look->line, look->col, 2);
	delete now;
	return 0;
}

bool ModeSyntexAnalysis::conStat() //continue语句，bottom为continue关键字的位置,tag为KEY_CON
{
	AltExpr *now = new AltExpr(it, it);
	now->tag = KEY_CON;
	match(KEY_CON);
	if (!match(SEMICO))
	{
		getError(look->line, look->col, 2);
		delete now;
		return 0;
	}
	CodeStore.push_back(now);
	return 1;
}
bool ModeSyntexAnalysis::inStat() //in语句，bottom为分号位置，tag为KEY_IN
{
	AltExpr *now = new AltExpr(it, it);
	now->tag = KEY_IN;
	match(KEY_IN);
	while (it != subEnd + 1)
	{
		now->bottom = it;
		if (!match(SEMICO))
			sMove();
		else
		{
			CodeStore.push_back(now);
			return 1;
		}

	}
	getError(look->line, look->col, 2);
	delete now;
	return 0;
}
bool ModeSyntexAnalysis::outStat()//out语句，bottom为分号前一个位置，tag为KEY_OUT
{
	AltExpr *now = new AltExpr(it, it);
	now->tag = KEY_OUT;
	match(KEY_OUT);
	while (it != subEnd + 1)
	{
		now->bottom = it;
		if (!match(SEMICO))
			sMove();
		else
		{
			CodeStore.push_back(now);
			return 1;
		}
	}
	getError(look->line, look->col, 2);
	delete now;
	return 0;
}
void ModeSyntexAnalysis::sMove()
{
	if (it <= subEnd)
		it++;
	if (it <= subEnd)
		look = buffer[it];//读入下一个词法记号
}
bool ModeSyntexAnalysis::match(Tag need)
{
	if (it == subEnd + 1)
		return 0;
	if (need == TYPE)
	{
		if (match(KEY_REAL))
			return 1;
		if (match(KEY_STRING))
			return 1;
		if (match(KEY_INT))
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
	now->tag = WHILE;
	match(KEY_WHILE);
	now->conditionExprTop = it;
	now->conditionExprBottom = -1;
	while (it != subEnd + 1)
	{
		if (!match(LBRACE))
		{
			now->conditionExprBottom = it;
			sMove();
		}
		else
		{
			if (now->conditionExprBottom == -1)
			{
				getError(look->line, look->col, 4);
				return 0;
			}

			now->top = it;
			int cnt = 1;
			while (it != subEnd + 1)
			{
				now->bottom = it;
				if (match(LBRACE))
					cnt++;
				else if (match(RBRACE))
					cnt--;
				else
					sMove();
				if (cnt == 0)
				{
					(now->bottom) = (now->bottom) - 1;
					CodeStore.push_back(now);
					return 1;
				}
			}
		}

	}
	getError(look->line, look->col, 1);
	delete now;
	return 0;
}

bool ModeSyntexAnalysis::ifStat()//if语句分析，无大括号
{
	SoIf * now = new SoIf(0, 0, 0, 0);
	now->tag = IF;
	match(KEY_IF);
	now->judgeExprTop = it;
	now->judgeExprBottom = -1;
	while (it != subEnd + 1)
	{
		if (!match(LBRACE))
		{
			now->judgeExprBottom = it;
			sMove();
		}
		else
		{
			if (now->judgeExprBottom == -1)
			{
				getError(look->line, look->col, 5);
				return 0;
			}
			now->top = it;
			int cnt = 1;
			while (it != subEnd + 1)
			{
				now->bottom = it;
				if (match(LBRACE))
					cnt++;
				else if (match(RBRACE))
					cnt--;
				else
					sMove();
				if (cnt == 0)
				{
					(now->bottom) = (now->bottom) - 1;
					CodeStore.push_back(now);
					return 1;
				}
			}

		}

	}
	getError(look->line, look->col, 1);
	delete now;
	return 0;

}

bool ModeSyntexAnalysis::elseStat()
{
	match(KEY_ELSE);
	if (!match(LBRACE))
	{
		getError(look->line, look->col, 4);
		return 0;
	}
	SoElse * now = new SoElse(it, it);
	now->tag = ELSE;
	int cnt = 1;
	while (it != subEnd + 1)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
		if (cnt == 0)
		{
			(now->bottom) = (now->bottom) - 1;
			CodeStore.push_back(now);
			return 1;
		}
	}
	getError(look->line, look->col, 1);
	delete now;
	return 0;
}

bool ModeSyntexAnalysis::altExprStat() //区分函数定义与声明、变量声明与定义语句块
{
	string nowName;
	Tag nowTag;
	if (look->tag == KEY_INT || look->tag == KEY_STRING || look->tag == KEY_REAL)
	{
		nowTag = look->tag;
		sMove();
		if (look->tag == IDT)
		{
			nowName = ((Idt*)look)->name;
			//cout<<nowName<<endl;
			sMove();
			if (look->tag == LPAR)    //函数定义与声明
			{
				sMove();
				if (!funStat(nowTag, nowName)) return 0;
				else return 1;
			}
			else
				return exp();

		}
		else
		{
			getError(look->line, look->col, 6);
			return 0;
		}

	}
	else
	{
		getError(look->line, look->col, 7);
		return 0;
	}
}

bool ModeSyntexAnalysis::exp()
{
	int st = it - 2;
	while (it != subEnd + 1)
	{
		if (match(SEMICO))
		{
			int en = it - 2;
			AltExpr *now = new AltExpr(st, en);
			now->tag = STATE;
			CodeStore.push_back(now);
			return 1;
		}
		else
			sMove();
	}
	getError(look->line, look->col, 2);
	return 0;

	/*
		int st=it-2;
		if(match(ASSIGN))
		{
			while(it!=subEnd+1)
			{
			   if(look->tag==SEMICO||look->tag==COMMA)
				   break;
			   else
					sMove();
			}
		}
		if(it==subEnd+1)
		{
			getError(look->line,look->col,2);
			return 0;
		}

		while(it!=subEnd+1)
		{
			if(match(SEMICO))
			{
				int en=it-2;
				AltExpr *now=new AltExpr(st,en);
				now->tag=STATE;
				CodeStore.push_back(now);
				return 1;
			}
			if(match(COMMA))
			{
				if(match(IDT))
				{
					if(!match(ASSIGN))
						continue;
					else
					{
						int tmp=it;
						while(look->tag!=SEMICO&&look->tag!=COMMA&&(it!=subEnd+1)) sMove();
						if(it==subEnd+1||tmp==it)
						{
							getError(look->line,look->col,2);
							return 0;
						}
					}
				}
			}
			else
			{
				getError(look->line,look->col,8);
				return 0;
			}

		}
		getError(look->line,look->col,2);
		return 0;*/
}

bool ModeSyntexAnalysis::funStat(Tag retType, string name)   //函数定义与声明
{
	SoFunc *now = new SoFunc(name, retType);
	now->tag = FUNC;
	Idt *q;
	while (it != (subEnd + 1))
	{
		if (look->tag == KEY_INT || look->tag == KEY_REAL || look->tag == KEY_STRING)
		{
			q = new Idt;
			q->tag = IDT;
			switch (look->tag)
			{
			case KEY_INT: q->assType = NUM; break;
			case KEY_REAL: q->assType = RNUM; break;
			case KEY_STRING: q->assType = STRING; break;
			default:
				break;
			}
			sMove();
			if (look->tag == IDT)
			{
				q->name = ((Idt*)look)->name;
				now->paralist.push_back(q);
				sMove();
				if (look->tag == COMMA)
				{
					sMove();
					continue;
				}
				if (look->tag == RPAR)
				{
					sMove();
					break;
				}
				getError(look->line, look->col, 9);
				return 0;
			}
			else
			{
				getError(look->line, look->col, 9);
				return 0;
			}
		}
		else if (look->tag == RPAR)
			break;
		else
		{
			getError(look->line, look->col, 9);
			return 0;
		}
	}
	if (it == subEnd + 1)
	{
		getError(look->line, look->col, 9);
		return 0;
	}
	match(RPAR);
	if (!match(LBRACE))
	{
		getError(look->line, look->col, 1);
		return 0;
	}
	now->top = it;
	int cnt = 1;
	while (it != subEnd + 1)
	{
		now->bottom = it;
		if (match(LBRACE))
			cnt++;
		else if (match(RBRACE))
			cnt--;
		else
			sMove();
		if (cnt == 0)
		{
			now->bottom = ((now->bottom) - 1);
			if (findSame(name, now))
			{
				delete now;
				return 0;
			}
			else
			{
				FuncStore.push_back(now);
				return 1;
			}
		}
	}
	getError(look->line, look->col, 1);
	delete now;
	return 0;
}

bool ModeSyntexAnalysis::findSame(string name, SoFunc *func)
{
	int cnt = func->paralist.size();
	for (int i = 0; i < FuncStore.size(); i++) {
		if ((FuncStore[i]->paralist.size() == cnt) && (name.compare(FuncStore[i]->name) == 0))
		{
			bool flag = 1;
			for (int j = 0; j < func->paralist.size(); j++) {
				Idt * a = (Idt *)FuncStore[i]->paralist[j];
				Idt * b = (Idt *)func->paralist[j];
				if ((a->assType) != (b->assType))
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				getError(look->line, look->col, 10);
				return 1;
			}
		}
	}
	return 0;
}

