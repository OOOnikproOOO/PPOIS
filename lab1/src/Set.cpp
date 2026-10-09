/**
 * @file Set.cpp
 * @brief Реализация методов класса Set ("Неориентированное канторовское множество").
 * @author Nikita Momot
 * @date 2026
 */

#include "Set.h"

Set::Set() {

}

Set::Set(const Set& other) {
    this->elements_ = other.elements_;
    this->set_elements_ = other.set_elements_;
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        this->elements_ = other.elements_;
        this->set_elements_ = other.set_elements_;
    }
    return *this;
}

bool Set::operator[](const std::string& element) const {
    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (elements_[i] == element)
            return true;
    }
    return false;
}

bool Set::operator[](const Set& subset) const {
    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (set_elements_[i] == subset)
            return true;
    }
    return false;
}

Set Set::operator+(const Set& other) const {
    Set result(*this);
    result += other;
    return result;
}

Set& Set::operator+=(const Set& other) {
    for (unsigned int i = 0; i < other.elements_.size(); i++)
        this->Add(other.elements_[i]);

    for (unsigned int i = 0; i < other.set_elements_.size(); i++)
        this->Add(other.set_elements_[i]);

    return *this;
}

Set Set::operator*(const Set& other) const {
    Set result;
    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (other[elements_[i]]) {
            result.Add(elements_[i]);
        }
    }
    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (other[set_elements_[i]]) {
            result.Add(set_elements_[i]);
        }
    }
    return result;
}

Set& Set::operator*=(const Set& other) {
    *this = *this * other;
    return *this;
}

Set Set::operator-(const Set& other) const {
    Set result;
    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (!(other[elements_[i]]))
            result.Add(elements_[i]);
    }
    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (!(other[set_elements_[i]]))
            result.Add(set_elements_[i]);
    }
    return result;
}

Set& Set::operator-=(const Set& other) {
    for (unsigned int i = 0; i < other.elements_.size(); i++)
        this->Delete(other.elements_[i]);

    for (unsigned int i = 0; i < other.set_elements_.size(); i++)
        this->Delete(other.set_elements_[i]);

    return *this;
}

bool Set::operator==(const Set& other) const {
    if ((elements_.size() != other.elements_.size()) || (set_elements_.size() != other.set_elements_.size()))
        return false;

    for (unsigned int i = 0; i < elements_.size(); i++) {
        if (!other[elements_[i]])
            return false;
    }

    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (!other[set_elements_[i]])
            return false;
    }
    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
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

bool Set::Add(const Set& subset) {
    if ((*this)[subset])
        return false;
    set_elements_.push_back(subset);
    return true;
}

bool Set::Delete(const Set& subset) {
    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        if (set_elements_[i] == subset) {
            set_elements_.erase(set_elements_.begin() + i);
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Set& the_set) {
    os << "{ ";
    bool first = true;

    for (unsigned int i = 0; i < the_set.elements_.size(); i++) {
        if (!first) 
            os << ", ";
        os << the_set.elements_[i];
        first = false;
    }

    for (unsigned int i = 0; i < the_set.set_elements_.size(); i++) {
        if (!first) 
            os << ", ";
        os << the_set.set_elements_[i];
        first = false;
    }

    os << " }";
    return os;
}

std::istream& operator>>(std::istream& is, Set& the_set) {
    std::string input;
    std::getline(is, input);
    the_set.FormSetFromString(input, 1);
    return is;
}

Set Set::Boolean() const {
    Set result;
    Set empty_set;

    result.Add(empty_set);

    for (unsigned int i = 0; i < elements_.size(); i++) {
        unsigned int the_size = result.set_elements_.size(); // Фиксирование числа подмножеств выходного множества, куда будет ложиться элемент

        for (unsigned int j = 0; j < the_size; j++) {
            Set new_subset = result.set_elements_[j];
            new_subset.Add(elements_[i]);
            result.Add(new_subset);
        }
    }

    for (unsigned int i = 0; i < set_elements_.size(); i++) {
        unsigned int the_size = result.set_elements_.size();

        for (unsigned int j = 0; j < the_size; j++) {
            Set new_subset = result.set_elements_[j];
            new_subset.Add(set_elements_[i]);
            result.Add(new_subset);
        }
    }

    return result;
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
