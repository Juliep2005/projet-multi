#include <iostream>
#include "GRC.h"

void afficherMenu() {
    std::cout << "\n---- Menu Principal ----\n";
    std::cout << "1. Afficher la salle de cinéma\n";
    std::cout << "2. Réserver des sièges\n";
    std::cout << "3. Confirmer une réservation\n";
    std::cout << "4. Annuler une réservation\n";
    std::cout << "5. Rechercher des sièges disponibles par catégorie\n";
    std::cout << "6. Rechercher des sièges disponibles par rangée\n";
    std::cout << "7. Sauvegarder la salle\n";
    std::cout << "8. Charger la salle\n";
    std::cout << "9. Quitter\n";
}

int main() {
    Salle salle;
    int choix;
    salle.chargerSalle(); // Charger la salle au démarrage

    do {
        afficherMenu();
        std::cout << "Choisissez une option: ";
        std::cin >> choix;

        if (choix == 1) {
            salle.afficherSalle();
        } else if (choix == 2) { // Information du client/utilisateur
            int numero;
            std::string nom, telephone;
            std::cout << "Entrez le numéro du siège: ";
            std::cin >> numero;
            std::cout << "Entrez votre nom: ";
            std::cin >> nom;
            std::cout << "Entrez votre numéro de téléphone: ";
            std::cin >> telephone;
            Utilisateur utilisateur(nom, telephone);

            if (salle.reserverSiege(numero, utilisateur)) {
                std::cout << "Réservation effectuée pour le siège " << numero << ".\n";
            } else {
                std::cout << "Le siège est déjà réservé ou occupé.\n";
            }
        } 
        
        else if (choix == 3) {
            int numero;
            std::cout << "Entrez le numéro du siège à confirmer: ";
            std::cin >> numero;
            salle.confirmerReservation(numero);

        } else if (choix == 4) {
            int numero;
            std::cout << "Entrez le numéro du siège à annuler: ";
            std::cin >> numero;
            salle.annulerReservation(numero);
        }

        else if (choix == 5) {
            std::string categorie;
            std::cout << "Entrez la catégorie de sièges à rechercher (Standard, Premium, VIP): ";
            std::cin >> categorie;
            salle.rechercherSiegesParCategorie(categorie);
            if (categorie != "Standard" && categorie != "Premium" && categorie != "VIP") {
            std::cout << "Catégorie invalide. Veuillez entrer une catégorie valide (Standard, Premium, VIP).\n";
            } else {
                salle.rechercherSiegesParCategorie(categorie);
            }
        } 
        
        else if (choix == 6) {
            int rangee;
            std::cout << "Entrez le numéro de la rangée à rechercher (1-10): ";
            std::cin >> rangee;
            salle.rechercherSiegesParRangee(rangee);
        } 
        
        else if (choix == 7) {
            salle.sauvegarderSalle();
        }
        
         else if (choix == 8) {
            salle.chargerSalle();
        }

    } while (choix != 9);

    return 0;
}
