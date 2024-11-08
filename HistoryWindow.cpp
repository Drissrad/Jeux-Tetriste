#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Historique {
public:
    Historique(const std::string& filename); 
    void show(); 
private:
    void draw(sf::RenderWindow& window); 
    void scrollUp(); 
    void scrollDown(); 
    bool loadFont(const std::string& fontPath);
    
    std::vector<std::vector<std::string>> data; 
    int scrollPosition; 
    sf::Font font; 
    sf::RectangleShape scrollUpButton; 
    sf::RectangleShape scrollDownButton; 
    sf::ConvexShape arrowUp; 
    sf::ConvexShape arrowDown;
    float startX;
    float startY;
    float cellWidth;
    float cellHeight;
    float margin;
    sf::Color cellColor;
    sf::Color textColor;
    sf::Color borderColor;
};

Historique::Historique(const std::string& filename) : scrollPosition(0),
    startX(10), startY(50), cellWidth(100), cellHeight(30), margin(5),
    cellColor(240, 230, 220), textColor(50, 50, 50), borderColor(150, 150, 150) {
    if (!loadFont("sansation.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
    }

    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty())
                continue;
            std::vector<std::string> rowData;
            std::stringstream ss(line);
            std::string item;
            while (std::getline(ss, item, ',')) {
                rowData.push_back(item);
            }
            data.push_back(rowData);
        }
        file.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
    }

    scrollUpButton.setSize(sf::Vector2f(20, 20));
    scrollUpButton.setFillColor(sf::Color::Green);
    scrollUpButton.setPosition(390, 5);

    scrollDownButton.setSize(sf::Vector2f(20, 20));
    scrollDownButton.setFillColor(sf::Color::Green);
    scrollDownButton.setPosition(390, 290);

    arrowUp.setPointCount(3);
    arrowUp.setPoint(0, sf::Vector2f(10, 10));
    arrowUp.setPoint(1, sf::Vector2f(20, 0));
    arrowUp.setPoint(2, sf::Vector2f(30, 10));
    arrowUp.setFillColor(sf::Color::White);
    arrowUp.setPosition(380, 10);

    arrowDown.setPointCount(3);
    arrowDown.setPoint(0, sf::Vector2f(10, 0));
    arrowDown.setPoint(1, sf::Vector2f(20, 10));
    arrowDown.setPoint(2, sf::Vector2f(30, 0));
    arrowDown.setFillColor(sf::Color::White);
    arrowDown.setPosition(380, 300);
}

void Historique::show() {
    sf::RenderWindow window(sf::VideoMode(410, 310), "Tableau d'utilisateurs");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (scrollUpButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        scrollUp();
                    } else if (scrollDownButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        scrollDown();
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        draw(window);
        window.draw(scrollUpButton);
        window.draw(scrollDownButton);
        window.draw(arrowUp);
        window.draw(arrowDown);
        window.display();
    }
}

void Historique::draw(sf::RenderWindow& window) {
    // Dessiner les titres du tableau
    std::vector<std::string> titles = { "ID", "Name", "Time", "Score", "Date" };
    for (size_t i = 0; i < titles.size(); ++i) {
        sf::Text titleText(titles[i], font, 20);
        titleText.setPosition(startX + i * (cellWidth + margin) + margin, startY - 40); 
        titleText.setFillColor(textColor);
        window.draw(titleText);
    }

    // Dessiner les données du tableau à partir de la position de défilement
    for (size_t i = scrollPosition; i < data.size() && i < scrollPosition + 8; ++i) { 
        const auto& row = data[i];
        for (size_t j = 0; j < row.size(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setPosition(startX + j * (cellWidth + margin), startY + (i - scrollPosition) * (cellHeight + margin));
            cell.setFillColor(cellColor);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(borderColor);
            window.draw(cell);

            sf::Text text(row[j], font, 15);
            text.setPosition(startX + j * (cellWidth + margin) + margin, startY + (i - scrollPosition) * (cellHeight + margin) + margin);
            text.setFillColor(textColor);
            window.draw(text);
        }
    }
}

void Historique::scrollUp() {
    if (scrollPosition > 0) {
        scrollPosition--;
    }
}

void Historique::scrollDown() {
    if (scrollPosition < static_cast<int>(data.size()) - 8) {
        scrollPosition++;
    }
}

bool Historique::loadFont(const std::string& fontPath) {
    return font.loadFromFile(fontPath);
}


