#ifndef CELL_H
#define CELL_H

#include <vector>

//If the value of the cell is unknown
#define UNKNOWN 0

/**
 * Represent a cell of the sudoku grid
 */
class Cell {
public:
  explicit Cell(int value = 0, bool prefilled = false);

  int getValue() const;
  void setValue(int newValue);
  std::vector<int> getPossiblesValues() const;
  void setPossiblesValues(std::vector<int> possibleValues);

  /**
   * Remove value in domain
   * @param value
   */
  void delPossiblesValues(int value);

  /**
   * Change domain to {0,1...,n} or i if m_val is set
   * @param n
   */
  void resetDomain(unsigned int n);

private:
  //Current value
  int m_val;
  //If m_val is blocked
  bool m_preFilled;
  //Domain
  std::vector<int> m_possibleValues;
};

#endif
