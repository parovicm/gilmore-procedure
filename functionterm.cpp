#include "functionterm.h"
#include <algorithm>
//#include <iterator>

FunctionTerm::FunctionTerm(const Signature::Sptr &signature, const FunctionSymbol &sym, const std::vector<Term> &terms)
    : BaseTerm(), m_signature(signature), m_symbol(sym), m_terms(terms)
{
    if(!signature->hasFunctionSymbol(sym, terms.size()))
        throw std::runtime_error("Unknown function symbol or incorrect arity!\n");

}

std::ostream &FunctionTerm::print(std::ostream &out) const
{
    out << m_symbol;
    if(!m_terms.size())
        return out;
    out << "(";
    for(auto first = m_terms.cbegin(); first + 1 != m_terms.cend(); first++) {
        (*first)->print(out);
        out << ", ";
    }
    m_terms.back()->print(out);
    return out << ")";
}

bool FunctionTerm::equalTo(const Term &t) const
{
    const FunctionTerm* funTerm = dynamic_cast<const FunctionTerm*>(t.get());
    if(funTerm) {
        return symbol() == funTerm->symbol() && m_terms.size() == funTerm->m_terms.size() &&
                std::equal(m_terms.cbegin(), m_terms.cend(), funTerm->m_terms.cbegin(),
                           [](const Term& t1, const Term& t2) {
            return t1->equalTo(t2);
        });
    }
    return false;
}

void FunctionTerm::getVariables(VariablesSet &vset) const
{
    for(const auto& t : m_terms)
        t->getVariables(vset);
}

void FunctionTerm::getFunctions(FunctionSet &fset) const
{
    fset.insert(m_symbol);
}

bool FunctionTerm::containsVariable(const Variable &v) const
{
    for(const auto& t : m_terms)
        if(t->containsVariable(v))
            return true;
    return false;
}

AnyType FunctionTerm::eval(const LStructure &structure, const Valuation &v) const
{
    Function f = structure.getFunction(m_symbol);
    std::vector<AnyType> termValues;
    termValues.reserve(m_terms.size());
    std::transform(m_terms.begin(), m_terms.end(), std::back_inserter(termValues),
        [&](const auto& x)
            {
                return x->eval(structure, v);
            });

    return f->eval(termValues);
}

Term FunctionTerm::substitute(const Variable &v, const Term &t) const
{
    std::vector<Term> terms;
    terms.reserve(m_terms.size());
    std::transform(m_terms.begin(), m_terms.end(), std::back_inserter(terms),
                   [&](const auto& term) { return term->substitute(v, t);}
                   );
    return std::make_shared<FunctionTerm>(m_signature, m_symbol, terms);
}
