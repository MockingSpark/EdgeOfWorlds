#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"
#include "mapDefines.h"
#include "pugixml.hpp"
#include "Statut.h"
#include "Elements.h"


class Skill
{
public:
	Skill(pugi::xml_node);

	int const & getCharges() const { return m_charges; } ;
	void updateCharges() { m_charges -= m_cost; };
	void refill() { m_charges = m_maxCharges; };

	std::vector<Statut> const & getStatuts() const { return m_statuts; };
	std::string const & getName() const { return m_name; };
	int const & getKnockback() const { return m_knockback; };
	int const & getModifier() const { return m_modifier; };
	int const & getPureDamage() const { return m_pureDamage; };
	bool const & isMagical() const { return m_magical; };
	int const & getRange() const { return m_range; };
	int const & getRadius() const { return m_radius; };
	int const & getAccuracy() const { return m_accuracy; };
	int const & getCost() const { return m_cost; };
	bool const & isHealer() const { return m_heal; };
	Element const & getElement() const { return m_element; };

protected:
	std::string m_name;
	int m_knockback;
	int m_modifier;
	int m_pureDamage;
	bool m_magical;
	int m_range;
	int m_radius;
	int m_accuracy;
	int m_cost;
	bool m_heal;
	std::vector<Statut> m_statuts;
	int m_charges;
	int const m_maxCharges;
	Element m_element;
	//pugi::xml_node const spawn;
	// TargetGroup const m_targetGroup;
	// TargetType const m_targetType;
	// EdgeSide const m_targetSide;

};

