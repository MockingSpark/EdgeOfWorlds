#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"
#include "mapDefines.h"
#include "pugixml.hpp"
#include "Statut.h"


class Skill
{
public:
	Skill(pugi::xml_node);

	int const & getCharges() const { return m_charges; } ;
	void updateCharges() { m_charges -= cost; };
	void refill() { m_charges = m_maxCharges; };

	std::vector<Statut> const & getStatuts() const { return statuts; };

public:
	std::string const name;
	int const knockback;
	int const modifier;
	int const pureDamage;
	bool const isMagical;
	int const range;
	int const radius;
	int const accuracy;
	int const cost;
	bool const heal;
	//pugi::xml_node const spawn;
	// TargetGroup const m_targetGroup;
	// TargetType const m_targetType;
	// EdgeSide const m_targetSide;
	// Type const m_type;

protected:
	std::vector<Statut> statuts;
	int m_charges;
	int const m_maxCharges;
};

