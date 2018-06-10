#pragma once
#include "GameState.h"
class DoneMovingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneMovingState state_doneMoving;