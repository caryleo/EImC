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
