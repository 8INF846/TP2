#include "Sudoku.h"

#include <fstream>
#include <math.h>
//TODO throw exception

Sudoku::Sudoku(std::string sudoku_file) {

    std::ifstream file(sudoku_file, std::ios::app);
    if(!file.is_open()) {
        throw std::string("Can't open file:" + sudoku_file);
    }
    std::string line;
    int width_grid = -1;
    std::string delimiter = ",";
    while(std::getline(file, line)) {
        m_grid.emplace_back();
        size_t pos = 0;
        int width = 0;
        std::string cell_value_str;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            cell_value_str = line.substr(0, pos);
            if(cell_value_str == "") {
                m_grid.back().push_back(Cell());
            } else {
                int cell_value = std::stoi(cell_value_str);
                m_grid.back().push_back(Cell(cell_value, (cell_value != UNKNOWN)));
            }
            ++width;
            line.erase(0, pos + delimiter.length());
        }
        if(width_grid == -1) {
            width_grid = width;
            if(width % (int) std::sqrt(width) != 0) throw std::string("Invalid size for sudoku");
        }
        else if(width_grid != width) throw std::string("Invalid size for sudoku");
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
