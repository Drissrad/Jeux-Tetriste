#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class VictoryWindow {
private:
    sf::RenderWindow* window;
    sf::Font* font;
    sf::Text* message;
    sf::Texture* backgroundTexture;
    sf::Sprite* backgroundSprite;
    sf::Sprite* happySprite;
    sf::RectangleShape* replayButton;
    sf::RectangleShape* quitButton;
    sf::Text* replayText;
    sf::Text* quitText;

public:
    VictoryWindow() {
        // Allocation dynamique des objets
        window = new sf::RenderWindow(sf::VideoMode(800, 600), "Victoire !", sf::Style::Close);
        font = new sf::Font();
        message = new sf::Text();
        backgroundTexture = new sf::Texture();
        backgroundSprite = new sf::Sprite();
        happySprite = new sf::Sprite();
        replayButton = new sf::RectangleShape(sf::Vector2f(100, 50));
        quitButton = new sf::RectangleShape(sf::Vector2f(100, 50));
        replayText = new sf::Text();
        quitText = new sf::Text();

        // Charger la texture de l'image de fond
        if (!backgroundTexture->loadFromFile("victory_background.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture victory_background.jpg" << std::endl;
        }
        backgroundSprite->setTexture(*backgroundTexture);
        backgroundSprite->setScale(
            static_cast<float>(window->getSize().x) / backgroundTexture->getSize().x,
            static_cast<float>(window->getSize().y) / backgroundTexture->getSize().y
        );

        // Charger la texture de l'image de victoire
        if (!font->loadFromFile("Arial.ttf")) {
            std::cerr << "Erreur lors du chargement de la police Arial.ttf" << std::endl;
        }
        message->setFont(*font);
        message->setString("Bravo ! Vous avez gagné !");
        message->setCharacterSize(50);
        message->setPosition(100.f, 50.f);
        message->setFillColor(sf::Color::Green);

        // Configuration du bouton "Rejouer"
        replayButton->setFillColor(sf::Color::White);
        replayButton->setPosition(100, 450);

        replayText->setFont(*font);
        replayText->setString("Rejouer");
        replayText->setCharacterSize(20);
        replayText->setPosition(115, 465);
        replayText->setFillColor(sf::Color::Black);

        // Configuration du bouton "Quitter"
        quitButton->setFillColor(sf::Color::White);
        quitButton->setPosition(250, 450);

        quitText->setFont(*font);
        quitText->setString("Quitter");
        quitText->setCharacterSize(20);
        quitText->setPosition(265, 465);
        quitText->setFillColor(sf::Color::Black);
    }

    ~VictoryWindow() {
        // Libération de la mémoire allouée
        delete window;
        delete font;
        delete message;
        delete backgroundTexture;
        delete backgroundSprite;
        delete happySprite;
        delete replayButton;
        delete quitButton;
        delete replayText;
        delete quitText;
    }

    void afficher() {
        while (window->isOpen()) {
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                // Vérifier si le bouton "Rejouer" est cliqué
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                        if (replayButton->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                            std::cout << "Rejouer !" << std::endl;
                                window->close();
                            int result = system("./main");
                            if (result == 0) {
                                std::cout << "Compilation réussie." << std::endl;
                            } else {
                                std::cerr << "Erreur lors de la compilation." << std::endl;
                            }
                        }
                        // Vérifier si le bouton "Quitter" est cliqué
                        else if (quitButton->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                            std::cout << "Quitter !" << std::endl;
                            window->close();
                        }
                    }
                }
            }

            window->clear();
            window->draw(*backgroundSprite);
            window->draw(*message);
            window->draw(*replayButton);
            window->draw(*quitButton);
            window->draw(*replayText);
            window->draw(*quitText);
            window->display();
        }
    }
};


class viewVictory{
    public:
        VictoryWindow v1;
    void show(){
        v1.afficher();    
    }
};


