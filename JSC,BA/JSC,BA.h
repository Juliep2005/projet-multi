#ifndef JSC,BA_H
#define JSC,BA_H

#include <string>

class Personnage {
public:
    std::string nom;
    int pointsDeVie;
    int pointsDeMana;
    int attaqueDeBase;
    int degatsCapaciteSpeciale;
    int vitesse;
    int pointsDeVieMax;
    bool bouclierMagique;

    Personnage(std::string n, int pv, int pm, int ad, int dcs, int v);
    void attaquer(Personnage &adversaire);
    void recevoirDegats(int degats);
    void afficherStats();
};

#endif
