#include "atomicformula.h"

AtomicFormula::AtomicFormula()
    : BaseFormula()
{
}

unsigned AtomicFormula::complexity() const
{
    return 0;
}

void AtomicFormula::getVars(VariablesSet &vset, bool free) const
{
    UNUSED_ARG(vset);
    UNUSED_ARG(free);
}

void AtomicFormula::getFunctions(FunctionSet &fset) const
{
    UNUSED_ARG(fset);
}

Formula AtomicFormula::substitute(const Variable &v, const Term &t) const
{
    UNUSED_ARG(v);
    UNUSED_ARG(t);
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}
