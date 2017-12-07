//
// Created by johncrossley on 15/10/17.
//

#ifndef CAPTAINSLOG_AUTHOR_H
#define CAPTAINSLOG_AUTHOR_H

#include <iostream>
#include <vector>
#include "Commit.h"
#include "ChangeCalculator.h"

class Author {
    private :
        std::string author;
        std::vector<Commit> commits;
        long add = 0;
        long remove = 0;
        long change = 0;
        ChangeCalculator *changeCalculator;

public:
    Author(std::string author, std::vector<Commit> commits, ChangeCalculator *changeCalculator1);

    std::string getAuthor() const;

    std::vector<Commit> getCommits() const;

    long getTotalAdd() const;

    long getTotalRemove() const;

    int getTotal() const;

    friend std::ostream& operator<<(std::ostream& ostream, const Author& author);
};


#endif //CAPTAINSLOG_AUTHOR_H
