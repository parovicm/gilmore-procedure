#ifndef LSTRUCTURE_H
#define LSTRUCTURE_H

#include "domain.h"
#include "common.h"
#include "signature.h"

#include <unordered_map>
#include <memory>
#include <vector>

class BaseFunction {
public:
    BaseFunction(const Arity& ar);
    virtual ~BaseFunction();

    inline Arity getArity() const { return m_arity; }
    virtual AnyType eval(const std::vector<AnyType>& args) const = 0;
private:
    Arity m_arity;
};


class BaseRelation {
public:
    BaseRelation(const Arity& ar);
    virtual ~BaseRelation();

    inline Arity getArity() const { return m_arity; }
    virtual bool eval(const std::vector<AnyType>& args) const = 0;
private:
    Arity m_arity;
};

using Function = std::shared_ptr<BaseFunction>;
using Relation = std::shared_ptr<BaseRelation>;

class LStructure {
public:
    using FuncMap = std::unordered_map<FunctionSymbol, Function>;
    using RelMap = std::unordered_map<RelationSymbol, Relation>;

    LStructure(const Domain& domain, const Signature::Sptr& signature);

    inline const Domain& getDomain() const { return m_domain; }

    void addFunction(const FunctionSymbol& fsymb, const Function& func);
    void addRelation(const RelationSymbol& rsymb, const Relation& rel);

    const Function& getFunction(const FunctionSymbol& fsymb) const;
    const Relation& getRelation(const RelationSymbol& rsymb) const;
private:
    Domain m_domain;
    Signature::Sptr m_signature;
    FuncMap m_fmap;
    RelMap m_rmap;
};

#endif // LSTRUCTURE_H
