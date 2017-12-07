//
// Created by Crossley, John : Personal & Corporate Banking on 01/12/2017.
//

#ifndef CAPTAINSLOG_SETTINGS_H
#define CAPTAINSLOG_SETTINGS_H

#include "ChangeProvider.h"

enum FileMode {
    FM_OFF,
    FM_FILE,
    FM_EXTENSION,
    FM_ALL
};

class Settings {
public:
    FileMode authorCommitMode = ::FileMode::FM_OFF;
    FileMode authorSummaryMode = ::FileMode::FM_OFF;
    FileMode repoSummaryMode = ::FileMode::FM_OFF;

    std::string root = "";
    std::string args = "";

    RankType rankType = RT_DELTA;//default
    std::string extensionToRank = "";
};

#endif //CAPTAINSLOG_SETTINGS_H
