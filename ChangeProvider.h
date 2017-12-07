//
// Created by Crossley, John : Personal & Corporate Banking on 06/12/2017.
//

#ifndef CAPTAINSLOG_CHANGEPROVIDER_H
#define CAPTAINSLOG_CHANGEPROVIDER_H

#include "Author.h"
#include "ChangeCalculator.h"
#include "RankType.h"

class ChangeProvider {
private:
    ChangeCalculator* getForAllFiles(RankType type);
    ChangeCalculator* getForExtension(RankType type, std::string extension);

public:
    ChangeCalculator *get(RankType type, std::string basic_string);
};

#endif //CAPTAINSLOG_CHANGEPROVIDER_H
