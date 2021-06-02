#include "item.h"

using namespace std;

// Item::map_t Item::items;

Item::Item() : Item::Item("", "")
{
}

Item::Item(const key_t &name, const string &description)
{
    primaryKey = name;
    this->description = description;
}

string Item::to_string() const
{
    return primaryKey + ": " + description;
}
