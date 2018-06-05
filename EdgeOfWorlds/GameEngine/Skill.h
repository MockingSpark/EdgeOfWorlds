#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"
#include "mapDefines.h"
#include "pugixml.hpp"


class Skill
{
public:
	Skill(pugi::xml_node);

	int getCharges() { return m_charges; };
	void updateCharges() { m_charges -= cost; };
	void refill() { m_charges = m_maxCharges; };

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
	bool heal;
	//pugi::xml_node const spawn;
	// TargetGroup const m_targetGroup;
	// TargetType const m_targetType;
	// EdgeSide const m_targetSide;
	// Type const m_type;

protected:
	int m_charges;
	int const m_maxCharges;
};

