#include "stdafx.h"
#include <pugixml.hpp>
#include "GameEngine.h"
#include <windows.h>
#include <iostream>

#include "DoneNothingState.h"
#include "DoneNothingKingState.h"



GameEngine::GameEngine() :
	m_map("..\\Assets\\maps\\exampleMap.tmx"),
	m_state(&state_doneNothing),
	m_window(sf::VideoMode(1900, 920), "SFML window")
{
	m_mapTexture.create(1900, 920);
	m_helper.setPosition(sf::Vector2f(250., 700.));
	m_mapSprite.setPosition(sf::Vector2f(310., 0.));

	initialise();
}

void GameEngine::initialise()
{
	m_map.resetMap();

	m_bluePlayers.clear();
	m_redPlayers.clear();

	pugi::xml_document doc;
	pugi::xml_parse_result result1 = doc.load_file("d:/Programmation/JIN/EdgeOfWorlds/EdgeOfWorlds/GameEngine/Level.xml");

	if (!result1)
	{
		std::cout << result1.description() << std::endl;
	}


	pugi::xml_node redNode = doc.child("Level").child("RED");
	pugi::xml_node blueNode = doc.child("Level").child("BLUE");

	m_redPlayers.push_back(std::make_unique<Character>(redNode.child("King")));
	Position posRedKing{ redNode.child("King").attribute("x").as_int(),
		redNode.child("King").attribute("y").as_int(), TECH };
	std::string sideRedKing = redNode.child("King").attribute("s").as_string();
	if (sideRedKing == "medieval")
		posRedKing.side = MEDIEVAL;
	else
		posRedKing.side = TECH;
	m_redKing = 0;
	m_map.addCharacter(m_redPlayers.back().get(), posRedKing);
	m_redPlayers.back()->setTeam(Character::RED);
	m_redPlayers.back()->setTexture();

	m_cards.push_back(std::make_unique<IdCard>());
	m_cards.back()->initialise(m_redPlayers.back().get());
	m_cards.back()->setPosition(sf::Vector2f(0., 100.));
	m_cards.back()->setRight();

	m_bluePlayers.push_back(std::make_unique<Character>(blueNode.child("King")));
	Position posBlueKing{ blueNode.child("King").attribute("x").as_int(),
		blueNode.child("King").attribute("y").as_int(), TECH };
	std::string sideBlueKing = blueNode.child("King").attribute("s").as_string();
	if (sideBlueKing == "medieval")
		posBlueKing.side = MEDIEVAL;
	else
		posBlueKing.side = TECH;
	m_blueKing = 0;
	m_map.addCharacter(m_bluePlayers.back().get(), posBlueKing);
	m_bluePlayers.back()->setTeam(Character::BLUE);
	m_bluePlayers.back()->setTexture();

	m_cards.push_back(std::make_unique<IdCard>());
	m_cards.back()->initialise(m_bluePlayers.back().get());
	m_cards.back()->setPosition(sf::Vector2f(m_window.getSize().x - 307.f, 100.f));
	m_cards.back()->setLeft();

	int i = 1;
	for (auto& n : blueNode.children("Character"))
	{
		m_bluePlayers.push_back(std::make_unique<Character>(n));
		Position posBlue{ n.attribute("x").as_int(),
			n.attribute("y").as_int(), TECH };
		std::string sideBlue = n.attribute("s").as_string();
		if (sideBlue == "medieval")
			posBlue.side = MEDIEVAL;
		else
			posBlue.side = TECH;
		m_map.addCharacter(m_bluePlayers.back().get(), posBlue);
		m_bluePlayers.back()->setTeam(Character::BLUE);
		m_bluePlayers.back()->setTexture();

		m_cards.push_back(std::make_unique<IdCard>());
		m_cards.back()->initialise(m_bluePlayers.back().get());
		m_cards.back()->setPosition(sf::Vector2f(m_window.getSize().x - 307.f, 100.f + i*(130)));
		m_cards.back()->setLeft();
		i++;
	}
	i = 1;
	for (auto& n : redNode.children("Character"))
	{
		m_redPlayers.push_back(std::make_unique<Character>(n));
		Position posRed{ n.attribute("x").as_int(),
			n.attribute("y").as_int(), TECH };
		std::string sideRed = n.attribute("s").as_string();
		if (sideRed == "medieval")
			posRed.side = MEDIEVAL;
		else
			posRed.side = TECH;
		m_map.addCharacter(m_redPlayers.back().get(), posRed);
		m_redPlayers.back()->setTeam(Character::RED);
		m_redPlayers.back()->setTexture();

		m_cards.push_back(std::make_unique<IdCard>());
		m_cards.back()->initialise(m_redPlayers.back().get());
		m_cards.back()->setPosition(sf::Vector2f(0.f, 100. + i*(130.f)));
		m_cards.back()->setRight();
		i++;
	}

	m_currentTeam = Character::RED;
	m_map.nextPlayer(m_redPlayers.front().get());
	m_helper.initialise(m_redPlayers.front().get());

	if (0 == m_redKing) {
		updateHelper(true, false, true);
		changeState(&state_doneNothingKing);
	}
	else {
		updateHelper();
		changeState(&state_doneNothing);
	}



	endOfTurn();

}

int GameEngine::run()
{

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

		for (auto & card : m_cards)
		{
			card->update();
			card->draw(m_window);
		}

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
			} while (m_bluePlayers[m_blueIterator]->isDead());
			m_currentTeam = Character::BLUE;
			m_map.nextPlayer(m_bluePlayers[m_blueIterator].get());
			m_helper.changeCharacter(m_bluePlayers[m_blueIterator].get());
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
			} while (m_redPlayers[m_redIterator]->isDead());
			m_currentTeam = Character::RED;
			m_map.nextPlayer(m_redPlayers[m_redIterator].get());
			m_helper.changeCharacter(m_redPlayers[m_redIterator].get());
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
		if (!ch->isDead())
			noMoreRed = false;
	}
	for (auto & ch : m_bluePlayers)
	{
		if (!ch->isDead())
			noMoreBlue = false;
	}
	return noMoreBlue || noMoreRed;
}
