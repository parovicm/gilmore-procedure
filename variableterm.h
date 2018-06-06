#ifndef VARIABLETERM_H
#define VARIABLETERM_H

#include "baseterm.h"

class VariableTerm : public BaseTerm {
public:
    VariableTerm(const Variable& v={});
    inline const Variable& variable() const { return m_var; }

    std::ostream &print(std::ostream &out) const;
    bool equalTo(const Term &t) const;
    void getVariables(VariablesSet &vset) const;

    void getFunctions(FunctionSet& fset) const;

    bool containsVariable(const Variable &v) const;
    AnyType eval(const LStructure &structure, const Valuation &v) const;
    Term substitute(const Variable &v, const Term &t) const;

private:
    Variable m_var;
};

#endif // VARIABLETERM_H
