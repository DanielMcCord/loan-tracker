#ifndef AUTOINCREMENTABLE_H
#define AUTOINCREMENTABLE_H

#include "record.h"
#include <cstddef>

class AutoIncrementable : public Record
{
  public:
    typedef size_t key_t;
    AutoIncrementable();
    ~AutoIncrementable();
    key_t primaryKey;
};

#endif // AUTOINCREMENTABLE_H
