#pragma once

#include "Character.h"
#include "Map.h"
#include "mapDefines.h"
#include "PersoDefines.h"
#include "Skill.h"
#include "skillDefine.h"
#include "Elements.h"
#include "GameState.h"
#include "IdCard.h"
#include "Helper.h"

class GameEngine final
{
public:

	GameEngine();

	int run(); 
	Map& getMap() { return m_map; };

	void changeState(GameState*);

	void endOfTurn(); //< Update the state 

	void initialise();

	void gameOver() { initialise(); };

	void updateHelper(bool move = true, bool change = true, bool attack = true) { m_helper.update(move, change, attack); };

private:

	bool isOver();

private:

	Map m_map;
	sf::RenderTexture m_mapTexture;
	sf::Sprite m_mapSprite;
	sf::RenderWindow m_window;

	GameState* m_state; //< Predicate : is ptr on static object so it is OK

	std::vector<Character> m_redPlayers;
	std::vector<Character> m_bluePlayers;

	int m_blueIterator = 0;
	int m_redIterator = 0;

	int m_blueKing = 0;
	int m_redKing = 0;

	Character::Team m_currentTeam;

	//cards
	IdCard m_card;


	Helper m_helper;


};
