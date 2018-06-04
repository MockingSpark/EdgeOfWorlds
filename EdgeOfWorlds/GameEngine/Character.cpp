#include "stdafx.h"
#include "Character.h"
/**
  * 
  */

Character::Character(std::string s , int PV, int st, int def, int pow, int res, int sp) :
	m_name(s),
	m_stats{PV, st, def, pow, res, sp},
	m_baseStats{PV, st, def, res, pow, sp}
{
}

Character::Character(pugi::xml_node node) :
	m_name(node.attribute("name").as_string()),
	m_stats{
		node.attribute("HP").as_int(),
		node.attribute("strength").as_int(),
		node.attribute("defense").as_int(),
		node.attribute("power").as_int(),
		node.attribute("resistence").as_int(),
		node.attribute("speed").as_int(),
    },
	m_baseStats{
		node.attribute("PV").as_int(),
		node.attribute("strength").as_int(),
		node.attribute("defense").as_int(),
		node.attribute("power").as_int(),
		node.attribute("resistence").as_int(),
		node.attribute("speed").as_int(),
	}
{
}

void Character::getHit(int const attPower, OnHitFlag const f)
{
	// TODO : flags

	m_stats.HP -= attPower / m_stats.Defense;
	m_stats.HP = (m_stats.HP < 0) ? 0 :
		  ((m_stats.HP > m_baseStats.HP) ? m_stats.HP :
			  m_stats.HP);
}

  void Character::hit(int const&, Character * target) const
  {
	  // For tests, TODO when skills OK
	  target->getHit(m_stats.Power * m_stats.Power);
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
