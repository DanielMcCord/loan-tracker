#ifndef ITEM_H
#define ITEM_H

#include "autoincrementable.h"
#include <map>
#include <string>

class Item : public AutoIncrementable
{
  public:
    //    typedef std::string key_t;
    Item();
    Item(const std::string &name, const std::string &description);
    key_t primaryKey;
    std::string name;
    std::string description;
    std::string to_string() const;
};

#endif // ITEM_H
