#pragma once
#include <vector>
#include <string>

using std::string;
using std::vector;

using CsvRow = vector<string>;
using CsvTable = vector<CsvRow>;

namespace Csv
{
CsvTable createTableFromString(const string &csv_str);
string createStringFromTable(const CsvTable &csv_table);
}
