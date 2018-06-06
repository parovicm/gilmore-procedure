#ifndef ATOM_H
#define ATOM_H

#include "atomicformula.h"
#include "baseterm.h"
#include "signature.h"
#include "lstructure.h"

#include <vector>

class Atom : public AtomicFormula {
public:
    Atom(Signature::Sptr signature, RelationSymbol symbol, std::vector<Term> terms={});

    inline const RelationSymbol& symbol() const { return m_symbol; }
    inline const std::vector<Term> operands() const { return m_terms; }

    std::ostream &print(std::ostream &out) const;
    bool equalTo(const Formula &f) const;
    void getVars(VariablesSet &vset, bool free = false) const;
    void getFunctions(FunctionSet& fset) const;

    bool containsVariable(Variable& v, bool free = false) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    LiteralListList listDNF() const;

private:
    Signature::Sptr m_signature;
    RelationSymbol m_symbol;
    std::vector<Term> m_terms;

};


#endif // ATOM_H
