#include "item.h"

using namespace std;

Item::Item() : Item::Item("", "")
{
}

Item::Item(const string &name, const string &description)
{
    this->name = name;
    this->description = description;
}

string Item::to_string() const
{
    return name + ": " + description;
}
