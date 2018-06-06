#include "valuation.h"

Valuation::Valuation(const Domain &d)
    : m_domain(d), m_values{}
{
}

void Valuation::setValue(const Variable &v, const AnyType &val)
{
    if(m_domain->hasValue(val))
        m_values[v] = val;
    else
        throw std::runtime_error("Given value not in the domain!");
}

const AnyType &Valuation::getValue(const Variable &v) const
{
    return m_values.at(v);
}
