#include "constants.h"

True::True()
    : AtomicFormula()
{
}

std::ostream &True::print(std::ostream &out) const
{
    return out << "T";
}

bool True::eval(const LStructure &structure, const Valuation &v) const
{
    UNUSED_ARG(structure);
    UNUSED_ARG(v);
    return true;
}

LiteralListList True::listDNF() const
{
    return {{}};
}

False::False()
    : AtomicFormula()
{
}

std::ostream &False::print(std::ostream &out) const
{
    return out << "F";
}

bool False::eval(const LStructure &structure, const Valuation &v) const
{
    UNUSED_ARG(structure);
    UNUSED_ARG(v);
    return false;
}

LiteralListList False::listDNF() const
{
    return {};
}
