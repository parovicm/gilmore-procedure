#ifndef FORALL_H
#define FORALL_H

#include "quantifier.h"

class Forall : public Quantifier {
public:
    Forall(const Variable& v, const Formula& op);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;

    Formula prenex() const;
    Formula skolem(Signature::Sptr s, VariablesSet &&vars) const;
};

#endif // FORALL_H
