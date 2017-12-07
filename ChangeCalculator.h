//
// Created by Crossley, John : Personal & Corporate Banking on 06/12/2017.
//
#ifndef CAPTAINSLOG_CHANGE_H
#define CAPTAINSLOG_CHANGE_H

#include <string>
class Author;//FD

class ChangeCalculator {
public:
    virtual long calculateChange(Author) = 0;
    virtual const std::string describe() = 0;
};

class AllFilesDeltaChange : public ChangeCalculator {
public:
    long calculateChange(const Author) override;
    const std::string describe() override;
};

class AllFilesTotalChange : public ChangeCalculator {
public:
    long calculateChange(const Author) override;
    const std::string describe() override;
};

class ByExtensionDeltaChange : public ChangeCalculator {
private:
    std::string extension;

public:
    ByExtensionDeltaChange(const std::string &ext);

    long calculateChange(const Author) override;
    const std::string describe() override;
};

class ByExtensionTotalChange : public ChangeCalculator {
private:
    std::string extension;

public:
    ByExtensionTotalChange(const std::string &ext);

    long calculateChange(const Author) override;
    const std::string describe() override;
};

#endif //CAPTAINSLOG_CHANGE_H
