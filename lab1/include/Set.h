#ifndef SET_H
#define SET_H

#include <vector>
#include <string>

class Set {
public:
    Set();
    ~Set();
    void FormSetFromString(const std::string& str, bool form_or_add);
    bool IsEmpty() const;
    unsigned int Size() const;
    bool Add(const std::string& element);
    bool Add(const Set& subset);
    bool Delete(const std::string& element);
    bool Delete(const Set& subset);
    bool Contains(const std::string& element) const;
    bool Contains(const Set& subset) const;
    std::string PrintSet();

private:
    std::vector<std::string> elements_;
    std::vector<Set> set_elements_;
    Set Recursive(const std::string& str, unsigned int& position);
    bool IsEqual(const Set& other) const;
};

#endif