#include "loan.h"

using namespace std;

Loan::Loan() : Loan::Loan(0, "")
{
}

Loan::Loan(const Item::key_t &itemID, const string &borrowerName)
{
    this->itemID = itemID;
    this->name = borrowerName;
    parent = nullptr;
}

Loan::~Loan()
{
}

bool Loan::isEmpty() const
{
    Loan empty;
    // Note: because empty.itemID refers to a usable itemID,
    // itemID cannot prove emptiness on its own, although it can still disprove it.
    return (itemID == empty.itemID && name == empty.name);
}

string Loan::toString() const
{
    // To find info about its item, the loan needs to be able to dereference both of these pointers.
    bool canGetItemInfo = parent != nullptr && parent->sibling != nullptr;
    string sep = " / ";

    // Due to a bug, this always gives the itemID, never the name.
    return to_string(primaryKey) + sep +
           (canGetItemInfo
                // Give the user-friendly item name if possible
                ? parent->sibling->records.at(itemID).name
                // or fall back on the itemID if necessary.
                : to_string(itemID)) +
           sep + name;
}
