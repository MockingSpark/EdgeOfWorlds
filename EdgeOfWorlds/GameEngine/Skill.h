#pragma once

#include <vector>
#include "skillDefine.h"
#include "PersoDefines.h"

class SkillEffect;

class Skill
{
public:
	void use(int, int);

protected:
	std::string m_name;
	std::vector<SkillEffect> m_effects;
	JobFlag m_allowedJobs;
	Target m_target;
	TargetType m_targetType;
	EdgeSide m_targetSide;

};

