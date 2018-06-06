#include "or.h"
#include "first_order_logic.h"

Or::Or(const Formula &op1, const Formula &op2)
    : BinaryConnective(op1, op2)
{
}

std::ostream &Or::print(std::ostream &out) const
{
    return printImpl(out, "\\/");
}

bool Or::eval(const LStructure &structure, const Valuation &v) const
{
    return m_op1->eval(structure, v) || m_op2->eval(structure, v);
}

Formula Or::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<Or>(v, t);
}


Formula Or::simplify() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    op1 = op1->simplify();
    op2 = op2->simplify();

    if(BaseFormula::isOfType<False>(op1))
        return op2;
    else if(BaseFormula::isOfType<False>(op2))
        return op1;
    else if(BaseFormula::isOfType<True>(op1) || BaseFormula::isOfType<True>(op2))
        return std::make_shared<True>();
    else
        return std::make_shared<Or>(op1, op2);
}


Formula Or::nnf() const
{
    return std::make_shared<Or>(m_op1->nnf(), m_op2->nnf());
}

Formula Or::pullQuantifiers() const
{

    const Exists* op1 = BaseFormula::isOfType<Exists>(m_op1);
    const Exists* op2 = BaseFormula::isOfType<Exists>(m_op2);

    if(op1 && op2) {
        if(op1->variable() == op2->variable()) {
            return std::make_shared<Exists>(op1->variable(),
                       std::make_shared<Or>(op1->operand(),
                                             op2->operand())->pullQuantifiers());
        }
        else {
            Variable renamed = Quantifier::getUniqueVarName(op1->operand(), op2->operand());
            return std::make_shared<Exists>(renamed,
                       std::make_shared<Or>(op1->operand()->substitute(op1->variable(),
                                 std::make_shared<VariableTerm>(renamed)),
                                             op2->operand()->substitute(op2->variable(),
                                 std::make_shared<VariableTerm>(renamed)))->pullQuantifiers());
        }
    }
    else if(op1) {
        if(m_op2->containsVariable(op1->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(op1->operand(), m_op2);
            return std::make_shared<Exists>(renamed,
                        std::make_shared<Or>(op1->operand()->substitute(op1->variable(),
                           std::make_shared<VariableTerm>(renamed)), m_op2)->pullQuantifiers());
        }
        else {
            return std::make_shared<Exists>(op1->variable(),
                        std::make_shared<Or>(op1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if(op2) {
        if(m_op1->containsVariable(op2->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(op2->operand(), m_op1);
            return std::make_shared<Exists>(renamed,
                        std::make_shared<Or>(m_op1, op2->operand()->substitute(op2->variable(),
                                std::make_shared<VariableTerm>(renamed)))->pullQuantifiers());
        }
        else {
            return std::make_shared<Exists>(op2->variable(),
                        std::make_shared<Or>(m_op1, op2->operand())->pullQuantifiers());
        }
    }


    const Forall* eop1 = BaseFormula::isOfType<Forall>(m_op1);
    const Forall* eop2 = BaseFormula::isOfType<Forall>(m_op2);

    if(eop1) {
        if(m_op2->containsVariable(eop1->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(eop1->operand(), m_op2);
            return std::make_shared<Forall>(renamed,
                        std::make_shared<Or>(eop1->operand()->substitute(eop1->variable(),
                           std::make_shared<VariableTerm>(renamed)), m_op2)->pullQuantifiers());
        }
        else {
            return std::make_shared<Forall>(eop1->variable(),
                        std::make_shared<Or>(eop1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if(eop2) {
        if(m_op1->containsVariable(eop2->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(eop2->operand(), m_op1);
            return std::make_shared<Forall>(renamed,
                        std::make_shared<Or>(m_op1, eop2->operand()->substitute(eop2->variable(),
                                std::make_shared<VariableTerm>(renamed)))->pullQuantifiers());
        }
        else {
            return std::make_shared<Forall>(eop2->variable(),
                        std::make_shared<Or>(m_op1, eop2->operand())->pullQuantifiers());
        }
    }
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula Or::prenex() const
{
    return std::make_shared<Or>(m_op1->prenex(), m_op2->prenex())->pullQuantifiers();
}

LiteralListList Or::listDNF() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    return BaseFormula::concatenate(op1->listDNF(), op2->listDNF());
}


