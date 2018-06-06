#include "stdafx.h"
#include "Skill.h"

Skill::Skill(pugi::xml_node node) :
	name(node.attribute("name").as_string()),
	knockback(node.attribute("knockback").as_int()),
	modifier(node.attribute("modifier").as_int()),
	pureDamage(node.attribute("pureDamage").as_int()),
	isMagical(node.attribute("isMagical").as_bool()),
	range(node.attribute("range").as_int()),
	radius(node.attribute("radius").as_int()),
	accuracy(node.attribute("accuracy").as_int()),
	heal(node.attribute("heal").as_bool()),
	cost(node.attribute("cost").as_int()),
	m_maxCharges(node.attribute("charges").as_int()),
	m_charges(node.attribute("charges").as_int())/*,
	spawn(node.child("Spawn"))*/
{

	for (auto n : node.children("Statut"))
	{
		statuts.push_back(Statut(n));
	}
}
