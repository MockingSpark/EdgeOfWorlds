#pragma once
#include <vector>
#include <memory>
#include "PersoDefines.h"
#include "mapDefines.h" 
#include "pugixml.hpp"
#include "Skill.h"
#include "Equipement.h"
#include "Statut.h"

#define NB_SKILLS 4


class Character
{
public:
	Character() = delete;

	Character( pugi::xml_node& );
	//Character(pugi::xml_node&, int const);

	void  getHit(int const);
	void  hit(int const& , Character* ) const;
	//void  addStatus   (std::string const);
	//void  removeStatus(std::string const);

	void setSkill( int, pugi::xml_node& );
	void updateStats();
	void addEquipement(pugi::xml_node&);
	void addStatut(Statut);

	void onDeath() {};
	void onHit() {};
	void onTurnEnd();

	Stats const & getStats() const;
	Stats const & getBaseStats() const;
	std::string const & getName() const;
	Skill const * getSkill(int) const;
	Equipement const * getEquipement(Equipement::EquipType) const;
	int const & getHP() const;
	std::vector<Statut> const & getActiveStatuts() const;

protected:
	std::string m_name;
	int m_level;
	int m_actualHP;
	std::unique_ptr<Skill> m_skills[NB_SKILLS]; // TODO : revoir le stoquage des skills après le changement d'archi.
	std::unique_ptr<Equipement> m_equipements[3]; 
	std::vector<Statut> m_activeStatuts;
	Stats m_stats;
	Stats m_baseStats;




private:
	
	void applyUniqueStatut(int i);

	void effect(int) {};
	void poison(int);
	void weak(int);
	void brittle(int);
	void mute(int);
	void slow(int);
	void softHeal(int);
	void strong(int);
	void unbreakable(int);
	void quick(int);
	void freeze(int);

};
