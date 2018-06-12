/**
* //////  Elements.h  //////
*
* Ce fichier constient les d�finitions n�cessaires � la gestion des �l�ments
*
* \author Cossec Est�ban
*
*/

#pragma once
#include <string>


/// le nombre d'�l�ments d�finis
#define NB_ELEMENTS 8

/// Cette �numeration liste tous les �l�ments disponibles dans le programme
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

/// Cette �numeration d�finit les niveaux de r�sistance �l�mentaire
enum Weakness {
	W_NONE,
	W_WEAK,
	W_RESISTANT,
	W_IMMUNE,
	W_ABSORB,
};

/// �l�ments de traduction n�cessasires pour le parsing du fichier XML
std::string stringFromElement(Element const &);
Element elementFromString(std::string const &);

std::string stringFromWeakness(Weakness const &);
Weakness weaknessFromString(std::string const &);

/// une somme red�finie pour les niveaux de r�sistance
Weakness combineWeakness(Weakness const &, Weakness const &);
/// donne le modificateur de d�gats en pourcentage selon le niveau de resistance
int getModifierFromWeakness(Weakness const &);

