//
// Created by johncrossley on 15/10/17.
//

#ifndef CAPTAINSLOG_AUTHOR_H
#define CAPTAINSLOG_AUTHOR_H

#include <iostream>
#include <vector>
#include "Commit.h"

class Author {
    private :
        std::string author;
        std::vector<Commit> commits;
        unsigned long add = 0;
        unsigned long remove = 0;

public:
    Author(std::string author, std::vector<Commit> commits);

    std::string getAuthor() const;

    std::vector<Commit> getCommits() const;

    friend std::ostream& operator<<(std::ostream& ostream, const Author& author);
};


#endif //CAPTAINSLOG_AUTHOR_H
