#include "Cell.h"

#include <algorithm>
#include <string>

Cell::Cell(int value, bool prefilled) : m_val(value), m_preFilled(prefilled) {
    for(auto i = 1; i <= 9; ++i) {
        if(value == UNKNOWN) {
            m_possibleValues.push_back(i);
        } else if (value == i) {
            m_possibleValues.push_back(i);
        }
    }
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
    m_possibleValues.push_back(value);
}

void Cell::delPossiblesValues(int value) {
    m_possibleValues.erase(
      std::remove(m_possibleValues.begin(), m_possibleValues.end(), value),
      m_possibleValues.end());
}
