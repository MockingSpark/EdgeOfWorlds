#include "stdafx.h"
#include "PersoDefines.h"

Stats::Stats(pugi::xml_node node) :
	HP(node.attribute("HP").as_int()),
	strength(node.attribute("strength").as_int()),
	defense(node.attribute("defense").as_int()),
	power(node.attribute("power").as_int()),
	resist(node.attribute("resistence").as_int()),
	speed(node.attribute("speed").as_int())
{
}
