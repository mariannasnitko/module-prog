#include "storage.h"
#include <fstream>
#include <iostream>

using namespace std;

void writeAllToFile(string const &filename, string const &text);

bool Storage::load()
{
    string inventors_filename = this->dir_name_ + "/inventors.csv";
    ifstream file;
    file.open(inventors_filename, ios::in);
    if (!file.good())
    {
        cerr << "Can't open the file: " << inventors_filename << endl;
        abort();
    }
    string tmp, str;
    while (getline(file, tmp))
    {
        str += tmp + '\n';
        tmp.clear();
    }
    CsvTable inventors_table = Csv::createTableFromString(str);
    for (CsvRow &row : inventors_table)
    {
        Inventor inv;
        if (row.size() > 0)
            inv.id = std::stoi(row[0]);
        if (row.size() > 1)
            inv.name = row[1];
        if (row.size() > 2)
            inv.invention = row[2];
        if (row.size() > 3)
            inv.patents = std::stoi(row[3]);
        this->inventors_.push_back(inv);
    }
    file.close();


    string inventions_filename = this->dir_name_ + "/inventions.csv";
    file.open(inventions_filename, ios::in);
    if (!file.good())
    {
        cerr << "Can't open the file: " << inventions_filename << endl;
        abort();
    }
    str.clear();
    while (getline(file, tmp))
    {
        str += tmp + '\n';
        tmp.clear();
    }
    CsvTable invention_table = Csv::createTableFromString(str);
    for (CsvRow &row : invention_table)
    {
        Invention invn;
        if (row.size() > 0)
            invn.id = std::stoi(row[0]);
        if (row.size() > 1)
            invn.invention = row[1];
        if (row.size() > 2)
            invn.data = row[2];
        if (row.size() > 3)
            invn.year = std::stoi(row[3]);
        this->inventions_.push_back(invn);
    }
    file.close();
    return true;
}

bool Storage::save()
{
    CsvTable table;
    for (Inventor inv : inventors_)
    {
        CsvRow row;
        row.push_back(to_string(inv.id));
        row.push_back(inv.name);
        row.push_back(inv.invention);
        row.push_back(to_string(inv.patents));
        table.push_back(row);
    };
    string filename = "inventors.csv";
    ofstream output;
    output.open(dir_name_ + filename);
    if (!output.is_open())
    {
        cout << "no such file: " << dir_name_;
        output.close();
        return 0;
    }
    output << Csv::createStringFromTable(table);
    output.close();

    CsvTable table1;
    for (Invention invn : inventions_)
    {
        CsvRow row;
        row.push_back(to_string(invn.id));
        row.push_back(invn.invention);
        row.push_back(invn.data);
        row.push_back(to_string(invn.year));
        table1.push_back(row);
    }
    filename = "inventions.csv";
    output.open(dir_name_ + filename);
    if (!output.is_open())
    {
        cout << "no such file: " << dir_name_;
        output.close();
        return 0;
    }
    output << Csv::createStringFromTable(table1);
    output.close();
    return 1;
}

int Storage::getNewInventorId()
{
    int max = 0;
    for (Inventor inv : this->inventors_)
    {
        if (max < inv.id)
            max = inv.id;
    }
    return max + 1;
}

int Storage::getNewInventionId()
{
    int max = 0;
    for (Invention inv : this->inventions_)
    {
        if (max < inv.id)
            max = inv.id;
    }
    return max + 1;
}

vector<Inventor> Storage::getAllInventors()
{
    return this->inventors_;
}

optional<Inventor> Storage::getInventorById(int inventor_id)
{
    for (Inventor &inv : this->inventors_)
    {
        if (inv.id == inventor_id)
        {
            return inv;
        }
    }
    return nullopt;
}

bool Storage::updateInventor(const Inventor &inventor)
{
    for (int i = 0; i < inventors_.size(); i++)
    {
        if (inventors_[i].id == inventor.id)
        {
            inventors_[i] = inventor;
            return 1;
        }
    }
    return 0;
}

bool Storage::removeInventor(int inventor_id)
{
    for (int i = 0; i < inventors_.size(); i++)
    {
        if (inventors_[i].id == inventor_id)
        {
            inventors_.erase(inventors_.begin() + i);
            return 1;
        }
    }
    return 0;
}

int Storage::insertInventor(const Inventor &inventor)
{
    Inventor inv = inventor;
    inv.id = getNewInventorId();
    inventors_.push_back(inv);
    return inv.id;
}

vector<Invention> Storage::getAllInventions()
{
    return this->inventions_;
}

optional<Invention> Storage::getInventionById(int inventor_id)
{
    for (Invention &inv : this->inventions_)
    {
        if (inv.id == inventor_id)
        {
            return inv;
        }
    }
    return nullopt;
}

bool Storage::updateInvention(const Invention &invention)
{
    for (int i = 0; i < inventions_.size(); i++)
    {
        if (inventions_[i].id == invention.id)
        {
            inventions_[i] = invention;
            return 1;
        }
    }
    return 0;
}

bool Storage::removeInvention(int invention_id)
{
    for (int i = 0; i < inventions_.size(); i++)
    {
        if (inventions_[i].id == invention_id)
        {
            inventions_.erase(inventions_.begin() + i);
            return 1;
        }
    }
    return 0;
}

int Storage::insertInvention(const Invention &invention)
{
    Invention inv = invention;
    inv.id = getNewInventionId();
    inventions_.push_back(inv);
    return inv.id;
}

void writeAllToFile(string const &filename, string const &text)
{
    ofstream file;
    file.open(filename);
    if (!file.good())
    {
        cerr << "The file cannot open for write: " << filename << endl;
        abort();
    }
    file << text;
    file.close();
}
