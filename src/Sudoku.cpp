#include "Sudoku.h"
#include "Except.h"

#include <fstream>
#include <cmath>

Sudoku::Sudoku(std::string sudoku_file) {
    std::ifstream file(sudoku_file, std::ios::app);
    if(!file.is_open()) {
        throw Except("Can't open file:" + sudoku_file);
    }
    //Construct sudoku grid
    std::string line;
    int width_grid = -1;
    std::string delimiter = ",";
    unsigned int r = 0;
    while(std::getline(file, line)) {
        size_t pos = 0;
        int width = 0;
        std::string cell_value_str;
        unsigned int c = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            cell_value_str = line.substr(0, pos);
            if(cell_value_str != "") {
                int cell_value = std::stoi(cell_value_str);
                m_grid[r][c] = Cell(cell_value, (cell_value != UNKNOWN));
            }
            ++width;
            line.erase(0, pos + delimiter.length());
            ++c;
        }
        if(width_grid == -1) {
            width_grid = width;
            if(width % (int) std::sqrt(width) != 0) throw Except("Invalid size for sudoku");
        }
        else if(width_grid != width) throw Except("Invalid size for sudoku");
        ++r;
    }

    for (auto r = 0; r < m_grid.size(); ++r) {
        for (auto c = 0; c < m_grid.size(); ++c) {
            m_grid[r][c].resetDomain(m_grid.size());
        }
    }
}

unsigned int Sudoku::size() {
    return m_grid.size();
}

Cell& Sudoku::getCell(unsigned int row, unsigned int col) {
    return m_grid[row][col];
}

void Sudoku::setCellValue(unsigned int row, unsigned int col, int newValue) {
    getCell(row, col).setValue(newValue);
}

std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku) {

    for (auto &line : sudoku.m_grid)
    {
        for (auto &cell: line) {
            output << cell.getValue() << ",";
        }
        output << std::endl;
    }
}
