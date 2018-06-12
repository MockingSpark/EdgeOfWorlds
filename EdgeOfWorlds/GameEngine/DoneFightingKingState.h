/**
* //////  DoneFightingKingState.h  //////
*
* Ce fichier constient la classe d'état Done Fighting King
*
* \author Cossec Estéban
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