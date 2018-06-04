#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"
#include "mapDefines.h"
#include "pugixml.hpp"
#include "Character.h"

//class SkillEffect;

class Skill
{
public:


	void use(Character const*) const;
	pugi::xml_node spawnOnMap() const;

protected:
	std::string m_name;
	int m_knockback;
	//std::vector<SkillEffect> m_effects;
	//JobFlag m_allowedJobs;
	//Target m_target;
	//TargetType m_targetType;
	//EdgeSide m_targetSide;

};

