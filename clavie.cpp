#include <iostream>
#include <unistd.h>
#include <termios.h>





char detecterTouche() {
    struct termios oldt, newt;
    char ch;

    // Sauvegarde des paramètres du terminal actuel
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Configuration du terminal pour lire sans attendre l'entrée de l'utilisateur
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Lecture en continu des touches
    while (true) {
        if (std::cin.get(ch)) {
            if (ch == '\x1b') { // Escape character
                if (std::cin.get() == '[') {
                    switch (std::cin.get()) {
                        case 'C':
                            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restauration des paramètres du terminal
                            return 'd';
                        case 'D':
                            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restauration des paramètres du terminal
                            return 'g';
                       
                        default:
                            break;
                    }
                }
            } else if (ch == 'q' || ch == 'Q') {
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restauration des paramètres du terminal
                return 'q';
            }
        }
    }
}




