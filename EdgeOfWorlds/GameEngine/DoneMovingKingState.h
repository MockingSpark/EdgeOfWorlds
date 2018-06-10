#pragma once
#include "GameState.h"
class DoneMovingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneMovingKingState state_doneMovingKing;