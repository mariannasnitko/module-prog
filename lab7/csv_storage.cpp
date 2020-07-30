#include <fstream>
#include <iostream>
#include "csv_storage.h"

#include <QDir>

using namespace std;

bool fillStringFromFile(string &str, string filename)
{
    ifstream inFile;
    inFile.open(filename);
    if (!inFile.good())
    {
        inFile.close();
        cerr << "File with such name [" << filename << "] can not be opened" << endl;
        return false;
    }
    char ch;
    while (!inFile.eof())
    {
        ch = inFile.get();
        str.push_back(ch);
    }
    str.pop_back();
    inFile.close();
    return true;
}

Inventor CsvStorage::rowToInventor(const CsvRow &row)
{
    Inventor inv;
    inv.id = stoi(row.at(0));
    inv.name = row.at(1);
    inv.invention = row.at(2);
    inv.patents = stoi(row.at(3));
    return inv;
}

CsvRow CsvStorage::inventorToRow(const Inventor &inv)
{
    CsvRow row;
    row.push_back(to_string(inv.id));
    row.push_back(inv.name);
    row.push_back(inv.invention);
    row.push_back(to_string(inv.patents));
    return row;
}

int CsvStorage::getNewInventorId()
{
    int max = 0;
    for (Inventor inv : this->inventors_)
    {
        if (max < inv.id)
        max = inv.id;
     }
     return max + 1;
}

bool CsvStorage::load()
{
    string newMainString;
    string main = this->dir_name_;
    main += "/inventors.csv";
    if (fillStringFromFile(newMainString, main) == false)
    {
        return false;
    }
    CsvTable table = Csv::createTableFromString(newMainString);
    for (size_t i = 0; i < table.size(); i++)
    {
        if (table.at(i).at(0).empty() == false)
        {
            Inventor newInv = rowToInventor(table.at(i));
            this->inventors_.push_back(newInv);
        }
    }
    return true;
}

bool CsvStorage::save()
{
    string main = this->dir_name_;
    main += "/inventors.csv";
    CsvTable mainTable;
    for (auto &i : this->inventors_)
    {
        mainTable.push_back(inventorToRow(i));
    }
    string mainString = Csv::createStringFromTable(mainTable);
    ofstream outFile;
    outFile.open(main);
    outFile << mainString;
    outFile.close();
    return true;
}

vector<Inventor> CsvStorage::getAllInventors(void)
{
    return this->inventors_;
}

optional<Inventor> CsvStorage::getInventorById(int inventor_id)
{
    for (auto item : this->inventors_)
    {
        if (item.id == inventor_id)
        {
            return item;
        }
    }
    return nullopt;
}

bool CsvStorage::updateInventor(const Inventor &inv)
{
    for (auto &item : this->inventors_)
    {
        if (item.id == inv.id)
        {
            item = inv;
            return true;
        }
    }
    return false;
}

bool CsvStorage::removeInventor(int inventor_id)
{
    for (size_t i = 0; i < this->inventors_.size(); i++)
    {
        Inventor item = this->inventors_.at(i);
        if (item.id == inventor_id)
        {
            this->inventors_.erase(inventors_.begin() + i);
            return true;
        }
    }
    return false;
}

int CsvStorage::insertInventor(const Inventor &inv)
{
    int newId = getNewInventorId();
    Inventor copy = inv;
    copy.id = newId;
    this->inventors_.push_back(copy);
    return newId;
}
