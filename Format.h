//
// Created by johncrossley on 30/10/17.
//

#ifndef CAPTAINSLOG_FORMAT_H
#define CAPTAINSLOG_FORMAT_H

#include <string>

std::string formatString(const std::string string);
std::string formatValue(const unsigned long value);
std::string formatCommit(const std::string string, const unsigned long add, const unsigned long remove);
std::string formatDiff(const std::string string, const unsigned long add, const unsigned long remove);

#endif //CAPTAINSLOG_FORMAT_H
