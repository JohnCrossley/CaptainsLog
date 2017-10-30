//
// Created by johncrossley on 22/10/17.
//

#ifndef CAPTAINSLOG_PATHDELTA_H
#define CAPTAINSLOG_PATHDELTA_H

#include <string>

class PathDelta {
    public :
        PathDelta(const long add, const long remove, const std::string path);

        int getAdd() const;

        int getRemove() const;

        std::string getPath() const;

        std::string getExtensionType() const;

    private :
        long add;
        long remove;
        std::string path;
        std::string extensionType;
};


#endif //CAPTAINSLOG_PATHDELTA_H
