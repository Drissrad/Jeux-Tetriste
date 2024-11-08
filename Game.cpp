#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "VictoireWindow .cpp" 
#include "DefaiteWindow.cpp"
#include "class.cpp"
#include "User.cpp"



using namespace std;


User user;
int ControllerForm::count= 0;
int ControllerForm::indexRemove = -1;

class Game {
private:
    int score = 0, timer = 0;
    int initialTime = 60;
    int courentTime = initialTime;
    sf::Clock clock ;
    sf::RenderWindow* window; // Pointeur vers la fenêtre principale
    sf::Event ev; // Objet pour gérer les événements SFML
    sf::VideoMode videoMode; // Mode vidéo de la fenêtre
    sf::Font font; // Police de caractères utilisée

    // Formes pour le titre
    sf::RectangleShape carre;
    sf::CircleShape Circle;
    sf::Text Stage; // Texte "Stage 1" "stage 2" "stage 3" "stage 4"
    sf::Text scoreText; // Texte "Score : "
    sf::Text timeText; // Texte "Time : "
    sf::Text seconde; // Texte "Time : "
    sf::Text ProchaineText; // Texte "Prochaine :"

    sf::Texture backgroundTexture; // Texture pour l'image de fond
    sf::Sprite backgroundSprite; // Sprite pour afficher l'image de fond

    std::vector<sf::Color> colors = { // Couleurs utilisées pour les formes
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Red,
        sf::Color::Green
    };
    std::vector<sf::Shape*> formes; // Vecteur pour stocker les formes affichées
    sf::Shape* nextShape; // Forme suivante à afficher

    
    // Initialisation des formes du titre
    void initShapes() {
        float size = 50.f;

        carre.setPosition(200.f, 60.f);
        carre.setSize(sf::Vector2f(size, size));
        carre.setFillColor(sf::Color::Cyan);
        carre.setOutlineColor(sf::Color::Green);
        carre.setOutlineThickness(1.f);

        Circle.setPosition(550.f, 60.f);
        Circle.setRadius(size / 2.f);
        Circle.setFillColor(sf::Color::Red);
    }

    // Initialisation des textes
    void initText() {
        font.loadFromFile("Arial.ttf");//font.loadFromFile("sansation.ttf");
        

        //pour le tite quel stage
        Stage.setFont(font);
        Stage.setCharacterSize(50);
        Stage.setString("Stage 1");
        Stage.setFillColor(sf::Color::White);
        Stage.setStyle(sf::Text::Bold);
        Stage.setPosition(340.f, 60.f);

        //pour le scrore
        scoreText.setFont(font);
        scoreText.setCharacterSize(40);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(100.f, 490.f);
        scoreText.setString("Score : " +std::to_string(score));

        //pour le time
        timeText.setFont(font);
        timeText.setCharacterSize(40);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(500.f, 490.f);
        timeText.setString("Time : " + std::to_string(getTime(clock))+"s");
        

        //text Prochaine
        ProchaineText.setFont(font);
        ProchaineText.setCharacterSize(35);
        ProchaineText.setFillColor(sf::Color::White);
        ProchaineText.setPosition(55.f, 150.f);
        ProchaineText.setString("Prochaine :");
    }

    // Initialisation des flèches
    void initArrows() {
        sf::ConvexShape arrowBefore(3);
        arrowBefore.setPoint(0, sf::Vector2f(0.f, 0.f));
        arrowBefore.setPoint(1, sf::Vector2f(40.f, -20.f));
        arrowBefore.setPoint(2, sf::Vector2f(40.f, 20.f));
        arrowBefore.setFillColor(sf::Color::White);
        arrowBefore.setPosition(50.f - 40.f, 325.f);

        sf::ConvexShape arrowAfter(3);
        arrowAfter.setPoint(0, sf::Vector2f(0.f, -20.f));
        arrowAfter.setPoint(1, sf::Vector2f(40.f, 0.f));
        arrowAfter.setPoint(2, sf::Vector2f(0.f, 20.f));
        arrowAfter.setFillColor(sf::Color::White);
        arrowAfter.setPosition(50.f + 12 * 60.f + 50.f, 325.f);

        this->window->draw(arrowBefore);
        this->window->draw(arrowAfter);
    }

    // Initialisation des variables
    void initVariables() {
        window = nullptr;
        nextShape = nullptr;
    }

    // Initialisation de la fenêtre
    void initWindow() {
        videoMode.height = 600;
        videoMode.width = 880;
        window = new sf::RenderWindow(videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
        window->setFramerateLimit(144);
    }

    public:
    //----------Console variables-------//
        ControllerForm formController;
        Form *actualForm;
        char key;
        bool winner, isdelte = false;
        

    //-------------------------


    Game() {
        initVariables();
        initWindow();
        initShapes();
        initText();
        initArrows();
        drawNextShape(); // Affiche la première forme

        // Charger la texture de l'image de fond
        if (!backgroundTexture.loadFromFile("backgroundGame.jpg")) {
            std::cerr << "Erreur lors du chargement de la texture backgroundGame.jpg" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture); // Définir la texture sur le sprite
        // Redimensionner le sprite pour remplir la fenêtre en conservant les proportions de l'image
        backgroundSprite.setScale(
            static_cast<float>(videoMode.width) / backgroundTexture.getSize().x,
            static_cast<float>(videoMode.height) / backgroundTexture.getSize().y
        );
    }

    ~Game() {
        delete window;
        for (auto& forme : formes) {
            delete forme;
        }
        delete nextShape;
    }

   
    //get score
    int getScore(){
        return score;
    }
    //calculer time
    int getTime(sf::Clock& clock) {
        sf::Time elapsedTime = clock.getElapsedTime();
        // Convert it to seconds using the asSeconds() method and round it to an integer
        int seconds = static_cast<int>(elapsedTime.asSeconds());
        if(isdelte){
            this->timer = courentTime-seconds + 3;
        }else{
            this->timer = courentTime-seconds;
        }
        
        formController.time = this->timer;

        return this->timer;
    } 

    //getTime2
    int getTimer(){
       return timer;
    } 

    //SUPPRESSION UN ELEMENT
    bool supprimerPiece(int index) {
        if (index >= 0 && index < formes.size())
        {
            delete formes[index];
            formes.erase(formes.begin() + index);
            return true;
        }
        return false;
    }

    // Met à jour le jeu
    void update() {
        timeText.setString("Time : " +std::to_string(getTimer())+"s");
        scoreText.setString("Score : " +std::to_string(score));

        if(getTime(clock) <= 0){
            ViewDefaite defaite;
            cout << "Execution time: " << getTime(clock) << " seconds" << std::endl;
            window->close();
            defaite.show();
        }
        
        pollEvents();

        

    }

    // Vérifie si le jeu est en cours d'exécution
    const bool running() const {
        return window->isOpen();
    }

    // Affiche les éléments du jeu

    void render() {
        window->clear();
        window->draw(backgroundSprite);// Dessiner l'image de fond en premier plan
        window->draw(Stage);
        window->draw(carre);
        window->draw(Circle);
        window->draw(scoreText);
        
        window->draw(timeText);

        
        
        
        
        window->draw(ProchaineText);
        
        float startX = 73.f;
        float startY = 305.f;
        float spacing = 60.f;

        for (size_t i = 0; i < formes.size(); ++i) {
            sf::Shape* forme = formes[i];
            forme->setPosition(startX + i * spacing, startY);
            window->draw(*forme);
        }

        if (nextShape != nullptr) {
            window->draw(*nextShape);
        }
        
        initArrows();
        window->display();
    }

    // Dessine la forme suivante à afficher  /////<---------------
    void drawNextShape() {
        
        
        if (formes.size() < 12) { // Vérifie si la liste est pleine
            actualForm = formController.Creat();
            nextShape = createNewShape(actualForm->key, actualForm->getColor());
            cout<<endl<<endl <<"=============================================================================="<<endl;
            cout<<"Pour ajouter au débuit click sur la touche droit "<<endl;
            cout<<"Pour ajouter à la fin click sur la touche gouche "<<endl;
            cout<<"Pour quétie click sur Q"<<endl;
            cout<<"=============================================================================================================="<<endl;
            cout <<"---------------------Voilà la form prochaine : ";
                actualForm->show();
                if (nextShape != nullptr) {
                    nextShape->setPosition(70.f, 200.f);
                }
                cout <<"--------------------------------------------------------------------------------";
            cout<<endl;
            
            formController.list.show();
            cout<<endl;
            cout<<"Entrez l'option qui vous voullez"<<endl;   
            //-------------
            
            
            cout<<"Remove"<<endl;
            
            
            
            
            
        }
    }

    // Crée une nouvelle forme //<--------------------------
    sf::Shape* createNewShape(int choix, Color color) {
        //int choix = rand() % 4;
        sf::Shape* nouvelleForme = nullptr;

        

        

        switch (choix) {
            case 0:
                nouvelleForme = new sf::RectangleShape();
                dynamic_cast<sf::RectangleShape*>(nouvelleForme)->setSize(sf::Vector2f(50.f, 50.f));
                break;
            case 1:
                nouvelleForme = new sf::CircleShape();
                dynamic_cast<sf::CircleShape*>(nouvelleForme)->setRadius(25.f);
                break;
            
           case 2:
                nouvelleForme = new sf::ConvexShape(3);
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(0, sf::Vector2f(0.f, 50.f)); // Modification ici
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(1, sf::Vector2f(50.f, 50.f)); // Modification ici
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(2, sf::Vector2f(25.f, 0.f)); // Modification ici
                break;
                
            case 3:
                nouvelleForme = new sf::ConvexShape(4);
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(0, sf::Vector2f(0.f, 25.f));
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(1, sf::Vector2f(25.f, 50.f));
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(2, sf::Vector2f(50.f, 25.f));
                dynamic_cast<sf::ConvexShape*>(nouvelleForme)->setPoint(3, sf::Vector2f(25.f, 0.f));
                break;
        }

        //if (nouvelleForme != nullptr) {
          //  nouvelleForme->setFillColor(colors[rand() % colors.size()]);
        //}


        switch (color) {
            case Color::Bleu:
                nouvelleForme->setFillColor(colors[0]);
                break;
            case Color::Jaun:
                nouvelleForme->setFillColor(colors[1]);
                break;
            case Color::Rouge:
                nouvelleForme->setFillColor(colors[2]);
                break;
            case Color::Vert:
                nouvelleForme->setFillColor(colors[3]);
                break;
        }

        return nouvelleForme;
    }

    // Ajoute une nouvelle forme au début de la liste
    void ajoutDebut() {
        if (formes.size() >= 12) {
            std::cout << "La liste est pleine !" << std::endl;
            return;
        }

        sf::Shape* nouvelleForme = nextShape;
        if (nouvelleForme != nullptr) {
            formes.insert(formes.begin(), nouvelleForme);
            drawNextShape(); // Affiche la prochaine forme
        }
    }

    // Ajoute une nouvelle forme à la fin de la liste
    void ajoutFin() {
        if (formes.size() >= 12) {
            std::cout << "La liste est pleine !" << std::endl;
            return;
        }

        sf::Shape* nouvelleForme = nextShape;
        if (nouvelleForme != nullptr) {
            formes.push_back(nouvelleForme);
            drawNextShape(); // Affiche la prochaine forme
        }
    }
    //initialisation la form de deux forms
    
        // Gère les événements du jeu
    void pollEvents() {
        bool isdelete = false;
        while (window->pollEvent(ev)) {
            switch (ev.type) {
                case sf::Event::Closed:
                    cout<<"exite";
                    window->close();
                    
                    break;
                case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape) {
                        cout<<"exite";
                        cout << "Execution time: " << getTime(clock) << " seconds" << std::endl;
                        window->close();

                        
                        break;
                    } else if (ev.key.code == sf::Keyboard::Left) {
                        formController.prepend(actualForm);
                        ajoutDebut();

                        formController.remove();
                        cout<<ControllerForm::indexRemove<<endl;
                        if(ControllerForm::indexRemove != -1){
                            score +=3;
                            isdelete = supprimerPiece(ControllerForm::indexRemove);
                                if(isdelete){isdelte = true;}else{cout<<"not delete"<<ControllerForm::indexRemove<<endl;}
                                
                                         
                            isdelete = supprimerPiece(ControllerForm::indexRemove);
                                if(isdelete){}else{cout<<"not delete"<<ControllerForm::indexRemove<<endl;}
                                
                                        
                            isdelete = supprimerPiece(ControllerForm::indexRemove);
                                if(isdelete){}else{cout<<"not delete"<<ControllerForm::indexRemove<<endl;}
                                 
                                            
                            ControllerForm::indexRemove = -1;
                        }
                        formController.list.show();
                
                        if(formes.empty() ){
                            viewVictory victory;
                            cout << "Execution time: " << getTime(clock) << " seconds" << std::endl;
                            window->close();
                            victory.show();
                        }else if (formes.size() >= 12) {
                            ViewDefaite defaite;
                            cout << "Execution time: " << getTime(clock) << " seconds" << std::endl;
                            window->close();
                            defaite.show();
                        }

                        
                        
                    } else if (ev.key.code == sf::Keyboard::Right) { 
                        formController.append(actualForm);
                        ajoutFin(); 

                        cout<<ControllerForm::indexRemove<<endl;
                        formController.remove();
                        if(ControllerForm::indexRemove != -1){
                            score +=3;
                             isdelete = supprimerPiece(ControllerForm::indexRemove);
                                if(isdelete){isdelte = true;}else{cout<<"not delete"<<ControllerForm::indexRemove<<endl;}
                             


                            isdelete = supprimerPiece(ControllerForm::indexRemove);
                                if(isdelete){}else{cout<<"not delete"<<ControllerForm::indexRemove<<endl;}
                            

                            isdelete = supprimerPiece(ControllerForm::indexRemove);
                                if(isdelete){}else{cout<<"not delete"<<ControllerForm::indexRemove<<endl;}

                             ControllerForm::indexRemove = -1;


                        }
                        formController.list.show();
                        if(formes.empty()){
                            cout << "Execution time: " << getTime(clock) << " seconds" << std::endl;

                            viewVictory victory;
                            window->close();
                            victory.show();
                        }else if (formes.size() >= 12) {
                            cout << "Execution time: " << getTime(clock) << " seconds" << std::endl;
                            ViewDefaite defaite;
                             window->close();
                            defaite.show();
                        }
                
                    }
                    break;
            }
        }
    }
};

class ViewGame{
    public:
    string nameUser;
    // Créez un objet sf::Clock pour mesurer le temps écoulé
    
     Game game;

    
    ViewGame(string name): nameUser(name){
        cout<<nameUser<<endl;
    }

    void show(){
       
      while (game.running())
        {
       game.update(); // Met à jour le jeu
       game.render(); // Affiche le jeu
        }

         
        user = UserController::createUser(nameUser, game.getScore(), game.getTimer());
        UserController::saveUser(user);
        user.showUser();
    
    }


   

    

    
};




