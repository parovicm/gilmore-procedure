#ifndef HERBRAND_UNIVERSE_H
#define HERBRAND_UNIVERSE_H

#include "first_order_logic.h"
#include "utils.h"

/**
  Klasa za generisanje Erbranovog univerzuma za datu signaturu i formulu.
 */
class HerbrandUniverse {
public:
    /* Konstruktor koji pravi objekat za datu signaturu i formulu. */
    HerbrandUniverse(const Signature::Sptr& signature, const Formula& formula);

    /* Metod koji generise sljedeci nivo E(i+1) Erbranovog univerzuma
       tako da i svi prethodni elementi univerzuma budu u njemu, tj.
       E(i) je podskup od E(i+1). */
    void nextApplication();

    /* Get metod za Erbranov univerzum. */
    const std::set<Term>& universe() const;

    /* Metod koji stampa elemente univerzuma na zadati ostream. */
    std::ostream& print(std::ostream& out) const;

private:
    /* Signatura */
    Signature::Sptr m_signature;

    /* Formula */
    Formula m_formula;

    /* Skup funkcijskih simbola formule ukljucujuci i konstante. */
    FunctionSet m_functions;

    /* Erbranov univerzum predstvljamo kao skup termova. */
    std::set<Term> m_universe;

    /* Ova clanica ce sadrzati generisanu konstantu, ako se u formuli ne javlja
       nijedna konstanta. */
    FunctionSymbol m_constant = "";
};

/* Operator << za ispis elemenata Erbranovog univerzuma. */
std::ostream& operator<<(std::ostream& out, const HerbrandUniverse& universe);

#endif // HERBRAND_UNIVERSE_H
