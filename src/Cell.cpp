#include "Cell.h"

Cell::Cell(int value, bool prefilled) : m_val(value), m_preFilled(prefilled) {

}

int Cell::getValue() const {
    return m_val;
}
