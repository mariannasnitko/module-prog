#ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H

#include "storage.h"
#include <QSqlDatabase>

using std::vector;
using std::string;

class SqliteStorage : public Storage
{
    const string dir_name_;
    QSqlDatabase db_;

public:

    SqliteStorage(const string &dir_name);

    bool open();
    bool close();

    vector<Inventor> getAllInventors(void);
    optional<Inventor> getInventorById(int inventor_id);
    bool updateInventor(const Inventor &inventor);
    bool removeInventor(int inventor_id);
    int insertInventor(const Inventor &inventor);

    vector<Invention> getAllInventions(void);
    optional<Invention> getInventionById(int invention_id);
    bool updateInvention(const Invention &invention);
    bool removeInvention(int invention_id);
    int insertInvention(const Invention &invention);
};

#endif // SQLITE_STORAGE_H
