#pragma once

#include "Map.h"
#include "Character.h"

class GameEngine;

class GameState
{
public:
	


public:
	virtual bool handleInput(GameEngine&, sf::Event&) = 0; //< \return true if the window has to be closed

protected:
};

