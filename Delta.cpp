//
// Created by johncrossley on 23/10/17.
//

#include <iostream>
#include "Delta.h"
#include "Format.h"

Delta::Delta(std::string name) {
    this->name = name;
    this->add = 0L;
    this->remove = 0L;
}

void Delta::addAmount(long value) {
    add += value;
}

void Delta::removeAmount(long value) {
    remove += value;
}

std::string Delta::getName() const {
    return name;
}

long Delta::getAdd() const {
    return add;
}

long Delta::getRemove() const {
    return remove;
}

std::ostream& operator<<(std::ostream& ostream, const Delta& delta) {
    ostream << formatDiff(delta.getName(), delta.getAdd(), delta.getRemove());
    return ostream;
}
