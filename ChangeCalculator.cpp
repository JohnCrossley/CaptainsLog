//
// Created by Crossley, John : Personal & Corporate Banking on 06/12/2017.
//

#ifndef CAPTAINSLOG_CHANGE_H

#include "ChangeCalculator.h"
#include "Author.h"

long AllFilesDeltaChange::calculateChange(const Author author) {
    return author.getTotalAdd() - author.getTotalRemove();
}

const std::string AllFilesDeltaChange::describe() {
    return "Delta (all ext)";
}

long AllFilesTotalChange::calculateChange(const Author author) {
    return author.getTotalAdd() + author.getTotalRemove();
}

const std::string AllFilesTotalChange::describe() {
    return "Change (all ext)";
}

ByExtensionDeltaChange::ByExtensionDeltaChange(const std::string &ext) {
    extension = ext;
}

long ByExtensionDeltaChange::calculateChange(const Author author) {
    long count = 0;
    for(const Commit commit : author.getCommits()) {
        for(const PathDelta pathDelta : commit.getPathDeltas()) {
            if (pathDelta.getExtensionType().compare(extension) == 0) {
                count += pathDelta.getAdd() - pathDelta.getRemove();
            }
        }
    }

    return count;
}

const std::string ByExtensionDeltaChange::describe() {
    return "Delta (" + extension + ")";
}

ByExtensionTotalChange::ByExtensionTotalChange(const std::string &ext) {
    extension = ext;
}

long ByExtensionTotalChange::calculateChange(const Author author) {
    long count = 0;
    for(const Commit commit : author.getCommits()) {
        for(const PathDelta pathDelta : commit.getPathDeltas()) {
            if (pathDelta.getExtensionType().compare(extension) == 0) {
                count += pathDelta.getAdd() - pathDelta.getRemove();
            }
        }
    }

    return count;
}

const std::string ByExtensionTotalChange::describe() {
    return "Change (" + extension + ")";
}

#endif //CAPTAINSLOG_CHANGE_H
