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
	m_baseStats{ node.child("Stats") },
	m_actualHP(node.child("Stats").attribute("HP").as_int())
{

	int i(0);
	for (auto & n : node.child("Skills").children())
	{
		m_skills[i] = std::make_unique<Skill>(n);
		i++;
	}
	pugi::xml_node n = node.child("Equipement");
	addEquipement(n);

	updateStats();

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

	m_actualHP -= attPower;
	if (m_actualHP > m_baseStats.HP)
	{
		m_actualHP = m_baseStats.HP;
	}
	else if (m_actualHP <= 0)
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

	if (m_skills[skillID]->isMagical && m_stats.power != 0){
		lostHP = m_skills[skillID]->pureDamage +
			(m_stats.power * m_stats.power * m_skills[skillID]->modifier) /
			target->m_stats.resist /
			100;	// les 100 du modifier en pourcentage
	}
	else if (m_skills[skillID]->isMagical) {
		lostHP = 0;
	}
	else {
		lostHP = m_skills[skillID]->pureDamage +
			(m_stats.strength * m_stats.strength * m_skills[skillID]->modifier) /
			target->m_stats.defense /
			100;	// les 100 du modifier en pourcentage
	}

	for (auto & s : m_skills[skillID]->statut)
	{
		target->m_activeStatuts.emplace_back(s);
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

void Character::updateStats()
{

	m_stats = m_baseStats;
	for (auto & i : m_activeStatuts)
	{
		if (!(i.getEffect() == SOFTHEAL || i.getEffect() == POISON))
		{
			applyUniqueStatut(i.getEffect());
		}
	}
	for (auto & i : m_equipements)
	{
		if (i.operator bool())
			m_stats += i->getBonuses();
	}
	m_actualHP = (m_stats.HP < m_actualHP) ? m_stats.HP : m_actualHP;

}

void Character::addEquipement(pugi::xml_node & node)
{
	Equipement::EquipType type = Equipement::equipTypeFromString(node.attribute("equipType").as_string());
	m_equipements[type].reset(new Equipement(node));
	updateStats();
}

void Character::addStatut(Statut s)
{
	m_activeStatuts.push_back(s);
}

void Character::onTurnEnd()
{
	int j = 0;
	for (auto & i : m_activeStatuts)
	{
		if (i.getEffect() == SOFTHEAL || i.getEffect() == POISON)
		{
			applyUniqueStatut(j);
		}
		i.update();
		if (i.isExpired())
		{
			m_activeStatuts.erase(m_activeStatuts.begin()+j);
		}
		j++;
	}
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

  Skill const * Character::getSkill(int i) const // précond. 0 <= i < 6
  {
	  return m_skills[i].get();
  }

  Equipement const * Character::getEquipement(Equipement::EquipType t) const
  {
	  return m_equipements[t].get();
  }

  int const & Character::getHP() const
  {
	  return m_actualHP;
  }

  std::vector<Statut> const & Character::getActiveStatuts() const
  {
	  return m_activeStatuts;
  }

  void Character::applyUniqueStatut(int i)
  {
	  int pow = m_activeStatuts[i].getPower();
	  switch (m_activeStatuts[i].getEffect()) {
	  case POISON:
		  poison(pow);
		  break;
	  case WEAK:
		  weak(pow);
		  break;
	  case BRITTLE:
		  brittle(pow);
		  break;
	  case MUTE:
		  mute(pow);
		  break;
	  case SLOW:
		  slow(pow);
		  break;
	  case SOFTHEAL:
		  softHeal(pow);
		  break;
	  case STRONG:
		  strong(pow);
		  break;
	  case UNBREAKABLE:
		  unbreakable(pow);
		  break;
	  case QUICK:
		  quick(pow);
		  break;
	  case FREEZE:
		  freeze(pow);
		  break;
	  default:
		  effect(pow);
		  break;
	  }
  }

  void Character::poison(int p)
  {
	  m_actualHP -= p * m_stats.HP / 100;
  }

  void Character::weak(int p)
  {
	  m_stats.strength -= p * m_stats.strength / 100;
  }

  void Character::brittle(int p)
  {
	  m_stats.defense -= p * m_stats.defense / 100;
  }

  void Character::mute(int p)
  {
	  m_stats.power = 0;
  }

  void Character::slow(int p)
  {
	  m_stats.speed -= p * m_stats.speed / 100;
  }

  void Character::softHeal(int p)
  {
	  m_actualHP += p * m_stats.HP / 100;
  }

  void Character::strong(int p)
  {
	  m_stats.strength += p * m_stats.strength / 100;
  }

  void Character::unbreakable(int p)
  {
	  m_stats.defense += p * m_stats.defense / 100;
  }

  void Character::quick(int p)
  {
	  m_stats.speed += p * m_stats.speed / 100;
  }

  void Character::freeze(int)
  {
	  m_stats.speed = 0;
  }
