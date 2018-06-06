#ifndef ATOMICFORMULA_H
#define ATOMICFORMULA_H

#include "baseformula.h"
#include "common.h"

class AtomicFormula : public BaseFormula {
public:
    AtomicFormula();
    unsigned complexity() const;
    void getVars(VariablesSet &vset, bool free) const;
    void getFunctions(FunctionSet& fset) const;

    Formula substitute(const Variable &v, const Term &t) const;
};


#endif // ATOMICFORMULA_H
