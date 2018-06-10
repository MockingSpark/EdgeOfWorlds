#pragma once
#include "GameState.h"
class DoneNothingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};


static DoneNothingState state_doneNothing;