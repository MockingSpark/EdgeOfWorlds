#pragma once
#include <string>
#include "PersoDefines.h"
#include "Skill.h"

class Equipement
{
public:

	enum EquipType {
		ARMOR = 0,
		WEAPON = 1,
		MISC = 2,
	};

	static EquipType equipTypeFromString(std::string);
	static std::string stringFromEquipType(EquipType);

	Equipement(pugi::xml_node&);

	Skill const * useAttack();
	Skill const * useSkill();

	Stats const & getBonuses() const;
	std::string const & getName() const;
	int const & getMunitions() const;
	EquipType const & getEquipType() const;
	std::string const & getDescription() const;
	Weakness const & getWeakness(Element e) const { return m_weaknesses[e]; };
	int const & getIncreaseness(Element e) const { return m_increases[e]; };

private:
	std::string m_name;
	Stats m_bonus;
	std::unique_ptr<Skill> m_attack;
	std::unique_ptr<Skill> m_skill;
	int m_munitions;
	EquipType m_type;
	std::string m_description;
	Weakness m_weaknesses[NB_ELEMENTS];
	int m_increases[NB_ELEMENTS];

};

