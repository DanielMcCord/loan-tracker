#include "loan.h"

using namespace std;

Loan::Loan() : Loan::Loan(0, "")
{
}

Loan::Loan(const Item::key_t &itemID, const string &borrowerName)
{
    this->itemID = itemID;
    this->borrowerName = borrowerName;
}

Loan::~Loan()
{
}


bool Loan::isEmpty() const
{
    Loan empty;
    // Note: because empty.itemID refers to a usable itemID,
    // itemID cannot prove emptiness on its own, although it can still disprove it.
    return (itemID == empty.itemID && borrowerName == empty.borrowerName);
}

string Loan::toString() const
{
    return "";
}
