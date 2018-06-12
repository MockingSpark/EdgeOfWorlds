/**
* //////  DoneFightingKingState.h  //////
*
* Ce fichier constient la classe d'�tat Done Fighting King
*
* \author Cossec Est�ban
*
*/
#pragma once
#include "GameState.h"


class DoneFightingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneFightingKingState state_doneFightingKing;