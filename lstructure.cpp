#include "lstructure.h"

BaseFunction::BaseFunction(const Arity &ar)
    : m_arity(ar)
{
}

BaseFunction::~BaseFunction()
{
}

BaseRelation::BaseRelation(const Arity &ar)
    : m_arity(ar)
{
}

BaseRelation::~BaseRelation()
{
}

LStructure::LStructure(const Domain &domain, const Signature::Sptr &signature)
    : m_domain(domain), m_signature(signature)
{
}

void LStructure::addFunction(const FunctionSymbol &fsymb, const Function &func)
{
    if (m_signature->hasFunctionSymbol(fsymb, func->getArity()))
        m_fmap[fsymb] = func;
    else
        throw std::runtime_error{"Unknown function symbol or incorrect arity!\n"};
}

void LStructure::addRelation(const RelationSymbol &rsymb, const Relation &rel)
{
    if (m_signature->hasRelationSymbol(rsymb, rel->getArity()))
        m_rmap[rsymb] = rel;
    else
        throw std::runtime_error{"Unknown relation symbol or incorrect arity!\n"};
}

const Function &LStructure::getFunction(const FunctionSymbol &fsymb) const
{
    return m_fmap.at(fsymb);
}

const Relation &LStructure::getRelation(const RelationSymbol &rsymb) const
{
    return m_rmap.at(rsymb);
}
