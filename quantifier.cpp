#include "quantifier.h"

uint64_t Quantifier::s_uniqueCounter = 0U;

Quantifier::Quantifier(const Variable &var, const Formula &op)
    : BaseFormula(), m_var(var), m_op(op)
{
}

unsigned Quantifier::complexity() const
{
    return 1 + m_op->complexity();
}

bool Quantifier::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)) {
        const Quantifier* qPtr = static_cast<const Quantifier*>(f.get());
        return m_var == qPtr->m_var && m_op->equalTo(qPtr->m_op);
    }
    return false;
}

void Quantifier::getVars(VariablesSet &vset, bool free) const
{
    VariablesSet tmp;
    m_op->getVars(tmp, free);
    if (free)
        tmp.erase(m_var);
    vset.insert(tmp.cbegin(), tmp.cend());
}

void Quantifier::getFunctions(FunctionSet &fset) const
{
    m_op->getFunctions(fset);
}

Formula Quantifier::operand() const
{
    return m_op;
}

Variable Quantifier::variable() const
{
    return m_var;
}

LiteralListList Quantifier::listDNF() const
{
    throw std::runtime_error("Error when applying DNF on quantified formula.\n");
}


std::ostream &Quantifier::printImpl(std::ostream &out, const std::string &quant) const
{

    out << "(" <<quant << " " << m_var << ")(" ;
    m_op->print(out);
    return out << ")";
}
