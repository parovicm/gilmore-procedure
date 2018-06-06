#include "signature.h"

uint64_t Signature::s_uniqueCounter = 0U;

void Signature::addFunctionSymbol(const FunctionSymbol &f, Arity ar)
{
    m_functions[f] = ar;
}

void Signature::addRelationSymbol(const RelationSymbol &r, Arity ar)
{
    m_relations[r] = ar;
}

bool Signature::hasFunctionSymbol(const FunctionSymbol &f, const Arity &ar) const
{
    auto it = m_functions.find(f);

    if(it == m_functions.cend())
        return false;
    return it->second == ar;
}

bool Signature::hasRelationSymbol(const RelationSymbol &r, const Arity &ar) const
{
    auto it = m_relations.find(r);

    if(it == m_relations.cend())
        return false;
    return it->second == ar;
}

Arity Signature::getFunctionArity(const FunctionSymbol &f) const
{
    auto it = m_functions.find(f);

    if(it == m_functions.cend())
        throw std::runtime_error{"Required arity of unknown function symbol!\n"};

    return it->second;
}

Arity Signature::getRelationArity(const FunctionSymbol &r) const
{
    auto it = m_relations.find(r);

    if(it == m_relations.cend())
        throw std::runtime_error{"Required arity of unknown relation symbol!\n"};

    return it->second;
}

FunctionSymbol Signature::getUniqueFunctionSymbol() const
{
    FunctionSymbol newSymb;
    do {
        newSymb = "uf" + std::to_string(s_uniqueCounter++);
    } while(m_functions.find(newSymb) != m_functions.cend());

    return newSymb;
}
