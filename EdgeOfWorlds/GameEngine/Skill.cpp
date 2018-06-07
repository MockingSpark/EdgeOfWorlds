#include "stdafx.h"
#include "Skill.h"
/*
<Skill name = "Hit">
<Target range = "1" radius = "1" accuracy = "100" side = "same" team = "any" reachable = "area" / >
<Usage charges = "1" cost = "0" / >
<Effect repel = "0" pureDamage = "0" heal = "false"  modifier = "100" isMagical = "false">
<!-- <Statut effect = "poison" power = "10" duration = "3" / > -->
< / Effect>
<Recoil power = "0">
<!-- <RecoilStatus effect = "poison" power = "10" duration = "3" / > -->
< / Recoil>
< / Skill>*/

std::string Skill::stringFromSkillRange(SkillRange t)
{
	switch (t)
	{
	case R_ALL:
		return "all";
	case R_OTHERS:
		return "others";
	case R_TEAM:
		return "team";
	case R_AREA:
		return "area";
	default:
		return "area";
	}
}

SkillRange Skill::skillRangeFromString(std::string t)
{
	if (t == "all")
	{
		return R_ALL;
	}
	if (t == "others")
	{
		return R_OTHERS;
	}
	if (t == "team")
	{
		return R_TEAM;
	}
	return R_AREA;
}

std::string Skill::stringFromTargetTeam(TargetTeam t)
{
	switch (t)
	{
	case T_ENEMY:
		return "enemy";
	case T_SELF:
		return "self";
	case T_STAGE:
		return "stage";
	case T_TEAM:
		return "team";
	default:
		return "both";
	}
}

TargetTeam Skill::targetTeamFromString(std::string t)
{
	if (t == "stage")
	{
		return T_STAGE;
	}
	if (t == "enemy")
	{
		return T_ENEMY;
	}
	if (t == "self")
	{
		return T_SELF;
	}
	if (t == "team")
	{
		return T_TEAM;
	}
	return T_SELF;
}

std::string Skill::stringFromEdgeSide(EdgeSide t)
{
	switch (t)
	{
	case S_BOTH:
		return "both";
	case S_EITHER:
		return "either";
	case S_MEDIEVAL:
		return "medieval";
	case S_TECH:
		return "tech";
	case S_OTHER:
		return "other";
	case S_SAME:
		return "same";
	default:
		return "same";
	}
}

EdgeSide Skill::edgeSideFromString(std::string t)
{
	if (t == "both")
	{
		return S_BOTH;
	}
	if (t == "either")
	{
		return S_EITHER;
	}
	if (t == "medieval")
	{
		return S_MEDIEVAL;
	}
	if (t == "tech")
	{
		return S_TECH;
	}
	if (t == "other")
	{
		return S_OTHER;
	}
	return S_SAME;
}

Skill::Skill(pugi::xml_node node) :
	m_name(node.attribute("name").as_string()),
	m_repel(node.child("Effect").attribute("repel").as_int()),
	m_modifier(node.child("Effect").attribute("modifier").as_int()),
	m_pureDamage(node.child("Effect").attribute("pureDamage").as_int()),
	m_magical(node.child("Effect").attribute("isMagical").as_bool()),
	m_heal(node.child("Effect").attribute("heal").as_bool()),
	m_element(elementFromString(node.child("Effect").attribute("element").as_string())),
	m_range(node.child("Target").attribute("range").as_int()),
	m_radius(node.child("Target").attribute("radius").as_int()),
	m_accuracy(node.child("Target").attribute("accuracy").as_int()),
	m_targeted(skillRangeFromString(node.child("Target").attribute("reachable").as_string())),
    m_targetTeam(targetTeamFromString(node.child("Target").attribute("team").as_string())),
    m_targetSide(edgeSideFromString(node.child("Target").attribute("side").as_string())),
	m_cost(node.child("Usage").attribute("cost").as_int()),
	m_maxCharges(node.child("Usage").attribute("charges").as_int()),
	m_charges(node.child("Usage").attribute("charges").as_int()),
	m_recoil(node.child("Recoil").attribute("power").as_int())/*,
	spawn(node.child("Spawn"))*/
{
	for (auto n : node.child("Effect").children("Statut"))
	{
		m_statuts.push_back(Statut(n));
	}
	for (auto n : node.child("Recoil").children("Statut"))
	{
		m_recoilStatuts.push_back(Statut(n));
	}
}
