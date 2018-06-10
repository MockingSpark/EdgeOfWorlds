#include "stdafx.h"
#include "DoneFightingState.h"

#include "GameEngine.h"
#include "EndOfTurnState.h"

bool DoneFightingState::handleInput(GameEngine& e, sf::Event& event)
{
	Map& map = e.getMap();

	if (event.type == sf::Event::Closed)
		return true;
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Z:
			map.moveCursor(UP);
			break;
		case sf::Keyboard::S:
			map.moveCursor(DOWN);
			break;
		case sf::Keyboard::Q:
			map.moveCursor(LEFT);
			break;
		case sf::Keyboard::D:
			map.moveCursor(RIGHT);
			break;
		case sf::Keyboard::Space:
			if (map.makeMove())
			{
				e.updateHelper(false, false, false);
				e.changeState(&state_endOfTurn);
			}
			break;
		case sf::Keyboard::LShift:
			map.changeViewSide();
			break;
		case sf::Keyboard::A:
			e.changeState(&state_endOfTurn);
			e.updateHelper(false, false, false);
			break;
		case sf::Keyboard::E:
			if (map.makeChangeSide()) {
				e.changeState(&state_endOfTurn);
				e.updateHelper(false, false, false);
				map.changeViewSide();
			}
			break;
		default:
			break;
		}
	}

	return false;
}
