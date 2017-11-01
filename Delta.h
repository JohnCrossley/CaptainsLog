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

    void addAmount(unsigned long value);

    void removeAmount(unsigned long value);

    unsigned long getAdd() const;

    unsigned long getRemove() const;

    friend std::ostream& operator<<(std::ostream& ostream, const Delta& delta);

private :
    std::string name;
    unsigned long add;
    unsigned long remove;
};

#endif //CAPTAINSLOG_DELTA_H
