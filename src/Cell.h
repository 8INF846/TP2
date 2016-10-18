#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
public:
  Cell(int value = 0, bool prefilled = false);
  int getValue() const;

private:
  int m_val;
  bool m_preFilled;
  std::vector<int> m_constraints;
};

#endif
