#include <iostream>
#include <cstdlib>

#include "storage.h"

using namespace std;

class Cui
{
  Storage *const storage_;

  void inventorMainMenu();
  void inventorMenu(int entity_id);
  void inventorUpdateMenu(int entity_id);
  void inventorDeleteMenu(int entity_id);
  void inventorCreateMenu();
  void printInventor(vector<Inventor> &inventor);

  void inventionMainMenu();
  void inventionMenu(int entity_id);
  void inventionUpdateMenu(int entity_id);
  void inventionDeleteMenu(int entity_id);
  void inventionCreateMenu();
  void printInvention(vector<Invention> &invention);

public:
  Cui(Storage *storage) : storage_(storage) {}
  void show();
};
