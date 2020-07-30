#include "cui.h"

void Cui::show()
{
    system("clear");
    int opt;
    cout << "Choose an entity:" << endl;
    cout << "\n1). Inventors\n2). Inventions\n3). Exit" << endl;
    cin >> opt;
    if (opt == 1)
        inventorMainMenu();
    else if (opt == 2)
        inventionMainMenu();
    else if (opt == 3)
    {
        system("clear");
        int out;
        cout << "Enter 1 if you want to save, otherwise enter smth" << endl;
        cin >> out;
        if (out == 1)
            storage_->save();
        exit(0);
    }
}

void Cui::inventorMainMenu()
{
    system("clear");
    int opt;
    cout << "Choose an option:"
         << "\n1). Show inventors\n2). Update inventor\n3). Delete inventor\n4). Add inventor\n5). Check detailed info\n6). Back" << endl;
    cin >> opt;
    if (opt == 1)
    {
        system("clear");
        for (Inventor inv : storage_->getAllInventors())
        {
            cout << inv.id << "  " << inv.name << endl;
        }
        cout << "Enter anything to go back\n";
        cin >> opt;
        inventorMainMenu();
    }
    else if (opt == 2)
    {
        cout << "\nInventor`s id\n";
        int id;
        cin >> id;
        inventorUpdateMenu(id);
    }
    else if (opt == 3)
    {
        cout << "\nInventor`s id\n";
        int id;
        cin >> id;
        inventorDeleteMenu(id);
    }
    else if (opt == 4)
    {
        inventorCreateMenu();
    }
    else if (opt == 5)
    {
        cout << "\nInventor`s id\n";
        int id;
        cin >> id;
        inventorMenu(id);
    }
    else if (opt == 6)
    {
        show();
    }
    else
    {
        cout << "\nIncorrect input";
        exit(1);
    }
}

void Cui::printInventor(vector<Inventor> &inventor)
{
    for (Inventor &inventor : inventor)
    {
        cout << inventor.id << "  ";
        cout << inventor.name.c_str() << "  ";
        cout << inventor.invention.c_str() << "  ";
        cout << inventor.patents << endl;
    }
}

void Cui::inventorMenu(int entity_id)
{
    system("clear");

    if (!storage_->getInventorById(entity_id))
    {
        cout << "No inventor with this id\n" << endl;
    }
    else
    {
        optional<Inventor> inv_opt = storage_->getInventorById(entity_id);
        Inventor inv = inv_opt.value();
        cout << "Inventor with id " << entity_id << endl;
        cout << "Inventor`s name " << inv.name << endl;
        cout << "The most well-known invention " << inv.invention << endl;
        cout << "Quantity of patents " << inv.patents << endl;
    }
    cout << endl
         << "Enter anything to go back\n"
         << endl;
    int out;
    cin >> out;
    inventorMainMenu();
}

void Cui::inventorUpdateMenu(int entity_id)
{
    Inventor inv;
    inv.id = entity_id;
    cout << "\nNew inventor`s name: ";
    cin >> inv.name;
    cout << "New invention: ";
    cin >> inv.invention;
    cout << "New quantity of patents: ";
    cin >> inv.patents;
    if (storage_->updateInventor(inv))
        cout << "Updated\n";
    else
    {
        cout << "No inventor with this id " << entity_id;
    }
    cout << "\n\nEnter anything to go back" << endl;
    char c;
    cin >> c;
    inventorMainMenu();
}

void Cui::inventorDeleteMenu(int entity_id)
{
    system("clear");
    if (storage_->removeInventor(entity_id))
        cout << "\nInventor with id " << entity_id << " was deleted";
    else
        cout << "No inventor with this id " << entity_id;
    cout << "\n\nEnter anything to go back\n";
    char c;
    cin >> c;
    inventorMainMenu();
}

void Cui::inventorCreateMenu()
{
    Inventor inv;
    cout << "\nEnter new name: ";
    cin >> inv.name;
    cout << "Enter new invention: ";
    cin >> inv.invention;
    cout << "Enter quantity of patents: ";
    cin >> inv.patents;
    inv.id = storage_->insertInventor(inv);
    cout << "\n New inventor was created and their id is " << inv.id << endl;
    cout << "\n\nEnter anything to back";
    char c;
    cin >> c;
    inventorMainMenu();
}

void Cui::inventionMainMenu()
{
    system("clear");
    int opt;
    cout << "Choose an option:"
         << "\n1). Show inventions\n2). Update invention\n3). Delete invention\n4). Add invention\n5). Check detailed info\n6). Back" << endl;
    cin >> opt;
    if (opt == 1)
    {
        system("clear");
        for (Invention invtn : storage_->getAllInventions())
        {
            cout << invtn.id << "  " << invtn.data << endl;
        }
        cout << "Enter any number to go back: ";
        cin >> opt;
        inventionMainMenu();
    }
    else if (opt == 2)
    {
        cout << "\nEnter invention's id\n";
        int id;
        cin >> id;
        inventionUpdateMenu(id);
    }
    else if (opt == 3)
    {
        cout << "\nEnter invention's id\n";
        int id;
        cin >> id;
        inventionDeleteMenu(id);
    }
    else if (opt == 4)
    {
        inventionCreateMenu();
    }
    else if (opt == 5)
    {
        cout << "\nEnter invention's id\n";
        int id;
        cin >> id;
        inventionMenu(id);
    }
    else if (opt == 6)
    {
        show();
    }
    else
    {
        cout << "\nIncorrect input";
        exit(1);
    }
}

void Cui::printInvention(vector<Invention> &invention)
{
    for (Invention &invention : invention)
    {
        cout << invention.id << "  ";
        cout << invention.invent.c_str() << "  ";
        cout << invention.data.c_str() << "  ";
        cout << invention.year << endl;
    }
}

void Cui::inventionMenu(int entity_id)
{
    system("clear");
    if (!storage_->getInventionById(entity_id))
    {
        cout << "No invention with this id" << endl;
    }
    else
    {
        optional<Invention> invtn_opt = storage_->getInventionById(entity_id);
        Invention invtn = invtn_opt.value();
        cout << "Invention with id " << entity_id << endl;
        cout << "The invention is " << invtn.invent << endl;
        cout << "Brief info: " << invtn.data << endl;
        cout << "The year it was invented is " << invtn.year << endl;
    }
    cout << endl
         << "Enter anything to go back" << endl;
    int out;
    cin >> out;
    inventionMainMenu();
}

void Cui::inventionUpdateMenu(int entity_id)
{
    Invention invtn;
    invtn.id = entity_id;
    cout << "\nEnter new invention`s name: ";
    cin >> invtn.invent;
    cout << "Enter brief description of the invention: ";
    cin >> invtn.data;
    cout << "Enter the year it was invented in: ";
    cin >> invtn.year;
    if (storage_->updateInvention(invtn))
        cout << "Updated";
    else
    {
        cout << "No invention with this id " << entity_id;
    }
    cout << "\n\nEnter anything to go back" << endl;
    char c;
    cin >> c;
    inventionMainMenu();
}

void Cui::inventionDeleteMenu(int entity_id)
{
    system("clear");
    if (storage_->removeInvention(entity_id))
        cout << "\nInvention with id " << entity_id << " was deleted";
    else
        cout << "No invention with this id " << entity_id;
    cout << "\n\nEnter anything to go back\n";
    char c;
    cin >> c;
    inventionMainMenu();
}

void Cui::inventionCreateMenu()
{
    Invention invtn;
    cout << "\nEnter new name: ";
    cin >> invtn.invent;
    cout << "Enter brief description: ";
    cin >> invtn.data;
    cout << "Year of invention: ";
    cin >> invtn.year;
    invtn.id = storage_->insertInvention(invtn);
    cout << "\n Invention created and its id is " << invtn.id << endl;
    cout << "\n\nEnter anything to go back\n";
    char c;
    cin >> c;
    inventionMainMenu();
}
