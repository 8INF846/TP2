#include <iostream>
#include <string>
#include <exception>

#include "Solver.h"
#include "Console.h"
#include "Displayer.h"

void help() {
    std::cout << "Utilisation : sudokusolver [sudoku_file]" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        help();
        return EXIT_FAILURE;
    }

    try {
        // Initialize the sudoku
        std::string fileName(argv[1]);
        Sudoku sudoku(fileName);

        // Initialise and launch graphic interface
        Displayer displayer(sudoku);
        auto displayerThread = displayer.start();

        // Solve sudoku
        std::ostream& out = Console::out(LEVEL::INFO);
        out << sudoku;
        Solver solver(sudoku);
        solver.solve();
        out << std::endl << "Solution:" << std::endl << sudoku;

        // Wait for graphic interface to be closed before exiting
        displayerThread.join();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
