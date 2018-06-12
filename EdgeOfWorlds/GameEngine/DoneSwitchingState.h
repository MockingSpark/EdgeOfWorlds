/**
* //////  DoneSwitchingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Switching
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"
class DoneSwitchingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneSwitchingState state_doneSwitching;
