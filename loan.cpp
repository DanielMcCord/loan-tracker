#include "loan.h"

using namespace std;

Loan::Loan() : Loan::Loan(0, "")
{
}

Loan::Loan(const Item::key_t &itemID, const string &borrowerName)
{
    this->itemID = itemID;
    this->name = borrowerName;
    time_t temp = time(nullptr);
    string timeWithNewline = ctime(&temp);
    timeCreated = timeWithNewline.substr(0, timeWithNewline.find_last_not_of('\n') + 1);
}

Loan::Loan(const string &serialized)
{
    size_t FIELD_COUNT = 4;
    vector<string> data = deserialize(serialized);

    if (data.size() >= FIELD_COUNT)
    {
        primaryKey = stoi(data.at(0));
        itemID = stoi(data.at(1));
        name = data.at(2);
        timeCreated = data.at(3);
    }
}

Loan::~Loan()
{
}

bool Loan::isEmpty() const
{
    Loan empty;
    // Note: because empty.itemID refers to a usable itemID,
    // itemID cannot prove emptiness on its own, although it can still disprove it.
    return (itemID == empty.itemID && name == empty.name);
}

string Loan::toString() const
{
    return to_string(primaryKey) + fieldDelimiter + to_string(itemID) + fieldDelimiter + name +
           fieldDelimiter + timeCreated;
}
