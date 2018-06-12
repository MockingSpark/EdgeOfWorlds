/**
* //////  Statut.h  //////
*
* Ce fichier constient la classe Statut, gérant les altérations d'état
*
* \author Cossec Estéban
*
*/

#pragma once
#include "PersoDefines.h"
#include <pugixml.hpp>

/**
  * \class Statut
  *
  * La classe statut gère les altérations d'état
  */
class Statut
{
private:
	/// fonctions nécessaires au parsing
	std::string stringFromStatut(StatutEnum t);
	StatutEnum statutFromString(std::string t);

public:
	/// constructeur basique
	Statut(StatutEnum const s, int const c, int const pow);
	/// constructeur par noeud XML
	Statut(pugi::xml_node);
	/// fonction de mise àjour à appeler à chaque tour de jeu
	void update() { if (m_compteur > 0) { m_compteur--; } if (m_compteur == 0) { m_needDelete = true; } };
	/// fonction retournant si le Statut doit être supprimé ou non
	bool const & isExpired() const { return m_needDelete; };

	/// accesseurs
	StatutEnum const & getEffect() const { return m_effect; };
	int const & getPower() const { return m_power; };
	int const & getCompteur() const { return m_compteur; };
	
private:
	int m_power;	///< puissance de l'effet
	StatutEnum m_effect;	///< type d'effet
	int m_compteur;	///< compteur de durée de vie
	bool m_needDelete;	///< indicateur de fin de vie
};