#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <vector>

#include "Cell.h"

class Sudoku {
public:
    Sudoku(std::string sudoku_file);

    /**
    * Print a map
    */
    friend std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku);

private:
    std::vector<std::vector<Cell>> m_grid;
};

#endif //SUDOKU_H
