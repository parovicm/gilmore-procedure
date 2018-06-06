#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <set>

/*
  Funkcija generise sve varijacije sa ponavljanjem zadate duzine koje se dobijaju od
  elemenata skupa items.
  Rezultat je u vektoru result.
  Argument pos je fiktivni argument koji olaksava realizaciju rekurzije. Prilikom
  poziva treba proslijediti 0 na mjestu tog argumenta.
  Varijacija koja se trenutno generise je smjestena u vektor current.
*/

template <typename T>
void variations_with_repetition(unsigned pos, unsigned length, std::vector<T> current, const std::set<T>& items,
                std::vector< std::vector<T> >& result)
{
    if (pos == length) {
        result.push_back(current);
        current.clear();
    } else {
        for (auto i = items.cbegin(); i != items.cend(); i++) {
            current[pos] = *i;
            variations_with_repetition(pos + 1, length, current, items, result);
        }
    }
}


#endif // UTILS_H
