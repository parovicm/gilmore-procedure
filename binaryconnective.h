#ifndef BINARYCONNECTIVE_H
#define BINARYCONNECTIVE_H

#include "baseformula.h"

class BinaryConnective : public BaseFormula {
public:
    BinaryConnective(const Formula& op1, const Formula& op2);

    unsigned complexity() const;
    bool equalTo(const Formula &f) const;
    void getVars(VariablesSet &vset, bool free) const;
    void getFunctions(FunctionSet& fset) const;

    std::pair<Formula, Formula> operands() const;

    Formula pullQuantifiers() const;
    Formula prenex() const;
protected:
    template<typename Derived>
    Formula substituteImpl(const Variable& v, const Term& t) const;

    std::ostream& printImpl(std::ostream& out, const std::string& symbol) const;

protected:
    Formula m_op1;
    Formula m_op2;

};

template<typename Derived>
Formula BinaryConnective::substituteImpl(const Variable &v, const Term &t) const
{
    return std::make_shared<Derived>(m_op1->substitute(v, t), m_op2->substitute(v, t));
}


#endif // BINARYCONNECTIVE_H
