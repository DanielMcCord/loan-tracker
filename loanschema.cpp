#include "loanschema.h"

using namespace std;

LoanSchema::LoanSchema() : loans(&(this->items))
{
}

LoanSchema::LoanSchema(const string &encoded)
{
    // TODO: write decoding logic
}

string LoanSchema::encode() const
{
    // TODO: write encoding logic
}

bool LoanSchema::itemsAvailable() const
{
    return !this->items.records.empty();
}

bool LoanSchema::empty() const
{
    return this->items.records.empty() && this->loans.records.empty();
}
