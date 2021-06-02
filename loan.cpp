#include "loan.h"

using namespace std;

Loan::Loan() : Loan::Loan("", "")
{
}

Loan::Loan(const Item::key_t &itemName, const string &borrowerName)
{
    this->itemName = itemName;
    this->borrowerName = borrowerName;
}

Loan::~Loan()
{

}

string Loan::to_string() const
{
    return "";
}
