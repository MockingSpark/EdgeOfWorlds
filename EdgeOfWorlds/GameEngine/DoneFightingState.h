/**
* //////  DoneFightingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Fighting
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"
class DoneFightingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneFightingState state_doneFighting;

