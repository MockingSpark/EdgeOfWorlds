/**
* //////  DoneSwitchingState.h  //////
*
* Ce fichier constient la classe d'état Done Switching
*
* \author Cossec Estéban
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
