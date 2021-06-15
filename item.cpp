#include "item.h"

using namespace std;

Item::Item() : Item("", "")
{
}

Item::Item(const string &name, const string &description)
{
    this->name = name;
    this->description = description;
}

Item::Item(const string &serialized) : Item()
{
    const size_t FIELD_COUNT = 3;
    vector<string> data = deserialize(serialized);

    if (data.size() >= FIELD_COUNT)
    {
        primaryKey = stoi(data.at(0));
        name = data.at(1);
        description = data.at(2);
    }
}

bool Item::isEmpty() const
{
    Item empty;
    return (name == empty.name && description == empty.description);
}

string Item::toString() const
{
    return to_string(primaryKey) + fieldDelimiter + name + fieldDelimiter + description;
}
