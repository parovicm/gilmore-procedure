#include "atom.h"
#include <iterator>
#include <algorithm>
#include "first_order_logic.h"

Atom::Atom(Signature::Sptr signature, RelationSymbol symbol, std::vector<Term> terms)
    : AtomicFormula(), m_signature(signature), m_symbol(symbol), m_terms(terms)
{
    if(!m_signature->hasRelationSymbol(m_symbol, m_terms.size()))
        throw std::runtime_error("Unknown relation symbol or incorrect arity!\n");
}

std::ostream &Atom::print(std::ostream &out) const
{
    out << m_symbol << "(";
    for(auto first = m_terms.begin(); first + 1 != m_terms.end(); first++) {
        (*first)->print(out);
        out << ", ";
    }
    m_terms.back()->print(out);
    return out << ")";
}

bool Atom::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)) {
        const Atom* atomPtr = static_cast<const Atom*>(f.get());
        return m_symbol == atomPtr->m_symbol && m_terms.size() == atomPtr->m_terms.size() &&
                std::equal(m_terms.cbegin(), m_terms.cend(), atomPtr->m_terms.cbegin(),
                           [](const Term& t1, const Term& t2) {
            return t1->equalTo(t2);
        });
    }
    return false;
}

void Atom::getVars(VariablesSet &vset, bool free) const
{
    UNUSED_ARG(free);
    for(const auto& t : m_terms)
        t->getVariables(vset);
}

void Atom::getFunctions(FunctionSet &fset) const
{
    for(const Term& t : m_terms)
        t->getFunctions(fset);
}

bool Atom::containsVariable(Variable &v, bool free) const
{
    UNUSED_ARG(free);
    for(const auto& t : m_terms)
        if(t->containsVariable(v))
            return true;
    return false;
}

bool Atom::eval(const LStructure &structure, const Valuation &v) const
{
    Relation r = structure.getRelation(m_symbol);
    std::vector<AnyType> termValues;
    termValues.reserve(m_terms.size());
    std::transform(m_terms.begin(), m_terms.end(), std::back_inserter(termValues),
                   [&](const auto& t) {
                        return t->eval(structure, v);
    });
    return r->eval(termValues);
}

Formula Atom::substitute(const Variable &v, const Term &t) const
{
    std::vector<Term> terms;
    terms.reserve(m_terms.size());
    std::transform(m_terms.begin(), m_terms.end(), std::back_inserter(terms),
                   [&](const auto& term) {
                        return term->substitute(v, t);
    });
    return std::make_shared<Atom>(m_signature, m_symbol, terms);


}

LiteralListList Atom::listDNF() const
{
    return {{std::const_pointer_cast<BaseFormula>(shared_from_this())}};
}
