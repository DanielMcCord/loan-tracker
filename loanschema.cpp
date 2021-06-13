#include "loanschema.h"

LoanSchema::LoanSchema() : loans(&(this->items))
{
}

bool LoanSchema::itemsAvailable() const
{
    return !this->items.records.empty();
}
