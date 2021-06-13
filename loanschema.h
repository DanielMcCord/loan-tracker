#ifndef LOANSCHEMA_H
#define LOANSCHEMA_H

#include <string>
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
    LoanSchema(const std::string &encoded);
    std::string encode() const;
    DBTable<Item> items;
    DBTable<Loan> loans;
    bool itemsAvailable() const;
    bool empty() const;
};

#endif // LOANSCHEMA_H
