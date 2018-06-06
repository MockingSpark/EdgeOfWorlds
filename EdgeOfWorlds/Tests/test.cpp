#include "pch.h"
#include <string>
#include "../GameEngine/GameEngine.h"

TEST(Test00, Test) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCharacter, Xml) {

	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Character c(doc.child("lol").child("Character"));
	EXPECT_EQ(c.getName(), "Bob");
	EXPECT_EQ(c.getStats().HP, 10);
	EXPECT_EQ(c.getStats().defense, 10);
	EXPECT_EQ(c.getStats().strength, 10);
	EXPECT_EQ(c.getStats().power, 10);
	EXPECT_EQ(c.getStats().resist, 10);
	EXPECT_EQ(c.getStats().speed, 10);
	EXPECT_EQ(c.getBaseStats().HP, 10);
	EXPECT_EQ(c.getBaseStats().defense, 10);
	EXPECT_EQ(c.getBaseStats().strength, 10);
	EXPECT_EQ(c.getBaseStats().power, 10);
	EXPECT_EQ(c.getBaseStats().resist, 10);
	EXPECT_EQ(c.getBaseStats().speed, 10);

	EXPECT_EQ(c.getSkill(0)->getName(), "Hit");
	EXPECT_EQ(c.getSkill(1)->getName(), "FireBall");

	EXPECT_EQ(c.getSkill(0)->getStatuts().size(), 1);

	// TODO CharacterTestSuit
}
TEST(TestCharacter, Hit) {

	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Character fighter(doc.child("lol").child("Character")); 

	Character target(doc.child("lol").child("Character2"));

	fighter.hit(0, &target);

	EXPECT_EQ(target.getHP(), 12);
}

TEST(TestCharacter, HitWeak) {

	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Character fighter(doc.child("lol").child("Character"));

	Character target(doc.child("lol").child("Character2"));

	fighter.hit(1, &target);

	EXPECT_EQ(target.getHP(), 7);
}
TEST(TestSkills, Xml) {
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Skill s(doc.child("lol").child("Character").child("Skills").first_child());
	EXPECT_EQ(s.getAccuracy(), 100);
	EXPECT_FALSE(s.isMagical());
	EXPECT_EQ(s.getKnockback(), 0);
	EXPECT_EQ(s.getModifier(), 100);
	EXPECT_EQ(s.getName(), "Hit");
	EXPECT_EQ(s.getPureDamage(), 0);
	EXPECT_EQ(s.getRadius(), 1);
	EXPECT_EQ(s.getRange(), 1);
	EXPECT_FALSE(s.isHealer());
	EXPECT_EQ(s.getCharges(), 1);
	EXPECT_EQ(s.getCost(), 0);
	//TODO : test spawn
}
TEST(TestSkills, Update) {
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Skill s(doc.child("lol").child("Character").child("Skills").first_child().next_sibling());
	s.updateCharges();

	EXPECT_EQ(s.getCharges(), 2);

}

TEST(TestSkills, addToCharacter)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Character c(doc.child("lol").child("Character"));
	c.setSkill(1, doc.child("lol").child("Character").child("Skills").first_child());

	Skill const* s = c.getSkill(1);
	EXPECT_EQ(s->getAccuracy(), 100);
	EXPECT_FALSE(s->isMagical());
	EXPECT_EQ(s->getKnockback(), 0);
	EXPECT_EQ(s->getModifier(), 100);
	EXPECT_EQ(s->getName(), "Hit");
	EXPECT_EQ(s->getPureDamage(), 0);
	EXPECT_EQ(s->getRadius(), 1);
	EXPECT_EQ(s->getRange(), 1);
	EXPECT_FALSE(s->isHealer());
	EXPECT_EQ(s->getCharges(), 1);
	EXPECT_EQ(s->getCost(), 0);
}

TEST(TestEquipement, Construct)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Equipement.xml");

	Equipement e(doc.child("Weapons").child("Equipement"));

	EXPECT_EQ(e.getMunitions(), 1);
	EXPECT_EQ(e.getEquipType(), Equipement::WEAPON);
	EXPECT_EQ(e.getName(), "Infinity Gauntlet");
	EXPECT_EQ(e.getDescription(), "A cute gauntlet with five gemstones on it. It's use is easy as a snap.");
	//bonus stats <Bonus HP="0" strength="14" defense="3" power="10" resistence="3" speed="0"/>
	EXPECT_EQ(e.getBonuses().HP, 0);
	EXPECT_EQ(e.getBonuses().strength, 14);
	EXPECT_EQ(e.getBonuses().defense, 3);
	EXPECT_EQ(e.getBonuses().power, 10);
	EXPECT_EQ(e.getBonuses().resist, 3);
	EXPECT_EQ(e.getBonuses().speed, 0);

	EXPECT_EQ(e.useAttack()->getName(), "Hit");
	EXPECT_EQ(e.useSkill()->getName(), "Half");

}

TEST(TestEquipement, UpdateStats)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("../GameEngine/Player.xml");

	Character c(doc.child("lol").child("Character"));

	pugi::xml_document doc1;
	pugi::xml_parse_result result1 = doc1.load_file("../GameEngine/Equipement.xml");

	c.addEquipement(doc1.child("Weapons").child("Equipement"));
	//bonus stats <Bonus HP="0" strength="14" defense="3" power="10" resistence="3" speed="0"/>

	EXPECT_EQ(c.getStats().HP, 10);
	EXPECT_EQ(c.getStats().defense, 13);
	EXPECT_EQ(c.getStats().strength, 24);
	EXPECT_EQ(c.getStats().power, 20);
	EXPECT_EQ(c.getStats().resist, 13);
	EXPECT_EQ(c.getStats().speed, 10);
	EXPECT_EQ(c.getBaseStats().HP, 10);
	EXPECT_EQ(c.getBaseStats().defense, 10);
	EXPECT_EQ(c.getBaseStats().strength, 10);
	EXPECT_EQ(c.getBaseStats().power, 10);
	EXPECT_EQ(c.getBaseStats().resist, 10);
	EXPECT_EQ(c.getBaseStats().speed, 10);
}

TEST(TestEquipement, Add)
{
	// Disparu dans le pb de Git eu au commit Spoiler Aleeeert ! TODO
}

TEST(TestStatut, Create)
{
	std::string xml(R"(<?xml version = "1.0"?>
<Statut effect="poison" power="10" duration="3"/>
	)");

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xml.c_str());
	Statut s(doc.child("Statut"));

	EXPECT_EQ(s.getEffect(), POISON);
	EXPECT_EQ(s.getPower(), 10);
	EXPECT_FALSE(s.isExpired());
}

TEST(TestStatut, WithCharacter)
{
	std::string xml(R"(<?xml version = "1.0"?>
<Statut effect="poison" power="10" duration="3"/>
	)");

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xml.c_str());
	Statut s(doc.child("Statut"));

	pugi::xml_document doc1;
	pugi::xml_parse_result result1 = doc1.load_file("../GameEngine/Player.xml");

	Character c(doc1.child("lol").child("Character"));

	c.addStatut(s);
	EXPECT_EQ(c.getActiveStatuts().size(), 1);
	EXPECT_EQ(c.getActiveStatuts()[0].getEffect(), POISON);

	for (int i = 1; i <= 3; i++)
	{
		EXPECT_EQ(c.getActiveStatuts().size(), 1);
		c.onTurnEnd();
		EXPECT_EQ(c.getHP(), 10 - i);
	}
	EXPECT_EQ(c.getActiveStatuts().size(), 0);

}