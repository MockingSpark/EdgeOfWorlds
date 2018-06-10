#include "stdafx.h"
#include "DoneNothingState.h"
#include "GameEngine.h"
#include "DoneFightingState.h"
#include "DoneMovingState.h"
#include "DoneSwitchingState.h"
#include "EndOfTurnState.h"

bool DoneNothingState::handleInput(GameEngine& e, sf::Event& event)
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
				e.changeState(&state_doneMoving);
			break;
		case sf::Keyboard::LShift:
			map.changeViewSide();
			break;
		case sf::Keyboard::E:
			if (map.makeChangeSide())
			{
				e.changeState(&state_doneSwitching);
				map.changeViewSide();
			}
			break;
		case sf::Keyboard::A:
			e.changeState(&state_endOfTurn);
			break;
		case sf::Keyboard::Numpad0:
			if (map.makeHit(0))
				e.changeState(&state_doneFighting);
			break;
		case sf::Keyboard::Numpad5:
			if (map.makeHit(5))
				e.changeState(&state_doneFighting);
			break;
		case sf::Keyboard::Numpad1:
			if (map.makeHit(1))
				e.changeState(&state_doneFighting);
			break;
		case sf::Keyboard::Numpad2:
			if (map.makeHit(2))
				e.changeState(&state_doneFighting);
			break;
		case sf::Keyboard::Numpad3:
			if (map.makeHit(3))
				e.changeState(&state_doneFighting);
			break;
		case sf::Keyboard::Numpad4:
			if (map.makeHit(4))
				e.changeState(&state_doneFighting);
			break;
		default:
			break;
		}
	}

	return false;
}
