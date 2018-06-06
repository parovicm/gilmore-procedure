#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "atomicformula.h"

class True : public AtomicFormula {
public:
    True();
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    LiteralListList listDNF() const;
};

class False : public AtomicFormula {
public:
    False();
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    LiteralListList listDNF() const;
};


#endif // CONSTANTS_H
