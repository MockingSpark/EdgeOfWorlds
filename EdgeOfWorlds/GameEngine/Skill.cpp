#include "stdafx.h"
#include "Skill.h"

Skill::Skill(pugi::xml_node node) :
	m_name(node.attribute("name").as_string()),
	m_knockback(node.attribute("knockback").as_int()),
	m_modifier(node.attribute("modifier").as_int()),
	m_pureDamage(node.attribute("pureDamage").as_int()),
	m_magical(node.attribute("isMagical").as_bool()),
	m_range(node.attribute("range").as_int()),
	m_radius(node.attribute("radius").as_int()),
	m_accuracy(node.attribute("accuracy").as_int()),
	m_heal(node.attribute("heal").as_bool()),
	m_cost(node.attribute("cost").as_int()),
	m_maxCharges(node.attribute("charges").as_int()),
	m_charges(node.attribute("charges").as_int()),
	m_element(E_NONE)/*,
	spawn(node.child("Spawn"))*/
{
	m_element = elementFromString(node.attribute("element").as_string());
	for (auto n : node.children("Statut"))
	{
		m_statuts.push_back(Statut(n));
	}
}
