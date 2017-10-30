//
// Created by johncrossley on 15/10/17.
//

#include "Author.h"
#include "Date.h"

Author::Author(std::string author, std::vector<Commit> commits) {
    this->author = author;
    this->commits = commits;

    for(const Commit &commit : commits) {
        add += commit.getTotalAdd();
        remove += commit.getTotalRemove();
    }
}

std::string Author::getAuthor() const {
    return author;
}

std::vector<Commit> Author::getCommits() const {
    return commits;
}

std::ostream& operator<<(std::ostream& ostream, const Author& author) {
    std::string firstCommit = (author.getCommits().size() == 0) ? "n/a" : formatDate(author.getCommits()[author.getCommits().size() - 1]);
    std::string lastCommit = (author.getCommits().size() == 0) ? "n/a" : formatDate(author.getCommits()[0]);

    std::cout << author.getAuthor() << " -> " << author.getCommits().size() << " commits [" << firstCommit << " - " << lastCommit << "]" << std::endl;
    return ostream;
}


