#include "binaryconnective.h"

BinaryConnective::BinaryConnective(const Formula &op1, const Formula &op2)
    : BaseFormula(), m_op1(op1), m_op2(op2)
{
}

unsigned BinaryConnective::complexity() const
{
    return 1 + m_op1->complexity() + m_op2->complexity();
}

bool BinaryConnective::equalTo(const Formula &f) const
{
    if(BaseFormula::equalTo(f)) {
        const BinaryConnective* bPtr = static_cast<const BinaryConnective*>(f.get());
        return m_op1->equalTo(bPtr->m_op1) && m_op2->equalTo(bPtr->m_op2);
    }
    return false;
}

void BinaryConnective::getVars(VariablesSet &vset, bool free) const
{
    m_op1->getVars(vset, free);
    m_op2->getVars(vset, free);
}

void BinaryConnective::getFunctions(FunctionSet &fset) const
{
    m_op1->getFunctions(fset);
    m_op2->getFunctions(fset);
}

std::pair<Formula, Formula> BinaryConnective::operands() const
{
    return std::make_pair(m_op1, m_op2);
}

Formula BinaryConnective::pullQuantifiers() const
{
    //za iff i imp
    throw std::runtime_error{"Formula in NNF does not contain this connective!\n"};
}

Formula BinaryConnective::prenex() const
{
    //za iff i imp
    throw std::runtime_error{"Formula in NNF does not contain this connective!\n"};
}

std::ostream &BinaryConnective::printImpl(std::ostream &out, const std::string &symbol) const
{
    out << '(';
    m_op1->print(out);
    out << ' ' << symbol << ' ';
    m_op2->print(out);
    return out << ')';
}
