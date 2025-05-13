#include "ListJobs.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

using namespace std;

void listAllJobs(const string &dbPath)
{
    try
    {
        SQLite::Database db(dbPath, SQLite::OPEN_READONLY);
        SQLite::Statement query(db,
                                "SELECT id, company, role, status, deadline, score FROM jobs");
        cout << "\n--- Job Applications ---\n";
        bool found = false;
        while (query.executeStep())
        {
            found = true;
            cout << "ID: " << query.getColumn(0).getInt() << "\n"
                 << "Company: " << query.getColumn(1).getString() << "\n"
                 << "Role: " << query.getColumn(2).getString() << "\n"
                 << "Status: " << query.getColumn(3).getString() << "\n"
                 << "Deadline: " << query.getColumn(4).getString() << "\n"
                 << "Score: " << query.getColumn(5).getInt() << "\n"
                 << "------------------------\n";
        }
        if (!found)
            cout << "\n-----------------------------------\n"
                 << "    No entries currently present   \n"
                 << "-----------------------------------\n";
        return;
    }
    catch (const exception &e)
    {
        cerr << "Error listing jobs: " << e.what() << endl;
    }
}
