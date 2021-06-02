#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record
{
  public:
    Record();
    virtual ~Record() = 0;
    virtual std::string to_string() const = 0;
};

#endif // RECORD_H
