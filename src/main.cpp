#include <iostream>
#include <Windows.h>
#include "DatabaseInit.hpp"
#include "AddJob.hpp"
#include "ListJobs.hpp"
#include "DeleteEntry.hpp"
#include "EditEntry.hpp"

using namespace std;

int main()
{
    // Start Python server automatically
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a mutable command string
    string cmd = "python matcher_api.py";
    char cmdLine[256];
    strcpy_s(cmdLine, cmd.c_str()); // safe copy into modifiable buffer

    if (!CreateProcess(
            NULL,
            (LPSTR) "python matcher_api.py", 
            NULL,
            NULL,
            FALSE,
            CREATE_NO_WINDOW,
            NULL,
            NULL,
            &si,
            &pi))
    {
        cerr << "Failed to start Python matcher API server.\n";
        return 1;
    }

    // Give Python server time to start
    Sleep(3000); // 3 seconds

    string dbPath = "../database/jobs.db";
    initializeDatabase(dbPath);

    while (true)
    {
        cout << "\n==== Job Application Tracker ====\n"
             << "1. Add Job Entry\n"
             << "2. List All Jobs\n"
             << "3. Edit Job Entry\n"
             << "4. Delete Job Entry\n"
             << "5. Exit\n"
             << "Select an option: ";

        string input;
        getline(cin, input);

        if (input.empty())
            continue;

        try
        {
            int choice = stoi(input);
            switch (choice)
            {
            case 1:
                addJob(dbPath);
                break;
            case 2:
                listAllJobs(dbPath);
                break;
            case 3:
                editEntry(dbPath);
                break;
            case 4:
                deleteEntry(dbPath);
                break;
            case 5:
                cout << "Goodbye!\n";
                TerminateProcess(pi.hProcess, 0); // Kill Python server
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
            }
        }
        catch (...)
        {
            cout << "Invalid input. Enter a number 1-5.\n";
        }
    }
}
