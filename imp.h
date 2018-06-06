#ifndef IMP_H
#define IMP_H

#include "binaryconnective.h"

class Imp : public BinaryConnective {

public:
    Imp(const Formula& op1, const Formula& op2);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;
    LiteralListList listDNF() const;
};

#endif // IMP_H
