#include "Displayer.h"
#include <sstream>
#include <cmath>

Displayer::Displayer(Sudoku& sudoku) : m_sudoku(sudoku), m_tileSize(50) {
}

std::thread Displayer::start() {
    return std::thread(&Displayer::run, this);
}

void Displayer::run() {
    // Création de la fenêtre de rendu
    int size = m_tileSize * m_sudoku.size();
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
    switch(event.type) {
    case sf::Event::Closed:
        m_pWindow->close();
        break;
    default:
        break;
    }
}

void Displayer::drawScene() {
    m_pWindow->clear(sf::Color(0, 0, 0));

    // Tracé de la grille
    int size = m_tileSize * m_sudoku.size();
    unsigned int sqrtSize = ((unsigned int) std::sqrt(m_sudoku.size()));
    int cell_size = m_sudoku.size()/sqrtSize;
    sf::RectangleShape row(sf::Vector2f(2, size));
    sf::RectangleShape col(sf::Vector2f(size, 2));
    for(int i = 1; i < m_sudoku.size(); ++i) {
        if(i % cell_size == 0) {
            row.setFillColor(sf::Color(200, 50, 50));
            col.setFillColor(sf::Color(200, 50, 50));
        }
        else {
            row.setFillColor(sf::Color(150, 150, 150));
            col.setFillColor(sf::Color(150, 150, 150));
        }
        row.move(sf::Vector2f(m_tileSize, 0));
        m_pWindow->draw(row);
        col.move(sf::Vector2f(0, m_tileSize));
        m_pWindow->draw(col);
    }

    // Tracé des numéros
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text("", font);
    int fontSize = std::round(m_tileSize * 0.8);
    text.setCharacterSize(fontSize);
    text.setColor(sf::Color(150, 150, 150));
    for(int r = 0; r < m_sudoku.size(); ++r) {
        for(int c = 0; c < m_sudoku.size(); ++c) {
            auto n = m_sudoku.getCell(r, c).getValue();
            if(n != UNKNOWN) {
                std::ostringstream oss("");
                oss << n;
                text.setString(oss.str());
                auto bounds = text.getGlobalBounds();
                // WTF x1.5 ? but it works !
                int rPad = std::round((m_tileSize - bounds.height * 1.5) / 2);
                int cPad = std::round((m_tileSize - bounds.width) / 2);
                text.setPosition(c * m_tileSize + cPad, r * m_tileSize + rPad);
                m_pWindow->draw(text);
            }
        }
    }

    m_pWindow->display();
}

void Displayer::stop() {
    m_pWindow->close();
}
