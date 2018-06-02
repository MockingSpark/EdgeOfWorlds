#pragma once
#include <vector>
#include <memory>
#include "PersoDefines.h"
#include "mapDefines.h" 

class Skill;
class Status;

class Character
{
public:
	Character() = delete;

	void getHit(int, OnHitFlag = 0);
	int hit(std::weak_ptr<Skill>);
	void addStatus(std::string);
	void removeStatus(std::string);

protected:
	std::string m_name;
	std::shared_ptr<Skill> m_skills[6];   // on utilise des shared ptr pour des 
										  // raisons de stoquage : les skills
										  // utilisés sont instanciés UNE fois
	std::vector<Status> m_activeStatus;
	stats m_stats;
	int m_PV;
	int m_PM;


};