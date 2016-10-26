#ifndef SOLVER_H
#define SOLVER_H

#include "Sudoku.h"

class Solver {
public:
    Solver(Sudoku& sudoku, int sleepingTime);

    /**
     * Constraint propagation + AC3
     */
    void updateSudokuConstraints();

    /**
     * Solve the sudoku grid
     * return if the sudoku is solved
     * throw exception if the sudoku is not solvable
     */
    bool solve();

private:
    std::vector<int> getLineConstraints(unsigned int row);
    std::vector<int> getColumnConstraints(unsigned int column);
    std::vector<int> getBoxConstraints(unsigned int row, unsigned int column);

    void removeConstraints(const unsigned int row, const unsigned int col, const unsigned int value);
    void removeLineConstraints(const unsigned int row, const unsigned int value);
    void removeColumnConstraints(const unsigned int col, const unsigned int value);
    void removeBoxConstraints(const unsigned int row, const unsigned int col, const unsigned int value);

    Sudoku& m_sudoku;
    int m_sleepingTime;
};

#endif //SOLVER_H
