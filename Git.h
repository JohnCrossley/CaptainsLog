//
// Created by johncrossley on 19/10/17.
//

#ifndef CAPTAINSLOG_GIT_H
#define CAPTAINSLOG_GIT_H

#include <string>
#include <vector>
#include "Commit.h"

const std::string exec(const std::string root, const std::string cmd);

const std::vector<std::string> getAuthorNames(const std::string root, std::string args);

const std::vector<Commit> getCommitMetaData(std::string root, std::string args, std::string authorName);

#endif //CAPTAINSLOG_GIT_H
