#pragma once
#include "PersoDefines.h"
#include <pugixml.hpp>

class Statut
{
private:
	std::string stringFromStatut(StatutEnum t);
	StatutEnum statutFromString(std::string t);
public:
	Statut(StatutEnum s, int c, int pow);
	Statut(pugi::xml_node);
	void update() { if (m_compteur > 0) { m_compteur--; } if (m_compteur == 0) { m_needDelete = true; } };
	bool const & isExpired() const { return m_needDelete; };

	StatutEnum const & getEffect() const { return m_effect; };
	int const & getPower() const { return m_power; };
	
private:
	int m_power;
	StatutEnum m_effect;
	int m_compteur;
	bool m_needDelete;
};