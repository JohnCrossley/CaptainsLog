//
// Created by johncrossley on 23/10/17.
//

#ifndef CAPTAINSLOG_DELTA_H
#define CAPTAINSLOG_DELTA_H


#include <ostream>
#include <string>

class Delta {
public :
    Delta(std::string name);

    std::string getName() const;

    void addAmount(long value);

    void removeAmount(long value);

    long getAdd() const;

    long getRemove() const;

    friend std::ostream& operator<<(std::ostream& ostream, const Delta& delta);

private :
    std::string name;
    long add;
    long remove;
};

#endif //CAPTAINSLOG_DELTA_H
