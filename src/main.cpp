#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>

#include "Solver.h"
#include "Console.h"
#include "Displayer.h"

void help() {
    std::cout << "Utilisation : sudokusolver";
    std::cout << " [sudoku_file]" << " [sleeping_time]" << std::endl;
    std::cout << std::endl;
    std::cout << "Paramètres :" << std::endl;
    std::cout << "    sudoku_file     ";
    std::cout << "Relative path to a file containing a sudoku grid" << std::endl;
    std::cout << "    sleeping_time   ";
    std::cout << "Time to wait between two iteration in milliseconds" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        help();
        return EXIT_FAILURE;
    }

    try {
        // Initialize the sudoku
        Sudoku sudoku = Sudoku(std::string(argv[1]));

        // Initialise and launch graphic interface
        Displayer displayer(sudoku);
        auto displayerThread = displayer.start();

        // Solve sudoku
        std::ostream& out = Console::out(LEVEL::INFO);
        out << sudoku;
        Solver solver(sudoku, std::atoi(argv[2]));
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
