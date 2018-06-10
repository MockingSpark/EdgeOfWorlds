#pragma once
#include "GameState.h"
class DoneSwitchingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneSwitchingState state_doneSwitching;
