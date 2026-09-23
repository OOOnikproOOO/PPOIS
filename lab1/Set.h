#ifndef SET_H
#define SET_H

#include <vector>
#include <string>

class Set {
private:
    std::vector<std::string> elements;
    std::vector<Set> set_elements;
    Set Recursive(const std::string& str, unsigned int& position);

public:
    Set();
    void FormSetFromString(const std::string& str, bool form_or_add);
    bool IsEmpty() const;
    unsigned int Size() const;
    bool Add(const std::string& element);
    bool Add(const Set& element);
    bool Delete(const std::string& element);
    bool Delete(const Set& element);
};

#endif