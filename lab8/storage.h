#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "optional.h"
#include "inventor.h"
#include "invention.h"

using namespace std;

class Storage
{
 public:
   virtual ~Storage() {}

   virtual bool open() = 0;
   virtual bool close() = 0;

   virtual vector<Inventor> getAllInventors(void) = 0;
   virtual optional<Inventor> getInventorById(int inventor_id) = 0;
   virtual bool updateInventor(const Inventor &inventor) = 0;
   virtual bool removeInventor(int inventor_id) = 0;
   virtual int insertInventor(const Inventor &inventor) = 0;

    virtual vector<Invention> getAllInventions(void) = 0;
    virtual optional<Invention> getInventionById(int invention_id) = 0;
    virtual bool updateInvention(const Invention &invention) = 0;
    virtual bool removeInvention(int invention_id) = 0;
    virtual int insertInvention(const Invention &invention) = 0;
};
