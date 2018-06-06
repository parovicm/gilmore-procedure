#ifndef FUNCTIONTERM_H
#define FUNCTIONTERM_H

#include "baseterm.h"
#include "signature.h"

#include <vector>

class FunctionTerm : public BaseTerm {

public:
    FunctionTerm(const Signature::Sptr& signature, const FunctionSymbol& sym,
                 const std::vector<Term>& terms={});

    inline const FunctionSymbol& symbol() const { return m_symbol; }
    inline const std::vector<Term>& terms() const { return m_terms; }

    std::ostream &print(std::ostream &out) const;
    bool equalTo(const Term &t) const;
    void getVariables(VariablesSet &vset) const;

    void getFunctions(FunctionSet& fset) const;

    bool containsVariable(const Variable &v) const;
    AnyType eval(const LStructure &structure, const Valuation &v) const;
    Term substitute(const Variable &v, const Term &t) const;
private:
    Signature::Sptr m_signature;
    FunctionSymbol m_symbol;
    std::vector<Term> m_terms;
};

#endif // FUNCTIONTERM_H
