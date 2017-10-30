//
// Created by johncrossley on 30/10/17.
//

#include <iostream>
#include <sstream>
#include <iomanip>

#define MAX_STRING  50
#define MAX_LONG     8

const std::string ELLIPSES = "...";

std::string formatString(const std::string string) {
    if (string.length() > MAX_STRING) {
        return ELLIPSES + string.substr(string.length() - MAX_STRING + ELLIPSES.length(), MAX_STRING - ELLIPSES.length());
    }

    std::stringstream ss;
    ss << std::setw(MAX_STRING) << string;
    return ss.str();
}


std::string formatValue(const long value) {
    std::stringstream ss;
    ss << std::setw(MAX_LONG) << value;
    return ss.str();
}

std::string formatCommit(const std::string string, const long add, const long remove) {
    return string + " " + formatValue(add) + "+  " + formatValue(remove) + "-";
}

std::string formatDiff(const std::string string, const long add, const long remove) {
    return formatString(string) + formatValue(add) + "+  " + formatValue(remove) + "-";
}

