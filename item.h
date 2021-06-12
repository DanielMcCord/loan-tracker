#ifndef ITEM_H
#define ITEM_H

#include "autoincrementable.h"
#include <map>
#include <string>

class Item : public AutoIncrementable
{
  public:
    Item();
    Item(const std::string &name, const std::string &description);
    key_t primaryKey;
    std::string name;
    std::string description;
    bool isEmpty() const override;
    std::string toString() const override;
};

#endif // ITEM_H
