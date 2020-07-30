#pragma once

#include <string>
#include <QMetaType>

using std::string;

struct Inventor
{
    int id;
    string name;
    string invention;
    int patents;
};

Q_DECLARE_METATYPE(Inventor)