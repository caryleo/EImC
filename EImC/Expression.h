#include "ModeTokenAnalysis.h"

class ExprIR
{
public:
    //��ȡ����ֵ
    Tag getValType(Idt);
    string getStrVal(Idt);
    short getIntVal(Idt);
    double getRealVal(Idt);

    //��������ȼ�
    int oper_priority(Idt);
    //�ж���������ȼ�
    int judge_priority(Idt,Idt);
    //�������㣺 +�� | -�� | *�� | /�� | %��
    Idt add_opr(Idt,Idt);
    Idt sub_opr(Idt,Idt);
    Idt mul_opr(Idt,Idt);
    Idt div_opr(Idt,Idt);
    Idt mod_opr(Idt,Idt);
    //��Ŀ���㣺+�� | -��
    Idt pos_opr(Idt);
    Idt neg_opr(Idt);
    //�������㣺(������ | )������
    //��������$���� | #ɾһ���ַ�
    Idt connect_opr(Idt,Idt);
    Idt deltail_opr(Idt);
    //Idt delspecial_opr(Idt,Idt);
    //��ϵ���㣺>���� | <С�� | >=���ڵ��� | <=С�ڵ��� | ==��� | <>����
    //int Greater(Idt,Idt);
    //int Greater_equal(Idt,Idt);
    //int Less(Idt,Idt);
    //int Less_equal(Idt,Idt);
    //int Equal(Idt,Idt);
    //int NEqual(Idt,Idt);
    //�߼����㣺&&�� | ||�� | !��
    //int And_opr(Idt,Idt);
    //int Or_opr(Idt,Idt);
    //int Not_opr(Idt);
};
