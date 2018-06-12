/**
* //////  Elements.h  //////
*
* Ce fichier constient les définitions nécessaires à la gestion des éléments
*
* \author Cossec Estéban
*
*/

#pragma once
#include <string>


/// le nombre d'éléments définis
#define NB_ELEMENTS 8

/// Cette énumeration liste tous les éléments disponibles dans le programme
enum Element {
	E_FIRE = 0,
	E_WATER = 1,
	E_WIND = 2,
	E_THUNDER = 3,
	E_EARTH = 4,
	E_HOLY = 5,
	E_DARK = 6,
	E_NONE = 7
};

/// Cette énumeration définit les niveaux de résistance élémentaire
enum Weakness {
	W_NONE,
	W_WEAK,
	W_RESISTANT,
	W_IMMUNE,
	W_ABSORB,
};

/// éléments de traduction nécessasires pour le parsing du fichier XML
std::string stringFromElement(Element const &);
Element elementFromString(std::string const &);

std::string stringFromWeakness(Weakness const &);
Weakness weaknessFromString(std::string const &);

/// une somme redéfinie pour les niveaux de résistance
Weakness combineWeakness(Weakness const &, Weakness const &);
/// donne le modificateur de dégats en pourcentage selon le niveau de resistance
int getModifierFromWeakness(Weakness const &);

