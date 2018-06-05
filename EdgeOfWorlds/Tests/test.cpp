#include "pch.h"
#include <string>
#include "../GameEngine/GameEngine.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCharacter, Xml) {

	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");
	EXPECT_NE(0, result1);

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

	EXPECT_TRUE(c.getSkill(0));
	EXPECT_TRUE(c.getSkill(1));

	// TODO CharacterTestSuit
}
TEST(TestCharacter, Hit) {

	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");
	EXPECT_NE(0, result1);

	Character fighter(doc.child("lol").child("Character")); 

	Character target(doc.child("lol").child("Character2"));

	fighter.hit(0, &target);

	EXPECT_EQ(target.getHP(), 12);
}
TEST(TestSkills, Xml) {
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");
	EXPECT_NE(0, result1);

	Skill s(doc.child("lol").child("Character").child("Skills").first_child());
	EXPECT_EQ(s.accuracy, 100);
	EXPECT_FALSE(s.isMagical);
	EXPECT_EQ(s.knockback, 0);
	EXPECT_EQ(s.modifier, 100);
	EXPECT_EQ(s.name, "Hit");
	EXPECT_EQ(s.pureDamage, 0);
	EXPECT_EQ(s.radius, 1);
	EXPECT_EQ(s.range, 1);
	EXPECT_FALSE(s.heal);
	EXPECT_EQ(s.getCharges(), 1);
	EXPECT_EQ(s.cost, 0);
	//TODO : test spawn
}
TEST(TestSkills, Update) {
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");
	EXPECT_NE(0, result1);

	Skill s(doc.child("lol").child("Character").child("Skills").first_child().next_sibling());
	s.updateCharges();

	EXPECT_EQ(s.getCharges(), 2);

}

TEST(TestSkills, addToCharacter)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");
	EXPECT_NE(0, result1);

	Character c(doc.child("lol").child("Character"));
	c.setSkill(1, doc.child("lol").child("Character").child("Skills").first_child());

	Skill const* s = c.getSkill(1);
	EXPECT_EQ(s->accuracy, 100);
	EXPECT_FALSE(s->isMagical);
	EXPECT_EQ(s->knockback, 0);
	EXPECT_EQ(s->modifier, 100);
	EXPECT_EQ(s->name, "Hit");
	EXPECT_EQ(s->pureDamage, 0);
	EXPECT_EQ(s->radius, 1);
	EXPECT_EQ(s->range, 1);
	EXPECT_FALSE(s->heal);
	EXPECT_EQ(s->getCharges(), 1);
	EXPECT_EQ(s->cost, 0);
}

TEST(TestEquipement, Construct)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Equipement.xml");
	EXPECT_NE(0, result1);

	Equipement e(doc.child("Weapons").child("Equipement"));

}