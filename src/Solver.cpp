#include "Solver.h"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

#include "Console.h"
#include "Except.h"

Solver::Solver(Sudoku& sudoku, int sleepingTime) : m_sudoku(sudoku),
        m_sleepingTime(sleepingTime) {
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

bool Solver::solve() {
    //AC3
    updateSudokuConstraints();

    //Choose MRV Value
    bool isFinish = true;
    unsigned int mrvR, mrvC;
    unsigned int mrvSize = m_sudoku.size();
    for (auto r = 0; r < m_sudoku.size(); ++r)
    {
        for (auto c = 0; c < m_sudoku.size(); ++c) {
            auto cell = m_sudoku.getCell(r, c);
            auto possibleValues = cell.getPossiblesValues();
            //Forward checking
            if(possibleValues.size() == 0 && cell.getValue() == UNKNOWN) {
                throw Except("can't solve this sudoku");
            }
            if(cell.getValue() == UNKNOWN && possibleValues.size() < mrvSize) {
                mrvSize = possibleValues.size();
                mrvR = r; mrvC = c;
            }
            if(isFinish && cell.getValue() == UNKNOWN) {
                isFinish = false;
            }
        }
    }
    if(isFinish) return isFinish;

    //Backtracking search
    auto cell = m_sudoku.getCell(mrvR, mrvC);
    auto possibleValues = cell.getPossiblesValues();
    for(auto& value : possibleValues) {
        Sudoku m_sudokuCopy = m_sudoku;
        std::ostream& out = Console::out(LEVEL::DEBUG);
        try {
            m_sudoku.setCellValue(mrvR, mrvC, value);
            removeConstraints(mrvR, mrvC, value);

            out << "Change: " << mrvR << "," << mrvC << " to " << value << std::endl;
            out << m_sudoku;

            // Sleep for graphic interface
            std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepingTime));

            isFinish = solve();
            if(isFinish) return true;
        } catch (const std::exception& e) {
            out << "Can't resolve sudoku, return to" << std::endl << m_sudokuCopy;
            for (auto r = 0; r < m_sudoku.size(); ++r) {
                for (auto c = 0; c < m_sudoku.size(); ++c) {
                    m_sudoku.setCellValue(r, c, m_sudokuCopy.getCell(r, c).getValue());
                    m_sudoku.getCell(r, c).setPossiblesValues(m_sudokuCopy.getCell(r, c).getPossiblesValues());

                }
            }
        }
    }
    throw Except("Can't find the solution");
    return false;
}

std::vector<int> Solver::getLineConstraints(unsigned int row) {
    if(row > m_sudoku.size()) {
        std::ostringstream oss("Can't access to row ");
        oss << row;
        throw Except(oss.str());
    }

    std::vector<int> result;
    for (auto c = 0; c < m_sudoku.size(); ++c) {
        auto cell_value = m_sudoku.getCell(row, c).getValue();
        if (cell_value != UNKNOWN) {
            if(std::find(result.begin(), result.end(), cell_value) != result.end())
            throw Except("2 values are identical in a row!");
            result.push_back(cell_value);
        }
    }
    return result;
}

std::vector<int> Solver::getColumnConstraints(unsigned int column) {
    if(column > m_sudoku.size()) {
        std::ostringstream oss("Can't access to column ");
        oss << column;
        throw Except(oss.str());
    }

    std::vector<int> result;
    for (auto r = 0; r < m_sudoku.size(); ++r) {
        auto cell_value = m_sudoku.getCell(r, column).getValue();
        if (cell_value != UNKNOWN) {
            if(std::find(result.begin(), result.end(), cell_value) != result.end())
            throw Except("2 values are identical in a row!");
            result.push_back(cell_value);
        }
    }
    return result;
}

std::vector<int> Solver::getBoxConstraints(unsigned int row, unsigned int col) {
    if(row > m_sudoku.size()) {
        std::ostringstream oss("Can't access to row ");
        oss << row;
        throw Except(oss.str());
    }
    if(col > m_sudoku.size()) {
        std::ostringstream oss("Can't access to column ");
        oss << col;
        throw Except(oss.str());
    }

    std::vector<int> result;

    unsigned int c_size_box = (unsigned int) m_sudoku.size()/((unsigned int) std::sqrt(m_sudoku.size()));
    unsigned int r_size_box = (unsigned int) m_sudoku.size()/c_size_box;
    unsigned int base_r = row - row%r_size_box;
    unsigned int base_c = col - col%c_size_box;

    for (auto r = base_r; r < base_r + r_size_box; ++r) {
        for (auto c = base_c; c < base_c + c_size_box; ++c) {
            auto cell_value = m_sudoku.getCell(r, c).getValue();
            if (cell_value != UNKNOWN) {
                if(std::find(result.begin(), result.end(), cell_value) != result.end())
                throw Except("2 values are identical in a box!");
                result.push_back(cell_value);
            }
        }
    }

    return result;
}

void Solver::removeConstraints(const unsigned int row, const unsigned int col, const unsigned int value) {
    removeLineConstraints(row, value);
    removeColumnConstraints(col, value);
    removeBoxConstraints(row, col, value);
}

void Solver::removeLineConstraints(const unsigned int row, const unsigned int value) {
    for (auto c = 0; c < m_sudoku.size(); ++c) {
        m_sudoku.getCell(row, c).delPossiblesValues(value);
    }
}

void Solver::removeColumnConstraints(const unsigned int col, const unsigned int value) {
    for (auto r = 0; r < m_sudoku.size(); ++r) {
        m_sudoku.getCell(r, col).delPossiblesValues(value);
    }
}

void Solver::removeBoxConstraints(const unsigned int row, const unsigned int col, const unsigned int value) {
    unsigned int c_size_box = (unsigned int) m_sudoku.size()/((unsigned int) std::sqrt(m_sudoku.size()));
    unsigned int r_size_box = (unsigned int) m_sudoku.size()/c_size_box;
    unsigned int base_r = row - row%r_size_box;
    unsigned int base_c = col - col%c_size_box;

    for (auto r = base_r; r < base_r + r_size_box; ++r) {
        for (auto c = base_c; c < base_c + c_size_box; ++c) {
            m_sudoku.getCell(r, c).delPossiblesValues(value);
        }
    }
}
