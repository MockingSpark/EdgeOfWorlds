#include "stdafx.h"
#include "Elements.h"
#include <string>

Weakness  combineWeakness(Weakness const & w1, Weakness const & w2)
{
	if (w1 == W_NONE)
		return w2;
	if (w2 == W_NONE)
		return w1;
	if (w1 == W_ABSORB || w2 == W_ABSORB)
		return W_ABSORB;
	if (w1 == W_IMMUNE || w2 == W_IMMUNE)
		return W_IMMUNE;
	if ((w1 == W_WEAK && w2 == W_RESISTANT) || (w1 == W_RESISTANT && w2 == W_WEAK))
		return W_NONE;
	if (w1 == W_WEAK || w2 == W_WEAK)
		return W_WEAK;
	if (w1 == W_RESISTANT || w2 == W_RESISTANT)
		return W_RESISTANT;
	return W_NONE;
}

int getModifierFromWeakness(Weakness const & w)
{
	switch (w)
	{
	case W_ABSORB:
		return -100;
	case W_IMMUNE:
		return 0;
	case W_RESISTANT:
		return 50;
	case W_WEAK:
		return 150;
	default:
		return 100;
	}
}


std::string stringFromElement(Element const & e)
{
	switch (e)
	{
	case E_FIRE:
		return "fire";
		break;
	case E_WATER:
		return "water";
		break;
	case E_WIND:
		return "wind";
		break;
	case E_THUNDER:
		return "thunder";
		break;
	case E_EARTH:
		return "earth";
		break;
	case E_HOLY:
		return "holly";
		break;
	case E_DARK:
		return "dark";
		break;
	default:
		return "none";
		break;
	}
}


std::string stringFromWeakness(Weakness const & w)
{
	switch (w)
	{
	case W_ABSORB:
		return "absorb";
		break;
	case W_IMMUNE:
		return "immune";
		break;
	case W_RESISTANT:
		return "resistant";
		break;
	case W_WEAK:
		return "weak";
		break;
	default:
		return "none";
		break;
	}
}

Weakness weaknessFromString(std::string const & s)
{
	if (s == "absorb")
	{
		return W_ABSORB;
	}
	if (s == "immune")
	{
		return W_IMMUNE;
	}
	if (s == "none")
	{
		return W_NONE;
	}
	if (s == "resistant")
	{
		return W_RESISTANT;
	}
	if (s == "weak")
	{
		return W_WEAK;
	}
	return W_NONE;
}

Element elementFromString(std::string const & s)
{
	if (s == "fire")
	{
		return E_FIRE;
	}
	if (s == "water")
	{
		return E_WATER;
	}
	if (s == "wind")
	{
		return E_WIND;
	}
	if (s == "thunder")
	{
		return E_THUNDER;
	}
	if (s == "earth")
	{
		return E_EARTH;
	}
	if (s == "holy")
	{
		return E_HOLY;
	}
	if (s == "dark")
	{
		return E_DARK;
	}
	return E_NONE;
}