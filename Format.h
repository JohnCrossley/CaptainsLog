//
// Created by johncrossley on 30/10/17.
//

#ifndef CAPTAINSLOG_FORMAT_H
#define CAPTAINSLOG_FORMAT_H

#include <string>

std::string formatString(const std::string string);
std::string formatValue(const long value);
std::string formatCommit(const std::string string, const long add, const long remove);
std::string formatDiff(const std::string string, const long add, const long remove);

#endif //CAPTAINSLOG_FORMAT_H
