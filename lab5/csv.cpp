#include "csv.h"

CsvTable Csv::createTableFromString(const string &csv_str)
{
    CsvTable table;
    const char *p = csv_str.c_str();
    char buf[1000];
    int bufX = 0;
    CsvRow row;
    while (1)
    {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';

            if (bufX > 0)
                row.push_back(string(buf));

            if (*p == '\n')
            {
                if (row.size() > 0)
                    table.push_back(row);
                row = CsvRow();
            }
            else if (*p == '\0')
            {
                if (row.size() > 0)
                    table.push_back(row);
            }
            bufX = 0;
        }
        else
        {
            buf[bufX] = *p;
            bufX += 1;
        }
        if (*p == '\0')
        {
            break;
        }
        p += 1;
    }
    return table;
}

string Csv::createStringFromTable(const CsvTable &csv_table)
{
    string csv_text;
    for (int i = 0; i < csv_table.size(); i++)
    {
        CsvRow row = csv_table[i];

        for (int j = 0; j < row.size(); j++)
        {
            string value = row[j];
            csv_text += value;
            if (j != row.size() - 1)
            {
                csv_text += ',';
            }
        }
        if (i != csv_table.size() - 1)
            csv_text += '\n';
    }
    return csv_text;
}
