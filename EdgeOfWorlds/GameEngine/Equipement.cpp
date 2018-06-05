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
}

Equipement::Equipement(pugi::xml_node& node) :
	m_name(node.attribute("name").as_string()),
	m_munitions(node.attribute("munition").as_int()),
	m_bonus(node.child("Bonus")),
	m_description(node.child("Descriptor").text().as_string())
{
	m_attack = std::make_unique<Skill>(node.child("Attack"));
    m_skill = std::make_unique<Skill>(node.child("Skill"));
	m_type = equipTypeFromString(node.attribute("equipType").as_string());
}

Skill const * Equipement::useAttack()
{

	return nullptr;
}

Skill const * Equipement::useSkill()
{
	return nullptr;
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
