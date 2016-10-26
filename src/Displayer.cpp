#include "Displayer.h"

Displayer::Displayer(Sudoku& sudoku) : m_sudoku(sudoku) {
}

std::thread Displayer::start() {
    return std::thread(&Displayer::run, this);
}

void Displayer::run() {
    // Création de la fenêtre de rendu
    int size = 20 * m_sudoku.size();
    m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(size, size),
            "TP2 IA");
    m_pWindow->setVerticalSyncEnabled(true);
    m_pWindow->setFramerateLimit(60);

    // Boucle d'affichage et de gestion des évènements
    while(m_pWindow->isOpen()) {
        handleEvents();
        drawScene();
    }
}

void Displayer::handleEvents() {
    if(m_pWindow) {
        sf::Event event;
        while(m_pWindow->pollEvent(event)) {
            handleEvent(event);
        }
    }
}

void Displayer::handleEvent(sf::Event& event) {
}

void Displayer::drawScene() {
    m_pWindow->clear(sf::Color(0, 0, 0, 255));

    // Tracé des bordures de la grille
}
