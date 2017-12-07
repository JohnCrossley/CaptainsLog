//
// Created by johncrossley on 30/10/17.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <climits>

const int MAX_STRING = 100;
const int MAX_LONG   = std::to_string(LONG_MAX).length();
const std::string ELLIPSES = "...";

std::string formatString(const std::string string) {
    if (string.length() > MAX_STRING) {
        return ELLIPSES + string.substr(string.length() - MAX_STRING + ELLIPSES.length(), MAX_STRING - ELLIPSES.length());
    }

    std::stringstream ss;
    ss << std::left << std::setw(MAX_STRING) << string;
    return ss.str();
}


std::string formatValue(const long value) {
    std::stringstream ss;
    ss << std::setw(MAX_LONG) << value;
    return ss.str();
}

std::string formatValueSigned(const long value) {
    bool positive = value >= 0;

    std::stringstream ss;
    ss << std::setw(MAX_LONG + 1) << std::abs(value) << (positive ? "+" : "-");
    return ss.str();
}

std::string formatCommit(const std::string string, const long add, const long remove) {
    return string + " " + formatValue(add) + "+  " + formatValue(remove) + "-";
}

std::string formatDiff(const std::string string, const long add, const long remove) {
    return formatString(string) + formatValue(add) + "+  " + formatValue(remove) + "-";
}

std::string padCommand(const std::string command) {
    std::stringstream ss;
    ss << std::left << std::setw(25) << command;
    return ss.str();
}