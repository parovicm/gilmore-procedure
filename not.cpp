#include "not.h"
#include "first_order_logic.h"

Not::Not(const Formula &f)
    : UnaryConnective(f)
{
}

std::ostream &Not::print(std::ostream &out) const
{
    out << "~(";
    m_op->print(out);
    return out << ")";
}

bool Not::eval(const LStructure &structure, const Valuation &v) const
{
    return !m_op->eval(structure, v);
}

Formula Not::substitute(const Variable &v, const Term &t) const
{
    return std::make_shared<Not>(m_op->substitute(v, t));
}

Formula Not::simplify() const
{
    Formula op = operand()->simplify();
    if(BaseFormula::isOfType<True>(op))
        return std::make_shared<False>();
    else if(BaseFormula::isOfType<False>(op))
        return std::make_shared<True>();
    else
        return std::make_shared<Not>(op);
}

Formula Not::nnf() const
{
    Formula op = operand()->nnf();

    if(BaseFormula::isOfType<Not>(op)) {
        const Not* notOp = static_cast<const Not*>(op.get());
        return notOp->operand()->nnf();
    }

    else if(BaseFormula::isOfType<And>(op)) {
        const And* andOp = static_cast<const And*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = andOp->operands();
        return std::make_shared<Or>(std::make_shared<Not>(op1)->nnf(),
                                    std::make_shared<Not>(op2)->nnf());
    }

    else if(BaseFormula::isOfType<Or>(op)) {
        const Or* orOp = static_cast<const Or*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = orOp->operands();
        return std::make_shared<And>(std::make_shared<Not>(op1)->nnf(),
                                    std::make_shared<Not>(op2)->nnf());
    }

    else if(BaseFormula::isOfType<Imp>(op)) {
        const Imp* impOp = static_cast<const Imp*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = impOp->operands();
        return std::make_shared<And>(op1->nnf(),
                                     std::make_shared<Not>(op2)->nnf());
    }

    else if(BaseFormula::isOfType<Iff>(op)) {
        const Iff* iffOp = static_cast<const Iff*>(op.get());
        Formula op1, op2;
        std::tie(op1, op2) = iffOp->operands();
        return std::make_shared<Or>(std::make_shared<And>(
                                        std::make_shared<Not>(op1)->simplify(),
                                        op2->simplify()),
                                    std::make_shared<And>(
                                        op1->simplify(),
                                        std::make_shared<Not>(op2)->simplify()
                                        ));
    }
    else if(BaseFormula::isOfType<Exists>(op)) {
        const Exists* existsOp = static_cast<const Exists*>(op.get());
        Formula op1 = existsOp->operand();
        Variable var = existsOp->variable();
        return std::make_shared<Forall>(var, std::make_shared<Not>(op1)->nnf());
    }
    else if(BaseFormula::isOfType<Forall>(op)) {
        const Forall* forallOp = static_cast<const Forall*>(op.get());
        Formula op1 = forallOp->operand();
        Variable var = forallOp->variable();
        return std::make_shared<Exists>(var, std::make_shared<Not>(op1)->nnf());
    }
    else
        return std::make_shared<Not>(op);
}

LiteralListList Not::listDNF() const
{
    return {{ std::const_pointer_cast<BaseFormula>(shared_from_this()) }};
}
