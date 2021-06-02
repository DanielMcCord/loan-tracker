#ifndef LOAN_H
#define LOAN_H

// Include What You Use
#include "autoincrementable.h"
#include "item.h"
#include <cstddef> // for size_t
#include <string>

class Loan : public AutoIncrementable
{
  public:
    Loan();
    Loan(const Item::key_t &itemName, const std::string &borrowerName);
    ~Loan();
    Item::key_t itemName;
    std::string borrowerName;
    std::string to_string() const;
};

#endif // LOAN_H
