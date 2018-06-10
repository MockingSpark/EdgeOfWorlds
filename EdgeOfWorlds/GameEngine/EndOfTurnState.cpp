#include "stdafx.h"
#include "EndOfTurnState.h"

#include "GameEngine.h"

bool EndOfTurnState::handleInput(GameEngine & e, sf::Event & event)
{

	Map& map = e.getMap();

	if (event.type == sf::Event::Closed)
		return true;
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Z:
			map.makeChangeDirection(UP);
			e.endOfTurn();
			break;
		case sf::Keyboard::S:
			map.makeChangeDirection(DOWN);
			e.endOfTurn();
			break;
		case sf::Keyboard::Q:
			map.makeChangeDirection(LEFT);
			e.endOfTurn();
			break;
		case sf::Keyboard::D:
			map.makeChangeDirection(RIGHT);
			e.endOfTurn();
			break;
		case sf::Keyboard::LShift:
			map.changeViewSide();
			break;
		default:
			break;
		}
	}

	return false;
}
