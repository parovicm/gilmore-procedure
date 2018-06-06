#include "baseterm.h"
#include <typeinfo>

BaseTerm::BaseTerm()
{
}

BaseTerm::~BaseTerm()
{
}

/* Mislim da moze da se implementira hasVariable i equalTo i u ovoj klasi BaseTerm,
 * bas kao sto je moglo i u klasi BaseFormula. */

bool operator==(const Term &lhs, const Term &rhs)
{
    return lhs->equalTo(rhs);
}
