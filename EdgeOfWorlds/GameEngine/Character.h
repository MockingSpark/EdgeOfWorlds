#pragma once
#include <vector>
#include <memory>
#include "PersoDefines.h"
#include "mapDefines.h" 
#include "pugixml.hpp"

class Skill;
class Status;

class Character
{
public:
	Character() = delete;

	Character( std::string,
		       int, int, int, int, int, int);	// constructeur de débug. TO DELETE

	Character( pugi::xml_node ); //TODO

	void  getHit(int const, OnHitFlag const = 0);
	void  hit(int const& , Character* ) const;
	//void  addStatus   (std::string const);
	//void  removeStatus(std::string const);

	Stats       const& getStats()      const;
	Stats       const& getBaseStats()  const;
	std::string const& getName()       const;


protected:
	std::string m_name;
	//std::unique_ptr<Skill> m_skills[6];
	//std::vector<Status> m_activeStatus;
	Stats m_stats;
	Stats m_baseStats;


};