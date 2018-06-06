#include "iff.h"
#include "first_order_logic.h"

Iff::Iff(const Formula &op1, const Formula &op2)
    : BinaryConnective(op1, op2)
{
}

std::ostream &Iff::print(std::ostream &out) const
{
    return printImpl(out, "<=>");
}

bool Iff::eval(const LStructure &structure, const Valuation &v) const
{
    return m_op1->eval(structure, v) == m_op2->eval(structure, v);
}

Formula Iff::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Iff>(v, t);
}

Formula Iff::simplify() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    op1 = op1->simplify();
    op2 = op2->simplify();

    if(BaseFormula::isOfType<True>(op1))
        return op2;
    else if(BaseFormula::isOfType<True>(op2))
        return op1;
    else if(BaseFormula::isOfType<False>(op1))
        return std::make_shared<Not>(op2)->simplify();
    else if(BaseFormula::isOfType<False>(op2))
        return std::make_shared<Not>(op1)->simplify();
    else
        return std::make_shared<Imp>(op1, op2);

}

Formula Iff::nnf() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    return std::make_shared<And>(std::make_shared<Or>(
                                     std::make_shared<Not>(op1)->nnf(),
                                     op2->nnf()),
                                 std::make_shared<Or>(
                                     op1->nnf(),
                                     std::make_shared<Not>(op2)->nnf()));

}

LiteralListList Iff::listDNF() const
{
    throw std::runtime_error("Error when applying DNF on equivalence formula.\n");
}
