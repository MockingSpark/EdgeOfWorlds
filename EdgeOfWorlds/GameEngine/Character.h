#pragma once
#include <vector>
#include <memory>
#include "PersoDefines.h"
#include "mapDefines.h" 
#include "pugixml.hpp"
#include "Skill.h"
#include "Equipement.h"
#include "Statut.h"
#include "Elements.h"
#include <SFML/Graphics.hpp>

#define NB_SKILLS 4



class Character
{
public:

	enum Team {
		RED,
		BLUE
	};

	Character() = delete;

	Character( pugi::xml_node& );
	//Character(pugi::xml_node&, int const);

	void  getHit(int const);
	void  hit(int const& , Character* );

	void setSkill( int, pugi::xml_node& );
	void updateStats();
	void addEquipement(pugi::xml_node&);
	void addStatut(Statut);
	void setTeam(Team t) { m_team = t; };

	void onDeath();
	void onHit() {};
	void onTurnEnd();

	Stats const & getStats() const;
	Stats const & getBaseStats() const;
	std::string const & getName() const;
	Skill const * getSkill(int) const;
	Equipement const * getEquipement(Equipement::EquipType) const;
	int const & getHP() const;
	std::vector<Statut> const & getActiveStatuts() const;
	int const getIncreaseness(Element) const;
	Team const & getTeam() const { return m_team; };
	bool isDead() const { return m_dead; };

protected:
	std::string m_name;
	int m_level;
	int m_actualHP;
	std::unique_ptr<Skill> m_skills[NB_SKILLS +2]; // nb skills + 2 base attck
	std::unique_ptr<Equipement> m_equipements[3]; 
	std::vector<Statut> m_activeStatuts;
	Stats m_stats;
	Stats m_baseStats;
	Weakness m_weaknesses[NB_ELEMENTS];
	Weakness m_baseWeaknesses[NB_ELEMENTS];

	Team m_team = RED;
	bool m_dead = false;



private:
	
	void applyUniqueStatut(int i);

	void effect(int) {};
	void poison(int);
	void weak(int);
	void brittle(int);
	void mute(int);
	void slow(int);
	void softHeal(int);
	void strong(int);
	void unbreakable(int);
	void quick(int);
	void freeze(int);

	// Graphic Management :
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Sprite m_spriteGohst;
	sf::Texture m_textureGohst;
	int m_animationLine = 8; int m_animationIterator = 0;
	int m_spriteWidth, m_spriteHeight;

public:
	void draw(sf::RenderTarget & t);
	void drawGohst(sf::RenderTarget & t);

	void setPosition(sf::Vector2f v);

	void setTexture();

	void update();

	void move(Direction);

	void HitAnimation(Direction);

	void die();

	void changeDirection(Direction);
};
