#include "forall.h"
#include "first_order_logic.h"

Forall::Forall(const Variable &v, const Formula &op)
    : Quantifier(v, op)
{
}

std::ostream &Forall::print(std::ostream &out) const
{
    return printImpl(out, "V");
}

bool Forall::eval(const LStructure &structure, const Valuation &v) const
{
    Valuation copyVal = v;
    std::vector<AnyType> domain = structure.getDomain()->getValues();
    for(const auto& elem : domain) {
        copyVal.setValue(m_var, elem);
        if(!m_op->eval(structure, copyVal))
            return false;
    }
    return true;
}

Formula Forall::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Forall>(v, t);
}

Formula Forall::simplify() const
{
    Formula op = operand()->simplify();
    if(op->containsVariable(m_var, true))
        return std::make_shared<Forall>(m_var, op);
    else
        return op;
}

Formula Forall::nnf() const
{
    return std::make_shared<Forall>(m_var, operand()->nnf());
}

Formula Forall::prenex() const
{
    return std::make_shared<Forall>(m_var, operand()->prenex());
}

Formula Forall::skolem(Signature::Sptr s, VariablesSet &&vars) const
{
    vars.insert(m_var);
    return m_op->skolem(s, std::move(vars));
}


