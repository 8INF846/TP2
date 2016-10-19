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
  void addPossibleValues(int value);
  void delPossiblesValues(int value);

private:
  int m_val;
  bool m_preFilled;
  std::vector<int> m_possibleValues;
};

#endif
