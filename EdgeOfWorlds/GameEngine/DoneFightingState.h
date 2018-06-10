#pragma once
#include "GameState.h"
class DoneFightingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneFightingState state_doneFighting;

