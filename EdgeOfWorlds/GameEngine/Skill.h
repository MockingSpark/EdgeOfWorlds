#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"
#include "mapDefines.h"
#include "pugixml.hpp"
#include "Statut.h"
#include "Elements.h"


// TODO accuracy

class Skill
{
protected:
	std::string stringFromSkillRange(SkillRange t);
	SkillRange skillRangeFromString(std::string t);
	std::string stringFromTargetTeam(TargetTeam t);
	TargetTeam targetTeamFromString(std::string t);
	std::string stringFromEdgeSide(EdgeSide t);
	EdgeSide edgeSideFromString(std::string t);

public:
	Skill(pugi::xml_node);

	void updateCharges() { m_charges -= m_cost; };
	void refill() { m_charges = m_maxCharges; };

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
	std::string m_name;
	int m_repel;
	int m_modifier; // %
	int m_pureDamage;
	bool m_magical;
	int m_range;
	int m_radius;
	int m_accuracy;
	int m_cost;
	bool m_heal;
	std::vector<Statut> m_statuts;
	int m_charges;
	int m_maxCharges;
	Element m_element;
	int m_recoil; // %
	std::vector<Statut> m_recoilStatuts;
	SkillRange m_targeted;
	TargetTeam m_targetTeam;
	EdgeSide m_targetSide;
	//pugi::xml_node const spawn;

};

