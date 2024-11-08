#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Gmenu.cpp" // Inclusion du fichier Gmenu.cpp

// Déclaration de la classe Identification
class Identification {
private:
    sf::RenderWindow window; // Fenêtre SFML
    sf::Font font; // Police de caractères
    sf::RectangleShape nameField; // Champ de texte pour le nom
    sf::Text placeholderText; // Texte de remplacement dans le champ de texte
    sf::Text nameText; // Texte du nom saisi par l'utilisateur
    sf::RectangleShape nextButton; // Bouton "Suivant"
    sf::Text nextText; // Texte du bouton "Suivant"
    sf::Text titleText; // Texte du titre de la fenêtre

private:
    // Fonction pour initialiser les éléments graphiques
    void initElements() {
        font.loadFromFile("sansation.ttf"); // Chargement de la police

        // Titre de la fenêtre
        titleText.setString("Identification");
        titleText.setFont(font);
        titleText.setCharacterSize(36);
        titleText.setFillColor(sf::Color::White);
        titleText.setStyle(sf::Text::Bold);
        titleText.setPosition(300, 50);

        // Champ de texte pour le nom
        nameField.setSize(sf::Vector2f(400, 50));
        nameField.setPosition(200, 200);
        nameField.setFillColor(sf::Color::White);
        nameField.setOutlineColor(sf::Color::Black);
        nameField.setOutlineThickness(2);

        // Texte de remplacement dans le champ de texte
        placeholderText.setString("Nom");
        placeholderText.setFont(font);
        placeholderText.setCharacterSize(24);
        placeholderText.setFillColor(sf::Color(128, 128, 128));
        placeholderText.setPosition(220, 210);

        // Texte du nom saisi par l'utilisateur
        nameText.setFont(font);
        nameText.setCharacterSize(24);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(220, 210);

        // Bouton "Suivant"
        nextButton.setSize(sf::Vector2f(200, 50));
        nextButton.setPosition(300, 350);
        nextButton.setFillColor(sf::Color(30, 144, 255)); // Couleur bleue
        nextButton.setOutlineColor(sf::Color::Black);
        nextButton.setOutlineThickness(2);

        // Texte du bouton "Suivant"
        nextText.setString("Suivant");
        nextText.setFont(font);
        nextText.setCharacterSize(24);
        nextText.setFillColor(sf::Color::White);
        nextText.setPosition(350, 360);
    }

public:
    Identification() : window(sf::VideoMode(800, 600), "Identification") {
        initElements(); // Initialisation des éléments graphiques
    }

    // Méthode pour vérifier si la fenêtre est ouverte
    bool running() const {
        return window.isOpen();
    }

    // Méthode pour obtenir le nom saisi par l'utilisateur
    std::string getName() const {
        return nameText.getString().toAnsiString();
    }

    // Méthode pour mettre à jour la fenêtre
    void update() {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvent(event); // Gestion des événements
        }
    }

    // Méthode pour gérer les événements
    void handleEvent(sf::Event& event) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                handleTextEntered(event); // Gestion de la saisie de texte
                break;
            case sf::Event::MouseButtonPressed:
                handleMouseButtonPressed(event); // Gestion du clic de souris
                break;
            default:
                break;
        }
    }

    // Méthode pour gérer la saisie de texte
    void handleTextEntered(sf::Event& event) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8 && !nameText.getString().isEmpty()) {
                std::string text = nameText.getString();
                text.pop_back();
                nameText.setString(text);
            } else if (event.text.unicode != 8) {
                std::string text = nameText.getString();
                text += static_cast<char>(event.text.unicode);
                nameText.setString(text);
            }
        }
    }

    // Méthode pour gérer le clic de souris
    void handleMouseButtonPressed(sf::Event& event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (nextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (!nameText.getString().isEmpty()) {
                    window.close();
                }
            }
        }
    }

    // Méthode pour dessiner les éléments graphiques
    void draw() {
        window.clear(sf::Color::Black); // Efface le contenu précédent

        // Dessine les différents éléments
        window.draw(titleText);
        window.draw(nameField);
        if (nameText.getString().isEmpty())
            window.draw(placeholderText);
        window.draw(nameText);
        window.draw(nextButton);
        window.draw(nextText);

        window.display(); // Affiche le contenu à l'écran
    }
};

// Déclaration de la classe View
class View {
public:
    Identification iden; // Instance de la classe Identification

    // Méthode pour afficher la fenêtre d'identification
    void show() {
        while (iden.running()) {
            iden.update(); // Met à jour la fenêtre
            iden.draw();   // Affiche la fenêtre
        }
        if (!iden.getName().empty()) {
            // Si un nom a été saisi, lance le menu de jeu
            GameMenu gameMenu(iden.getName());
            gameMenu.run();
        }
    }
};
