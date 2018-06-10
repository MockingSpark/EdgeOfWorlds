#include "stdafx.h"
#include <pugixml.hpp>
#include "GameEngine.h"
#include <windows.h>

#include "DoneNothingState.h"
#include "DoneNothingKingState.h"



GameEngine::GameEngine() :
	m_map("..\\Assets\\maps\\exampleMap.tmx"),
	m_state(&state_doneNothing),
	m_window(sf::VideoMode(1800, 920), "SFML window")
{
	m_mapTexture.create(1800, 900);

	initialise();
}

void GameEngine::initialise()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("../GameEngine/Player.xml");

	Position pos{ 5, 5, TECH };

	pugi::xml_node node = doc.child("lol").child("Character");

	m_redPlayers.push_back(Character(node));
	m_redPlayers[0].setTexture();

	m_map.addCharacter(&m_redPlayers[0], pos);

	Position pos2{ 3, 9, TECH };

	pugi::xml_node node2 = doc.child("lol").child("Character2");

	m_bluePlayers.push_back(Character(node2));

	m_bluePlayers[0].setTeam(Character::BLUE);
	m_bluePlayers[0].setTexture();

	m_map.addCharacter(&m_bluePlayers[0], pos2);

	m_map.nextPlayer(&m_redPlayers[0]);

	m_card.initialise(&m_bluePlayers[0]);

	m_helper.initialise(&m_redPlayers[0]);
	m_helper.setPosition(sf::Vector2f(200., 700.));

	endOfTurn();

}

int GameEngine::run()
{
	
	m_card.setPosition(sf::Vector2f( 60., 60.));


	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (m_state->handleInput(*this, event ) ) {
				m_window.close();
			}
		}


		m_mapTexture.clear();
		m_map.draw(m_mapTexture);
		m_mapTexture.display();

		m_window.clear(sf::Color::Black);
		m_mapSprite.setTexture(m_mapTexture.getTexture());
		m_window.draw(m_mapSprite);

		m_card.update();
		m_card.draw(m_window);

		m_helper.draw(m_window);

		Sleep(180);

		m_window.display();
	}
	return EXIT_SUCCESS;
}

void GameEngine::changeState(GameState *state)
{
	m_state = state;
}

void GameEngine::endOfTurn()
{
	if (!isOver())
	{
		switch (m_currentTeam)
		{
		case Character::RED:
			do {
				m_blueIterator++;
				m_blueIterator %= m_bluePlayers.size();
			} while (m_bluePlayers[m_blueIterator].isDead());
			m_currentTeam = Character::BLUE;
			m_map.nextPlayer(&m_bluePlayers[m_blueIterator]);
			if (m_blueIterator == m_blueKing) {
				updateHelper(true, false, true);
				changeState(&state_doneNothingKing);
			}
			else {
				updateHelper();
				changeState(&state_doneNothing);
			}
			break;
		case Character::BLUE:
			do {
				m_redIterator++;
				m_redIterator %= m_redPlayers.size();
			} while (m_redPlayers[m_redIterator].isDead());
			m_currentTeam = Character::RED;
			m_map.nextPlayer(&m_redPlayers[m_redIterator]);
			if (m_redIterator == m_redKing) {
				changeState(&state_doneNothingKing);
				updateHelper(true, false);
			}
			else {
				updateHelper();
				changeState(&state_doneNothing);
			}
			break;
		}
	}
	else {
		gameOver();
	}
	
}


bool GameEngine::isOver()
{
	bool noMoreBlue = true;
	bool noMoreRed = true;
	for (auto & ch : m_redPlayers)
	{
		if (!ch.isDead())
			noMoreRed = false;
	}
	for (auto & ch : m_bluePlayers)
	{
		if (!ch.isDead())
			noMoreBlue = false;
	}
	return noMoreBlue || noMoreRed;
}
