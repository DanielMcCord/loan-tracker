#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record
{
  public:
    Record();
    virtual ~Record() = 0;
    /**
     * @brief Returns true if therecord is empty; otherwise, false.
     * A record is considered empty if all fields match those of a
     * default-constructed record of the same type.
     * @return
     */
    virtual bool isEmpty() const = 0;
    virtual std::string toString() const = 0;
};

#endif // RECORD_H
