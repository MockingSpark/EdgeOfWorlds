/**
* //////  Skill.h  //////
*
* Ce fichier constient la Skill, permettant de g�rer les comp�tences
*
* \author Cossec Est�ban
*
*/

#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"
#include "mapDefines.h"
#include "pugixml.hpp"
#include "Statut.h"
#include "Elements.h"


/**
  * \class Skill
  * 
  * Un skill a un grand nombre d'effets possibles d�crits ci-dessous
  */
class Skill
{
protected:
	/// fonctions de parsing
	std::string stringFromSkillRange(SkillRange t);
	SkillRange skillRangeFromString(std::string t);
	std::string stringFromTargetTeam(TargetTeam t);
	TargetTeam targetTeamFromString(std::string t);
	std::string stringFromEdgeSide(EdgeSide t);
	EdgeSide edgeSideFromString(std::string t);

public:
	/// constructeur depuis un oeud XML
	Skill(pugi::xml_node);

	/// fonction de mise � jour des charges restantes. � appeler lors de l'utilisation
	void updateCharges() { m_charges -= m_cost; };
	/// fonctions permettant de recharger la comp�tences
	void refill() { m_charges = m_maxCharges; };

	/// accesseurs
	std::string const & getName() const { return m_name; };
	int const & getRepel() const { return m_repel; };
	int const & getModifier() const { return m_modifier; };
	int const & getPureDamage() const { return m_pureDamage; };
	bool const & isMagical() const { return m_magical; };
	int const & getRange() const { return m_range; };
	int const & getRadius() const { return m_radius; };
	int const & getAccuracy() const { return m_accuracy; };
	int const & getCost() const { return m_cost; };
	bool const & isHealer() const { return m_heal; };
	std::vector<Statut> const & getStatuts() const { return m_statuts; };
	int const & getCharges() const { return m_charges; };
	int const & getMaxCharges() const { return m_maxCharges; };
	Element const & getElement() const { return m_element; };
	int const & getRecoil() const { return m_recoil; };
	std::vector<Statut> const & getRecoilStatuts() const { return m_recoilStatuts; };
	SkillRange const & getTargeted() const { return m_targeted; };
	TargetTeam const & getTargetTeam() const { return m_targetTeam; };;
	EdgeSide const & getTargetSide() const { return m_targetSide; };

protected:
	std::string m_name;	///< nom de la comp�tences
	int m_repel;	///< effet de repousse NYI
	int m_modifier; ///< modificateur de d�gats en %
	int m_pureDamage;	///< d�gats bruts appliqu�s En Plus des d�gats classique
	bool m_magical;	///< d�finit sur quelle statistique agir
	int m_range;	///< la distance � laquelle l'attaque peut �tre lanc�e
	int m_radius;	///< le rayon d'action de l'attaque par raport � son point d'impact
	int m_accuracy;	///< pr�cision de l'attaque NYI
	int m_cost;		///< co�t d'utilisation de l'attaque (sur ses charges)
	bool m_heal;	///< d�termine si il s'agit d'un sort de soin
	std::vector<Statut> m_statuts;	///< les statuts que l'attaque inflige
	int m_charges;	///< le nomre de charges encore disponibles
	int m_maxCharges;	///< le nombre de charges maximales
	Element m_element;	///< L'�l�ment de l'attaque
	int m_recoil;	///< les d�gats de recul en % de vie
	std::vector<Statut> m_recoilStatuts;	///< les status inflig�s lors du recul
	SkillRange m_targeted;	///< Les trois suivants d�terminent quelles sont les cibles de l'attaque
	TargetTeam m_targetTeam;
	EdgeSide m_targetSide;

};

