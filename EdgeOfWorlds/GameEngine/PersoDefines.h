/**
* //////  PersoDefines.h  //////
*
* Ce fichier constient les définitions nécessaires à la gestion des personnages
*
* \author Cossec Estéban
*
*/

#pragma once
#include <pugixml.hpp>

/// structure contenant les tatistiques d'un Personnage
struct Stats {
	Stats(pugi::xml_node node);

	Stats& operator+=(Stats const &);

	int HP;		///< HP
	int strength;	///< force physique
	int defense;	///< resistance physique
	int power;		///< force magique
	int resist;		///< resistance magique
	int speed;		///< capacité de mouvement
};

/// Enumeration pour la gestion des statuts
enum StatutEnum {
	EFFECT,
	POISON,
	WEAK,
	BRITTLE,
	MUTE,
	SLOW,
	SOFTHEAL,
	STRONG,
	UNBREAKABLE,
	QUICK,
	FREEZE,
};