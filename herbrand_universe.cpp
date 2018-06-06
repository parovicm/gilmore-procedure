#include "herbrand_universe.h"
#include <algorithm>
#include <iterator>

HerbrandUniverse::HerbrandUniverse(const Signature::Sptr &signature, const Formula &formula)
    : m_signature(signature), m_formula(formula)
{
    /* Nalaze se funkcijski simboli u formuli, ukljucujuci i konstante. */
    m_formula->getFunctions(m_functions);

    /* Inicijalno se u Erbanov univerzum dodaju samo konstante iz formule. */
    for(const FunctionSymbol& fsymb : m_functions)
        if(signature->getFunctionArity(fsymb) == 0)
            m_universe.insert(std::make_shared<FunctionTerm>(m_signature, fsymb));

    /* Ako formula ne sadrzi nijednu konstantu, dodaje se nova konstanta
     * u Erbranov univerzum i u signaturu. */
    if(m_universe.empty()) {
        m_constant = m_signature->getUniqueFunctionSymbol();
        m_signature->addFunctionSymbol(m_constant, 0);
        m_universe.insert(std::make_shared<FunctionTerm>(m_signature, m_constant));
    }
}

void HerbrandUniverse::nextApplication()
{
    /* Vektor za cuvanje svih varijacija sa ponavljanjem. */
    std::vector<std::vector<Term>> variations;
    /* Kopija prethnodnog univerzuma. */
    std::set<Term> universeCopy;
    universeCopy.insert(m_universe.cbegin(), m_universe.cend());
    m_universe.clear();

    /* Ako je u univerzum bila dodata nova konstanta dodajemo je ponovo. */
    if(m_constant != "")
        m_universe.insert(std::make_shared<FunctionTerm>(m_signature, m_constant));

    /*Za svaki funkcijski simbol koji se pojavljuje u formuli... */
    for(const FunctionSymbol& fsym : m_functions) {
        variations.clear();
        unsigned length = m_signature->getFunctionArity(fsym);
        /* ... arnosti length, generisu se sve varijacije sa ponavljanjem
         * elemenata prethodnog Erbranovog univerzuma duzine length...
         */
        std::vector<Term> current(length);
        variations_with_repetition<Term>(0, length, current, universeCopy, variations);

        /* ... i u Erbranov univerzum se dodaje term koji nastaje primjenom
         * tog funkcijskog simbola na svaku od dobijenih varijacija.
         */
        for(const auto& v : variations)
            m_universe.insert(std::make_shared<FunctionTerm>(m_signature, fsym, v));
    }
}

const std::set<Term> &HerbrandUniverse::universe() const
{
    return m_universe;
}

std::ostream& HerbrandUniverse::print(std::ostream &out) const
{
    /* Stampaju se svi termovi koji se nalaze u Erbranovom univerzumu,
     * razdvojeni znakom za novi red. */
    for(const auto& t : m_universe) {
        t->print(out);
        out << '\n';
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const HerbrandUniverse& universe) {
    return universe.print(out);
}
