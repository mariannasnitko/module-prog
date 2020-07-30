#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "optional.h"
#include "inventor.h"
#include "invention.h"
#include "storage.h"

using std::string;
using std::vector;

class XmlStorage : public Storage
{
  const string dir_name_;

  vector<Inventor> inventors_;
  vector<Invention> inventions_;
  int getNewInventorId();
  int getNewInventionId();

public:
  XmlStorage(const string &dir_name) : dir_name_(dir_name) {}

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
