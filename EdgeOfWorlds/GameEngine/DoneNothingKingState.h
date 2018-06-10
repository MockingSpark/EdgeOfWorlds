#pragma once
#include "GameState.h"
class DoneNothingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneNothingKingState state_doneNothingKing;