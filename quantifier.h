#ifndef QUANTIFIER_H
#define QUANTIFIER_H

#include <cstdint>

#include "baseformula.h"
#include "common.h"
#include "variableterm.h"

class Quantifier : public BaseFormula {
public:
    Quantifier(const Variable& var, const Formula& op);

    unsigned complexity() const;
    bool equalTo(const Formula &f) const;
    void getVars(VariablesSet &vset, bool free) const;
    void getFunctions(FunctionSet& fset) const;

    Formula operand() const;
    Variable variable() const;

    template <typename T1, typename T2>
    static Variable getUniqueVarName(const T1& t1, const T2& t2);

    LiteralListList listDNF() const;

protected:
    template <typename Derived>
    Formula substituteImpl(const Variable& v, const Term& t) const;

    std::ostream& printImpl(std::ostream& out, const std::string& quant) const;

    Variable m_var;
    Formula m_op;

private:
    static uint64_t s_uniqueCounter;
};

template <typename T1, typename T2>
Variable Quantifier::getUniqueVarName(const T1 &t1, const T2 &t2)
{
    Variable unique;
    do {
        unique = "uv" + std::to_string(s_uniqueCounter++);

    } while(t1->containsVariable(unique) || t2->containsVariable(unique));

    return unique;
}


template <typename Derived>
Formula Quantifier::substituteImpl(const Variable& v, const Term& t) const {

    if(v == m_var)
        return std::const_pointer_cast<BaseFormula>(shared_from_this());
    if(t->containsVariable(m_var)) {
        Variable newVar = Quantifier::getUniqueVarName
                (std::const_pointer_cast<BaseFormula>(shared_from_this()), t);
        Formula newOp = m_op->substitute(m_var, std::make_shared<VariableTerm>(newVar));
        return std::make_shared<Derived>(newVar, newOp->substitute(v, t));
    }
    return std::make_shared<Derived>(m_var, m_op->substitute(v, t));
}





#endif // QUANTIFIER_H
