#ifndef GRC_H
#define GRC_H

#include <string>
#include <vector>

// Structure représentant un utilisateur
struct Utilisateur {
    std::string nom;
    std::string telephone;

    Utilisateur(const std::string& n, const std::string& t);
};

// Structure représentant un siège dans la salle
struct Siege {
    int numero;
    std::string categorie; // Standard, Premium, VIP
    enum Etat { DISPONIBLE, RESERVE, OCCUPE } etat;
    Utilisateur* utilisateur; // Pointeur vers l'utilisateur qui a réservé ce siège (si réservé)

    Siege();
};

// Classe représentant la salle de cinéma
class Salle {
public:
    Salle();

    void afficherSalle() const;
    bool reserverSiege(int numero, const Utilisateur& utilisateur);
    void confirmerReservation(int numero);
    void annulerReservation(int numero);
    void rechercherSiegesParCategorie(const std::string& categorie) const;
    void rechercherSiegesParRangee(int rangee) const;
    void sauvegarderSalle() const;
    void chargerSalle();

private:
    std::vector<Siege> salle;
};

#endif // GRC_H
