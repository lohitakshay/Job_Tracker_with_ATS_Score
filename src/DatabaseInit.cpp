#include "DatabaseInit.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

using namespace std;

void initializeDatabase(const string &dbPath)
{
    try
    {
        SQLite::Database db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        db.exec(R"(
            CREATE TABLE IF NOT EXISTS jobs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                company TEXT NOT NULL,
                role TEXT NOT NULL,
                status TEXT DEFAULT 'Applied',
                deadline TEXT,
                resume_path TEXT,
                description TEXT,
                score INTEGER DEFAULT 0
            )
        )");
        cout << "\n-----------------------------------\n"
             << "  Database initialized successfully   \n"
             << "-----------------------------------\n";
    }
    catch (const exception &e)
    {
        cerr << "SQLite error: " << e.what() << endl;
    }
}
