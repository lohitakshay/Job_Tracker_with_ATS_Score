@echo off
echo Building Job Tracker...

g++ main.cpp ^
    AddJob.cpp ^
    DatabaseInit.cpp ^
    DeleteEntry.cpp ^
    EditEntry.cpp ^
    utils.cpp ^
    ListJobs.cpp ^
    ResumeMatcher.cpp ^
    C:/Users/USER/Documents/SQLiteCpp/src/*.cpp ^
    C:/Users/USER/Documents/sqlite-amalgamation-3490200/sqlite3.o ^
    -o output.exe ^
    -I../include ^
    -IC:/Users/USER/Documents/SQLiteCpp/include ^
    -IC:/Users/USER/Documents/sqlite-amalgamation-3490200 ^
    -IC:/Users/USER/Documents/curl-8.13.0_3-win64-mingw/curl-8.13.0_3-win64-mingw/include ^
    -LC:/Users/USER/Documents/curl-8.13.0_3-win64-mingw/curl-8.13.0_3-win64-mingw/lib ^
    -lcurl

if %ERRORLEVEL%==0 (
    echo Build succeeded.
    echo Running output.exe...
    output.exe
) else (
    echo Build failed.
)
pause
