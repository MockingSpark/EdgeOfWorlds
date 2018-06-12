/**
* //////  Skill.h  //////
*
* Ce fichier constient la Skill, permettant de gérer les compétences
*
* \author Cossec Estéban
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
  * Un skill a un grand nombre d'effets possibles décrits ci-dessous
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

	/// fonction de mise à jour des charges restantes. à appeler lors de l'utilisation
	void updateCharges() { m_charges -= m_cost; };
	/// fonctions permettant de recharger la compétences
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
	std::string m_name;	///< nom de la compétences
	int m_repel;	///< effet de repousse NYI
	int m_modifier; ///< modificateur de dégats en %
	int m_pureDamage;	///< dégats bruts appliqués En Plus des dégats classique
	bool m_magical;	///< définit sur quelle statistique agir
	int m_range;	///< la distance à laquelle l'attaque peut être lancée
	int m_radius;	///< le rayon d'action de l'attaque par raport à son point d'impact
	int m_accuracy;	///< précision de l'attaque NYI
	int m_cost;		///< coût d'utilisation de l'attaque (sur ses charges)
	bool m_heal;	///< détermine si il s'agit d'un sort de soin
	std::vector<Statut> m_statuts;	///< les statuts que l'attaque inflige
	int m_charges;	///< le nomre de charges encore disponibles
	int m_maxCharges;	///< le nombre de charges maximales
	Element m_element;	///< L'élément de l'attaque
	int m_recoil;	///< les dégats de recul en % de vie
	std::vector<Statut> m_recoilStatuts;	///< les status infligés lors du recul
	SkillRange m_targeted;	///< Les trois suivants déterminent quelles sont les cibles de l'attaque
	TargetTeam m_targetTeam;
	EdgeSide m_targetSide;

};

