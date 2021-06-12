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

string Loan::to_string() const
{
    return "";
}
