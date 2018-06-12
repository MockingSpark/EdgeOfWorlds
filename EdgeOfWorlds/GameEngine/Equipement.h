/**
* //////  Equipements.h  //////
*
* Ce fichier constient la classe Equipement, repr�sentant un �quipement portable par le Personnage.
*
* \author Cossec Est�ban
*
*/

#pragma once
#include <string>
#include "PersoDefines.h"
#include "Skill.h"

/**
  * \class Equipement
  * 
  * Cette classe repr�sente les �quipements. Un �quipement peut �tre une Arme, une Armure ou un divers.
  *
  * TODO : Une modification du mod�le de gestion des attaques a rendue cette classe maladroite.
  * elle m�riterait une refonte avec arborescence de classe pour diff�rencier les armes des autres.
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
	std::string m_name;	///< le nom de l'�quipement
	std::string m_description;	///< description de l'equipement
	Weakness m_weaknesses[NB_ELEMENTS];	///< faiblesses �l�mentaires apport�es
	int m_increases[NB_ELEMENTS];	///< am�liorations �l�mentaires apport�es

};

class Armor : public Equipement
{
public:
	Armor(pugi::xml_node&);
	/// accesseurs
	Stats const & getBonuses() const;
protected:
	Stats m_bonus;	///< les bonus de stats associ�s
};

class Weapon : public Equipement
{
public:
	Weapon(pugi::xml_node&);

	/// fonctions permettant d'acc�der aux comp�tences donn�es par cet �quipement
	/// TODO red�finir � la refonte.
	Skill const & useAttack();
	Skill const & useSkill();

	/// accesseurs
	Stats const & getBonuses() const;
protected:
	Stats m_bonus;	///< les bonus de stats associ�s
	Skill m_attack; ///< le skill d'attaque de base de l'arme 
	Skill m_skill;	///< le skill apport� par l'arme 
};

