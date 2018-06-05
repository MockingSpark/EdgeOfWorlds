#pragma once
#include <vector>
#include <memory>
#include "PersoDefines.h"
#include "mapDefines.h" 
#include "pugixml.hpp"
#include "Skill.h"
#include "Equipement.h"

#define NB_SKILLS 4

class Status;

class Character
{
public:
	Character() = delete;

	Character( pugi::xml_node& );
	Character(pugi::xml_node&, int const);

	void  getHit(int const);
	void  hit(int const& , Character* ) const;
	//void  addStatus   (std::string const);
	//void  removeStatus(std::string const);

	void setSkill( int, pugi::xml_node& );
	void updateStats();
	void addEquipement(pugi::xml_node&);

	Stats       const& getStats()      const;
	Stats       const& getBaseStats()  const;
	std::string const& getName()       const;
	Skill		const* getSkill(int)   const;
	Equipement	const* getEquipement(Equipement::EquipType)	const;
	int const & getHP() const;


protected:
	std::string m_name;
	int m_level;
	int m_actualHP;
	std::unique_ptr<Skill> m_skills[NB_SKILLS];
	std::unique_ptr<Equipement> m_equipements[3];
	//std::vector<Status> m_activeStatus;
	Stats m_stats;
	Stats m_baseStats;

	void onDeath() {};
	void onHit() {};


};