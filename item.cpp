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

bool Item::isEmpty() const
{
    Item empty;
    return (name == empty.name && description == empty.description);
}

string Item::toString() const
{
    return name + ": " + description;
}
