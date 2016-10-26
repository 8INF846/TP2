#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <array>

#include "Cell.h"

class Sudoku {
public:
    Sudoku();
    Sudoku(std::string sudoku_file);

    /**
     * Print a sudoku grid
     */
    friend std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku);

    unsigned int size();
    Cell& getCell(unsigned int row, unsigned int col);
    void setCellValue(unsigned int row, unsigned int col, int newValue);

private:
    std::array<std::array<Cell, 9>, 9> m_grid;
};

#endif //SUDOKU_H
