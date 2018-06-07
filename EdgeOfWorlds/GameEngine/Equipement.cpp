#include "stdafx.h"
#include "Equipement.h"

Equipement::EquipType Equipement::equipTypeFromString(std::string s)
{
	if (s == "weapon")
		return WEAPON;
	if (s == "armor")
		return ARMOR;
	if (s == "misc")
		return MISC;
	exit(-666);
}

std::string Equipement::stringFromEquipType(EquipType t)
{
	switch (t)
	{
	case WEAPON:
		return "weapon";
		break;
	case ARMOR:
		return "armor";
		break;
	case MISC:
		return "misc";
		break;
	}
	return "";
}

Equipement::Equipement(pugi::xml_node& node) :
	m_name(node.attribute("name").as_string()),
	m_munitions(node.attribute("munitions").as_int()),
	m_bonus(node.child("Bonus")),
	m_weaknesses{ W_NONE, W_NONE, W_NONE, W_NONE, W_NONE, W_NONE, W_NONE, W_NONE },
	m_increases{ 100, 100, 100, 100, 100, 100, 100, 100 },
	m_description(node.child("Descriptor").text().as_string())
{
	m_attack = std::make_unique<Skill>(node.child("Attack"));
    m_skill = std::make_unique<Skill>(node.child("Skill"));
	m_type = equipTypeFromString(node.attribute("equipType").as_string());
	for (auto & a : node.child("Weakness").attributes())
	{
		m_weaknesses[elementFromString(a.name())] = weaknessFromString(a.as_string());
	}
	for (auto & a : node.child("Increase").attributes())
	{
		m_increases[elementFromString(a.name())] = a.as_int();
	}
}

Skill const * Equipement::useAttack()
{

	return m_attack.get();
}

Skill const * Equipement::useSkill()
{
	return m_skill.get(); 
}

Stats const & Equipement::getBonuses() const
{
	return m_bonus;
}

std::string const & Equipement::getName() const
{
	return m_name;
}

int const & Equipement::getMunitions() const
{
	return m_munitions;
}

Equipement::EquipType const & Equipement::getEquipType() const
{
	return m_type;
}

std::string const & Equipement::getDescription() const
{
	return m_description;
}