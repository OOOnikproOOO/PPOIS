#include "Set.h"

Set::Set() {

}

Set::~Set() {

}

void Set::FormSetFromString(const std::string& str, bool form_or_add) {
    if (form_or_add) {
        elements_.clear();
        set_elements_.clear();
    }

    unsigned int position = 0;
    while (position < str.length() && str[position] != '{')
        position++;

    if (position < str.length() && str[position] == '{')
        *this = Recursive(str, position);
}

Set Set::Recursive(const std::string& str, unsigned int& position) {
    Set the_set;
    std::string the_element = "";
    position++; // Пропуск "{"

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
            break; // Выход из рекурсии
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
    if (elements_.empty() && set_elements_.empty())
        return true;
    else return false;
}

unsigned int Set::Size() const {
    return elements_.size() + set_elements_.size();
}

bool Set::Add(const std::string& element) {
    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (elements_[i] == element)
            return false;
    }
    elements_.push_back(element);
    return true;
}

bool Set::Delete(const std::string& element) {
    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (elements_[i] == element)
        {
            elements_.erase(elements_.begin() + i);
            return true;
        }
    }
    return false;
}

bool Set::Contains(const std::string& element) const {
    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (elements_[i] == element)
            return true;
    }
    return false;
}

bool Set::Contains(const Set& subset) const {
    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (set_elements_[i].IsEqual(subset)) 
            return true;
    }
    return false;
}

bool Set::IsEqual(const Set& other) const {
    if ((elements_.size() != other.elements_.size()) || (set_elements_.size() != other.set_elements_.size())) 
        return false;

    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (!other.Contains(elements_[i])) 
            return false;
    }

    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (!other.Contains(set_elements_[i]))
            return false;
    }
    return true;
}

bool Set::Add(const Set& subset) {
    if (this->Contains(subset))
        return false;
    set_elements_.push_back(subset);
    return true;
}

bool Set::Delete(const Set& subset) {
    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (set_elements_[i].IsEqual(subset)) {
            set_elements_.erase(set_elements_.begin() + i);
            return true;
        }
    }
    return false;
}

std::string Set::PrintSet() {
    std::string result = "{ ";
    bool first = true; // Флажок, чтобы не ставить запятую перед первым элементом

    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (!first)
            result += ", ";
        result += elements_[i];
        first = false;
    }

    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (!first) {
            result += ", ";
        }
        result += set_elements_[i].PrintSet();
        first = false;
    }

    result += " }";
    return result;
}