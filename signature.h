#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "common.h"
#include <unordered_map>
#include <memory>

class Signature {
public:
    using Sptr = std::shared_ptr<Signature>;

    void addFunctionSymbol(const FunctionSymbol& f, Arity ar);
    void addRelationSymbol(const RelationSymbol& r, Arity ar);

    bool hasFunctionSymbol(const FunctionSymbol& f, const Arity& ar) const;
    bool hasRelationSymbol(const RelationSymbol& r, const Arity& ar) const;

    Arity getFunctionArity(const FunctionSymbol& f) const;
    Arity getRelationArity(const FunctionSymbol& r) const;

    FunctionSymbol getUniqueFunctionSymbol() const;
private:
    using Map = std::unordered_map<std::string, Arity>;

    static uint64_t s_uniqueCounter;

    Map m_functions;
    Map m_relations;
};

#endif // SIGNATURE_H
