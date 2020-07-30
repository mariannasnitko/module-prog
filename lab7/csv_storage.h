#pragma once

#include <vector>
#include <string>

#include "optional.h"
#include "inventor.h"
#include "csv.h"
#include "storage.h"

using std::string;
using std::vector;

class CsvStorage : public Storage
{
  const string dir_name_;

  vector<Inventor> inventors_;

  static Inventor rowToInventor(const CsvRow &row);
  static CsvRow inventorToRow(const Inventor &inv);

  int getNewInventorId();

public:
  CsvStorage(const string &dir_name) : dir_name_(dir_name) {}

  bool load();
  bool save();

  vector<Inventor> getAllInventors(void);
  optional<Inventor> getInventorById(int inventor_id);
  bool updateInventor(const Inventor &inventor);
  bool removeInventor(int inventor_id);
  int insertInventor(const Inventor &inventor);
};
