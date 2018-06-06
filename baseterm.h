#ifndef BASETERM_H
#define BASETERM_H

#include "common.h"
#include "lstructure.h"
#include "valuation.h"

#include <memory>
#include <iostream>

class BaseTerm;

using Term = std::shared_ptr<BaseTerm>;

class BaseTerm : public std::enable_shared_from_this<BaseTerm> {
public:
    BaseTerm();
    virtual ~BaseTerm();

    virtual std::ostream& print(std::ostream& out) const = 0;

    virtual bool equalTo(const Term& t) const = 0;

    virtual void getVariables(VariablesSet& vset) const = 0;

    virtual bool containsVariable(const Variable& v) const = 0;

    virtual void getFunctions(FunctionSet& fset) const = 0;

    virtual AnyType eval(const LStructure& structure, const Valuation& v) const = 0;
    virtual Term substitute(const Variable& v, const Term& t) const = 0;

};

bool operator==(const Term& lhs, const Term& rhs);


#endif // BASETERM_H
