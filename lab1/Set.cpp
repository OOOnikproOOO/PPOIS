#include "Set.h"

Set::Set() {}

void Set::FormSetFromString(const std::string& str, bool form_or_add) {
    if (form_or_add) {
        elements.clear();
        set_elements.clear();
    }

    unsigned int position = 0;
    while (position < str.length() && str[position] != '{') position++;

    if (position < str.length() && str[position] == '{') {
        *this = Recursive(str, position);
    }
}

Set Set::Recursive(const std::string& str, unsigned int& position) {
    Set the_set;
    std::string the_element = "";
    position++; // пропуск "{"

    while (position < str.length()) {
        char sign = str[position];

        if (sign == ' ') {
            position++;
            continue;
        }

        if (sign == '{') {
            Set subset = Recursive(str, position);
            the_set.Add(subset);
        }
        else if (sign == '}') {
            if (!the_element.empty()) {
                the_set.Add(the_element);
                the_element = "";
            }
            position++;
            break; // выход из рекурсии
        }
        else if (sign == ',') {
            if (!the_element.empty()) {
                the_set.Add(the_element);
                the_element = "";
            }
            position++;
        }
        else {
            the_element += sign;
            position++;
        }
    }

    return the_set;
}

bool Set::IsEmpty() const {
    if (elements.empty() && set_elements.empty()) return true;
    else return false;
}

unsigned int Set::Size() const {
    return elements.size() + set_elements.size();
}

bool Set::Add(const std::string& element) {
    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements[i] == element)
            return false;
    elements.push_back(element);
    return true;
}

bool Set::Delete(const std::string& element) {
    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements[i] == element)
        {
            elements.erase(elements.begin() + i);
            return true;
        }
    return false;
}