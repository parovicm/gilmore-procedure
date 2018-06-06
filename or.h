#ifndef OR_H
#define OR_H

#include "binaryconnective.h"

class Or : public BinaryConnective {

public:
    Or(const Formula& op1, const Formula& op2);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;

    Formula pullQuantifiers() const;
    Formula prenex() const;

    LiteralListList listDNF() const;
};


#endif // OR_H
