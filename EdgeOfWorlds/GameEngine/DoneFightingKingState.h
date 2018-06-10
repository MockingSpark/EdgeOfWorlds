#pragma once
#include "GameState.h"
class DoneFightingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneFightingKingState state_doneFightingKing;