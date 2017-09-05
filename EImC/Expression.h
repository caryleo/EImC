#include "ModeTokenAnalysis.h"

class ExprIR
{
public:
    //��ѯ����
    Tag getValType(Token *);
    //��ѯIDT asstype
    Tag getAsstype(Token *);
    //�ж��Ƿ�ΪIDT

    bool isIDT(Token *);
    //Token*����ת��ΪIdt*
    Idt* TransIDT(Token *);
    //Token*����ת��ΪSoString*
    SoString *TransStr(Token *);
    //Token*����ת��ΪSoInt*
    SoInt *TransInt(Token *);
    //Token*����ת��ΪSoReal*
    SoReal *TransReal(Token *);

    //��ѯֵ
    string getStrVal(Token *);
    short getIntVal(Token *);
    float getRealVal(Token *);

    //�жϲ�����,�����ǲ��������ǲ�����
    bool isOperand(Token *);
    //��������ȼ�
    int oper_priority(Token *);
    //�ж���������ȼ�
    bool judge_priority(Token * ,Token *);

    //�������㣺ADD,SUB,MUL,DIV,MOD
    Token * add_op(Token *,Token *);
    Token * sub_op(Token *,Token *);
    Token * mul_op(Token *,Token *);
    Token * div_op(Token *,Token *);
    Token * mod_op(Token *,Token *);

    //��Ŀ����������������Ź涨������Ҫ���������磨-a��
    Token * pos_op(Token *);
    Token * neg_op(Token *);

    //�ַ�������DOLLA, HASH
    Token * connect_op(Token *,Token *);
    Token * delete_spec(Token *,Token *);
    Token * delete_tail(Token *);
};
