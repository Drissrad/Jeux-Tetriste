#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Game.cpp" 
#include "HistoryWindow.cpp" 


class GameMenu {
private:
    sf::RenderWindow window; // Fenêtre SFML pour afficher le menu
    sf::Font font; // Police de caractères pour le texte
    sf::Text titleText; // Texte du titre du menu
    sf::Text playText; // Texte du bouton "Jouer"
    sf::Text historyText; // Texte du bouton "Historique"
    sf::Text QuiteText; // Texte du bouton "Quite"
    
    std::string playerName; // Nom du joueur
    sf::Texture backgroundTexture; // Texture de l'image de fond
    sf::Sprite backgroundSprite; // Sprite pour afficher l'image de fond
    sf::RectangleShape playButton; // Rectangle pour le bouton "Jouer"
    sf::RectangleShape historyButton; // Rectangle pour le bouton "Historique"
    sf::RectangleShape QuiteButton; // Rectangle pour le bouton "QuiteButton"

public:
    // Constructeur prenant le nom du joueur en argument
    GameMenu(const std::string& playerName) : window(sf::VideoMode(800, 600), "Menu du jeu"), playerName(playerName) {
        // Chargement de la police de caractères
        if (!font.loadFromFile("Arial.ttf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
            return;
        }

        // Chargement de l'image de fond
        if (!backgroundTexture.loadFromFile("back.jpg")) {
            std::cerr << "Erreur lors du chargement de l'image de fond" << std::endl;
            return;
        }

        // Ajuster la mise à l'échelle de l'image de fond en fonction de la taille de la fenêtre
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );

        // Initialisation du texte du titre du menu
        titleText.setString("Menu du jeu");
        titleText.setFont(font);
        titleText.setCharacterSize(50);
        titleText.setFillColor(sf::Color::White);
        titleText.setStyle(sf::Text::Bold);
        titleText.setPosition(140, 50);

        // Initialisation du texte du bouton "Jouer"
        playText.setString("Jouer");
        playText.setFont(font);
        playText.setCharacterSize(36);
        playText.setFillColor(sf::Color::Black); // Couleur du texte en noir
        playText.setPosition(50, 200);

        // Initialisation du texte du bouton "Historique"
        historyText.setString("Historique");
        historyText.setFont(font);
        historyText.setCharacterSize(36);
        historyText.setFillColor(sf::Color::Black); // Couleur du texte en noir
        historyText.setPosition(50, 300);

        
        // Initialisation du texte du bouton "Quite"
        QuiteText.setString("Quite");
        QuiteText.setFont(font);
        QuiteText.setCharacterSize(36);
        QuiteText.setFillColor(sf::Color::Black); // Couleur du texte en noir
        QuiteText.setPosition(50, 400);

        // Définir la taille et la position des rectangles pour les boutons
        //boutton jouer
        playButton.setSize(sf::Vector2f(200, 50));
        playButton.setPosition(20, 200);
        playButton.setFillColor(sf::Color::White); // Couleur du bouton en blanc

        //boutton historique
        historyButton.setSize(sf::Vector2f(200, 50));
        historyButton.setPosition(20, 300);
        historyButton.setFillColor(sf::Color::White); // Couleur du bouton en blanc

        ///POUR quite
        QuiteButton.setSize(sf::Vector2f(200, 50));
        QuiteButton.setPosition(20, 400);
        QuiteButton.setFillColor(sf::Color::White); // Couleur du bouton en blanc
    }

    // Méthode pour exécuter le menu
    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    handleClick(event); // Gérer les clics de souris sur les boutons
                }
            }
            // Effacer le contenu de la fenêtre
            window.clear();
            // Dessiner l'image de fond, le titre, les boutons et le texte du joueur
            window.draw(backgroundSprite);
            window.draw(titleText);
            window.draw(playButton);
            window.draw(historyButton);
            window.draw(QuiteButton);
            window.draw(playText);
            window.draw(historyText);
            window.draw(QuiteText);
            sf::Text playerNameText("Bienvenue, " + playerName + "!", font, 24);
            playerNameText.setFillColor(sf::Color::White);
            playerNameText.setPosition(20, 20);
            window.draw(playerNameText);
            // Afficher le contenu dessiné
            window.display();
        }
    }

private:
    // Méthode pour gérer les clics de souris sur les boutons
    void handleClick(sf::Event& event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Si le bouton "Jouer" est cliqué, fermer la fenêtre du menu et afficher le jeu
                window.close();
                ViewGame jouer(playerName);
                jouer.show(); // Afficher le jeu
                std::cout << "Bouton Jouer cliqué!" << std::endl;
            } else if (historyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Si le bouton "Historique" est cliqué, afficher l'historique
                std::cout << "Bouton Historique cliqué!" << std::endl;
                 Historique historique("users.txt");
                 historique.show();
            }else if (QuiteButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                // Si le bouton "Historique" est cliqué, afficher l'historique
                std::cout << "Bouton Quite cliqué!" << std::endl;
                 window.close();
                 
            }
        }
    }
};
