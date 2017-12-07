//
// Created by johncrossley on 19/10/17.
//

#ifndef CAPTAINSLOG_GIT_H
#define CAPTAINSLOG_GIT_H

#include <string>
#include <vector>
#include "Commit.h"
#include "Settings.h"

const std::string exec(const Settings, const std::string cmd);

const std::vector<std::string> getAuthorNames(const Settings settings);

const std::vector<Commit> getCommitMetaData(const Settings settings, std::string authorName);

#endif //CAPTAINSLOG_GIT_H
