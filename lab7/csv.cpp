#include <vector>

#include "csv.h"

using namespace std;

CsvTable Csv::createTableFromString(const string &csv_str)
{
    CsvTable newTable;
    string buf;
    CsvRow newRow;
    string::const_iterator it = csv_str.begin();
    while (1)
    {
        if (*it == '"')
        {
            int counter = 1;
            it += 1;
            while (1)
            {
                if (*it == '"')
                {
                    counter += 1;
                    if (*(it + 1) == '"')
                    {
                        it += 1;
                    }
                    if ((*(it + 1) == ',' || *(it + 1) == '\n' || *(it + 1) == '\0') && counter % 2 == 0)
                    {
                        it++;
                        break;
                    }
                }
                buf.push_back(*it);
                it++;
            }
        }
        if (*it == ',' || *it == '\n' || *it == '\0')
        {

            newRow.push_back(buf);
            if (*it == '\n' || it == csv_str.end())
            {
                newTable.push_back(newRow);
                newRow.clear();
            }
            buf.clear();
        }
        else
        {
            buf.push_back(*it);
        }
        if (it == csv_str.end())
        {
            break;
        }
        it += 1;
    }
    return newTable;
}

string Csv::createStringFromTable(const CsvTable &csv_table)
{
    string newString;
    bool wasQuote = false;
    for (size_t i = 0; i < csv_table.size(); i++)
    {
        CsvRow row = csv_table.at(i);
        for (size_t j = 0; j < row.size(); j++)
        {
            string item = row.at(j);
            wasQuote = false;
            if (item.find('"') != string::npos || item.find(',') != string::npos || item.find('\n') != string::npos)
            {
                wasQuote = true;
                newString.push_back('"');
            }
            if (wasQuote == true)
            {
                for (size_t i = 0; i < item.size(); i++)
                {
                    if (item.at(i) == '"')
                    {
                        newString.push_back('"');
                        newString.push_back('"');
                    }
                    else
                    {
                        newString.push_back(item.at(i));
                    }
                }
                newString.push_back('"');
            }
            else
            {
                for (size_t i = 0; i < item.size(); i++)
                {
                    newString.push_back(item.at(i));
                }
            }
            if (j != row.size() - 1)
            {
                newString.push_back(',');
            }
        }
        if (i != csv_table.size() - 1)
        {
            newString.push_back('\n');
        }
    }
    return newString;
}