#ifndef DOMAIN_H
#define DOMAIN_H

#include "common.h"

#include <unordered_map>
#include <set>
#include <memory>
#include <vector>

class BaseDomain {
public:
    virtual ~BaseDomain();

    virtual void insert(const AnyType& val) = 0;

    virtual bool hasValue(const AnyType& val) const = 0;

    virtual std::vector<AnyType> getValues() const = 0;
};

template <typename ValueType>
class DomainSpecialization : public BaseDomain {
public:
    DomainSpecialization();

    virtual void insert(const AnyType& val);

    virtual bool hasValue(const AnyType& val) const;

    virtual std::vector<AnyType> getValues() const;
private:
    std::set<ValueType> m_values;
};

template <typename ValueType>
DomainSpecialization<ValueType>::DomainSpecialization()
    : BaseDomain()
{}

template <typename ValueType>
void DomainSpecialization<ValueType>::insert(const AnyType& val) {
    m_values.insert(AnyTypeToType(ValueType, val));
}

template <typename ValueType>
bool DomainSpecialization<ValueType>::hasValue(const AnyType& val) const {
    return m_values.find(AnyTypeToType(ValueType, val)) != m_values.cend();
}

template <typename ValueType>
std::vector<AnyType> DomainSpecialization<ValueType>::getValues() const {

    std::vector<AnyType> values;
    values.reserve(m_values.size());

    for(const ValueType& v : m_values)
        values.emplace_back(v);

    return values;
}

using Domain = std::shared_ptr<BaseDomain>;

#endif // DOMAIN_H
