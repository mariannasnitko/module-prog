#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "optional.h"
#include "inventor.h"
#include "invention.h"
#include "csv.h"

using std::string;
using std::vector;

class Storage
{
  const string dir_name_;

  vector<Inventor> inventors_;
  vector<Invention> inventions_;

  int getNewInventorId();
  int getNewInventionId();
  void print();

public:
  Storage(const string &dir_name) : dir_name_(dir_name) {}

  bool load();
  bool save();

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
