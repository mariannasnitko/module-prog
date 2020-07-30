#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <fstream>

#include <QDebug>
#include <QString>
#include <QFileInfo>

#include "xml_storage.h"
#include "csv_storage.h"
#include "sqlite_storage.h"
#include "cui.h"

Storage * createStorage(const QString & qpath);

int main(int argc, char *argv[])
{
    QString app_name = QFileInfo(argv[0]).fileName();
    Storage * storage_ptr = createStorage("../" + app_name + "/data/sql");
    storage_ptr->open();
    Cui cui(storage_ptr);
    cui.show();
    storage_ptr->close();
    delete storage_ptr;
    return 0;
}

Storage * createStorage(const QString & qpath)
{
    if(qpath.endsWith("csv"))
    {
        CsvStorage * storage = new CsvStorage(qpath.toLocal8Bit().constData());
        return storage;
    }
    if(qpath.endsWith("xml"))
    {
        XmlStorage * storage = new XmlStorage(qpath.toLocal8Bit().constData());
        return storage;
    }
    if(qpath.endsWith("sql"))
    {
        SqliteStorage * storage = new SqliteStorage(qpath.toLocal8Bit().constData());
        return storage;
    }
    else {
        qDebug() << "I dont know that storage type";
        abort();
    }
}
