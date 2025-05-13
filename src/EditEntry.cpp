#include "EditEntry.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include "utils.hpp"

using namespace std;

void editEntry(const string &dbPath)
{

    if (!hasJobs(dbPath))
    {
        cout << "\n-----------------------------------\n"
             << "    No entries currently present   \n"
             << "-----------------------------------\n";
        return;
    }

    int id;
    SQLite::Database db(dbPath, SQLite::OPEN_READWRITE);

    while (true)
    {
        string input;
        cout << endl;
        cout << "Enter the ID of the job to edit (or press Enter to cancel): ";
        getline(cin, input);

        if (input.empty())
        {
            cout << "\n-----------------------------------\n"
                 << "      Edit Operation Cancelled     \n"
                 << "-----------------------------------\n";
            return;
        }

        try
        {
            id = stoi(input);

            // Check if ID exists
            SQLite::Statement check(db, "SELECT company, role, status, deadline FROM jobs WHERE id = ?");
            check.bind(1, id);

            if (!check.executeStep())
            {
                cout << "\n-----------------------------------\n"
                     << "     No Job Entry Found with ID    \n"
                     << "-----------------------------------\n";
                continue; // Retry
            }

            string curr_comp = check.getColumn(0).getString();
            string curr_role = check.getColumn(1).getString();
            string curr_stat = check.getColumn(2).getString();
            string curr_deadl = check.getColumn(3).getString();

            string new_comp, new_role, new_stat, new_deadl;

            cout << "Enter new company (leave blank to keep '" << curr_comp << "'): ";
            getline(cin, new_comp);
            if (new_comp.empty())
                new_comp = curr_comp;

            cout << "Enter new role (leave blank to keep '" << curr_role << "'): ";
            getline(cin, new_role);
            if (new_role.empty())
                new_role = curr_role;

            cout << "Enter new status (leave blank to keep '" << curr_stat << "'): ";
            getline(cin, new_stat);
            if (new_stat.empty())
                new_stat = curr_stat;

            while (true)
            {
                cout << "Enter new deadline (leave blank to keep '" << curr_deadl << "'): ";
                getline(cin, new_deadl);
                if (new_deadl.empty())
                {
                    new_deadl = curr_deadl;
                    break;
                }
                if (isValidDate(new_deadl))
                    break;
                cout << "Invalid date format or date. Try again.\n";
            }

            SQLite::Statement update(db, "UPDATE jobs SET company = ?, role = ?, status = ?, deadline = ? WHERE id = ?");
            update.bind(1, new_comp);
            update.bind(2, new_role);
            update.bind(3, new_stat);
            update.bind(4, new_deadl);
            update.bind(5, id);

            if (update.exec() > 0)
            {
                cout << "\n-----------------------------------\n"
                     << "   Job Entry Updated Successfully  \n"
                     << "-----------------------------------\n";
            }
            else
            {
                cout << "\n-----------------------------------\n"
                     << "     Update Failed. No Changes     \n"
                     << "-----------------------------------\n";
            }

            break; // Edit complete
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a valid numeric ID.\n";
        }
    }
}
