#ifndef EXISTS_H
#define EXISTS_H

#include "quantifier.h"

class Exists : public Quantifier {
public:
    Exists(const Variable& v, const Formula& op);
    std::ostream &print(std::ostream &out) const;
    bool eval(const LStructure &structure, const Valuation &v) const;
    Formula substitute(const Variable &v, const Term &t) const;

    Formula simplify() const;
    Formula nnf() const;

    Formula prenex() const;
    Formula skolem(Signature::Sptr s, VariablesSet &&vars) const;
};

#endif // EXISTS_H
