/**
* //////  DoneFightingState.h  //////
*
* Ce fichier constient la classe d'état Done Fighting
*
* \author Cossec Estéban
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

