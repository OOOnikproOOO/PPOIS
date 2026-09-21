#include "Set.h"

Set::Set() {}

bool Set::IsEmpty() const {
    return elements.empty();
}

unsigned int Set::Size() const {
    return elements.size();
}

bool Set::Add(const std::string& element) {
    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements[i] == element)
            return false;
    elements.push_back(element);
    return true;
}