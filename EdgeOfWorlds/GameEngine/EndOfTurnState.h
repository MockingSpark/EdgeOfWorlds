#pragma once
#include "GameState.h"
class EndOfTurnState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};


static EndOfTurnState state_endOfTurn;