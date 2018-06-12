/**
* //////  Equipements.h  //////
*
* Ce fichier constient la classe Equipement, représentant un équipement portable par le Personnage.
*
* \author Cossec Estéban
*
*/

#pragma once
#include <string>
#include "PersoDefines.h"
#include "Skill.h"

/**
  * \class Equipement
  * 
  * Cette classe représente les équipements. Un équipement peut être une Arme, une Armure ou un divers.
  *
  * TODO : Une modification du modèle de gestion des attaques a rendue cette classe maladroite.
  * elle mériterait une refonte avec arborescence de classe pour différencier les armes des autres.
  */
class Equipement
{
public:

	/// constructeur prenant un noeud xml
	Equipement(pugi::xml_node&);


	/// accesseurs
	std::string const & getName() const;
	std::string const & getDescription() const;
	Weakness const & getWeakness(Element e) const { return m_weaknesses[e]; };
	int const & getIncreaseness(Element e) const { return m_increases[e]; };

private:
	std::string m_name;	///< le nom de l'équipement
	std::string m_description;	///< description de l'equipement
	Weakness m_weaknesses[NB_ELEMENTS];	///< faiblesses élémentaires apportées
	int m_increases[NB_ELEMENTS];	///< améliorations élémentaires apportées

};

class Armor : public Equipement
{
public:
	Armor(pugi::xml_node&);
	/// accesseurs
	Stats const & getBonuses() const;
protected:
	Stats m_bonus;	///< les bonus de stats associés
};

class Weapon : public Equipement
{
public:
	Weapon(pugi::xml_node&);

	/// fonctions permettant d'accéder aux compétences données par cet équipement
	/// TODO redéfinir à la refonte.
	Skill const & useAttack();
	Skill const & useSkill();

	/// accesseurs
	Stats const & getBonuses() const;
protected:
	Stats m_bonus;	///< les bonus de stats associés
	Skill m_attack; ///< le skill d'attaque de base de l'arme 
	Skill m_skill;	///< le skill apporté par l'arme 
};

