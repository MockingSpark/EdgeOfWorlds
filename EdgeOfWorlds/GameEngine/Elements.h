#pragma once
#include <string>

#define NB_ELEMENTS 8

enum Element {
	E_FIRE = 0,
	E_WATER = 1,
	E_WIND = 2,
	E_THUNDER = 3,
	E_EARTH = 4,
	E_HOLY = 5,
	E_DARK = 6,
	E_NONE = 7
};

enum Weakness {
	W_NONE,
	W_WEAK,
	W_RESISTANT,
	W_IMMUNE,
	W_ABSORB,
};

std::string stringFromElement(Element const &);
Element elementFromString(std::string const &);

std::string stringFromWeakness(Weakness const &);
Weakness weaknessFromString(std::string const &);

Weakness combineWeakness(Weakness const &, Weakness const &);
int getModifierFromWeakness(Weakness const &);

