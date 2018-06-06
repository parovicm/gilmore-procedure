#ifndef VALUATION_H
#define VALUATION_H

#include "domain.h"
#include <unordered_map>

class Valuation {
public:
    using Map = std::unordered_map<Variable, AnyType>;

    Valuation(const Domain& d);

    void setValue(const Variable& v, const AnyType& val);

    const AnyType& getValue(const Variable& v) const;

private:
    Domain m_domain;
    Map m_values;
};

#endif // VALUATION_H
