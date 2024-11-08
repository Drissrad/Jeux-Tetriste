#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>

class DefaiteWindow {
private:
    sf::RenderWindow window; 
    sf::Font font; // Police de caractères pour le texte
    sf::Text message; // Texte affiché pour indiquer la défaite
    sf::Texture backgroundTexture; // Texture pour l'image de fond
    sf::Sprite backgroundSprite; // Sprite pour afficher l'image de fond
    sf::Texture sadTexture; // Texture pour l'image triste
    sf::Sprite sadSprite; // Sprite pour afficher l'image triste
    sf::Clock clock; // Horloge pour gérer le temps
    sf::RectangleShape replayButton; // Bouton "Rejouer"
    sf::RectangleShape quitButton; // Bouton "Quitter"
    sf::Text replayText; // Texte pour le bouton "Rejouer"
    sf::Text quitText; // Texte pour le bouton "Quitter"

public:
    DefaiteWindow() {
        // Créer une fenêtre SFML avec une taille de 800x600 pixels et un titre "Défaite !"
        window.create(sf::VideoMode(800, 600), "Defaite !", sf::Style::Close);

        // Charger la texture de l'image de fond à partir du fichier "defaite.jpg"
        if (!backgroundTexture.loadFromFile("defaite.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture defaite.jpg" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture); // Définir la texture sur le sprite
        // Redimensionner le sprite pour remplir la fenêtre en conservant les proportions de l'image
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );

        // Charger la texture de l'image triste à partir du fichier "sadness.jpg"
        if (!sadTexture.loadFromFile("sadness.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture sadness.jpg" << std::endl;
        }
        sadSprite.setTexture(sadTexture); // Définir la texture sur le sprite
        sadSprite.setScale(0.5f, 0.5f); // Redimensionner le sprite à 50% de sa taille d'origine
        sadSprite.setPosition(300.f, 200.f); // Définir la position initiale du sprite triste

        // Charger la police de caractères à partir du fichier "sansation.ttf"
        font.loadFromFile("Arial.ttf");
        message.setFont(font); // Définir la police de caractères pour le texte
        message.setString("Vous avez perdu !"); // Définir le texte à afficher
        message.setCharacterSize(50); // Définir la taille du texte à 50 points
        message.setPosition(200.f, 50.f); // Définir la position du texte
        message.setFillColor(sf::Color::Red); // Définir la couleur du texte en rouge

        // Initialiser le bouton "Rejouer"
        replayButton.setSize(sf::Vector2f(200.f, 50.f));
        replayButton.setPosition(200.f, 400.f);
        replayButton.setFillColor(sf::Color::Green);

        // Initialiser le texte pour le bouton "Rejouer"
        replayText.setFont(font);
        replayText.setString("Rejouer");
        replayText.setCharacterSize(24);
        replayText.setFillColor(sf::Color::White);
        replayText.setPosition(230.f, 410.f);

        // Initialiser le bouton "Quitter"
        quitButton.setSize(sf::Vector2f(200.f, 50.f));
        quitButton.setPosition(400.f, 400.f);
        quitButton.setFillColor(sf::Color::Red);

        // Initialiser le texte pour le bouton "Quitter"
        quitText.setFont(font);
        quitText.setString("Quitter");
        quitText.setCharacterSize(24);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(440.f, 410.f);
    }

    // Méthode pour afficher la fenêtre de défaite
    void afficher() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                // Vérifier si un clic de souris a été effectué
                if (event.type == sf::Event::MouseButtonPressed) {
                    // Vérifier si le clic a eu lieu sur le bouton "Rejouer"
                    if (replayButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Bouton Rejouer cliqué !" << std::endl;
                        window.close();
                        int result = system("./main");
                        if (result == 0) {
                            std::cout << "Compilation réussie." << std::endl;
                        } else {
                            std::cerr << "Erreur lors de la compilation." << std::endl;
                        }
                    }
                    // Vérifier si le clic a eu lieu sur le bouton "Quitter"
                    if (quitButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Bouton Quitter cliqué !" << std::endl;
                        window.close(); // Fermer la fenêtre
                    }
                }
            }

            // Effacer le contenu de la fenêtre
            window.clear();
            // Dessiner l'image de fond en premier plan
            window.draw(backgroundSprite);
            // Dessiner le texte indiquant la défaite
            window.draw(message);
            // Dessiner l'image triste
            window.draw(sadSprite);
            // Dessiner le bouton "Rejouer"
            window.draw(replayButton);
            // Dessiner le texte pour le bouton "Rejouer"
            window.draw(replayText);
            // Dessiner le bouton "Quitter"
            window.draw(quitButton);
            // Dessiner le texte pour le bouton "Quitter"
            window.draw(quitText);
            // Afficher tout ce qui a été dessiné
            window.display();
        }
    }
};

class ViewDefaite {
public:
    DefaiteWindow d;
    void show() {
        d.afficher();    
    }
};
