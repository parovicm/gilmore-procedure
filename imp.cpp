#include "imp.h"
#include "first_order_logic.h"

Imp::Imp(const Formula &op1, const Formula &op2)
    : BinaryConnective(op1, op2)
{
}

std::ostream &Imp::print(std::ostream &out) const
{
    return printImpl(out, "=>");
}

bool Imp::eval(const LStructure &structure, const Valuation &v) const
{
    return !m_op1->eval(structure, v) || m_op2->eval(structure, v);
}

Formula Imp::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Imp>(v, t);
}

Formula Imp::simplify() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    op1 = op1->simplify();
    op2 = op2->simplify();

    if(BaseFormula::isOfType<False>(op1) || BaseFormula::isOfType<True>(op2))
        return std::make_shared<True>();
    else if(BaseFormula::isOfType<True>(op1))
        return op2;
    else if(BaseFormula::isOfType<False>(op2))
        return std::make_shared<Not>(op1)->simplify();
    else
        return std::make_shared<Imp>(op1, op2);
}

Formula Imp::nnf() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    return std::make_shared<Or>(std::make_shared<Not>(op1)->nnf(), op2->nnf());
}

LiteralListList Imp::listDNF() const
{
    throw std::runtime_error("Error when applying DNF on implication formula.\n");
}
