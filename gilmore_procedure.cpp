#include "gilmore_procedure.h"
#include <algorithm>

ProcedureState gilmoreProcedure(const Signature::Sptr &signature, const Formula &f)
{
    /* Formula f cija se valjanost dokazuje se negira. */
    Formula notF = std::make_shared<Not>(f);

    /* Negirana formula se prevodi u Skolemovu normalnu formu. */
    Formula skolemNotF = notF->simplify()->nnf()->prenex()->skolem(signature);

    /* Sa pocetka formule f se uklanjaju eventualni univerzalni kvantifikatori. */
    Formula fBase = removeUniversalFromSkolem(skolemNotF);

    /* Formira se Erbranov univezum formule f. */
    HerbrandUniverse universe(signature, skolemNotF);

    /* Nalazi se skup promjenljvih koje se pojavljuju u formuli nakon
     * skolemizacije, i taj skup se kopira u vektor zbog indeksiranja
     * prilikom supstitucije.
    */
    VariablesSet vset;
    f->getVars(vset);
    std::vector<Variable> variables;
    std::copy(vset.cbegin(), vset.cend(), std::back_inserter(variables));

    /* Promjenljiva nVars je broj promjenljivih u formuli nakon skolemizacije. */
    unsigned nVars = variables.size();

    /* MAX_ITERATIONS puta se ponavlja sljedeci korak... */
    for(unsigned iter = 0; iter < MAX_ITERATIONS; iter++) {

        /* Racuna se skup varijacija sa ponavljanjem duzine nVars
         * od elemenata Erbranovog univerzuma i tako dobijeni skup
         * se cuva u vektoru variations.
        */
        std::vector < std::vector<Term> > variations;
        std::vector <Term> current(nVars);        
        variations.clear();
        variations_with_repetition<Term>(0, nVars, current, universe.universe(), variations);

        /* Formira se formula F koja ce biti konjukcija svih baznih instanci dobijenih
         * supstitucijom promjenljivih iz formule fBase svakom od izracunatih varijacija
         * sa ponavljanjem.
        */

        /* Na pocetku, F prestavlja formulu nastalu supstitucijom promjenljivih termovima prve
         * varijacije... */
        Formula F = fBase;
        for(unsigned i = 0; i < nVars; i++)
            F = F->substitute(variables[i], variations[0][i]);

        /* ...a zatim se na F konjukcijom nadovezuju i formule Fi nastale supstitujom
         * svim ostalim varijacijama. */
        for(unsigned i = 1; i < variations.size(); i++) {
            Formula Fi = fBase;
            for(unsigned j = 0; j < nVars; j++)
                Fi = Fi->substitute(variables[j], variations[i][j]);
            F = std::make_shared<And>(F, Fi);
        }

        /* Nalazi se DNF tako dobijene formule. */
        LiteralListList dnfF = F->listDNF();

        /* Brojac koji ce biti jednak broju netacnih konjunkcija u DNF-u. */
        unsigned nFalseConjuctions = 0;

        /* Za svaku konjukciju u DNF-u... */
        for(const LiteralList& conjunction : dnfF) {
            /* Vektor nenegiranih atoma u trenutnoj konjunkciji. */
            LiteralList positive;

            /* Vektor negiranih atoma u trenutnoj konjunkciji. */
            LiteralList negative;

            /* Za svaki literal u konjunkciji... */
            for(const Formula& literal : conjunction) {
                /* Ako je literal negacija atoma... */
                if(BaseFormula::isOfType<Not>(literal)) {
                    const Not* notF = static_cast<const Not*>(literal.get());
                    /*... ako postoji atom koji je jednak njemu u vektoru nenegiranih atoma
                     * trenutna konjunkcija je netacna, pa se brojac uvecava i prelazi se na
                     * sljedecu zbog break naredbe. */
                    if(std::find_if(positive.begin(), positive.end(),
                                    [&](const auto& fla) {
                                        return notF->operand()->equalTo(fla);
                                    }) != positive.end()) {
                        nFalseConjuctions++;
                        break;
                    }
                    /* inace se operand negiranog atoma dodaje u vektor negiranih atoma formule. */
                    else
                        negative.push_back(notF->operand());
                }
                /* Ako je literal atom... */
                else {
                    /*... ako postoji atom koji je jednak njemu u vektoru negiranih atoma
                     * trenutna konjunkcija je netacna, pa se brojac uvecava i prelazi se na
                     * sljedecu zbog break naredbe. */
                    if(std::find_if(negative.begin(), negative.end(),
                                    [&](const auto& fla) {
                                        return literal->equalTo(fla);
                                    }) != negative.end()) {
                        nFalseConjuctions++;
                        break;
                    }
                    /* inace se atom dodaje u vektor nenegiranih atoma formule. */
                    else
                        positive.push_back(literal);
                }
            }
            /* Vektori se prazne da bi bili spremni za sljedecu konjunkciju. */
            positive.clear();
            negative.clear();
        }

        /* Ako je broj netacnih konjunkcija jednak ukupnom broju konjunkcija,
         * formula je nezadovoljiva, pa je f valjana.
         */
        if(nFalseConjuctions == dnfF.size())
            return VALID;
        /* inace se prelazi na sljedeci nivo Erbranovog univerzuma. */
        universe.nextApplication();
    }
    return MAX_ITERATIONS_REACHED;
}
