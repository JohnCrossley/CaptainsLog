//
// Created by johncrossley on 16/10/17.
//

#ifndef CAPTAINSLOG_COMMIT_H
#define CAPTAINSLOG_COMMIT_H

#include <iostream>
#include <vector>
#include "PathDelta.h"

class Commit {
    private :
        std::string hash;
        long time;
        std::vector<std::string> parents;
        std::vector<PathDelta> pathDeltas;

        long add = 0;
        long remove = 0;

    public :
        Commit(const std::string hash, const long time, const std::vector<std::string> parents, const std::vector<PathDelta> pathDeltas);

        std::vector<PathDelta> getPathDeltas() const;

        long getTime() const;

        long getTotalAdd() const;

        long getTotalRemove() const;

        friend std::ostream& operator<<(std::ostream& ostream, const Commit& commit);

};


#endif //CAPTAINSLOG_COMMIT_H
