#include "ResumeMatcher.hpp"
#include <curl/curl.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace ResumeMatcher
{

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }

    static string readFile(const string &path)
    {
        ifstream file(path);
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    int getScore(const string &resumePath, const string &jdText)
    {
        string resumeText = readFile(resumePath);
        string response;

        CURL *curl = curl_easy_init();
        if (curl)
        {
            string postData = "resume=" + string(curl_easy_escape(curl, resumeText.c_str(), 0)) +
                              "&jd=" + string(curl_easy_escape(curl, jdText.c_str(), 0));

            curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/match");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res == CURLE_OK)
            {
                size_t scorePos = response.find(":");
                if (scorePos != string::npos)
                {
                    return stoi(response.substr(scorePos + 1));
                }
            }
        }
        return 0;
    }

} // namespace ResumeMatcher
