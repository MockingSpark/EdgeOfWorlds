#pragma once
#include <pugixml.hpp>


struct Stats {
	Stats(pugi::xml_node node);

	int HP;
	int strength;
	int defense;
	int power;
	int resist;
	int speed;
};