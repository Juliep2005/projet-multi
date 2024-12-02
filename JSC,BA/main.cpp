#include <iostream>
#include <chrono>
#include "JSC,BA.h"

// Fonction pour afficher le menu principal et obtenir le choix du joueur
int afficherMenu() {
    int choix;
    std::cout << "\n--- Menu Principal ---\n";
    std::cout << "1. Jouer contre un autre joueur\n";
    std::cout << "2. Jouer contre l'ordinateur\n";
    std::cout << "3. Quitter\n";
    std::cout << "Entrez votre choix: ";
    std::cin >> choix;
    return choix;
}

// Fonction pour créer un personnage
Personnage creerPersonnage() {
    std::string nom;
    int pv, mana, attaque, degatsSpeciaux, vitesse;

    std::cout << "Nom du personnage: ";
    std::cin >> nom;
    std::cout << "Points de vie: ";
    std::cin >> pv;
    std::cout << "Points de mana: ";
    std::cin >> mana;
    std::cout << "Attaque de base: ";
    std::cin >> attaque;
    std::cout << "Dégâts capacité spéciale: ";
    std::cin >> degatsSpeciaux;
    std::cout << "Vitesse: ";
    std::cin >> vitesse;

    return Personnage(nom, pv, mana, attaque, degatsSpeciaux, vitesse);
}

// Fonction pour jouer un tour entre deux joueurs
void jouerTourJoueurVsJoueur(Personnage &joueur1, Personnage &joueur2) {
    joueur1.afficherStats();
    joueur2.afficherStats();

    std::cout << joueur1.nom << ", c'est votre tour !\n";
    joueur1.attaquer(joueur2);

    if (joueur2.pointsDeVie <= 0) {
        std::cout << joueur2.nom << " est mort ! " << joueur1.nom << " gagne !\n";
        return;
    }

    std::cout << joueur2.nom << ", c'est votre tour !\n";
    joueur2.attaquer(joueur1);

    if (joueur1.pointsDeVie <= 0) {
        std::cout << joueur1.nom << " est mort ! " << joueur2.nom << " gagne !\n";
        return;
    }
}

// Fonction pour jouer un tour contre l'IA
void jouerTourJoueurVsIA(Personnage &joueur, Personnage &ia) {
    joueur.afficherStats();
    ia.afficherStats();

    std::cout << joueur.nom << ", c'est votre tour !\n";
    joueur.attaquer(ia);

    if (ia.pointsDeVie <= 0) {
        std::cout << ia.nom << " est mort ! " << joueur.nom << " gagne !\n";
        return;
    }

    std::cout << ia.nom << " attaque " << joueur.nom << " pour " << ia.attaqueDeBase << " dégâts.\n";
    ia.attaquer(joueur);

    if (joueur.pointsDeVie <= 0) {
        std::cout << joueur.nom << " est mort ! " << ia.nom << " gagne !\n";
        return;
    }
}

int main() {
    bool quitter = false;
    while (!quitter) {
        int choix = afficherMenu();
        
        switch (choix) {
            case 1: {  // Jouer contre un autre joueur
                std::cout << "Création du personnage du Joueur 1:\n";
                Personnage joueur1 = creerPersonnage();
                std::cout << "Création du personnage du Joueur 2:\n";
                Personnage joueur2 = creerPersonnage();

                // Début de la mesure du temps
                auto start = std::chrono::high_resolution_clock::now();

                while (joueur1.pointsDeVie > 0 && joueur2.pointsDeVie > 0) {
                    jouerTourJoueurVsJoueur(joueur1, joueur2);
                }

                // Fin de la mesure du temps
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;

                std::cout << "Durée du combat : " << duration.count() << " secondes.\n";
                break;
            }

            case 2: {  // Jouer contre l'ordinateur
                std::cout << "Création de votre personnage:\n";
                Personnage joueur = creerPersonnage();
                Personnage ia("IA", 100, 50, 15, 20, 10);  // L'IA a des stats prédéfinies

                // Début de la mesure du temps
                auto start = std::chrono::high_resolution_clock::now();

                while (joueur.pointsDeVie > 0 && ia.pointsDeVie > 0) {
                    jouerTourJoueurVsIA(joueur, ia);
                }

                // Fin de la mesure du temps
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;

                std::cout << "Durée du combat : " << duration.count() << " secondes.\n";
                break;
            }

            case 3: {  // Quitter le jeu
                quitter = true;
                std::cout << "Merci d'avoir joué ! À bientôt !\n";
                break;
            }

            default:
                std::cout << "Choix invalide, veuillez réessayer.\n";
                break;
        }
    }

    return 0;
}
