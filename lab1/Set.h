#ifndef SET_H
#define SET_H

#include <vector>
#include <string>

class Set {
private:
    std::vector<std::string> elements;

public:
    Set();
    bool IsEmpty() const;
    unsigned int Size() const;
    bool Add(const std::string& element);
};

#endif