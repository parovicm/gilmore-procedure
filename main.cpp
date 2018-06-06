#include <iostream>

#include "first_order_logic.h"
#include "herbrand_universe.h"
#include "gilmore_procedure.h"

using namespace std;

class Zero : public BaseFunction {
public:
    Zero()
        : BaseFunction(0)
    {}

    AnyType eval(const std::vector<AnyType> &args) const {
        UNUSED_ARG(args);
        return 0;
    }
};

class One : public BaseFunction {
public:
    One()
        : BaseFunction(0)
    {}

    AnyType eval(const std::vector<AnyType> &args) const {
        UNUSED_ARG(args);
        return 1;
    }
};

class Even : public BaseRelation {

public:
    Even()
        : BaseRelation(1)
    {}

    bool eval(const std::vector<AnyType> &args) const {
        if(args.size() != getArity())
            throw std::runtime_error{"Invalid number of arguments for Even relation!\n"};
        int val = AnyTypeToType(int, args[0]);
        return val % 2 == 0;
    }
};

class PlusModN : public BaseFunction {
public:
    PlusModN(int mod)
        : BaseFunction(2), m_mod(mod)
    {}

    AnyType eval(const std::vector<AnyType> &args) const {
        if(args.size() != getArity())
            throw std::runtime_error{"Invalid number of arguments for PlusMod2 function!\n"};

        int val1 = AnyTypeToType(int, args[0]);
        int val2 = AnyTypeToType(int, args[1]);
        return (val1+val2)%m_mod;
    }
private:
    int m_mod;
};

int main()
{

    /*--------------------------------------------------------------------------------*/
    /* PRVI PRIMJER */
    /*--------------------------------------------------------------------------------*/

    Signature::Sptr sig_test1 = std::make_shared<Signature>();

    sig_test1->addFunctionSymbol("f", 1);
    sig_test1->addFunctionSymbol("g", 1);
    sig_test1->addRelationSymbol("P", 2);

    //tx = x
    Term tx = std::make_shared<VariableTerm>("x");

    Term fx = std::make_shared<FunctionTerm>(sig_test1, "f", std::vector<Term>{tx});
    //ty = y
    Term ty = std::make_shared<VariableTerm>("y");

    Term gy = std::make_shared<FunctionTerm>(sig_test1, "g", std::vector<Term>{ty});

    Formula f0 = std::make_shared<Atom>(sig_test1, "P", std::vector<Term>{tx, fx});
    Formula f1 = std::make_shared<Atom>(sig_test1, "P", std::vector<Term>{gy, ty});

    Formula f2 = std::make_shared<Atom>(sig_test1, "P", std::vector<Term>{tx, fx});
    f2->substitute("x", ty);

    Formula f0orNotf2 = std::make_shared<Or>(f0, std::make_shared<Not>(f2));

    Formula f0orNotf1 = std::make_shared<Or>(f0, std::make_shared<Not>(f1));

    Formula F_V = std::make_shared<Forall>("x", std::make_shared<Forall>("y", f0orNotf2));

    Formula F_UNV = std::make_shared<Forall>("x", std::make_shared<Forall>("y", f0orNotf1));


    if(gilmoreProcedure(sig_test1, F_V) == VALID)
        std::cout << "VALID" << std::endl;
    else
        std::cout << "MAX_ITERATIONS_REACHED" << std::endl;


    if(gilmoreProcedure(sig_test1, F_UNV) == VALID)
        std::cout << "VALID" << std::endl;
    else
        std::cout << "MAX_ITERATIONS_REACHED" << std::endl;


    /*--------------------------------------------------------------------------------*/
    /* DRUGI PRIMJER */
    /*--------------------------------------------------------------------------------*/

    /*
    Signature::Sptr sig = std::make_shared<Signature>();

    sig->addFunctionSymbol("0", 0);
    sig->addFunctionSymbol("1", 0);
    sig->addFunctionSymbol("+", 2);
    sig->addFunctionSymbol("*", 2);
    sig->addRelationSymbol("even", 1);
    sig->addRelationSymbol("odd", 1);
    sig->addRelationSymbol("=", 2);
    sig->addRelationSymbol("<=", 2);

    //t0 = 0
    Term t0 = std::make_shared<FunctionTerm>(sig, "0");
    //t1 = 1
    Term t1 = std::make_shared<FunctionTerm>(sig, "1");

    //f0 = even(t0) = even(0) -------------- True
    Formula f0 = std::make_shared<Atom>(sig, "even", std::vector<Term>{t0});

    std::cout << f0 << std::endl;

    //f1 = even(t1) = even(1) -------------- False
    Formula f1 = std::make_shared<Atom>(sig, "even", std::vector<Term>{t1});

    std::cout << f1 << std::endl;

    //tx = x
    Term tx = std::make_shared<VariableTerm>("x");
    //ty = y
    Term ty = std::make_shared<VariableTerm>("y");

    //xpy = tx+ty = x+y
    Term xpy = std::make_shared<FunctionTerm>(sig, "+", std::vector<Term>{tx, ty});

    //xeven = even(x)
    Formula xeven = std::make_shared<Atom>(sig, "even", std::vector<Term>{tx});

    //yeven = even(y)
    Formula yeven = std::make_shared<Atom>(sig, "even", std::vector<Term>{ty});

    //xpyeven = even(tx+ty) = even(x+y)
    Formula xpyeven = std::make_shared<Atom>(sig, "even", std::vector<Term>{xpy});

    std::cout << xpyeven << std::endl;

    //xandy = xeven /\\ yeven = even(x) /\\ even(y)
    Formula xandy = std::make_shared<And>(xeven, yeven);
    //imp = xandy => xpyeven = even(x) /\\ even(y) => even(x+y)
    Formula imp = std::make_shared<Imp>(xandy, xpyeven);

    //forall_x = Vx. imp
    Formula forall_x = std::make_shared<Forall>("x", imp);

    //forall_y = Vy. forall_x = Vy. Vx. imp
    Formula forall_y = std::make_shared<Forall>("y", forall_x);

    std::cout << forall_y << std::endl;

    Domain idomain = std::make_shared<DomainSpecialization<int>>();
    idomain->insert(0);
    idomain->insert(1);
    idomain->insert(2);
    idomain->insert(3);
    idomain->insert(4);
    idomain->insert(5);
    idomain->insert(6);
    idomain->insert(7);

    LStructure structure(idomain, sig);
    structure.addFunction("+", std::make_shared<PlusModN>(8));
    structure.addFunction("0", std::make_shared<Zero>());
    structure.addFunction("1", std::make_shared<One>());
    structure.addRelation("even", std::make_shared<Even>());

    Valuation v(idomain);
    //x = 0
    v.setValue("x", 0);
    //y = 0
    v.setValue("y", 0);

    std::cout << std::boolalpha << f0->eval(structure, v) << std::endl;
    std::cout << f1->eval(structure, v) << std::endl;
    std::cout << xpyeven->eval(structure, v) << std::endl;
    std::cout << forall_y->eval(structure, v) << std::endl;


    // f = (Ex. even(x) \/ Ex. odd(x)) => (Vx. even(x) \/ Vy.Ex. odd(x+y))
    Formula f = std::make_shared<Imp>(std::make_shared<Or>(std::make_shared<Exists>("x", xeven),
                           std::make_shared<Exists>("x", std::make_shared<Atom>(sig, "odd", std::vector<Term>{ tx }))),
                         std::make_shared<Forall>("x", std::make_shared<Or>(xeven,
                                   std::make_shared<Forall>("y", std::make_shared<Exists>("x",
                                               std::make_shared<Atom>(sig, "odd", std::vector<Term>{ xpy }))))));


    Formula fSimp = f->simplify();

    Formula fNNF = fSimp->nnf();

    Formula fPrenex = fNNF->prenex();

    VariablesSet varSet;
    Formula fSkolem = fPrenex->skolem(sig);

    fSkolem->getVars(varSet);

    //(even(0) \/ even(1)) /\ f
    Formula myF = std::make_shared<And>(std::make_shared<Or>(f0, f1), f);
    HerbrandUniverse universe(sig, myF);

    if(gilmoreProcedure(sig, forall_y) == VALID)
        std::cout << "VALID" << std::endl;
    else
        std::cout << "MAX_ITERATIONS_REACHED" << std::endl;
    */
    return 0;
}
