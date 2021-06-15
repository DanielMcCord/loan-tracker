#include "record.h"

using namespace std;

Record::Record()
{
}

Record::~Record()
{
}

vector<string> Record::deserialize(const string &serializedData) const
{
    istringstream adapter;
    adapter.str(serializedData);
    vector<string> data;

    for (string member; getline(adapter, member, fieldDelimiter);)
    {
        data.push_back(member);
    }

    return data;
}
