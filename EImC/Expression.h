#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include "ModeTokenAnalysis.h"
#include"Stack.h"
#include "EImC.h"
#include<string>
#include<cmath>

class ExprIR
{
private:
	//当前扫描到表达式的位置
	int pos;
	//表达式头指针和尾指针
	int start;
	int term;
	//操作符栈
	Stack operator_s;
	//操作数栈
	Stack operand_s;
public:
	//查询类型
	Tag getType(Token *);
	//查询IDT asstype
	Tag getAsstype(Token *);

	bool isAssign(Token *);
	//判断是否为IDT
	bool isIDT(Token *);

	//查询值
	string getStrVal(Token *);
	short getIntVal(Token *);
	float getRealVal(Token *);

	//判断操作数,若不是操作数就是操作符
	bool isOperand(Token *);
	//运算符优先级
	int oper_priority(Token *, Token *);
	int isp(Tag);
	int icp(Tag);

	//双目算术运算：ADD,SUB,MUL,DIV,MOD
	Token * add_op(Token *, Token *);
	Token * sub_op(Token *, Token *);
	Token * mul_op(Token *, Token *);
	Token * div_op(Token *, Token *);
	Token * mod_op(Token *, Token *);


	//字符串处理DOLLA, HASH
	//定义$不改变原字符串的值，#删除字符对原字符串进行更改
	Token * connect_op(Token *, Token *);
	Token * delete_spec(Token *, Token *);
	Token * delete_tail(Token *);

	//关系运算:>,< ,>=,<=,==,<>
	//GT, GE, LT, LE, EQU, NEQU
	Token * is_greater(Token *, Token *);
	Token * not_less(Token *, Token *);
	Token * is_less(Token *, Token *);
	Token * not_greater(Token *, Token *);
	Token * is_equal(Token *, Token *);
	Token * not_equal(Token *, Token *);

	//逻辑运算：&&与 | ||或 | !非
	//AND, OR, NOT
	Token * and_lop(Token *, Token *);
	Token * or_lop(Token *, Token *);
	Token * not_lop(Token *);
	//vector<Token*>buffer
	//表达式处理入口
	Token * calculate_expr(int, int);
	//查找对应的运算符处理模块
	int find_op(Token *);
	//当扫描到运算符时执行
	int solve_op(Token *);
};

#endif // !EXPRESSION_H_
