#include "exists.h"
#include "first_order_logic.h"
#include <algorithm>

Exists::Exists(const Variable &v, const Formula &op)
    : Quantifier(v, op)
{
}

std::ostream &Exists::print(std::ostream &out) const
{
    return printImpl(out, "E");
}

bool Exists::eval(const LStructure &structure, const Valuation &v) const
{
    Valuation copyVal = v;
    std::vector<AnyType> domain = structure.getDomain()->getValues();
    for(const auto& elem : domain) {
        copyVal.setValue(m_var, elem);
        if(m_op->eval(structure, copyVal))
            return true;
    }
    return false;
}

Formula Exists::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Exists>(v, t);
}

Formula Exists::simplify() const
{
    Formula op = operand()->simplify();
    if(op->containsVariable(m_var, true))
        return std::make_shared<Exists>(m_var, op);
    else
        return op;
}

Formula Exists::nnf() const
{
    return std::make_shared<Exists>(m_var, operand()->nnf());
}

Formula Exists::prenex() const
{
    return std::make_shared<Exists>(m_var, operand()->prenex());
}

Formula Exists::skolem(Signature::Sptr s, VariablesSet &&vars) const
{
    FunctionSymbol funSym = s->getUniqueFunctionSymbol();
    s->addFunctionSymbol(funSym, vars.size());
    std::vector<Term> terms;
    std::transform(vars.begin(), vars.end(), std::back_inserter(terms),
                   [&] (const auto& v) {
                        return std::make_shared<VariableTerm>(v);
                   });

    return m_op->substitute(m_var, std::make_shared<FunctionTerm>(s, funSym, terms)
                            )->skolem(s, std::move(vars));

}
