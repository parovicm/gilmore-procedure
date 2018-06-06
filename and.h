#ifndef AND_H
#define AND_H

#include "binaryconnective.h"

class And : public BinaryConnective {

public:
    And(const Formula& op1, const Formula& op2);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;

    Formula pullQuantifiers() const;
    Formula prenex() const;

    LiteralListList listDNF() const;
};




#endif // AND_H
