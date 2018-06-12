/**
* //////  DoneMovingKingState.h  //////
*
* Ce fichier constient la classe d'état Done Moving King
*
* \author Cossec Estéban
*
*/
#pragma once
#include "GameState.h"
class DoneMovingKingState :
	public GameState
{
public:
	virtual bool handleInput(GameEngine&, sf::Event&);
};

static DoneMovingKingState state_doneMovingKing;