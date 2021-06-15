#ifndef ITEM_H
#define ITEM_H

// Include What You Use
#include "autoincrementable.h"
#include <cstddef> // size_t
#include <map>
#include <string>
#include <vector>

class Item : public AutoIncrementable
{
  public:
    Item();
    Item(const std::string &name, const std::string &description);
    Item(const std::string &serialized);
    key_t primaryKey;
    std::string name;
    std::string description;
    bool isEmpty() const override;
    std::string toString() const override;
};

#endif // ITEM_H
