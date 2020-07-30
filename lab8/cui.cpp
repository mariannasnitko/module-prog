#include "cui.h"
#include <iostream>
#include <string>

void Cui::show()
{
    bool isRunning = true;
    while (isRunning)
    {
        int opt;
        cout << "Main Menu" << endl;
        cout << "1). Inventors\n2). Inventions" << endl;
        cin >> opt;
        if (opt == 1)
        {
            while (isRunning)
            {
                int c;
                cout << "1). Show all inventors" << endl;
                cout << "2). Get inventor by id" << endl;
                cout << "3). Update inventor" << endl;
                cout << "4). Delete inventor" << endl;
                cout << "5). Add new inventor" << endl;
                cout << "6). Exit" << endl;
                cin >> c;
                switch (c)
                {
                case 1:
                {
                    system("clear");
                    inventorsMainMenu();
                    cout << " " << endl;
                    break;
                }
                case 2:
                {
                    cout << "Id: ";
                    int id;
                    cin >> id;
                    system("clear");
                    inventorMenu(id);
                    cout << " " << endl;
                    break;
                }
                case 3:
                {
                    cout << "Id: ";
                    int id;
                    cin >> id;
                    system("clear");
                    inventorUpdateMenu(id);
                    cout << " " << endl;
                    break;
                }
                case 4:
                {
                    cout << "Id: ";
                    int id;
                    cin >> id;
                    system("clear");
                    inventorDeleteMenu(id);
                    cout << " " << endl;
                    break;
                }
                case 5:
                {
                    system("clear");
                    inventorCreateMenu();
                    cout << " " << endl;
                    break;
                }
                case 6:
                {
                    isRunning = false;
                    break;
                }
                }
            }
        }
        else if (opt == 2)
        {
            while (isRunning)
            {
                int b;
                cout << "1). Show all inventions" << endl;
                cout << "2). Get invention by id" << endl;
                cout << "3). Update invention" << endl;
                cout << "4). Delete invention" << endl;
                cout << "5). Add new invention" << endl;
                cout << "6). Exit" << endl;
                cin >> b;
                switch (b)
                {
                case 1:
                {
                    system("clear");
                    inventionsMainMenu();
                    cout << " " << endl;
                    break;
                }
                case 2:
                {
                    cout << "Id: ";
                    int id;
                    cin >> id;
                    system("clear");
                    inventionMenu(id);
                    cout << " " << endl;
                    break;
                }
                case 3:
                {
                    cout << "Id: ";
                    int id;
                    cin >> id;
                    system("clear");
                    inventionUpdateMenu(id);
                    cout << " " << endl;
                    break;
                }
                case 4:
                {
                    cout << "Id: ";
                    int id;
                    cin >> id;
                    system("clear");
                    inventionDeleteMenu(id);
                    cout << " " << endl;
                    break;
                }
                case 5:
                {
                    system("clear");
                    inventionCreateMenu();
                    cout << " " << endl;
                    break;
                }
                case 6:
                {
                    isRunning = false;
                    break;
                }
                }
            }
        }
        else
        {
            cout << "Incorrect input!" << endl;
        }
    }
    cout << " " << endl;
}

void Cui::inventorsMainMenu()
{
    vector<Inventor> inv = this->storage_->getAllInventors();
    for (auto &item : inv)
    {
        cout << item.id << "  " << item.name << endl;
    }
}

void Cui::inventorMenu(int entity_id)
{
    optional<Inventor> inv_opt = this->storage_->getInventorById(entity_id);
    if (inv_opt)
    {
        Inventor &inv = inv_opt.value();
        cout << "Name: " << inv.name << endl;
        cout << "Invention: " << inv.invention << endl;
        cout << "Patents: " << inv.patents << endl;
    }
    else
    {
        cout << "No inventor with this id" << endl;
    }
}

void Cui::inventorUpdateMenu(int entity_id)
{
    optional<Inventor> inv_opt = this->storage_->getInventorById(entity_id);
    if (inv_opt)
    {
        Inventor &inv1 = inv_opt.value();
        cout << "1. name 2. invention 3. patents" << endl;
        cout << "Enter the field you want to change: ";
        string fieldName;
        cin.ignore();
        getline(cin, fieldName);
        if (fieldName == "name")
        {
            cout << "Enter new name: ";
            string newName;
            getline(cin, newName);
            inv1.name = newName;
            this->storage_->updateInventor(inv1);
        }
        else if (fieldName == "invention")
        {
            cout << "Enter new invention: ";
            string newInv;
            getline(cin, newInv);
            inv1.invention = newInv;
            this->storage_->updateInventor(inv1);
        }
        else if (fieldName == "patents")
        {
            cout << "Enter new patents: ";
            int newP;
            cin >> newP;
            inv1.patents = newP;
            this->storage_->updateInventor(inv1);
        }
        else
        {
            cout << "Error! Field not found" << endl;
        }
    }
    else
    {
        cout << "No inventor with this id" << endl;
    }
}

void Cui::inventorDeleteMenu(int entity_id)
{
    optional<Inventor> inv_opt = this->storage_->getInventorById(entity_id);
    if (inv_opt)
    {
        this->storage_->removeInventor(entity_id);
        cout << "Deleted!" << endl;
    }
    else
    {
        cout << "No inventor with this id" << endl;
    }
}

void Cui::inventorCreateMenu()
{
    Inventor inv;
    cout << "Name: ";
    string newName;
    cin.ignore();
    getline(cin, newName);
    inv.name = newName;
    cout << "Invention: ";
    string newInv;
    cin.ignore();
    getline(cin, newInv);
    inv.invention = newInv;
    cout << "Number of Patents: ";
    int newPatents;
    cin >> newPatents;
    inv.patents = newPatents;
    this->storage_->insertInventor(inv);
}

void Cui::inventionsMainMenu()
{
    vector<Invention> inv = this->storage_->getAllInventions();
    for (auto &item : inv)
    {
        cout << item.id << "  " << item.invent << endl;
    }
}

void Cui::inventionMenu(int entity_id)
{
    optional<Invention> inv_opt = this->storage_->getInventionById(entity_id);
    if (inv_opt)
    {
        Invention &inv = inv_opt.value();
        cout << "Invention: " << inv.invent << endl;
        cout << "Data: " << inv.data << endl;
        cout << "Year: " << inv.year << endl;
    }
    else
    {
        cout << "No invention with this id" << endl;
    }
}

void Cui::inventionUpdateMenu(int entity_id)
{
    optional<Invention> inv_opt = this->storage_->getInventionById(entity_id);
    if (inv_opt)
    {
        Invention &inv1 = inv_opt.value();
        cout << "(invention, data, year)" << endl;
        cout << "Enter the field you want to change: ";
        string fieldName;
        cin.ignore();
        getline(cin, fieldName);
        if (fieldName == "invention")
        {
            cout << "Enter new invention: ";
            string newInv;
            getline(cin, newInv);
            inv1.invent = newInv;
            this->storage_->updateInvention(inv1);
        }
        else if (fieldName == "data")
        {
            cout << "Enter new data: ";
            string newData;
            getline(cin, newData);
            inv1.data = newData;
            this->storage_->updateInvention(inv1);
        }
        else if (fieldName == "year")
        {
            cout << "Enter new year: ";
            int newYear;
            cin >> newYear;
            inv1.year = newYear;
            this->storage_->updateInvention(inv1);
        }
        else
        {
            cout << "Error! Field not found" << endl;
        }
    }
    else
    {
        cout << "No invention with this id" << endl;
    }
}

void Cui::inventionDeleteMenu(int entity_id)
{
    optional<Invention> inv_opt = this->storage_->getInventionById(entity_id);
    if (inv_opt)
    {
        this->storage_->removeInvention(entity_id);
        cout << "Deleted!" << endl;
    }
    else
    {
        cout << "No invention with this id" << endl;
    }
}

void Cui::inventionCreateMenu()
{
    Invention inv;
    cout << "Invention: ";
    string newInv;
    cin.ignore();
    getline(cin, newInv);
    inv.invent = newInv;
    cout << "Data: ";
    string newData;
    cin.ignore();
    getline(cin, newData);
    inv.data = newData;
    cout << "Year: ";
    int newYear;
    cin >> newYear;
    inv.year = newYear;
    this->storage_->insertInvention(inv);
}
