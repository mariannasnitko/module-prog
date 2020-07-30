#include <iostream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <fstream>

#include <QDebug>
#include "cui.h"
#include "xml_storage.h"
#include <QCoreApplication>

using namespace std;
using namespace Csv;

void xmlStorage();
void csvStorage();

int main()
{
    int choose;
    cout << "1). CSV" << endl << "2). XML" << endl << "3). Exit" << endl;
    cin >> choose;
    if (choose == 1)
        csvStorage();
    if (choose == 2)
        xmlStorage();
    return 0;
}

void xmlStorage()
{
    XmlStorage xml_storage("../lab6/data/xml");
    Storage * storage_ptr = &xml_storage;
    storage_ptr->load();
    Cui cui(storage_ptr);
    cui.show();
}

void csvStorage(){
    CsvStorage csv_storage("../lab6/data/csv");
    Storage * storage_ptr = &csv_storage;
    storage_ptr->load();
    Cui cui(storage_ptr);
    cui.show();
}
