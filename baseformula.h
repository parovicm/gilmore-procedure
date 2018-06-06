#ifndef BASEFORMULA_H
#define BASEFORMULA_H

#include <iostream>
#include <memory>
#include <vector>
#include "common.h"
#include "lstructure.h"
#include "valuation.h"
#include "baseterm.h"

class BaseFormula;

using Formula = std::shared_ptr<BaseFormula>;

using LiteralList = std::vector<Formula>;
using LiteralListList = std::vector<LiteralList>;

class BaseFormula : public std::enable_shared_from_this<BaseFormula> {
public:
    BaseFormula();
    virtual ~BaseFormula();
    virtual std::ostream& print(std::ostream& out) const = 0;
    virtual unsigned complexity() const = 0;
    virtual bool equalTo(const Formula& f) const;

    virtual void getVars(VariablesSet& vset, bool free=false) const = 0;

    virtual void getFunctions(FunctionSet& fset) const = 0;

    bool containsVariable(const Variable& v, bool free = false) const;

    virtual bool eval(const LStructure& structure, const Valuation& v) const = 0;
    virtual Formula substitute(const Variable& v, const Term& t) const = 0;

    template <typename Derived>
    static inline const Derived* isOfType(const Formula &f) {
            return dynamic_cast<const Derived*>(f.get());
    }

    virtual Formula simplify() const;
    virtual Formula nnf() const;
    virtual LiteralListList listDNF() const = 0;

    virtual Formula pullQuantifiers() const;
    virtual Formula prenex() const;

    virtual Formula skolem(Signature::Sptr s, VariablesSet &&vars={}) const;

    template <typename ListType>
    static ListType concatenate(const ListType& l1, const ListType& l2);

    static LiteralListList cross(const LiteralListList& l1, const LiteralListList& l2);

};

template <typename ListType>
ListType BaseFormula::concatenate(const ListType& l1, const ListType& l2) {

    ListType result;
    result.reserve(l1.size() + l2.size());
    std::copy(l1.begin(), l1.end(), std::back_inserter(result));
    std::copy(l2.begin(), l2.end(), std::back_inserter(result));
    return result;
}

/* Funkcija racuna matriks formule f koja je u Skolemovoj normalnoj formi. */
Formula removeUniversalFromSkolem(const Formula& f);

std::ostream& operator<<(std::ostream& out, const LiteralListList& l);


std::ostream& operator<<(std::ostream& out, const Formula& f);

#endif // BASEFORMULA_H
