#include "item.h"

using namespace std;

Item::Item() : Item("", "")
{
}

Item::Item(const string &name, const string &description) : primaryKey(0)
{
    this->name = name;
    this->description = description;
}

Item::Item(const string &serialized)
{
    const size_t FIELD_COUNT = 3;
    vector<string> data = deserialize(serialized);

    if (data.size() >= FIELD_COUNT)
    {
        istringstream keyStream(data.at(0));
        keyStream >> primaryKey;
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
