#include "variableterm.h"

VariableTerm::VariableTerm(const Variable &v)
    : BaseTerm(), m_var(v)
{
}

std::ostream &VariableTerm::print(std::ostream &out) const
{
    return out << m_var;
}

bool VariableTerm::equalTo(const Term &t) const
{
    const VariableTerm* varTerm = dynamic_cast<const VariableTerm*>(t.get());
    if(varTerm)
        return variable() == varTerm->variable();
    return false;
}

void VariableTerm::getVariables(VariablesSet &vset) const
{
    vset.insert(m_var);
}

void VariableTerm::getFunctions(FunctionSet &fset) const
{
    UNUSED_ARG(fset);
}

bool VariableTerm::containsVariable(const Variable &v) const
{
    return v == m_var;
}

AnyType VariableTerm::eval(const LStructure &structure, const Valuation &v) const
{
    UNUSED_ARG(structure);
    return v.getValue(m_var);
}

Term VariableTerm::substitute(const Variable &v, const Term &t) const
{
    if(v == m_var)
        return t;
    return std::const_pointer_cast<BaseTerm>(shared_from_this());
}
