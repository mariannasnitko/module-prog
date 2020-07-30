#include "sqlite_storage.h"
#include <QtSql>

SqliteStorage::SqliteStorage(const string &dir_name): dir_name_(dir_name)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
}

bool SqliteStorage::open()
{
    QString path = QString::fromStdString(this->dir_name_) + "/data.sqlite";
    db_.setDatabaseName(path);
    bool connected = db_.open();
    if (!connected) {return false;}
    return true;
}

bool SqliteStorage::close()
{
    db_.close();
    return true;
}

vector<Inventor> SqliteStorage::getAllInventors(void)
{
    vector<Inventor> inventors;
    QSqlQuery query("SELECT * FROM inventors");

    if (!query.exec()) {
        qDebug() << "getAllInventors error:" << query.lastError().text();
    }

    while (query.next())
    {
        Inventor inv;
        inv.id = query.value("id").toInt();
        inv.name = query.value("name").toString().toStdString();
        inv.invention = query.value("invention").toString().toStdString();
        inv.patents = query.value("patents").toInt();
        inventors.push_back(inv);
    }
    return inventors;
}

optional<Inventor> SqliteStorage::getInventorById(int inventor_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM inventors WHERE id = :id");
    query.bindValue(":id", inventor_id);
    if (!query.exec())
    {
        qDebug() << "getInventorById error:" << query.lastError();
        return nullopt;
    }
    if (query.next())
    {
        Inventor inv;
        inv.id = query.value("id").toInt();
        inv.name = query.value("name").toString().toStdString();
        inv.invention = query.value("invention").toString().toStdString();
        inv.patents = query.value("patents").toInt();
        return inv;
    }
    else
    {
        return nullopt;
    }
}

bool SqliteStorage::updateInventor(const Inventor &inventor)
{
    QSqlQuery query;
    query.prepare("UPDATE inventors SET name = :name, invention = :invention, patents = :patents WHERE id = :id");
    query.bindValue(":name", QString::fromStdString(inventor.name));
    query.bindValue(":invention", QString::fromStdString(inventor.invention));
    query.bindValue(":patents", inventor.patents);
    query.bindValue(":id", inventor.id);
    if (!query.exec()){
        qDebug() << "updateInventor error:" << query.lastError();
        return false;
    }
    return true;
}

bool SqliteStorage::removeInventor(int inventor_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM inventors WHERE id = :id");
    query.bindValue(":id", inventor_id);
    if (!query.exec()){
        qDebug() << "removeInventor error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

int SqliteStorage::insertInventor(const Inventor &inventor)
{
    QSqlQuery query;
    query.prepare("INSERT INTO inventors (name, invention, patents) "
                  "VALUES (:name, :invention, :patents)");
    query.bindValue(":name", QString::fromStdString(inventor.name));
    query.bindValue(":invention",QString::fromStdString(inventor.invention));
    query.bindValue(":patents", inventor.patents);
    if (!query.exec()){
        qDebug() << "insertInventor error:" << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();
    return var.toInt();
}

vector<Invention> SqliteStorage::getAllInventions(void)
{
    vector<Invention> inventions;
    QSqlQuery query("SELECT * FROM inventions");

    if (!query.exec()) {
        qDebug() << "getAllInventions error:" << query.lastError().text();
    }

    while (query.next())
    {
        Invention in;
        in.id = query.value("id").toInt();
        in.invent = query.value("invention").toString().toStdString();
        in.data = query.value("data").toString().toStdString();
        in.year = query.value("year").toInt();
        inventions.push_back(in);
    }
    return inventions;
}

optional<Invention> SqliteStorage::getInventionById(int invention_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM inventions WHERE id = :id");
    query.bindValue(":id", invention_id);
    if (!query.exec())
    {
        qDebug() << "getInventionById error:" << query.lastError();
        return nullopt;
    }
    if (query.next())
    {
        Invention in;
        in.id = query.value("id").toInt();
        in.invent = query.value("invention").toString().toStdString();
        in.data = query.value("data").toString().toStdString();
        in.year = query.value("year").toInt();
        return in;
    }
    else
    {
        return nullopt;
    }
}

bool SqliteStorage::updateInvention(const Invention &invention)
{
    QSqlQuery query;
    query.prepare("UPDATE inventions SET invention = :invention, data = :data, year = :year WHERE id = :id");
    query.bindValue(":invention", QString::fromStdString(invention.invent));
    query.bindValue(":data", QString::fromStdString(invention.data));
    query.bindValue(":year", invention.year);
    query.bindValue(":id", invention.id);
    if (!query.exec()){
        qDebug() << "updateInvention error:" << query.lastError();
        return false;
    }
    return true;
}

bool SqliteStorage::removeInvention(int invention_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM invention WHERE id = :id");
    query.bindValue(":id", invention_id);
    if (!query.exec()){
        qDebug() << "removeInvention error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

int SqliteStorage::insertInvention(const Invention &invention)
{
    QSqlQuery query;
    query.prepare("INSERT INTO inventions (invention, data, year) "
                  "VALUES (:invention, :data, :year)");
    query.bindValue(":invention", QString::fromStdString(invention.invent));
    query.bindValue(":data",QString::fromStdString(invention.data));
    query.bindValue(":year", invention.year);
    if (!query.exec()){
        qDebug() << "insertInvention error:" << query.lastError();
        return 0;
    }
    QVariant var = query.lastInsertId();
    return var.toInt();
}
