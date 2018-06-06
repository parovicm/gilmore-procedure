#include "unaryconnective.h"

UnaryConnective::UnaryConnective(const Formula &op)
    : BaseFormula(), m_op(op)
{
}

unsigned UnaryConnective::complexity() const
{
    return 1 + m_op->complexity();
}

void UnaryConnective::getVars(VariablesSet &vset, bool free) const
{
    m_op->getVars(vset, free);
}

void UnaryConnective::getFunctions(FunctionSet &fset) const
{
    m_op->getFunctions(fset);
}

bool UnaryConnective::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)) {
        const UnaryConnective* uPtr = static_cast<const UnaryConnective*>(f.get());
        return m_op->equalTo(uPtr->m_op);
    }
    return false;
}

Formula UnaryConnective::operand() const
{
    return m_op;
}
