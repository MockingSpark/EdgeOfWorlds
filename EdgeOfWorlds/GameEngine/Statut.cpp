#include "stdafx.h"
#include "Statut.h"


Statut::Statut(StatutEnum const s, int const c, int const pow) :
	m_compteur(c),
	m_needDelete(false),
	m_power(pow),
	m_effect(s)
{
}

Statut::Statut(pugi::xml_node node) :
	m_compteur(node.attribute("duration").as_int()),
	m_needDelete(false),
	m_power((node.attribute("power").as_int()))
{
	m_effect = statutFromString(node.attribute("effect").as_string());
}

std::string Statut::stringFromStatut(StatutEnum t)
{
	switch (t)
	{
	case POISON:
		return "poison";
	case WEAK:
		return "weak";
	case BRITTLE:
		return "brittle";
	case MUTE:
		return "mute";
	case SLOW:
		return "slow";
	case SOFTHEAL:
		return "softHeal";
	case STRONG:
		return "strong";
	case UNBREAKABLE:
		return "unbreakable";
	case QUICK:
		return "quick";
	case FREEZE:
		return "freeze";
	default:
		return "none";
	}
}

StatutEnum Statut::statutFromString(std::string t)
{
	if (t == "poison")
	{
		return POISON;
	}
	if (t == "weak")
	{
		return WEAK;
	}
	if (t == "brittle")
	{
		return BRITTLE;
	}
	if (t == "mute")
	{
		return MUTE;
	}
	if (t == "slow")
	{
		return SLOW;
	}
	if (t == "softHeal")
	{
		return SOFTHEAL;
	}
	if (t == "strong")
	{
		return STRONG;
	}
	if (t == "unbreakable")
	{
		return UNBREAKABLE;
	}
	if (t == "quick")
	{
		return QUICK;
	}
	if (t == "freeze")
	{
		return FREEZE;
	}
	return EFFECT;
}
