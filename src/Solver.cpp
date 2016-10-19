#include "Solver.h"
#include <math.h>

#include <iostream>

Solver::Solver(Sudoku& sudoku) : m_sudoku(sudoku) {

}

void Solver::updateSudokuConstraints() {
    for (auto r = 0; r < m_sudoku.size(); ++r)
    {
        for (auto c = 0; c < m_sudoku.size(); ++c) {
            for(auto &constraint: getLineConstraints(r)) {
                m_sudoku.getCell(r, c).delPossiblesValues(constraint);
            }

            for(auto &constraint: getColumnConstraints(c)) {
                m_sudoku.getCell(r, c).delPossiblesValues(constraint);
            }

            for(auto &constraint: getBoxConstraints(r, c)) {
                m_sudoku.getCell(r, c).delPossiblesValues(constraint);
            }
        }
    }
}

void Solver::solve() {
    updateSudokuConstraints();
    for (auto r = 0; r < m_sudoku.size(); ++r)
    {
        for (auto c = 0; c < m_sudoku.size(); ++c) {
            auto cell = m_sudoku.getCell(r, c);
            auto possibleValues = cell.getPossiblesValues();
            if(possibleValues.size() == 1 && cell.getValue() == UNKNOWN) {
                std::cout << "(" << r << ";" << c << "):" << possibleValues[0] << std::endl;
                m_sudoku.setCellValue(r, c, possibleValues[0]);
            }
        }
    }
}

std::vector<int> Solver::getLineConstraints(unsigned int row) {
    if(row > m_sudoku.size()) throw std::string("Can't access to row " + row);
    std::vector<int> result;
    for (auto c = 0; c < m_sudoku.size(); ++c) {
        auto cell_value = m_sudoku.getCell(row, c).getValue();
        if (cell_value != UNKNOWN) result.push_back(cell_value);
    }
    return result;
}

std::vector<int> Solver::getColumnConstraints(unsigned int column) {
    if(column > m_sudoku.size()) throw std::string("Can't access to column " + column);
    std::vector<int> result;
    for (auto r = 0; r < m_sudoku.size(); ++r) {
        auto cell_value = m_sudoku.getCell(r, column).getValue();
        if (cell_value != UNKNOWN) result.push_back(cell_value);
    }
    return result;
}

std::vector<int> Solver::getBoxConstraints(unsigned int row, unsigned int col) {
    if(row > m_sudoku.size()) throw std::string("Can't access to row " + row);
    if(col > m_sudoku.size()) throw std::string("Can't access to column " + col);
    std::vector<int> result;

    unsigned int size_box = (unsigned int) std::sqrt(m_sudoku.size());
    unsigned int base_r = row - row%size_box;
    unsigned int base_c = col - col%size_box;

    for (auto r = base_r; r < base_r + size_box; ++r) {
        for (auto c = base_c; c < base_c + size_box; ++c) {
            auto cell_value = m_sudoku.getCell(r, c).getValue();
            if (cell_value != UNKNOWN) result.push_back(cell_value);
        }
    }

    return result;
}
