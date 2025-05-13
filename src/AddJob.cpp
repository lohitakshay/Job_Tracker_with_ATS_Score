#include "AddJob.hpp"
#include "ResumeMatcher.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

using namespace std;

void addJob(const string &dbPath)
{
    string company, role, status, deadline, description, resume_path;

    cout << "Enter Company's name: ";
    getline(cin, company);

    cout << "Enter Job Role: ";
    getline(cin, role);

    cout << "Enter Status [Applied/Rejected/Interview/Wishlist]: ";
    getline(cin, status);

    cout << "Enter deadline [DD-MM-YYYY]: ";
    getline(cin, deadline);

    cout << "Paste the job description (type END on a new line to finish):\n";
    string line;
    while (getline(cin, line) && line != "END")
    {
        description += line + "\n";
    }

    cout << "Enter path to your resume file (TXT only): ";
    getline(cin, resume_path);

    int score = 0;
    if (!resume_path.empty())
    {
        score = ResumeMatcher::getScore(resume_path, description);
        cout << "Resume-JD match score: " << score << endl;
    }

    try
    {
        SQLite::Database db(dbPath, SQLite::OPEN_READWRITE);
        SQLite::Statement query(db,
                                "INSERT INTO jobs (company, role, status, deadline, resume_path, description, score) "
                                "VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.bind(1, company);
        query.bind(2, role);
        query.bind(3, status);
        query.bind(4, deadline);
        query.bind(5, resume_path);
        query.bind(6, description);
        query.bind(7, score);
        query.exec();
        cout<<endl;
        cout << "Job entry added successfully!" << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error adding job entry: " << e.what() << endl;
    }
}
