#include "DeleteEntry.hpp"
#include "utils.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

using namespace std;


void deleteEntry(const string &dbPath)
{
    if (!hasJobs(dbPath)) 
    {
        cout << "\n-----------------------------------\n"
             << "    No entries currently present   \n"
             << "-----------------------------------\n";
        return;
    }

    SQLite::Database db(dbPath, SQLite::OPEN_READWRITE);
    int id;
    string input;
    cout << endl;
    cout << "Enter the Job ID you want to delete (or press Enter to cancel): ";
    getline(cin, input);

    if (input.empty())
    {
        cout << "\n-----------------------------------\n"
             << "     Delete Operation Cancelled    \n"
             << "-----------------------------------\n";
        return;
    }

    try
    {
        id = stoi(input);
    }
    catch (...)
    {
        cout << "\n-----------------------------------\n"
             << "     Invalid Job ID Provided       \n"
             << "-----------------------------------\n";
        return; // Exit function on invalid ID
    }

    SQLite::Statement check(db, "SELECT id FROM jobs WHERE id = ?");
    check.bind(1, id);

    if (!check.executeStep())
    {
        cout << "\n-----------------------------------\n"
             << "        No Such Entry Found        \n"
             << "-----------------------------------\n";
        return; // Exit function if no matching job ID found
    }

    string confirm;
    cout << "Are you sure you want to delete the job entry with ID " << id << "? (y/n): ";
    getline(cin, confirm);

    if (confirm == "y" || confirm == "Y")
    {
        SQLite::Statement del(db, "DELETE FROM jobs WHERE id = ?");
        del.bind(1, id);
        int rows = del.exec();

        if (rows > 0)
        {
            cout << "\n-----------------------------------\n"
                 << "  Job entry deleted successfully   \n"
                 << "-----------------------------------\n";
        }
        else
        {
            cout << "\n-----------------------------------\n"
                 << "        Deletion Failed!           \n"
                 << "-----------------------------------\n";
        }
    }
    else
    {
        cout << "\n-----------------------------------\n"
             << "     Delete Operation Cancelled    \n"
             << "-----------------------------------\n";
    }
}
