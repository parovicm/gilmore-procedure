#include "and.h"
#include "first_order_logic.h"

And::And(const Formula &op1, const Formula &op2)
    : BinaryConnective(op1, op2)
{
}

std::ostream &And::print(std::ostream &out) const
{
    return printImpl(out, "/\\");
}

bool And::eval(const LStructure &structure, const Valuation &v) const
{
    return m_op1->eval(structure, v) && m_op2->eval(structure, v);
}

Formula And::substitute(const Variable &v, const Term &t) const
{
    return substituteImpl<And>(v, t);
}

Formula And::simplify() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    op1 = op1->simplify();
    op2 = op2->simplify();

    if(BaseFormula::isOfType<True>(op1))
        return op2;
    else if(BaseFormula::isOfType<True>(op2))
        return op1;
    else if(BaseFormula::isOfType<False>(op1) || BaseFormula::isOfType<False>(op2))
        return std::make_shared<False>();
    else
        return std::make_shared<And>(op1, op2);
}

Formula And::nnf() const
{
    return std::make_shared<And>(m_op1->nnf(), m_op2->nnf());
}

Formula And::pullQuantifiers() const
{
    const Forall* op1 = BaseFormula::isOfType<Forall>(m_op1);
    const Forall* op2 = BaseFormula::isOfType<Forall>(m_op2);

    if(op1 && op2) {
        if(op1->variable() == op2->variable()) {
            return std::make_shared<Forall>(op1->variable(),
                       std::make_shared<And>(op1->operand(),
                                             op2->operand())->pullQuantifiers());
        }
        else {
            Variable renamed = Quantifier::getUniqueVarName(op1->operand(), op2->operand());
            return std::make_shared<Forall>(renamed,
                       std::make_shared<And>(op1->operand()->substitute(op1->variable(),
                                 std::make_shared<VariableTerm>(renamed)),
                                             op2->operand()->substitute(op2->variable(),
                                 std::make_shared<VariableTerm>(renamed)))->pullQuantifiers());
        }
    }
    else if(op1) {
        if(m_op2->containsVariable(op1->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(op1->operand(), m_op2);
            return std::make_shared<Forall>(renamed,
                        std::make_shared<And>(op1->operand()->substitute(op1->variable(),
                           std::make_shared<VariableTerm>(renamed)), m_op2)->pullQuantifiers());
        }
        else {
            return std::make_shared<Forall>(op1->variable(),
                        std::make_shared<And>(op1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if(op2) {
        if(m_op1->containsVariable(op2->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(op2->operand(), m_op1);
            return std::make_shared<Forall>(renamed,
                        std::make_shared<And>(m_op1, op2->operand()->substitute(op2->variable(),
                                std::make_shared<VariableTerm>(renamed)))->pullQuantifiers());
        }
        else {
            return std::make_shared<Forall>(op2->variable(),
                        std::make_shared<And>(m_op1, op2->operand())->pullQuantifiers());
        }
    }


    const Exists* eop1 = BaseFormula::isOfType<Exists>(m_op1);
    const Exists* eop2 = BaseFormula::isOfType<Exists>(m_op2);

    if(eop1) {
        if(m_op2->containsVariable(eop1->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(eop1->operand(), m_op2);
            return std::make_shared<Exists>(renamed,
                        std::make_shared<And>(eop1->operand()->substitute(eop1->variable(),
                           std::make_shared<VariableTerm>(renamed)), m_op2)->pullQuantifiers());
        }
        else {
            return std::make_shared<Exists>(eop1->variable(),
                        std::make_shared<And>(eop1->operand(), m_op2)->pullQuantifiers());
        }
    }
    else if(eop2) {
        if(m_op1->containsVariable(eop2->variable(), true)) {
            Variable renamed = Quantifier::getUniqueVarName(eop2->operand(), m_op1);
            return std::make_shared<Exists>(renamed,
                        std::make_shared<And>(m_op1, eop2->operand()->substitute(eop2->variable(),
                                std::make_shared<VariableTerm>(renamed)))->pullQuantifiers());
        }
        else {
            return std::make_shared<Exists>(eop2->variable(),
                        std::make_shared<And>(m_op1, eop2->operand())->pullQuantifiers());
        }
    }
    return std::const_pointer_cast<BaseFormula>(shared_from_this());
}

Formula And::prenex() const
{
    return std::make_shared<And>(m_op1->prenex(), m_op2->prenex())->pullQuantifiers();
}

LiteralListList And::listDNF() const
{
    Formula op1, op2;
    std::tie(op1, op2) = operands();
    return BaseFormula::cross(op1->listDNF(), op2->listDNF());
}
