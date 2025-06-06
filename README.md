# 💼 Job Tracker with ATS Score

A modular C++ command-line tool for tracking job applications, featuring resume-to-job-description (JD) matching and scoring (ATS Score) powered by a Python API.  
Built with SQLite for persistent storage, libcurl for API calls, and a clean, maintainable codebase with each function in its own file.

---

## 🚀 Features

- **Add, List, Edit, and Delete Job Entries**  
  Track all your job applications with company, role, status, deadline, and more.

- **Resume vs JD Matching (ATS Score)**  
  Paste a job description and provide your resume (TXT file). The tool uses a Python Flask API to calculate a match score between your resume and the JD, helping you prioritize applications.

- **Persistent Storage**  
  All data is stored in a local SQLite database.

- **Modular Design**  
  Each major function is implemented in its own `.cpp`/`.hpp` file for easy maintenance and extension.

- **Cross-language Integration**  
  Uses Python for advanced text processing, called seamlessly from C++.

---

## 🗂️ Project Structure

```bash
Job_Tracker_with_ATS_Score/
├── include/ # All C++ header files
│ ├── AddJob.hpp
│ ├── DeleteEntry.hpp
│ ├── EditEntry.hpp
│ ├── ListJobs.hpp
│ ├── ResumeMatcher.hpp
│ └── DatabaseInit.hpp
├── src/ # All C++ source files
│ ├── main.cpp
│ ├── AddJob.cpp
│ ├── DeleteEntry.cpp
│ ├── EditEntry.cpp
│ ├── ListJobs.cpp
│ ├── matcher_api.py 
│ ├── ResumeMatcher.cpp
│ └── DatabaseInit.cpp
├── database
│ ├── job.db
├── CMakeLists.txt
└── README.md
```

---

## ⚙️ Dependencies

- **C++17**
- [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)
- [libcurl](https://curl.se/libcurl/)
- [Python 3.x](https://www.python.org/)
- [Flask](https://pypi.org/project/Flask/)

---

## 🛠️ Build & Run

### 1. Clone the Repository

```bash
git clone https://github.com/lohitakshay/Job_Tracker_with_ATS_Score.git
cd Job_Tracker_with_ATS_Score
```

### 2. Install Dependencies

C++ Libraries
Use vcpkg or your preferred package manager:

```bash
vcpkg install sqlitecpp curl
```

Python & Flask
```bash
pip install flask
```

### 3. Build the C++ Project
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 4. Run the Job Tracker
```bash
./JobTracker
```

---

📝 Usage
Add Job Entry:
Enter company, role, status, deadline, JD (multi-line, end with END), and path to your resume (TXT).

List All Jobs:
View all applications and their ATS scores.

Edit/Delete:
Update or remove entries by ID.

ATS Score:
The tool compares your resume with the JD and shows a score (higher is better).

🤖 How the ATS Score Works
The Python Flask API removes stopwords and punctuation, then compares unique words in your resume and the job description.

The score is based on the count of overlapping words, giving you a quick sense of how well your resume matches the job.

---

📦 .gitignore Includes
Build artifacts (/build/)

Compiled binaries (*.exe, *.o, etc.)

VSCode settings (.vscode/)

Python cache (__pycache__/)

SQLite database files

---

Happy job tracking and best of luck with your applications!
