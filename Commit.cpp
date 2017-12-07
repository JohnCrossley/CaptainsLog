//
// Created by johncrossley on 16/10/17.
//

#include "Commit.h"
#include "Date.h"
#include "Format.h"

Commit::Commit(const std::string hash, const long time, const std::vector<std::string> parents,
               const std::vector<PathDelta> pathDeltas) {
    this->hash = hash;
    this->time = time;
    this->parents = parents;
    this->pathDeltas = pathDeltas;

    for(const PathDelta &pathDelta : pathDeltas) {
        add += pathDelta.getAdd();
        remove += pathDelta.getRemove();
    }
}

std::vector<PathDelta> Commit::getPathDeltas() const {
    return pathDeltas;
}

long Commit::getTime() const {
    return time;
}

long Commit::getTotalAdd() const {
    return add;
}

long Commit::getTotalRemove() const {
    return remove;
}

std::ostream& operator<<(std::ostream& ostream, const Commit& commit) {
    ostream << formatDiff(formatDate(commit) + " " + commit.hash, commit.add, commit.remove);
    return ostream;
}
