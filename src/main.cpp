#include <iostream>
#include <string>

#include "Solver.h"

void help() {
    std::cout << "Utilisation : sudokusolver [sudoku_file]" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        help();
        return EXIT_FAILURE;
    }

    try {
        Sudoku sudoku = Sudoku(std::string(argv[1]));
        std::cout << sudoku;
        Solver solver = Solver(sudoku);
        unsigned int it = 0;
        while(!solver.solve()) {
            std::cout << "Iteration " << it << ":" << std::endl;
            it++;
            std::cout << sudoku;
        }
    } catch (const std::string& e) {
        std::cerr << e << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
