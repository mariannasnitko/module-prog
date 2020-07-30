#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <fstream>

#include "cui.h"

using namespace std;
using namespace Csv;

int main(int argc, char *argv[])
{
    Storage storage("./data/");
    storage.load();
    Cui cui(&storage);
    cui.show();
    return 0;
}
