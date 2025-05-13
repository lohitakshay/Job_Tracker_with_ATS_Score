cmake_minimum_required(VERSION 3.10)
project(JobTracker)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(SQLiteCpp REQUIRED)
find_package(CURL REQUIRED)

add_executable(JobTracker
    src/main.cpp
    src/DatabaseInit.cpp
    src/AddJob.cpp
    src/ListJobs.cpp
    src/DeleteEntry.cpp
    src/EditEntry.cpp
    src/ResumeMatcher.cpp
)

target_link_libraries(JobTracker
    PRIVATE SQLiteCpp
    PRIVATE SQLite::SQLite3
    PRIVATE CURL::libcurl
)
