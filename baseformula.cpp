#include "baseformula.h"
#include <typeinfo>
#include "first_order_logic.h"

BaseFormula::BaseFormula()
{
}

BaseFormula::~BaseFormula()
{
}

bool BaseFormula::equalTo(const Formula &f) const
{
    const BaseFormula* base = f.get();
    return typeid(*this) == typeid(*base);
}

bool BaseFormula::containsVariable(const Variable &v, bool free) const
{
    VariablesSet vset;
    getVars(vset, free);
    return vset.find(v) != vset.cend();
}

Formula BaseFormula::simplify() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::nnf() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::pullQuantifiers() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::prenex() const
{
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula BaseFormula::skolem(Signature::Sptr s, VariablesSet &&vars) const
{
    UNUSED_ARG(s);
    UNUSED_ARG(vars);
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

LiteralListList BaseFormula::cross(const LiteralListList &l1, const LiteralListList &l2)
{
    LiteralListList result;
    result.reserve(l1.size() * l2.size());
    for(auto& outerL : l1)
        for(auto& innerL : l2)
            result.push_back(concatenate(outerL, innerL));
    return result;
}

std::ostream &operator<<(std::ostream &out, const Formula &f)
{
    return f->print(out);
}

Formula removeUniversalFromSkolem(const Formula &f)
{
    if(BaseFormula::isOfType<Forall>(f)) {
        const Forall* forallF = static_cast<const Forall*>(f.get());
        return removeUniversalFromSkolem(forallF->operand());
    }
    return f;
}

std::ostream &operator<<(std::ostream &out, const LiteralListList &l)
{
    out << "[ ";
    for(const auto& list : l) {
        out << "[ ";

        for(unsigned i=0; i<list.size()-1; i++)
            out << list[i] << ", ";
        out << list.back();
        out << " ] ";
    }
    return out << "]";
}
