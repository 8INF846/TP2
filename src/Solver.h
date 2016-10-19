#ifndef SOLVER_H
#define SOLVER_H

#include "Sudoku.h"

class Solver {
public:
    Solver(Sudoku& sudoku);

    void updateSudokuConstraints();
    void solve();

private:
    std::vector<int> getLineConstraints(unsigned int row);
    std::vector<int> getColumnConstraints(unsigned int column);
    std::vector<int> getBoxConstraints(unsigned int row, unsigned int column);
    Sudoku& m_sudoku;
};

#endif //SOLVER_H
