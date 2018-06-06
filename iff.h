#ifndef IFF_H
#define IFF_H

#include "binaryconnective.h"

class Iff : public BinaryConnective {

public:
    Iff(const Formula& op1, const Formula& op2);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;
    LiteralListList listDNF() const;
};

#endif // IFF_H
