#ifndef GILMORE_PROCEDURE_H
#define GILMORE_PROCEDURE_H

#include "first_order_logic.h"
#include "herbrand_universe.h"

#define MAX_ITERATIONS 3

/* Nabrojivi tip koji je povratna vrijednost Gilmorove procedure. */
enum ProcedureState {
    VALID,
    MAX_ITERATIONS_REACHED
};

/* Glavna funkcija koja implementira Gilmorovu proceduru. Funkcija prihvata signaturu
 * i formulu f te signature za koju se dokazuje da je valjana.
 * Povratna vrijednost je: VALID - ako je f valjana ili
 *                         MAX_ITERATIONS_REACHED - ako je dostignut maksimalni
 *                         dozvoljeni broj iteracija prije nego sto je dokazano
 *                         da je formula valjana.
 * U funkciji se f negira, zatim se vrsi skolemizacija, a onda i uklanjanje
 * univerzalnih kvantifikatora sa pocetka formule. Nakon toga se, korak po korak,
 * generise Erbranov univerzum formule i na osnovu njega se prave bazne instance,
 * koje se spajaju konjunkcijom. Tako dobijena formula se prevodi u DNF, i provjerava
 * se da li su sve konjunkcije u DNF-u netacne. Ukoliko jesu, vraca se VALID, a inace
 * se generise sljedeci nivo Erbranovog univerzuma.
 * Opisani korak se ponavlja najvise MAX_ITERATIONS puta.
 */
ProcedureState gilmoreProcedure(const Signature::Sptr& signature, const Formula& f);

#endif // GILMORE_PROCEDURE_H
