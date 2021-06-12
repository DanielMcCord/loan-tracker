#ifndef LOAN_H
#define LOAN_H

// Include What You Use
#include "autoincrementable.h"
#include "dbtable.h"
#include "item.h"
#include <cstddef> // for size_t
#include <string>

class Loan : public AutoIncrementable
{
  public:
    Loan();
    Loan(const Item::key_t &itemID, const std::string &borrowerName);
    ~Loan();
    Item::key_t itemID;
    /**
     * @brief The name of the borrower.
     */
    std::string name;
    DBTable<Loan> *parent;
    bool isEmpty() const override;
    std::string toString() const override;
};

#endif // LOAN_H
