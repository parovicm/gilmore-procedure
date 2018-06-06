#ifndef UNARYCONNECTIVE_H
#define UNARYCONNECTIVE_H

#include "baseformula.h"

class UnaryConnective : public BaseFormula {
public:
    UnaryConnective(const Formula& op);

    unsigned complexity() const;
    void getVars(VariablesSet &vset, bool free) const;
    void getFunctions(FunctionSet& fset) const;

    bool equalTo(const Formula &f) const;
    Formula operand() const;

protected:
    Formula m_op;
};

#endif // UNARYCONNECTIVE_H
