#include "stdafx.h"
#include "Character.h"
#include <assert.h>
/**
  * 
  */

Character::Character(pugi::xml_node& node) :
	m_name(node.attribute("name").as_string()),
	m_level(node.attribute("level").as_int()),
	m_stats{node.child("Stats")},
	m_baseStats{ node.child("Stats") }
{


	m_skills[0] = std::make_unique<Skill>(node.child("Skills"));
	int i(0);
	for (auto n : node.child("Skills").children())
	{
		m_skills[i] = std::make_unique<Skill>(n);
		i++;
	}

}

/*
Character::Character(pugi::xml_node& node, int const level) :
	m_name(node.attribute("name").as_string()),
	m_level(level),
	m_stats{ node.child("BaseStats") },
	m_baseStats{ node.child("BaseStats") }
{

	/*
	 * TODO : - define stats by level
	 *        - add random skills by level + xml
	 *		  - add random equipement
	 *



	m_skills[0] = std::make_unique<Skill>(node.child("Skills"));
	int i(0);
	for (auto n : node.child("Skills").children())
	{
		m_skills[i] = std::make_unique<Skill>(n);
		i++;
	}

}*/

void Character::getHit(int const attPower)
{

	m_stats.HP -= attPower;
	if (m_stats.HP > m_baseStats.HP)
	{
		m_stats.HP = m_baseStats.HP;
	}
	else if (m_stats.HP <= 0)
	{
		onDeath();
	}
	else
	{
		onHit();
	}
}

void Character::hit(int const& skillID, Character * target) const
{
	// Pre-condition : skills[skillID] != NULL
	assert(m_skills[skillID] != nullptr);

	int lostHP = 0;

	if (m_skills[skillID]->isMagical){
		lostHP = m_skills[skillID]->pureDamage +
			(m_stats.power * m_stats.power * m_skills[skillID]->modifier) /
			target->m_stats.resist;
	}
	else {
		lostHP = m_skills[skillID]->pureDamage +
			(m_stats.strength * m_stats.strength * m_skills[skillID]->modifier) /
			target->m_stats.defense;
	}

	lostHP *= (m_skills[skillID]->heal ? -1 : 1);
	m_skills[skillID]->updateCharges();

	target->getHit(lostHP);
}

void Character::setSkill(int i, pugi::xml_node & node)
{
	if (!m_skills[i].operator bool())
	{
		m_skills[i].reset();
	}
	m_skills[i] = std::make_unique<Skill>(node);
}

Stats const& Character::getStats() const
  {
	  return m_stats;
  }

  Stats const& Character::getBaseStats() const
  {
	  return m_baseStats;
  }

  std::string const& Character::getName() const
  {
	  return m_name;
  }

  Skill* Character::getSkill(int i)
  {
	  return m_skills[i].get();
  }
