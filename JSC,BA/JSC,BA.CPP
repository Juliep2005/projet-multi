#include "JSC,BA.h"
#include <iostream>

Personnage::Personnage(std::string n, int pv, int pm, int ad, int dcs, int v)
    : nom(n), pointsDeVie(pv), pointsDeMana(pm), attaqueDeBase(ad),
      degatsCapaciteSpeciale(dcs), vitesse(v), pointsDeVieMax(pv), bouclierMagique(false) {}

void Personnage::attaquer(Personnage &adversaire) {
    std::cout << nom << " attaque " << adversaire.nom << " pour " << attaqueDeBase << " points de dégâts.\n";
    adversaire.recevoirDegats(attaqueDeBase);
}

void Personnage::recevoirDegats(int degats) {
    if (bouclierMagique) {
        std::cout << nom << " annule les dégâts avec son bouclier magique !\n";
        bouclierMagique = false; // Le bouclier est consommé
    } else {
        pointsDeVie -= degats;
        if (pointsDeVie < 0) pointsDeVie = 0;
        std::cout << nom << " reçoit " << degats << " dégâts. Points de vie restants : " << pointsDeVie << ".\n";
    }
}

void Personnage::afficherStats() {
    std::cout << "Nom: " << nom << " | PV: " << pointsDeVie << " | Mana: " << pointsDeMana << " | Attaque: " << attaqueDeBase << "\n";
}
