#include <iostream>
#include <string>
#include <exception>

#include "Solver.h"
#include "Console.h"

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
        std::ostream& out = Console::out(LEVEL::INFO);
        out << sudoku;
        Solver solver = Solver(sudoku);
        solver.solve();
        out << std::endl << "Solution:" << std::endl << sudoku;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
