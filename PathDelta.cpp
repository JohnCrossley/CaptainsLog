//
// Created by johncrossley on 22/10/17.
//

#include "PathDelta.h"

PathDelta::PathDelta(const long add, const long remove, const std::string path) {
    this->add = add;
    this->remove = remove;
    this->path = path;

    if (path.rfind('.') >= 0) {
        extensionType = path.substr(path.rfind('.'));
    }
}

int PathDelta::getAdd() const {
    return add;
}

int PathDelta::getRemove() const {
    return remove;
}

std::string PathDelta::getPath() const {
    return path;
}

std::string PathDelta::getExtensionType() const {
    return extensionType;
}



