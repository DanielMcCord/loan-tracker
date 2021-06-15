#include "loanschema.h"

using namespace std;

LoanSchema::LoanSchema()
{
}

LoanSchema::LoanSchema(const string &serialized)
{
    auto itemsStrStart = serialized.find(this->itemsStartLabel) + itemsStartLabel.length();
    auto itemsStrLength = itemsStrStart - serialized.find(this->itemsEndLabel);
    auto loansStrStart = serialized.find(this->loansStartLabel) + loansStartLabel.length();
    auto loansStrLength = loansStrStart - serialized.find(this->loansEndLabel);
    string itemsStr = serialized.substr(itemsStrStart, itemsStrLength);
    string loansStr = serialized.substr(loansStrStart, loansStrLength);
    items = DBTable<Item>(itemsStr);
    loans = DBTable<Loan>(loansStr);
}

string LoanSchema::serialize() const
{
    return itemsStartLabel + items.toString() + itemsEndLabel + loansStartLabel + loans.toString() +
           loansEndLabel;
}

bool LoanSchema::itemsAvailable() const
{
    return !this->items.records.empty();
}

bool LoanSchema::empty() const
{
    return this->items.records.empty() && this->loans.records.empty();
}
