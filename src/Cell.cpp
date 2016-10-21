#include "Cell.h"

#include <algorithm>
#include <string>

Cell::Cell(int value, bool prefilled) : m_val(value), m_preFilled(prefilled) {

}

void Cell::resetDomain(unsigned int n) {
    m_possibleValues.clear();
    for(auto i = 1; i <= n; ++i) {
        if(m_val == UNKNOWN) {
            m_possibleValues.push_back(i);
        } else if (m_val == i) {
            m_possibleValues.push_back(i);
        }
    }
}

void Cell::setPossiblesValues(std::vector<int> possibleValues) {
    m_possibleValues = possibleValues;
}

int Cell::getValue() const {
    return m_val;
}

void Cell::setValue(int newValue) {
    m_val = newValue;
}

std::vector<int> Cell::getPossiblesValues() const {
    return m_possibleValues;
}

void Cell::addPossibleValues(int value) {
    if(std::find(m_possibleValues.begin(), m_possibleValues.end(), value) == m_possibleValues.end())
    m_possibleValues.push_back(value);
}

void Cell::delPossiblesValues(int value) {
    m_possibleValues.erase(
    std::remove(m_possibleValues.begin(), m_possibleValues.end(), value),
    m_possibleValues.end());
}

Cell& Cell::operator=(const Cell& other)
{
    if (this != &other) {
        std::vector<int> possible;
        for(auto& v: other.m_possibleValues) {
            possible.push_back(v);
        }
        this->m_possibleValues = possible;
    }
    return *this;
}
