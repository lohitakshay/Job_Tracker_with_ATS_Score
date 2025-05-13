#ifndef RESUME_MATCHER_HPP
#define RESUME_MATCHER_HPP

#include <string>

namespace ResumeMatcher {
    int getScore(const std::string& resumePath, const std::string& jdText);
}

#endif
