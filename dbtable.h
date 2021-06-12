#ifndef DBTABLE_H
#define DBTABLE_H

#include "autoincrementable.h"
#include <map>
#include <queue>
#include <string>
#include <type_traits> // is_base_of_v

/**
 * A model of some of the features of a table in a relational database.
 * Will auto-increment the primary key if the records inherit from AutoIncrementable.
 */
template <typename RecordT> class DBTable
{
  public:
    // The table's key type must match the key type of the records
    typedef typename RecordT::key_t key_t;
    typedef std::map<key_t, RecordT> map_t;
    typedef typename DBTable<RecordT>::map_t::size_type size_type;
    DBTable();
    /**
     * @brief Adds a record to the table.
     * @param record
     * @param allowRecycledKey (optional) Whether, in the case of auto-incrementing primary keys,
     * previously-removed keys may be used. Only has an effect if keys auto-increment.
     * @return Whether the action was successful.
     */
    bool add(RecordT &record, bool allowRecycledKey = true);
    RecordT at(const key_t &primaryKey) const;
    /**
     * @brief Returns the record with the given name, or an empty record if none is found.
     * @param name
     * @return
     */
    RecordT findByName(const std::string &name) const;
    /**
     * @brief Removes a record from the table.
     * @param primaryKey
     * @return The number of records removed (0 or 1).
     */
    size_type remove(key_t primaryKey);

  private:
    map_t records;
    /**
     * @brief Specifies whether the name field must be unique for each record in the table.
     */
    bool uniqueNames;
    /**
     * Used with auto-incrementable records only. Contains the value of the next key.
     * If records are not auto-incrementable, this value sits unused and is never incremeneted.
     */
    size_type nextKey;
    /**
     * Used with auto-incrementable records to keep track of keys that are now available again.
     */
    std::queue<key_t> removedKeys;
};

template <typename RecordT> DBTable<RecordT>::DBTable() : nextKey(0), uniqueNames(true)
{
}

template <typename RecordT> bool DBTable<RecordT>::add(RecordT &record, bool allowRecycledKey)
{
    // Only use auto-incrementing logic on records that are AutoIncrementable
    if constexpr (std::is_base_of_v<AutoIncrementable, RecordT>)
    {
        // Prefers filling in gaps over making never-used keys.
        bool usingRecycledKey = allowRecycledKey && !removedKeys.empty();
        size_type primaryKey = usingRecycledKey ? removedKeys.front() : nextKey;
        bool recordAdded = records.try_emplace(primaryKey, record).second;

        if (recordAdded)
        {
            // Update the record so it knows what its own key is.
            record.primaryKey = primaryKey;

            // Make sure we don't try to use the same key next time.
            if (usingRecycledKey)
            {
                removedKeys.pop();
            }
            else
            {
                ++nextKey;
            }
        }

        return recordAdded;
    }
    else
    {
        // The reason this is so much simpler is that, in this case, the
        // caller is responsible for making sure the key is not already in use.
        return records.try_emplace(record.primaryKey, record).second;
    }
}

template <typename RecordT>
RecordT DBTable<RecordT>::at(const key_t &primaryKey) const
{
    return records.at(primaryKey);
}

template <typename RecordT>
RecordT DBTable<RecordT>::findByName(const std::string &name) const
{
    RecordT result;

    for(const auto &pair : records)
    {
        if (pair.second.name == name)
        {
            result = pair.second;
            break;
        }
    }

    return result;
}

template <typename RecordT>
typename DBTable<RecordT>::size_type DBTable<RecordT>::remove(key_t primaryKey)
{
    // As with add(), only use auto-incrementing logic on records that are AutoIncrementable.
    if constexpr (std::is_base_of_v<AutoIncrementable, RecordT>)
    {
        size_type recordsRemoved = records.erase(primaryKey);

        if (recordsRemoved > 0)
        {
            // Track the fact that the key is available again.
            removedKeys.push(primaryKey);
        }

        return recordsRemoved;
    }
    else
    {
        return records.erase(primaryKey);
    }
}

#endif // DBTABLE_H
