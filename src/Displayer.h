#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <memory>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Sudoku.h"

class Displayer {
public:
    Displayer(Sudoku& sudoku);

    /**
     * Start displaying sudoku while it is being solved
     */
    std::thread start();

private:
    Sudoku& m_sudoku;
    std::unique_ptr<sf::RenderWindow> m_pWindow;

    void run();
    void drawScene();
    void handleEvents();
    void handleEvent(sf::Event& event);
};

#endif
