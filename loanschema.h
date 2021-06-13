#ifndef LOANSCHEMA_H
#define LOANSCHEMA_H

#include "dbtable.h"
#include "item.h"
#include "loan.h"

/**
 * @brief The database for the loan system.
 */
class LoanSchema
{
  public:
    LoanSchema();
    DBTable<Item> items;
    DBTable<Loan> loans;
    bool itemsAvailable() const;
};

#endif // LOANSCHEMA_H
