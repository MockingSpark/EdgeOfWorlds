#include "stdafx.h"
#include "Equipement.h"

Equipement::Equipement(pugi::xml_node& node) :
	m_name(node.attribute("name").as_string()),
	m_weaknesses{ W_NONE, W_NONE, W_NONE, W_NONE, W_NONE, W_NONE, W_NONE, W_NONE },
	m_increases{ 100, 100, 100, 100, 100, 100, 100, 100 },
	m_description(node.child("Descriptor").text().as_string())
{
	for (auto & a : node.child("Weakness").attributes())
	{
		m_weaknesses[elementFromString(a.name())] = weaknessFromString(a.as_string());
	}
	for (auto & a : node.child("Increase").attributes())
	{
		m_increases[elementFromString(a.name())] = a.as_int();
	}
}

Armor::Armor(pugi::xml_node & node) :
	Equipement(node),
	m_bonus(node.child("Bonus"))
{
}

Weapon::Weapon(pugi::xml_node& node) :
	Equipement(node),
	m_attack(node.child("Attack")),
	m_skill(node.child("Skill")),
	m_bonus(node.child("Bonus"))
{

}

Skill const & Weapon::useAttack()
{

	return m_attack;
}

Skill const & Weapon::useSkill()
{
	return m_skill; 
}

Stats const & Weapon::getBonuses() const
{
	return m_bonus;
}

Stats const & Armor::getBonuses() const
{
	return m_bonus;
}

std::string const & Equipement::getName() const
{
	return m_name;
}

std::string const & Equipement::getDescription() const
{
	return m_description;
}

