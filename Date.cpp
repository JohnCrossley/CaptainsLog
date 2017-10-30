//
// Created by johncrossley on 27/10/17.
//

#include <ctime>
#include "Date.h"

std::string formatDate(const Commit &commit) {
    std::time_t test = commit.getTime();

    char s[11];
    struct tm * p = localtime(&test);

    strftime(s, 11, "%d/%m/%Y", p);

    return s;
}
