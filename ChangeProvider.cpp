//
// Created by Crossley, John : Personal & Corporate Banking on 06/12/2017.
//

#include "ChangeProvider.h"

ChangeCalculator* ChangeProvider::getForAllFiles(RankType type) {
    ChangeCalculator *impl;

    if (type == RT_DELTA) {
        impl = new AllFilesDeltaChange();
    } else {
        impl = new AllFilesTotalChange();
    }

    return impl;
}

ChangeCalculator* ChangeProvider::getForExtension(RankType type, std::string extension) {
    ChangeCalculator *impl;

    if (type == RT_DELTA) {
        impl = new ByExtensionDeltaChange(extension);
    } else {
        impl = new ByExtensionTotalChange(extension);
    }

    return impl;
}

ChangeCalculator *ChangeProvider::get(RankType type, std::string extension) {
    if (extension.empty()) {
        return getForAllFiles(type);
    } else {
        return getForExtension(type, extension);
    }
}
