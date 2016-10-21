#ifndef CELL_H
#define CELL_H

#include <vector>

#define UNKNOWN 0

class Cell {
public:
  explicit Cell(int value = 0, bool prefilled = false);
  int getValue() const;
  void setValue(int newValue);
  std::vector<int> getPossiblesValues() const;
  void setPossiblesValues(std::vector<int> possibleValues);
  void addPossibleValues(int value);
  void delPossiblesValues(int value);
  void resetDomain(unsigned int n);

  Cell& operator=(const Cell& other);

private:
  int m_val;
  bool m_preFilled;
  std::vector<int> m_possibleValues;
};

#endif
