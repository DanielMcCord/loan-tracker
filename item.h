#ifndef ITEM_H
#define ITEM_H

#include "record.h"
#include <map>
#include <string>

class Item : public Record
{
  public:
    typedef std::string key_t;
    Item();
    Item(const key_t &name, const std::string &description);
    key_t primaryKey;
    std::string description;
    std::string to_string() const;
};

#endif // ITEM_H
