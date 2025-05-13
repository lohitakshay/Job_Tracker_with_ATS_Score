#include "Utils.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <regex>

using namespace std;

bool hasJobs(const string &dbPath)
{
    SQLite::Database db(dbPath, SQLite::OPEN_READONLY);
    SQLite::Statement query(db, "SELECT COUNT(*) FROM jobs");
    query.executeStep();
    return query.getColumn(0).getInt() > 0;
}

bool isValidDate(const string &date)
{
    regex date_pattern(R"(^(\d{2})-(\d{2})-(\d{4})$)");
    smatch match;
    if (!regex_match(date, match, date_pattern))
        return false;

    int day = stoi(match[1]);
    int month = stoi(match[2]);
    int year = stoi(match[3]);

    if (month < 1 || month > 12)
        return false;

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        days_in_month[1] = 29;

    return day >= 1 && day <= days_in_month[month - 1];
}
