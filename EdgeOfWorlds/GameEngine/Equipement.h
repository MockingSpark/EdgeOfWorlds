#pragma once
#include <string>
#include "PersoDefines.h"
#include "Skill.h"

class Equipement
{
public:

	Skill const * useAttack();
	Skill const * useSkill();
private:
	std::string m_nom;
	Stats m_bonus;
	// Elements m_element;
	std::unique_ptr<Skill> effect[2];  // la prime attaque & la capacit� d'arme.
	int munitions;

};

