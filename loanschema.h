#ifndef LOANSCHEMA_H
#define LOANSCHEMA_H

#include "dbtable.h"
#include "item.h"
#include "loan.h"
#include <string>

/**
 * @brief The database for the loan system.
 */
class LoanSchema
{
  public:
    LoanSchema();
    LoanSchema(const std::string &encoded);
    std::string serialize() const;
    DBTable<Item> items;
    DBTable<Loan> loans;
    bool itemsAvailable() const;
    bool empty() const;

  private:
    // These are used for serialization purposes.
    std::string itemsStartLabel = "<items>\n";
    std::string itemsEndLabel = "</items>\n";
    std::string loansStartLabel = "<loans>\n";
    std::string loansEndLabel = "</loans>\n";
};

#endif // LOANSCHEMA_H
