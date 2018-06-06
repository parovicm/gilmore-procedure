#ifndef NOT_H
#define NOT_H

#include "unaryconnective.h"

class Not : public UnaryConnective {
public:
    Not(const Formula& f);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;
    LiteralListList listDNF() const;
};


#endif // NOT_H
