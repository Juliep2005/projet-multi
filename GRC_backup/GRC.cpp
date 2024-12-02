#include "GRC.h"
#include <iostream>
#include <fstream>
#include <sstream>

const int ROWS = 10; // Nombre de rangées
const int COLS = 12; // Nombre de sièges par rangée
const std::string FICHIER_SALLE = "salle_cinema.txt"; // Nom du fichier pour sauvegarder la salle

// Implémentation de la structure Utilisateur
Utilisateur::Utilisateur(const std::string& n, const std::string& t) : nom(n), telephone(t) {}

// Implémentation de la st5ructure Siege
Siege::Siege() : utilisateur(nullptr), etat(DISPONIBLE) {}

// Implémentation de la classe Salle

Salle::Salle() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            Siege siege;
            siege.numero = (i + 1) * 10 + (j + 1); // Numéro unique  A MODIFIERRRRRRR!!!!!!
            siege.etat = Siege::DISPONIBLE;
            siege.categorie = (i < 3) ? "VIP" : ((i < 7) ? "Premium" : "Standard"); // Catégorisation simple
            salle.push_back(siege);
        }
    }
}

void Salle::afficherSalle() const {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int index = i * COLS + j;

            // afficher l'état de la salle
            switch (salle[index].etat){
            case Siege::DISPONIBLE:
                std::cout << "D";
                break;
            case Siege::RESERVE:
                std::cout << "R";
                break;
            case Siege::OCCUPE:
                std::cout << "O";
                break;
            }

            // Sépration des sièges
            if (j != COLS - 1){
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
    }
}

bool Salle::reserverSiege(int numero, const Utilisateur& utilisateur) {
    for (auto& siege : salle) {
        if (siege.numero == numero && siege.etat == Siege::DISPONIBLE) {
            siege.etat = Siege::RESERVE;
            siege.utilisateur = new Utilisateur(utilisateur);
            return true;
        }
    }
    return false;
}

void Salle::confirmerReservation(int numero) {
    for (auto& siege : salle) {
        if (siege.numero == numero && siege.etat == Siege::RESERVE) {
            siege.etat = Siege::OCCUPE;
            return;
        }
    }
    std::cout << "Réservation non trouvée ou déjà confirmée.\n";
}

void Salle::annulerReservation(int numero) {
    for (auto& siege : salle) {
        if (siege.numero == numero && siege.etat == Siege::RESERVE) {
            delete siege.utilisateur;
            siege.utilisateur = nullptr;
            siege.etat = Siege::DISPONIBLE;
            return;
        }
    }
    std::cout << "Réservation non trouvée ou déjà annulée.\n";
}

void Salle::rechercherSiegesParCategorie(const std::string& categorie) const {
    bool trouve = false;

    std::cout << "Recherche de sièges disponibles pour la catégorie : " << categorie << "\n";
    std::cout << "--------------------------------------------\n";

    for (const auto& siege : salle) {

        // Vérification de la catégorie et de l'état du siège
        if (siege.categorie == categorie && siege.etat == Siege::DISPONIBLE) {
            std::cout << "Siège " << siege.numero << " est disponible.\n";
            trouve = true;
        }
    }

    if (!trouve) {
        std::cout << "Aucun siège disponible dans la catégorie " << categorie << ".\n";
    }

    std::cout << "--------------------------------------------\n";
}

void Salle::rechercherSiegesParRangee(int rangee) const {
    bool trouve = false;
    for (int i = (rangee - 1) * COLS; i < rangee * COLS; ++i) {
        const auto& siege = salle[i];
        if (siege.etat == Siege::DISPONIBLE) {
            std::cout << "Siège disponible: " << siege.numero << " (" << siege.categorie << ")\n";
            trouve = true;
        }
    }
    if (!trouve) {
        std::cout << "Aucun siège disponible dans la rangée " << rangee << ".\n";
    }
}

void Salle::sauvegarderSalle() const {
    std::ofstream fichier(FICHIER_SALLE);
    if (fichier) {
        for (const auto& siege : salle) {
            fichier << siege.numero << " "
                    << siege.categorie << " "
                    << siege.etat << " "
                    << (siege.utilisateur ? siege.utilisateur->nom : "") << " "
                    << (siege.utilisateur ? siege.utilisateur->telephone : "") << std::endl;
        }
        std::cout << "Salle sauvegardée avec succès.\n";
    } else {
        std::cout << "Erreur lors de la sauvegarde de la salle.\n";
    }
}

void Salle::chargerSalle() {
    std::ifstream fichier(FICHIER_SALLE);
    if (fichier) {
        salle.clear();
        int numero;
        std::string categorie, nom, telephone;
        int etat;
        while (fichier >> numero >> categorie >> etat) {
            Siege siege;
            siege.numero = numero;
            siege.categorie = categorie;
            siege.etat = static_cast<Siege::Etat>(etat);
            if (etat == Siege::RESERVE || etat == Siege::OCCUPE) {
                fichier >> nom >> telephone;
                siege.utilisateur = new Utilisateur(nom, telephone);
            }
            salle.push_back(siege);
        }
        std::cout << "Salle chargée avec succès.\n";
    } else {
        std::cout << "Aucun fichier de sauvegarde trouvé, nouvelle salle créée.\n";
    }
}
