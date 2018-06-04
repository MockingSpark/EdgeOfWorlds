#include "pch.h"
#include <string>
#include "../GameEngine/Character.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCharacter, TestConstruct) { // teste la construction du character
	Character c("nom", 10, 10, 10, 10, 10, 10);
	EXPECT_EQ(c.getName(), "nom");
	EXPECT_EQ(c.getStats().HP, 10);
	EXPECT_EQ(c.getStats().Defense, 10);
	EXPECT_EQ(c.getStats().Strength, 10);
	EXPECT_EQ(c.getStats().Power, 10);
	EXPECT_EQ(c.getStats().Resist, 10);
	EXPECT_EQ(c.getStats().Speed, 10);
	EXPECT_EQ(c.getBaseStats().HP, 10);
	EXPECT_EQ(c.getBaseStats().Defense, 10);
	EXPECT_EQ(c.getBaseStats().Strength, 10);
	EXPECT_EQ(c.getBaseStats().Power, 10);
	EXPECT_EQ(c.getBaseStats().Resist, 10);
	EXPECT_EQ(c.getBaseStats().Speed, 10);

	// TODO

}

TEST(TestCharacter, TestHit) {
	Character fighter("nom", 10, 10, 10, 10, 10, 10);
	Character target ("nom", 22, 10, 10, 10, 10, 10);

	fighter.hit(0, &target);

	EXPECT_EQ(target.getStats().HP, 12);
}

TEST(TestCharacter, TestXml) {
	std::string xml(R"~(<?xml version="1.0"?>
		<Character name="Bob" HP="10" strength="10" defense="10" power="10" resistence="10" speed="10"/>)~");

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xml.c_str());
	EXPECT_NE(0, result);

	Character c(doc.child("Character"));
	EXPECT_EQ(c.getName(), "Bob");
	EXPECT_EQ(c.getStats().HP, 10);
	EXPECT_EQ(c.getStats().Defense, 10);
	EXPECT_EQ(c.getStats().Strength, 10);
	EXPECT_EQ(c.getStats().Power, 10);
	EXPECT_EQ(c.getStats().Resist, 10);
	EXPECT_EQ(c.getStats().Speed, 10);
	EXPECT_EQ(c.getBaseStats().HP, 10);
	EXPECT_EQ(c.getBaseStats().Defense, 10);
	EXPECT_EQ(c.getBaseStats().Strength, 10);
	EXPECT_EQ(c.getBaseStats().Power, 10);
	EXPECT_EQ(c.getBaseStats().Resist, 10);
	EXPECT_EQ(c.getBaseStats().Speed, 10);

	// TODO
}