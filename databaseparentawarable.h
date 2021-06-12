#ifndef DATABASEPARENTAWARABLE_H
#define DATABASEPARENTAWARABLE_H

/**
 * @brief A record type can inherit from this one to indicate that it can be made aware of its
 * parent table. For this to do anything, the making-aware behavior must be implemented by the
 * parent table.
 */
class DatabaseParentAwarable
{
  public:
    DatabaseParentAwarable();
};

#endif // DATABASEPARENTAWARABLE_H
